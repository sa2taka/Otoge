//
//  ButtonDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/27.
//
//

#ifndef ButtonDirector_hpp
#define ButtonDirector_hpp

#include "cocos2d.h"
#include "TouchDirector.hpp"

class ButtonDirector{
public:
    static ButtonDirector *getInstance();
    
    void setButtonSprite(cocos2d::Sprite *notPushedRed,
                         cocos2d::Sprite *notPushedBlue,
                         cocos2d::Sprite *pushedRed,
                         cocos2d::Sprite *pushedBlue);
    
    //  ボタンがタッチされているのを確認する
    void checkTouchButton();
    //  タッチ開始時にボタンが押されたかどうかを確認する
    std::tuple<bool, bool> checkStartTouchButton(std::vector<cocos2d::Touch *> touches);
    
    bool isTouchingRed();
    bool isTouchingBlue();

private:
    static ButtonDirector *instance;
    
    cocos2d::Sprite *notPushedRed;
    cocos2d::Sprite *notPushedBlue;
    cocos2d::Sprite *pushedRed;
    cocos2d::Sprite *pushedBlue;
    
    bool isTouchRed;
    bool isTouchBlue;
    
    //  コンストラクタ
    ButtonDirector();
};

#endif /* ButtonDirector_hpp */
