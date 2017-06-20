//
//  MainUILayer.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#include "Common.h"

USING_NS_CC;

bool MainUILayer::init()
{
    if(!Layer::init())
        return false;
    
    this->scheduleUpdate();
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    float offset = 10;
    
    //スコアラベル
    _scoreLb = Label::createWithTTF("0", USE_FONT_PATH, 128);
    _scoreLb->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    _scoreLb->setPosition(origin + Vec2(vs.width / 2.0f, vs.height - offset));
    this->addChild(_scoreLb);
    
    //ミュージックボタン
    auto musicBt = ui::Button::create("Textures/Music.png");
    musicBt->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    musicBt->setPosition(origin + Vec2(offset,vs.height - offset));
    musicBt->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onMusicSelectButton, this));
    this->addChild(musicBt);
    
    //ランクボタン
    auto rankBt = ui::Button::create("Textures/Rank.png");
    rankBt->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    rankBt->setPosition(origin+Vec2(vs.width - offset,vs.height - offset));
    rankBt->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onRankingButton, this));
    this->addChild(rankBt);
    
    //チュートリアルボタン（左下）
    auto quesBt = ui::Button::create("Textures/HowToPlay.png");
    quesBt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    quesBt->setScale(0.5f);
    quesBt->setPosition(origin);
    quesBt->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onQuestionButton, this));
    this->addChild(quesBt);
    
    //ミュージック選択レイヤー
    _musicSelect = MusicSelect::create();
    this->addChild(_musicSelect);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainUILayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void MainUILayer::update(float delta)
{

}

void MainUILayer::setScoreString(int score,bool isAdd)
{
    auto set = CallFunc::create([this,score](){
        _scoreLb->setString(std::to_string(score));
    });
    
    Action* seq;
    
    if(isAdd){
        auto big = ScaleTo::create(0.2f, 2.0f);
        auto original = ScaleTo::create(0.2f,1.0f);
        seq = Sequence::create(big,set,original, NULL);
    }
    else{
        auto out = FadeOut::create(0.2f);
        auto in = FadeIn::create(0.2f);
        seq = Sequence::create(out,set,in, NULL);
    }
    
    _scoreLb->runAction(seq);
}

bool MainUILayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void MainUILayer::onMusicSelectButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            _musicSelect->setVisible(true);
            _musicSelect->getTouchEventListener()->setSwallowTouches(true);
            break;
            
        default:
            break;
    }
}

void MainUILayer::onRankingButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            Cocos2dExt::NativeCodeLauncher::openRanking();
            break;
            
        default:
            break;
    }
}

void MainUILayer::onQuestionButton(Ref* pSender,ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            getParent()->addChild(TutorialLayer::create(),16);
            break;
            
        default:
            break;
    }
}
