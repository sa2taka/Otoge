//
//  NoteDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#include "NoteDirector.hpp"
#include "gameProtocol.h"

USING_NS_CC;

NoteDirector* NoteDirector::instance = new NoteDirector();

NoteDirector::NoteDirector(){
    notesLocation.push_back(2);
    notesColor.push_back('r');
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
    beforeMove = MoveBy::create(speed, Vec2(0, -(Director::getInstance()->getWinSize().height - protocol::lineHeight) / (60 * speed)));
    afterMove = MoveBy::create(speed, Vec2(0, (-protocol::lineHeight) / (60 * speed)));
}

/**
 呼ばれる度にノートを一回分動かす操作
 */
void NoteDirector::updateNotes(){
    log("update:count = %d", count);
    count++;
    if(notesLocation.size() <= count){
        log("end");
        Director::getInstance()->end();
        exit(0);
    }
}
