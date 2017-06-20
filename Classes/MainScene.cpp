//
//  MainScene.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#include "Common.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto physicsWorld = scene->getPhysicsWorld();
    physicsWorld->setGravity(Vec2(0,-980));
    
    //コリジョンの境界を確認したいときはコメントを外す
    //physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init()
{
    if(!Layer::init())
        return false;
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.25f);
    auto playBgm = BGM + '/' + BGM_NAME[(int)random(0, BGM_COUNT-1)] + ".mp3";
    SimpleAudioEngine::getInstance()->playBackgroundMusic(playBgm.c_str(),true);
    
    this->scheduleUpdate();
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    //背景
    auto bg = Sprite::create("Textures/bg2.png");
    bg->setPosition(origin + vs/2.0f);
    this->addChild(bg,0);
    
    //---------------------------------------------------------
    //背景画像のアクションを設定
    auto bgBiright = TintTo::create(2.5f, 255, 255, 255);
    auto bgDark    = TintTo::create(2.5f, 150, 150, 150);
    auto bgSeq = Sequence::create(bgDark,bgBiright, NULL);
    auto bgRep = RepeatForever::create(bgSeq);
    bg->runAction(bgRep);
    //---------------------------------------------------------
    std::ostringstream ostr;
    auto userDef = UserDefault::getInstance();
    
    //ハイスコアラベルの設定
    _highScoreLb = Label::createWithTTF("HighScore 000", USE_FONT_PATH, 64);
    _highScoreLb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _highScoreLb->setPosition(origin + Vec2(0,90));
    this->addChild(_highScoreLb,2);
    ostr << "HightScore " << std::setw(3) << std::setfill(' ') << userDef->getIntegerForKey("HighScore", 0);
    _highScoreLb->setString(ostr.str());
    
    _uiLayer = MainUILayer::create();
    this->addChild(_uiLayer,15);
    
    _glass = Glass::create();
    _glass->setPosition(origin + GLASS_FIRST_POS);
    _glass->setScale(0.8f);
    this->addChild(_glass,10);
    
    _glassShadow = Sprite::create("Textures/Shadow.png");
    _glassShadow->setPosition(Vec2(_glass->getPosition().x,origin.y+51));
    _glassShadow->setOpacity(150);
    this->addChild(_glassShadow,5);
    
    //画面下の衝突判定エリア
    auto floor = PhysicsArea::create(origin, Size(vs.width,45));
    floor->getPhysicsBody()->setContactTestBitmask(0x0001);
    this->addChild(floor);
    
    //画面右の衝突判定エリア
    auto wallR = PhysicsArea::create(origin + Vec2(vs.width,0), Size(-50,vs.height));
    this->addChild(wallR);
    
    //机の画像
    auto table = Sprite::create("Textures/table.png");
    table->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    table->setPosition(origin + Vec2(vs.width/2.0f,0));
    this->addChild(table,3);
    
    //グラスを止める判定エリアの追加
    _customer = Customer::create();
    _customer->setPosition(origin + Vec2(vs.width/4.0f,45));
    this->addChild(_customer,4);
    
    //初めての起動であった場合チュートリアルを表示する
    if(userDef->getBoolForKey("IsFirstStart", true)){
        userDef->setBoolForKey("IsFirstStart", false);
        auto tutorial = TutorialLayer::create();
        this->addChild(tutorial,16);
    }
    
    //インタースティンシャル広告の設定
    char interstitialApiKey[] = "MyAPIKey";
    char interstitialSpotID[] = "MySpotID";
    NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void MainScene::preLoadResources()
{
    auto audio = SimpleAudioEngine::getInstance();
    
    audio->preloadEffect("Audio/SE/glass_break.mp3");
    audio->preloadEffect("Audio/SE/GlassSlide.mp3");
    audio->preloadEffect("Audio/SE/glassTakeOn.mp3");
    
    audio->preloadEffect("Audio/Voice/Excellent.mp3");
    audio->preloadEffect("Audio/Voice/Good.mp3");
    audio->preloadEffect("Audio/Voice/HighScore.mp3");
    audio->preloadEffect("Audio/Voice/Nice.mp3");
    audio->preloadEffect("Audio/Voice/OhMan.mp3");
    audio->preloadEffect("Audio/Voice/OhYeah.mp3");
    audio->preloadEffect("Audio/Voice/OK.mp3");
    audio->preloadEffect("Audio/Voice/Oops.mp3");
}

void MainScene::update(float delta)
{
    //グラスのシャドウをグラスの真下になるようにアップデート
    _glassShadow->setPositionX(_glass->getPosition().x);
}

void MainScene::addScore(int add)
{
    _score += add;
    _customer->changeJudgeAreaWidth();
    _customer->changePosition();
    _customer->setSpecialArea(_score);
    
    _uiLayer->setScoreString(_score,true);
    
    auto audio = SimpleAudioEngine::getInstance();
    
    auto userDef = UserDefault::getInstance();
    //ハイスコアであった場合の処理
    if(userDef->getIntegerForKey("HighScore",0) < _score)
    {
        userDef->setIntegerForKey("HighScore", _score);
        //ランキングにハイスコアを送信
        Cocos2dExt::NativeCodeLauncher::postHighScore(1, _score);
        
        std::ostringstream ostr;
        ostr << "HightScore " << std::setw(3) << std::setfill(' ') << userDef->getIntegerForKey("HighScore", 0);
        
        _highScoreLb->setString(ostr.str());
        
        //現在のターンでハイスコアを超えた時に１度だけハイスコアおめでとう演出を発生させる
        if(!_isHighScore){
            auto origin = Director::getInstance()->getVisibleOrigin();
            auto vs = Director::getInstance()->getVisibleSize();
            
            auto delay = DelayTime::create(0.5f);
            auto se = CallFunc::create([audio](){
                audio->playEffect("Audio/Voice/HighScore.mp3");
            });
            auto seq = Sequence::create(delay,se, NULL);
            this->runAction(seq);
            
            auto particle = ParticleSystemQuad::create("Particles/HighScore.plist");
            particle->setAutoRemoveOnFinish(true);
            particle->resetSystem();
            particle->setPosition(origin + Vec2(vs.width/2.0f,vs.height));
            this->addChild(particle,2);
        }
        
        _isHighScore = true;
    }
}

void MainScene::resetScore()
{
    _score = 0;
    _isHighScore = false;
    
    _uiLayer->setScoreString(_score, false);
    
    _customer->changeJudgeAreaWidth();
    _customer->changePosition();
    _customer->setSpecialArea(_score);
    
    NendInterstitialModule::showNADInterstitialView();
}

bool MainScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //タッチしたところにパーティクルを発生させる
    auto touchParticle = ParticleSystemQuad::create("Particles/TouchParticle.plist");
    touchParticle->setAutoRemoveOnFinish(true);
    touchParticle->resetSystem();
    touchParticle->setPosition(touch->getLocation());
    this->addChild(touchParticle,10);
    
    return true;
}

void MainScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void MainScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
