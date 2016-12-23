//
//  NoteDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#ifndef NoteDirector_hpp
#define NoteDirector_hpp

#include "cocos2d.h"
#include "Note.hpp"

class NoteDirector{
public:
    static NoteDirector* getInstance();
    
    void setSpeed(float speed);
    void setNoteSprite(cocos2d::SpriteBatchNode* blueNote, cocos2d::SpriteBatchNode* redNote, cocos2d::SpriteBatchNode* purpleNote);
    
    void updateNotes();
    
private:
    static NoteDirector* instance;
    Note *note;
    
    std::vector<int>  notesLocation;
    std::vector<char> notesColor;
    
    cocos2d::MoveBy* beforeMove;
    cocos2d::MoveBy* afterMove;
    
    int count;
    float speed;
    
    NoteDirector();
    
};
#endif /* NoteDirector_hpp */
