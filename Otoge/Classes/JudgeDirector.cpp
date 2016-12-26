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
    this->judgeSprite->setPosition(GameProtocol::lineHeight,
                                   Director::getInstance()->getWinSize().height / 4);
}

/**
 ジャッジラインの動き
 */
void JudgeDirector::moveJudgeLine(Vec2 position){
    float moveX = position.x;
    
    //  判定ライン画像の右端が画面の半分より右に行かないときのみ判定ラインを動かす
    if(moveX <= Director::getInstance()->getWinSize().width / 2 - judgeSprite->getContentSize().width / 2){
        if(moveX < judgeSprite->getContentSize().width / 2){
            moveX = judgeSprite->getContentSize().width / 2;
        }
        judgeSprite->setPosition(moveX, GameProtocol::lineHeight);
    }
}
