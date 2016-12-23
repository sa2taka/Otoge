//
//  GameProtocol.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/24.
//
//

#include "GameProtocol.hpp"

GameProtocol *GameProtocol::instance = new GameProtocol();

GameProtocol::GameProtocol(){
    lineHeight = 75.0;
}

GameProtocol *GameProtocol::getInstance(){
    return instance;
}
