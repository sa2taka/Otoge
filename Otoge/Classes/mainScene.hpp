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

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    
};

#endif /* mainScene_hpp */
