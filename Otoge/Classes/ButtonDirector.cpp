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
ButtonDirector::ButtonDirector(){}

/***
 public
 */

/**
 スプライトの設定
 */
void ButtonDirector::setButtonSprite(cocos2d::MenuItemSprite *redButton, cocos2d::MenuItemSprite *blueButton){
    redButton->setCallback(CC_CALLBACK_1(ButtonDirector::onPushedRedButton, this));
    blueButton->setCallback(CC_CALLBACK_1(ButtonDirector::onPushedBlueButton, this));
    
    auto winSize = Director::getInstance()->getWinSize();
    redButton->setAnchorPoint(Vec2(0, 0));
    redButton->setPosition(winSize.width / 2 + winSize.width / 4, 0);
    blueButton->setAnchorPoint(Vec2(0, 0));
    blueButton->setPosition(winSize.width / 2, 0);
}

/***
 private
*/

void ButtonDirector::onPushedRedButton(Ref *pSender){
    log("Pushed Red Button");
}

void ButtonDirector::onPushedBlueButton(Ref *pSender){
    log("Pushed Blue Button");
}
