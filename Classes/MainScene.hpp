//
//  MainScene.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "Glass.hpp"
#include "MainUILayer.hpp"
#include "Customer.hpp"

/*
 *@class MainScene : public cocos2d::Layer
 *@brief ゲームのメインになるシーン（このゲームでは唯一のシーン）
 */
class MainScene : public cocos2d::Layer
{
private:
    ///スコア
    int _score;
    ///今回のターンでハイスコアを超えたかどうか
    bool _isHighScore = false;
    ///ステージに置かれるグラスのポインタ
    Glass* _glass;
    ///グラスの影のスプライト
    cocos2d::Sprite* _glassShadow;
    ///グラスを止めるエリアのポインタ（判定エリア）
    Customer* _customer;
    ///ハイスコアを表示するラベル
    cocos2d::Label* _highScoreLb;
    ///UIを配置するレイヤーのポインタ
    MainUILayer* _uiLayer;
    ///リソースの読み込み
    void preLoadResources();
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
public:
    /*
     *@brief メインシーンの作成
     *@return 作成されたメインシーン
     */
    static cocos2d::Scene* createScene();
    /*
     *@brief 初期化関数
     *@return true 初期化成功
     *@return false 初期化失敗
     */
    virtual bool init();
    /*
     *@brief アップデート関数
     *@param[in] delta １フレーム更新にかかる時間
     */
    void update(float delta);
    ///create関数マクロ
    CREATE_FUNC(MainScene);
    /*
     *@brief 加点する際に呼ぶ
     *@param[in] add 加点するスコア
     */
    void addScore(int add);
    /*
     *@brief スコアをリセット（スコアを０にする）
     */
    void resetScore();
    /*
     *@brief グラスのポインタを得る
     *@return ステージのグラス
     */
    Glass* getGlass(){return _glass;}
    /*
     *@brief 判定エリアのポインタを得る
     *@return 判定エリア
     */
    Customer* getCustomoer(){return _customer;}
    /*
     *@brief 現在のスコアを得る
     *@return 現在のスコア
     */
    int getScore(){return _score;}
};

#endif /* MainScene_hpp */
