//
//  NoteDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#include "NoteDirector.hpp"
#include "GameProtocol.hpp"

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
    setSprite('r', 1);
    count++;
    setSprite('b', 2);
    count++;
    setSprite('r', 3);
    count++;
    setSprite('b', 4);
    count++;
    setSprite('r', 5);
    count++;
    setSprite('b', 6);
    count++;
    setSprite('r', 7);
    count++;
    setSprite('b', 8);
    count++;
    setSprite('p', 9);
    count++;
    setSprite('r', 10);
    count++;
    setSprite('b', 11);
    count++;
    setSprite('r', 12);
    count++;
    setSprite('b', 13);
    count++;
    setSprite('r', 14);
    count++;
    setSprite('b', 15);
    count++;
    setSprite('r', 16);
    count = 0;
    isLoadFinish = true;
    bpm = 120;
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(float delta){
    if(isLoadFinish){
        timeFromStart += delta;
        //  初期状態だと必ず実行される(あんまりにもbpmが高いときを除いて)
        if(timeFromStart - startBeatTime>= bpm / (60 * GameProtocol::beatPerSec)){
            //log("%f", timeFromStart - startBeatTime);
            createAndDeleteNote();
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
 色と横の位置からスプライトを生成する
 */
void NoteDirector::setSprite(char color, int location){
    notes.push_back(*new Note());
    
    if(color == 'n'){
        notes[count].isNote = false;
    }
    
    notes[count].color = color;
    notes[count].sprite = getSpriteFromColor(color);
    
    notes[count].location = location;
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

/**
 Locationに応じたノートの初期位置の取得
 */
Vec2 NoteDirector::getVec2FromWidthLocation(int WidthLocation){
    float y = Director::getInstance()->getWinSize().height;
    float winWidth = Director::getInstance()->getWinSize().width;
    float noteWidth = winWidth / 2 - GameProtocol::padding * 2;
    float x = noteWidth / GameProtocol::lineNum * WidthLocation + GameProtocol::padding;
    return Vec2(x, y);
}


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
    if(notes.size() + (60 * speed * 2)  > count){
        //  ノートの生成
        if(count >= 0 && count < notes.size() && notes[count].isNote){
            //  何故かこうするとうまくいく
            notes[count].sprite->runAction(getSequence());
        }
        int temp = count - (60 * speed * 2);
        //  ノートの削除
        if(temp >= 0 && temp <= notes.size() && notes[temp].isNote){
            notes[temp].sprite->getParent()->removeChild(notes[temp].sprite);
            notes[temp].sprite = nullptr;
            notes[temp].isExist = false;
        }
    }
}


