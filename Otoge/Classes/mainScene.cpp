//
//  mainScene.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/22.
//
//

#include "MainScene.hpp"
#include "GameProtocol.hpp"
#include <functional>

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
    //  スコア関連の初期化
    scoreInit();
    //  ディレクターに関係ない初期化
    otherInit();
    //  スタート時の初期化
    startInit();
    
    isFirstTouch = true;
    
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
    if(noteDirector->isLoadFinish()){
        noteDirector->updateNotes(delta);
        if(cover != nullptr){
            this->removeChild(cover);
            cover = nullptr;
        }
    }
}

void MainScene::noteInit(){
    noteDirector = NoteDirector::getInstance();
    
    auto blueNote = SpriteBatchNode::create("img/blue_note.png");
    auto redNote = SpriteBatchNode::create("img/red_note.png");
    auto purpleNote = SpriteBatchNode::create("img/purple_note.png");
    auto blueSlide = SpriteBatchNode::create("img/blue_slide.png");
    auto redSlide = SpriteBatchNode::create("img/red_slide.png");
    auto purpleSlide = SpriteBatchNode::create("img/purple_slide.png");
    
    noteDirector->setNoteSprite(blueNote,
                                redNote,
                                purpleNote,
                                blueSlide,
                                redSlide,
                                purpleSlide);
    
    this->addChild(blueNote);
    this->addChild(redNote);
    this->addChild(purpleNote);
    this->addChild(blueSlide);
    this->addChild(redSlide);
    this->addChild(purpleSlide);
}

void MainScene::judgeInit(){
    judgeDirector = JudgeDirector::getInstance();
    
    auto judgeSprite = Sprite::create("img/judge_line.png");
    auto judgeLine = DrawNode::create();
    
    float winWidth = Director::getInstance()->getWinSize().width;
    judgeLine->drawSegment(Vec2(0, 0),
                           Vec2(winWidth / 2, 0),
                           1,
                           Color4F::GRAY);
    
    judgeDirector->setJudgeSprite(judgeSprite, judgeLine);
    
    this->addChild(judgeLine);
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

void MainScene::scoreInit(){
    scoreDirector = ScoreDirector::getInstance();
    
    auto judgeLabel = Label::createWithSystemFont("", "Arial", 32);
    auto scoreLabel = Label::createWithSystemFont("", "Arial", 24);
    
    scoreDirector->setLabel(judgeLabel, scoreLabel);

    this->addChild(judgeLabel);
    this->addChild(scoreLabel);
}

void MainScene::startInit(){
    startDirector = StartDirector::getInstance();
    auto winSize = Director::getInstance()->getWinSize();
    
    auto readyLabel = Label::createWithSystemFont("ready...", "Arial", 16);
    auto progressBar = Sprite::create("img/progress_bar.png");
    auto progressTimer = ProgressTimer::create(progressBar);

    startDirector->setSprite(progressTimer, readyLabel);
    
    this->addChild(progressTimer);
    this->addChild(readyLabel);
}

void MainScene::otherInit(){
    touchLabel = Label::createWithSystemFont("Touch", "Arial", 24);
    cover = Sprite::create();
    auto winSize = Director::getInstance()->getWinSize();
    auto rect = Rect(0, 0, winSize.width, winSize.height);
    cover->setTextureRect(rect);
    cover->setColor(Color3B::BLACK);
    cover->setOpacity(192);
    touchLabel->setPosition(winSize.width / 2, winSize.height / 2);
    cover->setPosition(winSize.width / 2, winSize.height / 2);
    
    this->addChild(cover);
    this->addChild(touchLabel);
}

void MainScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *event){
    if(isFirstTouch) {
        isFirstTouch = false;
        noteDirector->loadList(FileUtils::getInstance()->fullPathForFilename("sco/banbado.sco"));
        this->removeChild(touchLabel);
    }
    touchDirector->checkTouch(touches, true);
    judgeDirector->moveJudgeLine();
    buttonDirector->checkTouchButton();
    auto temp = buttonDirector->checkStartTouchButton(touches);
    noteDirector->judgeTouchNote(std::get<0>(temp), std::get<1>(temp));
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
