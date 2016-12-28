//
//  NoteDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#include "NoteDirector.hpp"
#include "GameProtocol.hpp"
#include "JudgeDirector.hpp"
#include "ButtonDirector.hpp"
#include "ScoreDirector.hpp"

USING_NS_CC;

/***
 コンストラクタ系列
 */
NoteDirector *NoteDirector::instance = new NoteDirector();

NoteDirector::NoteDirector(){
    count = 0;
    startBeatTime = -1;
    timeFromStart = 0;
    allNotesNum = 0;
}

/***
 public
 */

/**
 インスタンスの取得
 */
NoteDirector* NoteDirector::getInstance(){
    return instance;
}

/**
 引数をもとに、動きを設定する
 */
void NoteDirector::setSpeed(float speed){
    this->speed = speed;
}

/**
 各ノーツの設定
 */
void NoteDirector::setNoteSprite(cocos2d::SpriteBatchNode* blueNote,
                                 cocos2d::SpriteBatchNode* redNote,
                                 cocos2d::SpriteBatchNode* purpleNote,
                                 cocos2d::SpriteBatchNode* blueSlide,
                                 cocos2d::SpriteBatchNode* redSlide,
                                 cocos2d::SpriteBatchNode* purpleSlide){
    this->blueNote = blueNote;
    this->redNote = redNote;
    this->purpleNote = purpleNote;
    this->blueSlide = blueSlide;
    this->redSlide = redSlide;
    this->purpleSlide = purpleSlide;
}

/**
 譜面の読み込み
 */
