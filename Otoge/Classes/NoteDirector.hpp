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
    void setNoteSprite(cocos2d::SpriteBatchNode* blueNote, cocos2d::SpriteBatchNode* redNote, cocos2d::SpriteBatchNode* purpleNote);
    
    void loadList(std::string filename);
    
    void updateNotes();
    
private:
    static NoteDirector* instance;
    
    std::vector<cocos2d::Sprite *>  notes;
    
    cocos2d::Sequence *noteSequence;
    
    cocos2d::SpriteBatchNode *blueNote;
    cocos2d::SpriteBatchNode *redNote;
    cocos2d::SpriteBatchNode *purpleNote;
    
    int count;
    float speed;
    
    bool isLoadFinish = false;
    
    NoteDirector();

    cocos2d::Sprite *getSpriteFromColor(char color);
    void setSprite(char color, int location);
    cocos2d::Vec2 getVec2FromWidthLocation(int WidthLocation);
    
    void createAndDeleteNote();
};
#endif /* NoteDirector_hpp */
