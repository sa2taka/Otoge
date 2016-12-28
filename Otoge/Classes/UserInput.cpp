//
//  UserInput.cpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#include "UserInput.hpp"

class UserInput{
public:
    UserInput *getInstance();
private:
    UserInput *instance;
    
    UserInput();
};
