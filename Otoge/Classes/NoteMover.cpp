//
//  NoteMover.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#include "NoteMover.hpp"
#include "gameProtocol.h"

USING_NS_CC;

NoteMover* NoteMover::instance = new NoteMover();   //  staticにインスタンスを保存

NoteMover::NoteMover(){
    speed = 2;
}

NoteMover* NoteMover::getInstance(){
    return instance;
}

void NoteMover::flowNote(Sprite* note, int location, Layer* layer){
    note->setPosition((location + 1) * (note->getContentSize().width), this->windowHeight - 1);
    layer->addChild(note);

    
    note->runAction(this->noteSequence);
}
