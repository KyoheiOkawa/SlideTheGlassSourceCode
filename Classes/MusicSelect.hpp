//
//  MusicSelect.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/04.
//
//

#ifndef MusicSelect_hpp
#define MusicSelect_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <ui/CocosGUI.h>

/*
 *@class MusicSelect : public cocos2d::LayerColor
 *@brief ミュージック選択レイヤー
 */
class MusicSelect : public cocos2d::LayerColor
{
private:
    ///タッチイベントリスナー
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    
    ///タッチ開始時に呼ばれる
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    /*
     *@brief レイヤーを閉じるボタンを押された時に呼ばれる
     *@par このレイヤーを非表示にする
     *@param[in] メッセージを送ったオブジェクト
     *@param[in] タッチのタイプ
     */
    void onBatsuButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    /*
     *@brief MusMusさんのHPに行くボタンが押された時に呼ばれる
     *@par MusMusさんのHPのURLを開く
     *@param[in] メッセージを送ったオブジェクト
     *@param[in] タッチのタイプ
     */
    void onMusMusButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    /*
     *@brief 楽曲リストのどれかが押された時に呼ばれる
     *@par 選択された曲を再生する
     *@param[in] 選択された曲のボタン
     */
    void musicChange(Ref* pSender);
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(MusicSelect);
    ///このレイヤーのタッチイベントリスナーのゲッター
    cocos2d::EventListenerTouchOneByOne* getTouchEventListener()
    {
        return _touchListener;
    }
};

#endif /* MusicSelect_hpp */
