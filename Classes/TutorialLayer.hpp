//
//  TutorialLayer.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/10.
//
//

#ifndef TutorialLayer_hpp
#define TutorialLayer_hpp

#include <stdio.h>
#include <cocos2d.h>

///ゲーム説明のスライドの数
const int MAX_SLIDES = 3;

/*
 *@class TutorialLayer : public cocos2d::LayerColor
 *@brief ゲーム説明レイヤー
 */
class TutorialLayer : public cocos2d::LayerColor
{
private:
    ///何回タッチされたか（今何スライド目か）
    int _touchNum;
    ///スライド中かどうか
    bool _isNowSlide;
    ///スライドのテクスチャ
    cocos2d::Texture2D* _slideTx[3];
    ///スライドを表示するスプライト
    cocos2d::Sprite* _slide;
    ///スライドアクション（フェード）を実行
    void runSlideAction();
    
    ///タッチ開始時に呼ばれる
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    ///指を離した時に呼ばれる
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(TutorialLayer);
};

#endif /* TutorialLayer_hpp */
