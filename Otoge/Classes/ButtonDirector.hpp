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

class ButtonDirector{
public:
    static ButtonDirector *getInstance();
    
    void setButtonSprite(cocos2d::MenuItemSprite *redButton, cocos2d::MenuItemSprite *blueButton);
    
private:
    static ButtonDirector *instance;
    
    cocos2d::MenuItemImage *redButton;
    cocos2d::MenuItemImage *blueButton;
    
    //  コンストラクタ
    ButtonDirector();
    
    //  コールバック
    void onPushedRedButton(cocos2d::Ref *pSender);
    void onPushedBlueButton(cocos2d::Ref *pSender);
};

#endif /* ButtonDirector_hpp */
