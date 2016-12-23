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

NoteDirector *NoteDirector::instance = new NoteDirector();

NoteDirector::NoteDirector(){
    notesLocation.push_back(2);
    notesColor.push_back('b');
    count = 0;
}

NoteDirector* NoteDirector::getInstance(){
     return instance;
}

/**
 引数をもとに、1フレームでどれだけ進むかを設定する
 */
void NoteDirector::setSpeed(float speed){
    //  cocos2dxはデフォルトで60FPS
    beforeMove = MoveBy::create(speed, Vec2(0, -(Director::getInstance()->getWinSize().height - GameProtocol::getInstance()->lineHeight) / (60 * speed)));
    afterMove = MoveBy::create(speed, Vec2(0, GameProtocol::getInstance()->lineHeight / (60 * speed)));
    this->speed = speed;
}

void NoteDirector::setNoteSprite(cocos2d::SpriteBatchNode* blueNote,
                                 cocos2d::SpriteBatchNode* redNote,
                                 cocos2d::SpriteBatchNode* purpleNote){
    this->blueNote = blueNote;
    this->redNote = redNote;
    this->purpleNote = purpleNote;
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(){
    if(notesLocation.size() + (60 * speed * 2)  > count){
        for(int i  = -(60 * speed);i < (60 * speed);i++){
            int nowIndex = count + i - (60 * speed);
            if(nowIndex >= 0 && nowIndex < notesLocation.size()){
                float winHeight = Director::getInstance()->getWinSize().height;
                float nowHeight;
                MoveBy* nowMove;
                if(i >= 0){
                    nowHeight = GameProtocol::getInstance()->lineHeight + winHeight * (i / (60 * speed));
                    nowMove = beforeMove;
                }
                else{
                    nowHeight = GameProtocol::getInstance()->lineHeight -  GameProtocol::getInstance()->lineHeight * -i / (60 * speed);
                    nowMove = afterMove;
                }
                log("%d: %f", i, nowHeight);
            }
        }
        count++;
    }
}

