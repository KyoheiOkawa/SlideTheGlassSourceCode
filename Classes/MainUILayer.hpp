//
//  MainUILayer.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#ifndef MainUILayer_hpp
#define MainUILayer_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include "MusicSelect.hpp"

/*
 *@class MainUILayer : public cocos2d::Layer
 *@brief メインで表示するUIのレイヤー
 *@par 現在のスコア、曲選択ボタン、ランキングボタンなど
 */
class MainUILayer : public cocos2d::Layer
{
private:
    ///現在のスコアを表示するラベル
    cocos2d::Label* _scoreLb;
    ///曲を選択するレイヤー
    MusicSelect* _musicSelect;
    ///タッチ開始時に呼ばれる
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    /*
     *@brief 曲選択ボタンを押した時に呼ばれる
     *@par 曲選択レイヤーを表示する
     *@param[in] メッセージを送ったオブジェクト
     *@param[in] タッチのタイプ
     */
    void onMusicSelectButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    /*
     *@brief　ランキングボタンを押した時に呼ばれる
     *@par ランキングを表示する
     *@param[in] メッセージを送ったオブジェクト
     *@param[in] タッチのタイプ
     */
    void onRankingButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    /*
     *@brief　はてなボタンを押した時に呼ばれる
     *@par 遊び方を説明するレイヤーを表示する
     *@param[in] メッセージを送ったオブジェクト
     *@param[in] タッチのタイプ
     */
    void onQuestionButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
public:
    ///初期化関数
    bool init();
    ///create関数
    CREATE_FUNC(MainUILayer);
    ///アップデート関数
    void update(float delta);
    /*
     *@brief スコアの文字列をラベルに設定する
     *@param[in] score セットするスコア
     *@param[in] isAdd 前のスコアより加算する場合はtrue減る場合はfalse
     */
    void setScoreString(int score,bool isAdd);
};

#endif /* MainUILayer_hpp */
