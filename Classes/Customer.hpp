//
//  Customer.hpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#ifndef Customer_hpp
#define Customer_hpp

#include <stdio.h>
#include <cocos2d.h>
///判定の幅の最大値
const float JUDGE_MAX_WIDTH = 400;
///判定の幅の最小値
const float JUDGE_MIN_WIDTH = 50;
///止めると得点が１０点のエリア（スペシャルエリア）の幅
const float SPECIAL_AREA_WIDTH = 25;
///小さくなっていく度合い
const float SHRINK_DEGREE = 5000.0f;

class Customer : public cocos2d::Node
{
private:
    ///グラスを止める判定エリアの幅
    float _acceptWidth = JUDGE_MAX_WIDTH;
    ///判定エリアを可視化するためのスプライト
    cocos2d::Sprite* _judgeArea;
    ///スペシャルエリアを可視化するためのスプライト
    cocos2d::Sprite* _specialArea;
public:
    ///初期化関数
    virtual bool init();
    ///create関数
    CREATE_FUNC(Customer);
    ///アップデート関数
    virtual void update(float delta);
    /*
     *@brief グラスが判定エリアに止まったか判定する
     *@return true エリア内に止まった
     *@return false エリア内に止まらなかった
     */
    bool Judge();
    /*
     *@brief 判定エリアの幅を変更する
     *@par 用途
     *      スコアが上がるごとに難易度を上げるために使用する
     */
    void changeJudgeAreaWidth();
    /*
     *@brief 判定エリアの位置をランダムに変更する
     */
    void changePosition();
    /*
     *@brief スペシャル判定エリアをセットする
     *@param[in] score 現在のスコア
     */
    void setSpecialArea(int score);
    /*
     *@brief グラスがスペシャルエリアに止まったか判定する
     *@return true エリア内に止まった
     *@return false エリア内に止まらなかった
     */
    bool judgeSpecialArea();
};

#endif /* Customer_hpp */
