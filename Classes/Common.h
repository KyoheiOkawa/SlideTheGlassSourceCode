//
//  Common.h
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//
/*
 *@file Common.h
 *@brief ゲームで使用するヘッダ、定数を定義する
 */
#ifndef Common_h
#define Common_h

#include <cocos2d.h>

///インクルード
//////////////////////////////////////
#include "MainScene.hpp"
#include "Glass.hpp"
#include "PhysicsArea.hpp"
#include "Customer.hpp"
#include "MainUILayer.hpp"
#include "SimpleAudioEngine.h"
#include "MusicSelect.hpp"
#include "TutorialLayer.hpp"
#include "NativeCodeLauncher.h"

#include <iomanip>
#include <ostream>

#include "NendInterstitialModule.h"
//////////////////////////////////////

using namespace CocosDenshion;

//フリックの判定時間　この時間を超えて指を離した場合フリックと判定されない
const float FLICK_TIME = 0.5f;
//グラスを滑らせる力
const float SLIDE_POWER = 40.0f;
//グラスと机の摩擦力
const float FRICTION = 0.45f;

//このゲームで使用するフォント
const std::string USE_FONT_PATH = "fonts/Rumburak.ttf";

//グラスの初期位置
const cocos2d::Vec2 GLASS_FIRST_POS = cocos2d::Vec2(1000,320);

//BGMパス
const std::string BGM = "Audio/BGM";
//BGMの数
const int BGM_COUNT = 15;
//曲名
const std::string BGM_NAME[] ={
    "blend",
    "[Investigation]DBD File No.03",
    "Girty Of Rainy Day",
    "Good Old Days",
    "Gunshot Straight",
    "Honeymoon",
    "Impromptu to Sleep in Winter",
    "inherit the Light Trail",
    "Light Up Delight",
    "Neon",
    "Pops up the mind wings",
    "Session On The Sofa",
    "sleepin' maple syrup jazz",
    "SMOKY",
    "Stable yet",
};
//褒めボイスのパス
const std::string VC_GOOD[]={
    "Audio/Voice/Good.mp3",
    "Audio/Voice/Nice.mp3",
    "Audio/Voice/OhYeah.mp3",
    "Audio/Voice/OK.mp3"
};

#endif /* Common_h */
