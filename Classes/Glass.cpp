//
//  Glass.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#include "Common.h"

USING_NS_CC;

bool Glass::init()
{
    if(!Sprite::initWithFile("Textures/Glass.png"))
        return false;
    
    this->scheduleUpdate();
    
    _flickTime = 0;
    _isAddForce = false;
    _isGround = false;
    
    auto mat = PHYSICSBODY_MATERIAL_DEFAULT;
    mat.restitution = 0.0f;
    mat.friction = FRICTION;
    
    auto ownSize = getContentSize();
    
    auto pb = PhysicsBody::createBox(ownSize,mat);
    pb->setMass(1.0f);
    pb->setRotationEnable(false);
    pb->setDynamic(true);
    pb->setContactTestBitmask(0x0001);
    setPhysicsBody(pb);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Glass::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Glass::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Glass::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Glass::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void Glass::update(float delta)
{
    auto pb = getPhysicsBody();
    auto parent = dynamic_cast<MainScene*>(getParent());
    
    //y軸のベロシティが０を超えた場合
    //y軸のベロシティを０にする
    if(pb->getVelocity().y > 0)
        pb->setVelocity(Vec2(pb->getVelocity().x,0));
    
    //グラスがほぼ静止した場合の処理
    if(pb->getVelocity().length() <= 0.1f && _isAddForce)
    {
        auto customer = parent->getCustomoer();
        //止めるべき場所に停められたかの判定
        if(customer->Judge())
        {
            //高得点エリアに止めることができた
            if(customer->judgeSpecialArea())
            {
                SimpleAudioEngine::getInstance()->playEffect("Audio/Voice/Excellent.mp3");
                parent->addScore(10);
            }
            //高得点エリアではないけど止められた場合
            else
            {
                //ボイスを再生
                int vcId = random(0, 3);
                SimpleAudioEngine::getInstance()->playEffect(VC_GOOD[vcId].c_str());
                parent->addScore(1);
            }
        }
        //止めることができなかった
        else
        {
            SimpleAudioEngine::getInstance()->playEffect("Audio/Voice/Oops.mp3");
            parent->resetScore();
        }
        reset();
    }
    
    //画面左端より左に行ってしまったらグラスが割れる
    if(getPositionY() < Director::getInstance()->getVisibleOrigin().y){
        SimpleAudioEngine::getInstance()->playEffect("Audio/SE/glass_break.mp3");
        auto delay = DelayTime::create(0.5f);
        auto se = CallFunc::create([](){
            SimpleAudioEngine::getInstance()->playEffect("Audio/Voice/OhMan.mp3");
        });
        auto seq = Sequence::create(delay,se, NULL);
        this->runAction(seq);
        reset();
        
        parent->resetScore();
    }
}

bool Glass::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    _flickTime = 0;
    return true;
}

void Glass::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    float delta = Director::getInstance()->getDeltaTime();
    _flickTime += delta;
}

void Glass::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //グラススライド処理
    if(_flickTime <= FLICK_TIME && !_isAddForce && _isGround)
    {
        float slideLen = touch->getStartLocation().x - touch->getLocation().x;
        
        //フリックした長さが短い場合は力を加えない
        float minLength = 100.0f;
        if(slideLen <= minLength || slideLen < 0)
            return;
        
        float power = (slideLen) * SLIDE_POWER;
        
        float speed = 1.0f / ((1.0f-FLICK_TIME)+_flickTime);
        
        Vec2 dir = Vec2(-1,0);
        
        auto pb = getPhysicsBody();
        pb->applyForce(dir*power*speed);
        SimpleAudioEngine::getInstance()->playEffect("Audio/SE/GlassSlide.mp3");
        
        //時間を置いてから_isAddForceをtrueにする
        //理由は滑り始めの速度が遅い時に判定されるのを防ぐため
        auto wait = DelayTime::create(0.1f);
        auto func = CallFunc::create([&](){_isAddForce = true;});
        auto seq = Sequence::create(wait,func, NULL);
        this->runAction(seq);

    }
}

bool Glass::onContactBegin(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto own = dynamic_cast<Glass*>(nodeA);
    if(!own){
        own = dynamic_cast<Glass*>(nodeB);
    }
    
    auto floor = dynamic_cast<PhysicsArea*>(nodeA);
    if(!floor){
        floor = dynamic_cast<PhysicsArea*>(nodeB);
    }
    
    if(!floor || own != this)
        return true;
    
    //グラスが机に着地した時にサウンドを再生
    if(!_isGround){
        _isGround = true;
        SimpleAudioEngine::getInstance()->playEffect("Audio/SE/glassTakeOn.mp3");
    }
    
    return true;
}

void Glass::reset()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    _isAddForce = false;
    _isGround = false;
    getPhysicsBody()->setVelocity(Vec2::ZERO);
    setPosition(origin + GLASS_FIRST_POS);
}