void NoteDirector::loadList(std::string filename){
    setNote('r', 1);
    count++;
    setNote('r', 2);
    count++;
    setNote('r', 3);
    count++;
    setNote('r', 4);
    count++;
    setNote('r', 5);
    count++;
    setNote('r', 6);
    count++;
    setNote('r', 7);
    count++;
    setNote('r', 8);
    count++;
    setNote('r', 7);
    count++;
    setNote('r', 6);
    count++;
    setNote('r', 5);
    count++;
    setNote('r', 4);
    count++;
    setNote('r', 3);
    count++;
    setNote('r', 2);
    count++;
    setNote('r', 1);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('B', 4);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('n', 0);
    count++;
    setNote('P', 8);
    isLoadFinish = true;
    bpm = 120;
    ScoreDirector::getInstance()->setNotesNum(allNotesNum);
    count = -GameProtocol::notePerBeat * 4;
    
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(float delta){
    if(isLoadFinish){
        timeFromStart += delta;
        //  初期状態だと必ず実行される(あんまりにもbpmが低いときを除いて)
        if(timeFromStart - startBeatTime>= 60 / (bpm * GameProtocol::notePerBeat)){
            createAndDeleteNote();
            judgeSlideNote();
            startBeatTime = timeFromStart;
            count++;
            
            //  ノートがgood未満判定確定のときに捨てる処理
            int referenceIndex = count - getFrameStartJudge() - 1;
            if(referenceIndex >= 0 && referenceIndex < notes.size()){
                noteEndProcess(referenceIndex);
            }
        }
    }
}

/**
 タッチノートの判定
 */
void NoteDirector::judgeTouchNote(bool isTouchBlue, bool isTouchRed){
    int i;
    int frameStartJudge = getFrameStartJudge();
    //  低い方から順に見ていき、一つでも判定があった場合は抜ける
    for(i = -frameStartJudge;i <= frameStartJudge;i++){
        int referenceIndex = count + i;
        if(referenceIndex >= 0 && referenceIndex < notes.size()
           && notes[referenceIndex].isNote){
            bool judge = JudgeDirector::getInstance()->judge(notes[referenceIndex].location,
                                                             notes[referenceIndex].color,
                                                             getSpriteFromColor(notes[referenceIndex].color)->getContentSize().width);
            if(judge){
                switch(notes[referenceIndex].color){
                    case 'B' :
                        if(isTouchBlue && !isTouchRed){
                            notes[referenceIndex].lastJudge = abs(i);
                            noteEndProcess(referenceIndex);
                        }
                        break;
                    case 'R' :
                        if(!isTouchBlue && isTouchRed){
                            notes[referenceIndex].lastJudge = abs(i);
                            noteEndProcess(referenceIndex);
                        }
                        break;
                    case 'P' :
                        if(isTouchBlue && isTouchRed){
                            notes[referenceIndex].lastJudge = abs(i);
                            noteEndProcess(referenceIndex);
                        }
                        break;
                }
            }
        }
    }
}

/***
 private関数
 */

/**
 char型で示した色からスプライトを取得する
 */
Sprite *NoteDirector::getSpriteFromColor(char color){
    switch(color){
        case 'b' : return Sprite::createWithTexture(blueSlide->getTexture());
        case 'r' : return Sprite::createWithTexture(redSlide->getTexture());
        case 'p' : return Sprite::createWithTexture(purpleSlide->getTexture());
        case 'B' : return Sprite::createWithTexture(blueNote->getTexture());
        case 'R' : return Sprite::createWithTexture(redNote->getTexture());
        case 'P' : return Sprite::createWithTexture(purpleNote->getTexture());
    }
    return nullptr;
}

/**
 色と横の位置からノートを生成する
 */
void NoteDirector::setNote(char color, int location){
    notes.push_back(*new Note());
    
    if(color != 'b' && color != 'r' && color != 'p'
       && color != 'B' && color != 'R' && color != 'P'){
        notes[count].isNote = false;
    }
    else{
        notes[count].color = color;
        notes[count].sprite = getSpriteFromColor(color);
        
        notes[count].location = (location - 1) % GameProtocol::lineNum + 1;
        notes[count].sprite->setPosition(getVec2FromWidthLocation(location));
        
        //  親子付け
        switch(color){
            case 'b' :
                blueSlide->addChild(notes[count].sprite);
                break;
            case 'r' :
                redSlide->addChild(notes[count].sprite);
                break;
            case 'p' :
                purpleSlide->addChild(notes[count].sprite);
                break;
            case 'B' :
                blueNote->addChild(notes[count].sprite);
                break;
            case 'R' :
                redNote->addChild(notes[count].sprite);
                break;
            case 'P' :
                purpleNote->addChild(notes[count].sprite);
                break;
        }
        allNotesNum++;
    }
}

/**
 Locationに応じたノートの初期位置の取得
 */
Vec2 NoteDirector::getVec2FromWidthLocation(int widthLocation){
    float y = Director::getInstance()->getWinSize().height;
    float winWidth = Director::getInstance()->getWinSize().width;
    float noteRangeWidth = winWidth / 2 - GameProtocol::padding * 2;
    float correctLocation = (widthLocation - 1) % GameProtocol::lineNum + 1;
    float x = noteRangeWidth / GameProtocol::lineNum * correctLocation + GameProtocol::padding;
    return Vec2(x, y);
}

/**
 動きを返す
 */
Sequence *NoteDirector::getSequence(){
    //  cocos2dxはデフォルトで60FPS
    MoveBy *beforeMove = MoveBy::create(speed, Vec2(0, -(Director::getInstance()->getWinSize().height - GameProtocol::lineHeight)));
    MoveBy *afterMove = MoveBy::create(speed, Vec2(0, -GameProtocol::lineHeight) / 2);
    FadeOut *afterFade = FadeOut::create(speed);
    Spawn *afterSpawn = Spawn::create(afterMove, afterFade, nullptr);
    return Sequence::create(beforeMove, afterSpawn, nullptr);
}

/**
 ノートの生成と削除を行う, Class変数であるcountを使うため引数はない
 */
void NoteDirector::createAndDeleteNote(){
    //  ノートの生成
    int temp = count + bpm / 60 * speed * GameProtocol::notePerBeat - 1;
    if(temp >= 0 && temp < notes.size()){
        if(notes[temp].isNote){
            notes[temp].sprite->runAction(getSequence());
            notes[temp].isExist = true;
        }
    }
    temp = count - bpm / 60 * speed * GameProtocol::notePerBeat;
    //  ノートの削除
    if(temp >= 0 && temp < notes.size()){
        if(notes[temp].isNote && notes[temp].isExist){
            notes[temp].sprite->getParent()->removeChild(notes[temp].sprite);
            notes[temp].sprite = nullptr;
            notes[temp].isExist = false;
        }
    }
}

/**
 スライドノートの判定を行う
 */
void NoteDirector::judgeSlideNote(){
    int i;
    int frameStartJudge = getFrameStartJudge();
    for(i = -frameStartJudge;i <= frameStartJudge;i++){
        int referenceIndex = count + i;
        if(referenceIndex >= 0 && referenceIndex < notes.size()
           && notes[referenceIndex].isNote){
            bool judge = JudgeDirector::getInstance()->judge(notes[referenceIndex].location,
                                                             notes[referenceIndex].color,
                                                             getSpriteFromColor(notes[referenceIndex].color)->getContentSize().width);
            
            //  FIXME   ここの条件分岐を直す
            if(judge){
                switch(notes[referenceIndex].color){
                    case 'b' :
                        if(!ButtonDirector::getInstance()->isTouchingBlue() &&
                           ButtonDirector::getInstance()->isTouchingRed()){
                            notes[referenceIndex].lastJudge = abs(i);
                        }
                        break;
                    case 'r' :
                        if(!ButtonDirector::getInstance()->isTouchingBlue() &&
                           ButtonDirector::getInstance()->isTouchingRed()){
                            notes[referenceIndex].lastJudge = abs(i);
                        }
                        break;
                    case 'p' :
                        if(ButtonDirector::getInstance()->isTouchingRed()&&
                           ButtonDirector::getInstance()->isTouchingBlue()){
                            notes[referenceIndex].lastJudge = abs(i);
                        }
                        break;
                }
            }
            //  iが+(判定ラインを超えているノート)かつノートが存在しているかつ判定はgood以上
            if(i <= 0 && notes[referenceIndex].isExist && notes[referenceIndex].lastJudge != -1){
                
                switch(notes[referenceIndex].color){
                    case 'b' :
                        if(!ButtonDirector::getInstance()->isTouchingBlue() &&
                           ButtonDirector::getInstance()->isTouchingRed()){
                            noteEndProcess(referenceIndex);
                        }
                        break;
                    case 'r' :
                        if(!ButtonDirector::getInstance()->isTouchingBlue() &&
                           ButtonDirector::getInstance()->isTouchingRed()){
                            noteEndProcess(referenceIndex);
                        }
                        break;
                    case 'p' :
                        if(ButtonDirector::getInstance()->isTouchingRed()&&
                           ButtonDirector::getInstance()->isTouchingBlue()){
                            noteEndProcess(referenceIndex);
                        }
                        break;
                }
            }
        }
    }
}

/**
 bpmからグッド以上となる判定で最も遠くなるフレームの差を取得する
 */
int NoteDirector::getFrameStartJudge(){
    //  1フレームでの最大ノーツ数 * goodの幅
    return (int)((bpm / 60 / 60 * GameProtocol::notePerBeat) * GameProtocol::goodRange);
}

/**
 ノーツの終了処理
 */
void NoteDirector::noteEndProcess(int index){
    if(notes[index].isExist && notes[index].isNote){
        int framePerNotes = GameProtocol::goodRange / getFrameStartJudge();
        ScoreDirector::getInstance()->updateScore(notes[index].lastJudge * framePerNotes);
        //  判定がgood以上のときのみノーツを消す処理
        if(notes[index].lastJudge >= 0){
            notes[index].sprite->stopAllActions();
            notes[index].sprite->getParent()->removeChild(notes[index].sprite);
            notes[index].sprite = nullptr;
            notes[index].isExist = false;
        }
    }
}



