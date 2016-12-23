//
//  gameProtocol.h
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#ifndef GameProtocol_h
#define GameProtocol_h

class GameProtocol{
public:
    static GameProtocol *getInstance();
    float lineHeight;
    
private:
    static GameProtocol *instance;
    
    GameProtocol();
};

#endif /* GameProtocol_h */
