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
    MoveBy *beforeMove = MoveBy::create(speed, Vec2(0, -(Director::getInstance()->getWinSize().height - GameProtocol::getInstance()->lineHeight)));
    MoveBy *afterMove = MoveBy::create(speed, Vec2(0, -GameProtocol::getInstance()->lineHeight) / 2);
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
    notes.push_back(getSpriteFromColor('b'));
    notes[0]->setPosition(2 * (notes[0]->getContentSize().width / 4 + GameProtocol::getInstance()->padding),
                         Director::getInstance()->getWinSize().height);
    blueNote->addChild(notes[0]);
    
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(){
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


