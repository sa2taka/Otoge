//
//  judgeDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/26.
//
//

#include "JudgeDirector.hpp"
#include "GameProtocol.hpp"
#include "UserInput.hpp"

USING_NS_CC;

/***
 コンストラクタ系列
 */
JudgeDirector *JudgeDirector::instance = new JudgeDirector();

JudgeDirector::JudgeDirector(){};

/***
 public
 */

/**
 インスタンスの取得
 */
JudgeDirector *JudgeDirector::getInstance(){
    return instance;
}

/**
 スプライトの設定
 */
void JudgeDirector::setJudgeSprite(Sprite *judgeSprite, DrawNode *judgeLine){
    bool isLeft = UserInput::getInstance()->getArrangement() == UserInput::LEFT;
    this->judgeSprite = judgeSprite;
    auto winWidth = Director::getInstance()->getWinSize().width;
    this->judgeSprite->setPosition(winWidth / 4 + (isLeft ? 0 : winWidth / 2),
                                   GameProtocol::lineHeight);
    judgeLine->setPosition(isLeft ? 0 : winWidth / 2, GameProtocol::lineHeight);
}

/**
 ジャッジラインに触れているか判定を行う
 */
bool JudgeDirector::judge(int location, char color, float noteWidth){
    float winWidth = Director::getInstance()->getWinSize().width;
    float noteRangeWidth = winWidth / 2 - GameProtocol::padding * 2;
    float noteCenterY = noteRangeWidth / GameProtocol::lineNum * location + GameProtocol::padding;
    bool isLeft = UserInput::getInstance()->getArrangement() == UserInput::LEFT;
    noteCenterY += isLeft ? 0 : winWidth / 2;
    //  判定の左端と右端と中央
    float judgeLeft   = judgeSprite->getPosition().x - judgeSprite->getContentSize().width / 2;
    float judgeRight  = judgeSprite->getPosition().x + judgeSprite->getContentSize().width / 2;
    float judgeCenter = judgeSprite->getPosition().x;
    //  ノートの左端と右端
    float noteLeft  = noteCenterY - noteWidth / 2;
    float noteRight = noteCenterY + noteWidth / 2;
    
    //  判定とノートが触れていたら
    if((judgeLeft   >= noteLeft && judgeLeft   <= noteRight) ||
       (judgeRight  >= noteLeft && judgeRight  <= noteRight) ||
       (judgeCenter >= noteLeft && judgeCenter <= noteRight)){
        return true;
    }
    else{
        return false;
    }
}


/**
 ジャッジラインの動き
 */
void JudgeDirector::moveJudgeLine(){
    int i;
    float moveX = judgeSprite->getPosition().x;
    int judgeLineTouchNum = 0;
    
    auto touchDirector = TouchDirector::getInstance();
    for(i = 0;i < touchDirector->getSize();i++){
        if(touchDirector->isTouching(i)){
            auto position = touchDirector->getPosition(i);
            //  判定ライン画像の端が中央より外に出ず、もう片端が画面外に出ない範囲で動ける
            if(isMovable(position)){
                //  押された平均を取る
                moveX *= judgeLineTouchNum; //一本でも何かの指が触れていたらここで初期値が消える
                moveX += position.x;
                moveX /= judgeLineTouchNum + 1;
                judgeLineTouchNum++;
            }
        }
    }
    judgeSprite->setPosition(moveX, GameProtocol::lineHeight);
}

/***
 private
 */

bool JudgeDirector::isMovable(Vec2 position){
    bool isLeft = UserInput::getInstance()->getArrangement() == UserInput::LEFT;
    if(isLeft){
        if(position.x <= Director::getInstance()->getWinSize().width / 2 - judgeSprite->getContentSize().width / 2
           && position.x >= judgeSprite->getContentSize().width / 2){
            return true;
        }
    }
    else{
        if(position.x <= Director::getInstance()->getWinSize().width - judgeSprite->getContentSize().width / 2
           && position.x >= Director::getInstance()->getWinSize().width / 2 + judgeSprite->getContentSize().width / 2){
            return true;
        }
    }
    return false;
}
