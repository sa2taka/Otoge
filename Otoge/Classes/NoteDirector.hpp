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

class NoteDirector{
public:
    static NoteDirector* getInstance();
    void setSpeed(float speed);
    void updateNotes();
    
private:
    static NoteDirector* instance;
    
    std::vector<int>  notesLocation;
    std::vector<char> notesColor;
    
    cocos2d::MoveBy* beforeMove;
    cocos2d::MoveBy* afterMove;
    
    int count;
    
    NoteDirector();
    
};
#endif /* NoteDirector_hpp */
