//
//  ScoreDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#include "ScoreDirector.hpp"
#include "GameProtocol.hpp"
#include "UserInput.hpp"

USING_NS_CC;

ScoreDirector *ScoreDirector::instance = new ScoreDirector();

ScoreDirector::ScoreDirector(){
    reset();
}

ScoreDirector *ScoreDirector::getInstance(){
    return instance;
}

void ScoreDirector::setLabel(Label *judgeText, Label *scoreText){
    bool isLeft = UserInput::getInstance()->getArrangement() == UserInput::LEFT;
    auto winSize = Director::getInstance()->getWinSize();
    judgeText->setPosition(winSize.width / 4 + (isLeft ? 0 : winSize.width / 2),
                            winSize.height - winSize.height / 4);
    scoreText->setAnchorPoint(Vec2(0.0, 1.0));
    scoreText->setPosition(isLeft ? 0 : winSize.width,
                           winSize.height - winSize.height / 8);
    
    scoreText->setString("0000000");
    judgeText->setString("");
    
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
    //  0以下のときもgood未満の判定
    if(lastJudge > GameProtocol::goodRange || lastJudge < 0){
        judgeText->setString("Miss..");
    }
    
    else if(lastJudge > GameProtocol::greatRange){
        score += scorePerNote / 2;
        goodNum++;
        judgeText->setString("good");
    }
    else{
        score += scorePerNote;
        greatNum++;
        judgeText->setString("great");
        //  double型にしても計算が合わないときがあるため
        if(greatNum == notesNum){
            score = GameProtocol::maxScore;
        }
    }
    char zeroFilledScore[8];
    sprintf(zeroFilledScore, "%07d", (int)score);
    scoreText->setString(zeroFilledScore);
}

/***
 private
*/

void ScoreDirector::reset(){
    goodNum = 0;
    greatNum = 0;
    score = 0;
    scorePerNote = 0;
}
