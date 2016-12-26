//
//  judgeDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/26.
//
//

#ifndef JudgeDirector_hpp
#define JudgeDirector_hpp

#include "cocos2d.h"

class JudgeDirector{
public:
    static JudgeDirector* getInstance();
    void setJudgeSprite(cocos2d::Sprite *judgeSprite);
    
    void moveJudgeLine(cocos2d::Vec2 position);
    
private:
    static JudgeDirector* instance;
    
    cocos2d::Sprite *judgeSprite;   //  判定のためのスプライトは画面に一つしか現れない
    
    //  コンストラクタ
    JudgeDirector();
};

#endif /* JudgeDirector_hpp */
