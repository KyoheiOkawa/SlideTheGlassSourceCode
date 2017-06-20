//
//  PhysicsArea.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef PhysicsArea_hpp
#define PhysicsArea_hpp

#include <cocos2d.h>

/**
 *@class PhysicsArea
 *@brief 見えない壁のクラス
 */
class PhysicsArea : public cocos2d::Node
{
public :
    ///初期化関数
    bool init() override;
    /**
     *@brief create関数
     *@param pos 位置
     *@param size 大きさ
     *@return 作成されたPhysicsArea
     */
    static PhysicsArea* create(const cocos2d::Vec2 &pos, const cocos2d::Size &size);
};

#endif /* PhysicsArea_hpp */
