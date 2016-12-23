//
//  SpriteMover.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/24.
//
//

#include "Note.hpp"

USING_NS_CC;

Note::Note(){}

void Note::setNoteSprite(cocos2d::SpriteBatchNode *blueNote,
                    cocos2d::SpriteBatchNode *redNote,
                    cocos2d::SpriteBatchNode *purpleNote){
    this->blueNote = blueNote;
    this->redNote = redNote;
    this->purpleNote = purpleNote;
}

void Note::flowNote(char color, Vec2 startPoint, MoveBy *move){
    Sprite *note;
    switch(color){
        case 'b' :
            note = Sprite::createWithTexture(blueNote->getTexture());
            break;
        case 'r' :
            note = Sprite::createWithTexture(redNote->getTexture());
            break;
        case 'p' :
            note = Sprite::createWithTexture(purpleNote->getTexture());
            break;
    }
    note->setPosition(startPoint);
    
    Director::getInstance()->getRunningScene()->addChild(note);
    note->runAction(move);
}
