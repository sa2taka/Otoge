//
//  SpriteMover.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/24.
//
//

#ifndef NoteMover_hpp
#define NoteMover_hpp

#include "cocos2d.h"

class Note{
public:
    Note();
    
    void setNoteSprite(cocos2d::SpriteBatchNode* blueNote, cocos2d::SpriteBatchNode* redNote, cocos2d::SpriteBatchNode* purpleNote);
    
    void flowNote(char color, cocos2d::Vec2 startPoint, cocos2d::MoveBy *move);   //MoveByの親クラスにするつもり
    
private:
    cocos2d::SpriteBatchNode *blueNote, *redNote, *purpleNote;
};

#endif /* NoteMover_hpp */
