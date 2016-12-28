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
    
    typedef struct note{
        cocos2d::Sprite* sprite;
        int location;
        char color;
        bool isExist;   //  存在しているかどうか
        bool isNote;    //  自身がノートなのかどうか(ノートでない場合もある)
        int lastJudge;  //  ノートの最後のジャッジフレーム数(-1は初期値であり、ジャッジされていないことを表している)
        
        note(){
            location = 0;
            color = 'n';
            isExist = false;
            isNote = true;
            lastJudge = -1;
        }
    }Note;
public:
    static NoteDirector* getInstance();
    
    void setSpeed(float speed);
    void setNoteSprite(cocos2d::SpriteBatchNode* blueNote,
                       cocos2d::SpriteBatchNode* redNote,
                       cocos2d::SpriteBatchNode* purpleNote,
                       cocos2d::SpriteBatchNode* blueSlide,
                       cocos2d::SpriteBatchNode* redSlide,
                       cocos2d::SpriteBatchNode* purpleSlide);
    
    void loadList(std::string filename);
    
    void updateNotes(float delta);
    void judgeTouchNote(bool isTouchBlue, bool isTouchRed);
    
private:
    static NoteDirector* instance;
    
    std::vector<Note>  notes;
    
    cocos2d::Sequence *noteSequence;
    
    cocos2d::SpriteBatchNode *blueNote;
    cocos2d::SpriteBatchNode *redNote;
    cocos2d::SpriteBatchNode *purpleNote;
    cocos2d::SpriteBatchNode *blueSlide;
    cocos2d::SpriteBatchNode *redSlide;
    cocos2d::SpriteBatchNode *purpleSlide;
    
    int count;
    float speed;
    double bpm;
    int allNotesNum;
    
    double startBeatTime;
    double timeFromStart;
    
    bool isLoadFinish = false;
    
    NoteDirector();

    cocos2d::Sprite *getSpriteFromColor(char color);
    void setNote(char color, int location);
    cocos2d::Vec2 getVec2FromWidthLocation(int WidthLocation);
    cocos2d::Sequence *getSequence();
    int getFrameStartJudge();
    
    void createAndDeleteNote();
    void judgeSlideNote();
    void noteEndProcess(int index);
};
#endif /* NoteDirector_hpp */
