//
//  StartDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/29.
//
//

#ifndef StartDirector_hpp
#define StartDirector_hpp

#include <cocos2d.h>

class StartDirector{
public:
    static StartDirector *getInstance();
    
    void setSprite(cocos2d::ProgressTimer *progressBar, cocos2d::Label *readyLabel);
    void setMaxNum(int maxNum);
    
    void updateBar();
private:
    static StartDirector *instance;
    
    int maxNum;
    int nowNum;
    
    cocos2d::ProgressTimer *progressBar;
    cocos2d::Label *readyLabel;
    
    StartDirector();
};

#endif /* StartDirector_hpp */
