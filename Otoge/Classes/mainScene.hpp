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
#include "ButtonDirector.hpp"
#include "TouchDirector.hpp"
#include "ScoreDirector.hpp"
#include "StartDirector.hpp"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    int count;
    bool isFirstTouch;
    
    NoteDirector *noteDirector;
    JudgeDirector *judgeDirector;
    ButtonDirector *buttonDirector;
    TouchDirector *touchDirector;
    ScoreDirector *scoreDirector;
    StartDirector *startDirector;
    
    cocos2d::Label *touchLabel;
    cocos2d::Sprite *cover;
    
    void noteInit();
    void judgeInit();
    void buttonInit();
    void scoreInit();
    void startInit();
    void otherInit();
    
    void update(float delta);
    
    //  イベントのコールバック関数
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onLoadFinished();
};

#endif /* mainScene_hpp */
