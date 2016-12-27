//
//  ScoreDirector.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#ifndef ScoreDirector_hpp
#define ScoreDirector_hpp

#include <cocos2d.h>

class ScoreDirector{
public:
    static ScoreDirector *getInstance();
    
    void setNotesNum(int notesNum);
    void setLabel(cocos2d::Label *judgeText, cocos2d::Label *scoreText);
    int getGoodNum();
    int getGreatNum();
    int getScore();
    
    void updateScore(int lastJudgeCount);
    
private:
    static ScoreDirector *instance;
    
    double score;
    double scorePerNote;
    int notesNum;
    int greatNum;
    int goodNum;
    
    cocos2d::Label *judgeText;
    cocos2d::Label *scoreText;
    
    ScoreDirector();
};

#endif /* ScoreDirector_hpp */
