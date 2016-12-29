//
//  StartDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/29.
//
//

#include "StartDirector.hpp"


USING_NS_CC;

StartDirector *StartDirector::instance = new StartDirector;
StartDirector::StartDirector(){
    maxNum = 0;
    nowNum = 0;
};

/***
 public
 */

StartDirector *StartDirector::getInstance(){
    return instance;
}

void StartDirector::setSprite(ProgressTimer *progressBar, Label *readyLabel){
    auto winSize = Director::getInstance()->getWinSize();
    progressBar->setPosition( winSize.width / 2, winSize.height / 2);
    readyLabel->setPosition(winSize.width / 2, winSize.height / 2);
    readyLabel->setVisible(false);
    
    progressBar->setPercentage(0);
    progressBar->setType(ProgressTimer::Type::BAR);
    
    progressBar->setBarChangeRate(Vec2(1, 0));
    progressBar->setMidpoint(Vec2(0, 0));
    
    this->progressBar = progressBar;
    this->readyLabel = readyLabel;
}

void StartDirector::setMaxNum(int maxNum){
    this->maxNum = maxNum;
}

void StartDirector::updateBar(){
    nowNum++;
    progressBar->setPercentage(nowNum / maxNum * 100);
    
    if(nowNum / maxNum >= 1){
        progressBar->getParent()->removeChild(progressBar);
        readyLabel->getParent()->removeChild(readyLabel);
    }
}
