//
//  TutorialLayer.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/10.
//
//

#include "Common.h"

USING_NS_CC;

bool TutorialLayer::init()
{
    if(!LayerColor::initWithColor(Color4B(0,0,0,150)))
        return false;
    
    _touchNum = 0;
    _isNowSlide = false;
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    auto textureCache = Director::getInstance()->getTextureCache();
    _slideTx[0] = textureCache->addImage("Textures/tutorial-1.png");
    _slideTx[1] = textureCache->addImage("Textures/tutorial-2.png");
    _slideTx[2] = textureCache->addImage("Textures/tutorial-3.png");
    
    _slide = Sprite::createWithTexture(_slideTx[0]);
    _slide->setPosition(origin+vs/2.0f);
    this->addChild(_slide);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TutorialLayer::onTouchEnded, this);
    touchListener->setSwallowTouches(true);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool TutorialLayer::onTouchBegan(Touch* touch,Event* event)
{
    return true;
}

void TutorialLayer::onTouchEnded(Touch* touch,Event* event)
{
    //前回のスライドのフェードアウトが終了していたら
    if(!_isNowSlide)
    {
        _touchNum++;
        
        //全てのスライドの表示が終わったら
        //このレイヤーを破棄する
        if(_touchNum >= MAX_SLIDES){
            _isNowSlide = true;
            
            auto textureCache = Director::getInstance()->getTextureCache();
            
            for(int i = 0; i < MAX_SLIDES; i++){
                textureCache->removeTexture(_slideTx[i]);
            }
            
            auto out = FadeOut::create(0.5f);
            auto remove = CallFunc::create([this](){
                removeFromParentAndCleanup(true);
            });
            auto seq = Sequence::create(out,remove, NULL);
            
            this->runAction(seq);
            
            return;
        }
        
        runSlideAction();
    }
}

void TutorialLayer::runSlideAction()
{
    _isNowSlide = true;
    auto out = FadeOut::create(0.5f);
    auto setTex = CallFunc::create([this](){
        _slide->setTexture(_slideTx[_touchNum]);
    });
    auto in = FadeIn::create(0.5f);
    auto setBool = CallFunc::create([this](){
        _isNowSlide = false;
    });
    auto seq = Sequence::create(out,setTex,in,setBool, NULL);
    _slide->runAction(seq);
}
