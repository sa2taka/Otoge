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
    this->schedule(schedule_selector(MainScene::update), 1/30);
    noteDirector = NoteDirector::getInstance();
    
    auto blueNote = SpriteBatchNode::create("img/blue_note.png");
    auto redNote = SpriteBatchNode::create("img/red_note.png");
    auto purpleNote = SpriteBatchNode::create("img/purple_note.png");
    
    noteDirector->setNoteSprite(blueNote, redNote, purpleNote);
    noteDirector->loadList("hogehoge");
    
    this->addChild(blueNote);
    this->addChild(redNote);
    this->addChild(purpleNote);
    
    noteDirector->setSpeed(2);
    
    return true;
}

void MainScene::update(float delta){
    noteDirector->updateNotes(delta);
    log("%f", delta);
}
