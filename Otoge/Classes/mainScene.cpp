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
    
    //  コールバックの設定
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
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

bool MainScene::onTouchBegan(Touch *touch, Event *event){
    judgeDirector->moveJudgeLine(touch->getLocation());
    return true;
}

void MainScene::onTouchMoved(Touch* touch, Event* event) {
    judgeDirector->moveJudgeLine(touch->getLocation());
}
