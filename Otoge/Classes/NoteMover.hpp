//
//  NoteMover.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#ifndef NoteMover_hpp
#define NoteMover_hpp

#include "cocos2d.h"

class NoteMover{
public:
    //  インスタンスの取得
    static NoteMover* getInstance();
    
    //  速さの変更
    void setSpeed(int speed);
    
    // ノートを流す
    void flowNote(cocos2d::Sprite* note, int location, cocos2d::Layer* layer);
    
private:
    static NoteMover* instance;
    
    float speed;
    float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
    cocos2d::Sequence* noteSequence;
    
    /**
     コンストラクタ
     */
    NoteMover();
};

#endif /* NoteMover_hpp */
