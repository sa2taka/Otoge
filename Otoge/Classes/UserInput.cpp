//
//  UserInput.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#include "UserInput.hpp"
#include <fstream>
#include <string>

UserInput *UserInput::instance = new UserInput();
UserInput::UserInput(){
    speed = 1;
    arrangement = LEFT;
    
    //  ファイルの読み込み
    std::ifstream ifs(fileName, std::ios::in);
    std::string reading_line;
    
    while(std::getline(ifs, reading_line)){
        std::string identifier;
        std::string value;
        std::sscanf(reading_line.c_str(), "%s %s\n", (char *)identifier.c_str(), (char *)value.c_str());
        if(strcmp(identifier.c_str(), "speed") == 0){
            speed = atoi(value.c_str());
        }
        if(strcmp(identifier.c_str(), "arrangement") == 0){
            arrangement = strcmp(value.c_str(), "left") == 0 ? LEFT : RIGHT;
        }
    }
}

/***
 public
*/
UserInput *UserInput::getInstance(){
    return instance;
}

void UserInput::setSpeed(int speed){
    this->speed = speed;
}

void UserInput::setArrangement(int arrangement){
    this->arrangement = arrangement;
}

int UserInput::getSpeed(){
    return speed;
}

int UserInput::getArrangement(){
    return arrangement;
}

void UserInput::saveStatus(){
    std::ofstream ofs(fileName, std::ios::trunc);
    
    ofs << "speed " << speed << std::endl;
    ofs << "arrangement" << arrangement << std::endl;
}

