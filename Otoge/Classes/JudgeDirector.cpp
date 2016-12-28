//
//  judgeDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/26.
//
//

#include "JudgeDirector.hpp"
#include "GameProtocol.hpp"

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
void JudgeDirector::setJudgeSprite(cocos2d::Sprite *judgeSprite){
    this->judgeSprite = judgeSprite;
    this->judgeSprite->setPositionZ(1);
    this->judgeSprite->setPosition(Director::getInstance()->getWinSize().width / 4,
                                   GameProtocol::lineHeight);
}

/**
 ジャッジラインに触れているか判定を行う
 */
bool JudgeDirector::judge(int location, char color, float noteWidth){
    float winWidth = Director::getInstance()->getWinSize().width;
    float noteRangeWidth = winWidth / 2 - GameProtocol::padding * 2;
    float noteCenterY = noteRangeWidth / GameProtocol::lineNum * location + GameProtocol::padding;
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
            //  判定ライン画像の右端が画面の半分より右に行かず、左端が画面端を超えないとき判定ラインを動かす
            if(position.x <= Director::getInstance()->getWinSize().width / 2 - judgeSprite->getContentSize().width / 2
               && position.x >= judgeSprite->getContentSize().width / 2){
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

