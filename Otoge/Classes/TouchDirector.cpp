
//
//  TouchDirector.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/27.
//
//

#include "TouchDirector.hpp"

USING_NS_CC;

TouchDirector *TouchDirector::instance = new TouchDirector();

TouchDirector::TouchDirector(){
    for(int i = 0;i < 5;i++){
        touchStatuses.push_back(new TouchStatus());
    }
}

/***
 public
 */

TouchDirector *TouchDirector::getInstance(){
    return instance;
}

Vec2 TouchDirector::getPosition(int index){
    if(index >= 0 && index < touchStatuses.size()){
        return touchStatuses[index]->position;
    }
    return Vec2::ZERO;
}

bool TouchDirector::isTouching(int index){
    if(index >= 0 && index < touchStatuses.size()){
        return touchStatuses[index]->isTouching;
    }
    return false;
}

int TouchDirector::getSize(){
    return (int)touchStatuses.size();
}

void TouchDirector::checkTouch(std::vector<Touch *> touches, bool isTouching){
    int i;
    for(i = 0;i < touches.size();i++){
        touchStatuses[touches[i]->getID()]->position = touches[i]->getLocation();
        touchStatuses[touches[i]->getID()]->isTouching = isTouching;
    }
}
