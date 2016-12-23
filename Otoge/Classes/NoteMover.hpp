//
//  NoteMover.hpp
//  Otoge
//
//  Created by 薩田和弘 on 2016/12/23.
//
//

#ifndef NoteMover_hpp
#define NoteMover_hpp

#include <cocos2d.h>

class NoteMover{
public:
    enum class NoteColor{
        Red,
        Blue,
        Purple
    };
    
    /**
    コンストラクタ(上から下まで流れる秒数)
     */
    NoteMover(int);
    
    //  速さの変更
    void setSpeed(int);
    
    // ノートを流す
    void flowNote(cocos2d::Sprite*, int, cocos2d::Layer*);
    
private:
    float speed;
    float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
    cocos2d::Sequence* noteSequence;
};

#endif /* NoteMover_hpp */
