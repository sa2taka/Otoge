//
//  TouchDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/27.
//
//

#ifndef TouchDirector_hpp
#define TouchDirector_hpp

#include <cocos2d.h>

class TouchDirector{
    typedef struct touchStatus{
        cocos2d::Vec2 position;
        bool isTouching;
        
        touchStatus(){
            position = cocos2d::Vec2::ZERO;
            isTouching = false;
        }
    }TouchStatus;
    
public:
    static TouchDirector *getInstance();
   
    void checkTouch(std::vector<cocos2d::Touch *> touches, bool isTouching);
    
    cocos2d::Vec2 getPosition(int index);
    bool isTouching(int index);
    int getSize();
    
private:
    static TouchDirector *instance;
    std::vector<TouchStatus *> touchStatuses;
    TouchDirector();
};

#endif /* TouchDirector_hpp */
