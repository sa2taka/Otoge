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
    
    //  cocos2dxはデフォルトで60FPS
    MoveBy *beforeMove = MoveBy::create(speed, Vec2(0, -(Director::getInstance()->getWinSize().height - GameProtocol::lineHeight)));
    MoveBy *afterMove = MoveBy::create(speed, Vec2(0, -GameProtocol::lineHeight) / 2);
    FadeOut *afterFade = FadeOut::create(speed);
    Spawn *afterSpawn = Spawn::create(afterMove, afterFade, nullptr);
    noteSequence = Sequence::create(beforeMove, afterSpawn, nullptr);
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
    setSprite('b', 4);
    count++;
    setSprite('p', 16);
    count = 0;
    isLoadFinish = true;
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(){
    if(isLoadFinish){
        createAndDeleteNote();
    }
    count++;
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
    switch(color){
        case 'b' :
            notes.push_back(getSpriteFromColor('b'));
            notes[count]->setPosition(getVec2FromWidthLocation(location));
            blueNote->addChild(notes[count]);
            break;
        case 'r' :
            notes.push_back(getSpriteFromColor('r'));
            notes[count]->setPosition(getVec2FromWidthLocation(location));
            redNote->addChild(notes[count]);
            break;
        case 'p' :
            notes.push_back(getSpriteFromColor('p'));
            notes[count]->setPosition(getVec2FromWidthLocation(location));
            purpleNote->addChild(notes[count]);
            break;
    }
}

Vec2 NoteDirector::getVec2FromWidthLocation(int WidthLocation){
    float y = Director::getInstance()->getWinSize().height;
    float winWidth = Director::getInstance()->getWinSize().width;
    float noteWidth = winWidth / 2 - GameProtocol::padding * 2;
    float x = noteWidth / GameProtocol::lineNum * WidthLocation;
    return Vec2(x, y);
}

/**
 ノートの生成と削除を行う, Class変数であるcountを使うため引数はない
 */
void NoteDirector::createAndDeleteNote(){
    if(notes.size() + (60 * speed * 2)  > count){
        //  ノートの生成
        if(count >= 0 && count < notes.size() && notes[count] != nullptr){
            //  何故かこうするとうまくいく
            auto tempSequence = noteSequence->clone();
            notes[count]->runAction(tempSequence);
            noteSequence = tempSequence;
        }
        int temp = count - (60 * speed * 2);
        //  ノートの削除
        if(temp >= 0 && temp <= notes.size() && notes[temp] != nullptr){
            notes[temp]->getParent()->removeChild(notes[temp]);
        }
    }
}


