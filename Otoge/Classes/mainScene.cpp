//
//  mainScene.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/22.
//
//

#include "mainScene.hpp"
#include "NoteMover.hpp"

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
    NoteMover noteMover = NoteMover(2);
    
    auto blue_note = SpriteBatchNode::create("img/blue_note.png");
    
    noteMover.flowNote(Sprite::createWithTexture(blue_note->getTexture()), 2, this);
    noteMover.flowNote(Sprite::createWithTexture(blue_note->getTexture()), 4, this);
    return true;
}
