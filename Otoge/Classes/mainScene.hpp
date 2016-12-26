//
//  mainScene.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/22.
//
//

#ifndef mainScene_hpp
#define mainScene_hpp

#include "cocos2d.h"
#include "NoteDirector.hpp"
#include "JudgeDirector.hpp"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    int count;
    NoteDirector *noteDirector;
    JudgeDirector *judgeDirector;
    
    void noteInit();
    void judgeInit();
    
    void update(float delta);
    
    //  イベントのコールバック関数
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif /* mainScene_hpp */
