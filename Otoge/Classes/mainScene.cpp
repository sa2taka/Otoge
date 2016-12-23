//
//  mainScene.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/22.
//
//

#include "mainScene.hpp"

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
    
    blueNote = SpriteBatchNode::create("img/blue_note.png");
    noteDirector->setSpeed(2);
    
    
    return true;
}

void MainScene::update(float delta){
    noteDirector->updateNotes();
}
