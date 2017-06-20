//
//  MusicSelect.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/04.
//
//

#include "Common.h"

USING_NS_CC;

bool MusicSelect::init()
{
    if(!LayerColor::initWithColor(Color4B(0,0,0,150)))
        return false;
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    float offset = 10.0f;
    
    //真ん中上に配置するラベル
    auto musicSelect = Label::createWithTTF("MusicSelect", USE_FONT_PATH, 64);
    musicSelect->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    musicSelect->setPosition(origin + Vec2(vs.width/2.0f,vs.height - offset));
    this->addChild(musicSelect);
    
    //レイヤーを閉じる（非表示にする）ボタン
    auto batsuBt = ui::Button::create("Textures/batsu.png");
    batsuBt->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    batsuBt->setPosition(origin + Vec2(vs.width-offset,vs.height-offset));
    batsuBt->addTouchEventListener(CC_CALLBACK_2(MusicSelect::onBatsuButton, this));
    this->addChild(batsuBt);
    
    //MusMus様のHPのURLを開くボタン
    auto musmusBt = ui::Button::create("Textures/MusMus.png");
    musmusBt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    musmusBt->setPosition(origin + Vec2(offset,offset));
    musmusBt->setScale(0.8f);
    musmusBt->addTouchEventListener(CC_CALLBACK_2(MusicSelect::onMusMusButton, this));
    this->addChild(musmusBt);
    
    //------------------------------------------------------------
    //スクロールビューの作成
    auto scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(true);
    scrollView->setPosition(origin+Vec2((vs.width-700)/2.0f,0));
    this->addChild(scrollView);
    
    auto selectLayer = LayerColor::create(Color4B(0,0,0,200), 700, 63*BGM_COUNT+offset*2*(BGM_COUNT+1));
    selectLayer->setPosition(Vec2::ZERO);
    
    auto selectLayerSz = selectLayer->getContentSize();
    
    for(int i = 0; i < BGM_COUNT; ++i)
    {
        auto bt = ui::Button::create("Textures/frame.png");
        bt->setName(BGM_NAME[i]);
        bt->setSwallowTouches(false);
        bt->addClickEventListener(CC_CALLBACK_1(MusicSelect::musicChange, this));
        bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
        bt->setPosition(origin+Vec2(selectLayerSz.width/2.0f,selectLayerSz.height - offset * 2 - bt->getContentSize().height * i - offset * 2 * i));
        
        auto lb = Label::createWithTTF(BGM_NAME[i], USE_FONT_PATH, 42);
        lb->setPosition(bt->getContentSize()/2.0f);
        bt->addChild(lb);
        
        selectLayer->addChild(bt);
    }
    
    scrollView->addChild(selectLayer);
    scrollView->setInnerContainerSize(selectLayer->getContentSize());
    scrollView->setContentSize(Size(700,vs.height-musicSelect->getContentSize().height - offset));
    //------------------------------------------------------------
    
    this->setVisible(false);
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(MusicSelect::onTouchBegan, this);
    _touchListener->setSwallowTouches(false);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    return true;
}

bool MusicSelect::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void MusicSelect::onBatsuButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            this->setVisible(false);
            _touchListener->setSwallowTouches(false);
            break;
            
        default:
            break;
    }
}

void MusicSelect::onMusMusButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            Application::getInstance()->openURL("http://musmus.main.jp/");
            break;
            
        default:
            break;
    }
}

void MusicSelect::musicChange(Ref* pSender)
{
    auto bt = (ui::Button*)pSender;
    float distance = bt->getTouchBeganPosition().distance(bt->getTouchEndPosition());
    if(10 > distance){
        auto audio = SimpleAudioEngine::getInstance();
        
        audio->stopBackgroundMusic(true);
        std::string music = BGM + '/' + bt->getName() + ".mp3";
        audio->playBackgroundMusic(music.c_str(),true);
    }
}
