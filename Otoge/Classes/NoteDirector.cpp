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

USING_NS_CC;

/***
 コンストラクタ系列
 */
NoteDirector *NoteDirector::instance = new NoteDirector();

NoteDirector::NoteDirector(){
    count = 0;
    startBeatTime = -1;
    timeFromStart = 0;
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
                                 cocos2d::SpriteBatchNode* purpleNote){
    this->blueNote = blueNote;
    this->redNote = redNote;
    this->purpleNote = purpleNote;
}

/**
 譜面の読み込み
 */
void NoteDirector::loadList(std::string filename){
    setNote('r', 1);
    count++;
    setNote('b', 2);
    count++;
    setNote('r', 3);
    count++;
    setNote('b', 4);
    count++;
    setNote('r', 5);
    count++;
    setNote('b', 6);
    count++;
    setNote('r', 7);
    count++;
    setNote('b', 8);
    count++;
    setNote('p', 9);
    count++;
    setNote('r', 10);
    count++;
    setNote('b', 11);
    count++;
    setNote('r', 12);
    count++;
    setNote('b', 13);
    count++;
    setNote('r', 14);
    count++;
    setNote('b', 15);
    count++;
    setNote('r', 16);
    count++;
    setNote('r', 1);
    count++;
    setNote('b', 2);
    count++;
    setNote('r', 3);
    count++;
    setNote('b', 4);
    count++;
    setNote('r', 5);
    count++;
    setNote('b', 6);
    count++;
    setNote('r', 7);
    count++;
    setNote('b', 8);
    count++;
    setNote('p', 9);
    count++;
    setNote('r', 10);
    count++;
    setNote('b', 11);
    count++;
    setNote('r', 12);
    count++;
    setNote('b', 13);
    count++;
    setNote('r', 14);
    count++;
    setNote('b', 15);
    count++;
    setNote('r', 16);
    isLoadFinish = true;
    bpm = 240;
    count = -GameProtocol::notePerBeat * 16;
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
            judgeNote();
            startBeatTime = timeFromStart;
            count++;
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
        case 'b' : return Sprite::createWithTexture(blueNote->getTexture());
        case 'r' : return Sprite::createWithTexture(redNote->getTexture());
        case 'p' : return Sprite::createWithTexture(purpleNote->getTexture());
    }
    return nullptr;
}

/**
 色と横の位置からノートを生成する
 */
void NoteDirector::setNote(char color, int location){
    notes.push_back(*new Note());
    
    if(color != 'b' && color != 'r' && color != 'p'){
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
                blueNote->addChild(notes[count].sprite);
                break;
            case 'r' :
                redNote->addChild(notes[count].sprite);
                break;
            case 'p' :
                purpleNote->addChild(notes[count].sprite);
                break;
        }
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
    int temp = count + bpm / 60 * speed * GameProtocol::notePerBeat + 1;
    if(temp >= 0 && temp < notes.size()){
        if(notes[temp].isNote){
            notes[temp].sprite->runAction(getSequence());
            notes[temp].isExist = true;
        }
    }
    temp = count - bpm / 60 * speed * GameProtocol::notePerBeat;
    //  ノートの削除
    if(temp >= 0 && temp < notes.size()){
        if(notes[temp].isNote){
            notes[temp].sprite->getParent()->removeChild(notes[temp].sprite);
            notes[temp].sprite = nullptr;
            notes[temp].isExist = false;
        }
    }
}

/**
 ノートの判定を行う
 */
void NoteDirector::judgeNote(){
    int i;
    for(i = -GameProtocol::goodRange;i <= GameProtocol::goodRange;i++){
        int referenceIndex = count + i;
        if(referenceIndex >= 0 && referenceIndex < notes.size()){
            notes[referenceIndex];
            bool judge = JudgeDirector::getInstance()->judge(notes[referenceIndex].location,
                                                             notes[referenceIndex].color,
                                                             getSpriteFromColor(notes[referenceIndex].color)->getContentSize().width);
            if(judge){
                notes[referenceIndex].lastJudge = abs(i);
            }
            //  iが+(判定ラインを超えているノート)かつノートが存在しているかつ判定はgood以上
            if(i < 0 && notes[referenceIndex].isExist && notes[referenceIndex].lastJudge != -1){
                notes[referenceIndex].isExist = false;
                notes[referenceIndex].sprite->getParent()->removeChild(notes[referenceIndex].sprite);
                notes[referenceIndex].sprite = nullptr;
                log("good or great");
            }
        }
    }
}


