//
//  mainScene.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/22.
//
//

#include "MainScene.hpp"

USING_NS_CC;

Scene* MainScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->scheduleUpdate();
    
    //  ノート関連の初期化
    noteInit();
    //  判定関連の初期化
    judgeInit();
    //  ボタン関連の初期化
    buttonInit();
    //  タッチ関連の初期化(インスタンスの取得のみ)
    touchDirector = TouchDirector::getInstance();
    
    //  コールバックの設定(コールバックと言うかタッチの設定)
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);        
    return true;
}

void MainScene::update(float delta){
    noteDirector->updateNotes(delta);
}

void MainScene::noteInit(){
    noteDirector = NoteDirector::getInstance();
    
    auto blueNote = SpriteBatchNode::create("img/blue_note.png");
    auto redNote = SpriteBatchNode::create("img/red_note.png");
    auto purpleNote = SpriteBatchNode::create("img/purple_note.png");
    
    noteDirector->setNoteSprite(blueNote, redNote, purpleNote);
    noteDirector->loadList("hogehoge");
    
    this->addChild(blueNote);
    this->addChild(redNote);
    this->addChild(purpleNote);
    
    noteDirector->setSpeed(1);
}

void MainScene::judgeInit(){
    judgeDirector = JudgeDirector::getInstance();
    
    auto judgeSprite = Sprite::create("img/judge_line.png");
    
    judgeDirector->setJudgeSprite(judgeSprite);
    
    this->addChild(judgeSprite);
}

void MainScene::buttonInit(){
    buttonDirector = ButtonDirector::getInstance();
    
    auto notPushedRedButton = Sprite::create();
    auto notPushedBlueButton = Sprite::create();
    auto pushedRedButton = Sprite::create();
    auto pushedBlueButton = Sprite::create();

    auto winSize = Director::getInstance()->getWinSize();
    auto rect = Rect(0, 0, winSize.width / 4, winSize.height);
    
    notPushedRedButton->setTextureRect(rect);
    notPushedBlueButton->setTextureRect(rect);
    pushedRedButton->setTextureRect(rect);
    pushedBlueButton->setTextureRect(rect);
    
    buttonDirector->setButtonSprite(notPushedRedButton,
                                    notPushedBlueButton,
                                    pushedRedButton,
                                    pushedBlueButton);
    
    this->addChild(notPushedRedButton);
    this->addChild(notPushedBlueButton);
    this->addChild(pushedRedButton);
    this->addChild(pushedBlueButton);
}

void MainScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event){
    touchDirector->checkTouch(touches, true);
    judgeDirector->moveJudgeLine();
    buttonDirector->checkTouchButton();
}

void MainScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *event){
    touchDirector->checkTouch(touches, true);
    judgeDirector->moveJudgeLine();
    buttonDirector->checkTouchButton();
}

void MainScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event){
    touchDirector->checkTouch(touches, false);
    judgeDirector->moveJudgeLine();
    buttonDirector->checkTouchButton();
}
