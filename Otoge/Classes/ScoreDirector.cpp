//
//  ScoreDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#include "ScoreDirector.hpp"
#include "GameProtocol.hpp"

USING_NS_CC;

ScoreDirector *ScoreDirector::instance = new ScoreDirector();

ScoreDirector::ScoreDirector(){};

ScoreDirector *ScoreDirector::getInstance(){
    return instance;
}

void ScoreDirector::setLabel(Label *judgeText, Label *scoreText){
    judgeText->setPosition(Director::getInstance()->getWinSize().width / 2,
                           Director::getInstance()->getWinSize().height);
    judgeText->setPositionZ(1);
    scoreText->setAnchorPoint(Vec2(0.0, 1.0));
    scoreText->setPosition(0, Director::getInstance()->getWinSize().height);
    scoreText->setPositionZ(1);
    
    scoreText->setString("0000000");
    judgeText->setString("hoge");
    
    this->judgeText = judgeText;
    this->scoreText = scoreText;
}

void ScoreDirector::setNotesNum(int notesNum){
    this->notesNum = notesNum;
    scorePerNote = (double)GameProtocol::maxScore / (double)notesNum;
}

int ScoreDirector::getGoodNum(){
    return goodNum;
}

int ScoreDirector::getGreatNum(){
    return greatNum;
}

int ScoreDirector::getScore(){
    return (int)score;
}

void ScoreDirector::updateScore(int lastJudge){
    if(abs(lastJudge) > GameProtocol::greatRange){
        score += scorePerNote / 2;
        goodNum++;
        judgeText->setString("good");
    }
    else{
        score += scorePerNote;
        greatNum++;
        judgeText->setString("great");
    }
    char zeroFilledScore[8];
    sprintf(zeroFilledScore, "%07d", (int)scorePerNote);
    scoreText->setString(zeroFilledScore);
}
