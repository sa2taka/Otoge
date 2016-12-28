//
//  ButtonDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/27.
//
//

#include "ButtonDirector.hpp"

USING_NS_CC;

ButtonDirector *ButtonDirector::instance = new ButtonDirector();
ButtonDirector::ButtonDirector(){
    isTouchRed = false;
    isTouchBlue = false;
}

/***
 public
 */
ButtonDirector *ButtonDirector::getInstance(){
    return instance;
}

/**
 スプライトの設定
 */
void ButtonDirector::setButtonSprite(cocos2d::Sprite *notPushedRed,
                                     cocos2d::Sprite *notPushedBlue,
                                     cocos2d::Sprite *pushedRed,
                                     cocos2d::Sprite *pushedBlue){
    notPushedRed->setColor(Color3B(160, 15, 15));
    notPushedBlue->setColor(Color3B(15, 15, 200));
    pushedRed->setColor(Color3B(220, 50, 50));
    pushedBlue->setColor(Color3B(50, 50, 230));
    
    notPushedRed->setOpacity(128);
    notPushedBlue->setOpacity(128);
    pushedRed->setOpacity(128);
    pushedBlue->setOpacity(128);
    
    float winWidth = Director::getInstance()->getWinSize().width;
    notPushedRed->setAnchorPoint(Vec2::ZERO);
    notPushedRed->setPosition(winWidth / 2 + winWidth / 4, 0);
    notPushedBlue->setAnchorPoint(Vec2::ZERO);
    notPushedBlue->setPosition(winWidth/2, 0);
    pushedRed->setAnchorPoint(Vec2::ZERO);
    pushedRed->setPosition(winWidth / 2 + winWidth / 4, 0);
    pushedBlue->setAnchorPoint(Vec2::ZERO);
    pushedBlue->setPosition(winWidth/2, 0);
    
    pushedRed->setVisible(false);
    pushedBlue->setVisible(false);
    
    this->notPushedRed = notPushedRed;
    this->notPushedBlue = notPushedBlue;
    this->pushedRed = pushedRed;
    this->pushedBlue = pushedBlue;
}


/**
 各色が押されているかを返す
 */
bool ButtonDirector::isTouchingRed(){
    return isTouchRed;
}

bool ButtonDirector::isTouchingBlue(){
    return isTouchBlue;
}

/**
 ボタンがタッチされているかを確認する
 */
void ButtonDirector::checkTouchButton(){
    int i;
    //  初期化
    isTouchRed = false;
    isTouchBlue = false;
    pushedRed->setVisible(false);
    pushedBlue->setVisible(false);
    notPushedRed->setVisible(true);
    notPushedBlue->setVisible(true);
    
    //  更新
    auto touchDirector = TouchDirector::getInstance();
    for(i = 0;i < touchDirector->getSize();i++){
        if(touchDirector->isTouching(i)){
            auto position = touchDirector->getPosition(i);
            float winWidth = Director::getInstance()->getWinSize().width;
            if(position.x >= winWidth / 2){
                if(position.x >= winWidth / 2 + winWidth / 4){
                    isTouchRed = true;
                    pushedRed->setVisible(true);
                    notPushedRed->setVisible(false);
                }
                else{
                    isTouchBlue = true;
                    pushedBlue->setVisible(true);
                    notPushedBlue->setVisible(false);
                }
            }
        }
    }
}

/**
 ボタンがタッチされ始めた瞬間かを確認する
 */
std::tuple<bool, bool> ButtonDirector::checkStartTouchButton(std::vector<Touch *> touches){
    int i;
    bool isStartTouchBlue = false;
    bool isStartTouchRed = false;
    for(i = 0;i < touches.size();i++){
        auto position = touches[i]->getLocation();
        float winWidth = Director::getInstance()->getWinSize().width;
        if(position.x >= winWidth / 2){
            if(position.x >= winWidth / 2 + winWidth / 4){
                isStartTouchRed = true;
            }
            else{
                isStartTouchBlue = true;
            }
        }
    }
    return std::tuple<bool, bool>(isStartTouchBlue, isStartTouchRed);
}
