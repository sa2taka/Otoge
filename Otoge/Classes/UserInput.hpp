//
//  UserInput.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#ifndef UserInput_hpp
#define UserInput_hpp

#include "cocos2d.h"

class UserInput{
public:
    const static int LEFT = 0;
    const static int RIGHT = 1;
    
    static UserInput *getInstance();
    
    void setSpeed(int speed);
    void setArrangement(int arrangement);
    int getSpeed();
    int getArrangement();
    
    void saveStatus();
private:
    static UserInput *instance;
    const std::string fileName = cocos2d::FileUtils::getInstance()->fullPathForFilename("user_status.status");
    
    int speed;
    int arrangement;
    
    UserInput();
};

#endif /* UserInput_hpp */
