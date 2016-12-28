//
//  UserInput.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/28.
//
//

#ifndef UserInput_hpp
#define UserInput_hpp

class UserInput{
public:
    UserInput *getInstance();
private:
    UserInput *instance;
    
    UserInput();
};

#endif /* UserInput_hpp */
