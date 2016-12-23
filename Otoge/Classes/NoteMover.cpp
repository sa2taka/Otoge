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

NoteMover::NoteMover(int speed){
    setSpeed(speed);
}

void NoteMover::setSpeed(int speed){
    auto move = MoveBy::create(speed, Vec2(0, -this->windowHeight + protocol::lineHeight));
    auto fading_move = Spawn::create(MoveBy::create(speed * 2.0, Vec2(0, -protocol::lineHeight / 2)),
                                     FadeOut::create(speed * 2.0), nullptr);
    
    this->noteSequence = Sequence::create(move, fading_move, nullptr);
}

void NoteMover::flowNote(Sprite* note, int location, Layer* layer){
    note->setPosition((location + 1) * (note->getContentSize().width), this->windowHeight - 1);
    layer->addChild(note);

    
    note->runAction(this->noteSequence);
}
