//
//  Glass.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#ifndef Glass_hpp
#define Glass_hpp

#include <stdio.h>
#include <cocos2d.h>

/*
 *@class Glass : public cocos2d::Sprite
 *@brief 滑らせるグラスクラス
 */
class Glass : public cocos2d::Sprite
{
private:
    /*
     *@brief タッチ開始時に呼ばれるイベント
     *@param[in] *touch タッチ情報
     *@param[in] *event イベント情報
     *@return true 以降のタッチイベントを実行する場合(この関数は常にtrueを返す)
     */
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    /*
     *@brief タッチされている間にに呼ばれるイベント
     *@param[in] *touch タッチ情報
     *@param[in] *event イベント情報
     */
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    /*
     *@brief 指が話された時に呼ばれるイベント
     *@param[in] *touch タッチ情報
     *@param[in] *event イベント情報
     *@return true 以降のタッチイベントを実行する場合(この関数は常にtrueを返す)
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    /*
     *@brief 衝突検知時に呼ばれる
     *@param[in] &contact 接触情報
     *@return true 常にtrueを返す
     */
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    ///フリックしている時間をカウントするための変数
    float _flickTime;
    ///グラスをスライドさせたかのフラグ
    bool _isAddForce;
    ///着地したか
    bool _isGround;
public:
    ///初期化関数
    bool init() override;
    ///create関数マクロ
    CREATE_FUNC(Glass);
    ///アップデート関数
    void update(float delta) override;
    /*
     *@brief グラスを初期位置にリセット
     */
    void reset();
};

#endif /* Glass_hpp */
