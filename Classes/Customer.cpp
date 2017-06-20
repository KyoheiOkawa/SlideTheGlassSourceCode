//
//  Customer.cpp
//  SlideTheGlass
//
//  Created by 大川恭平 on 2017/05/01.
//
//

#include "Common.h"

USING_NS_CC;

bool Customer::init()
{
    if(!Node::init())
        return false;
    
    this->scheduleUpdate();
    
    _judgeArea = Sprite::create();
    _judgeArea->setTextureRect(Rect(0,0,_acceptWidth,90));
    _judgeArea->setColor(Color3B(66, 244, 119));
    _judgeArea->setOpacity(100);
    this->addChild(_judgeArea);
    
    _specialArea = Sprite::create();
    _specialArea->setTextureRect(Rect(0,0,SPECIAL_AREA_WIDTH,90));
    _specialArea->setColor(Color3B::YELLOW);
    _specialArea->setOpacity(0);
    this->addChild(_specialArea);
    
    return true;
}

void Customer::update(float delta)
{
    //グラスが判定エリア内にあるときは
    //判定エリアのスプライトを赤にする
    if(Judge()){
        _judgeArea->setColor(Color3B::RED);
    }
    else{
        _judgeArea->setColor(Color3B(66, 244, 119));
    }
}

bool Customer::Judge()
{
    auto glass = dynamic_cast<MainScene*>(getParent())->getGlass();
    bool result = false;
    
    Vec2 glassPos = glass->getPosition();
    float glassWidthHalf = glass->getContentSize().width / 2.0f;
    
    float left = glassPos.x - glassWidthHalf;
    float right = glassPos.x + glassWidthHalf;
    
    Vec2 ownPos = getPosition();
    float ownLeft = ownPos.x - (_acceptWidth / 2.0f);
    float ownRight = ownPos.x + (_acceptWidth / 2.0f);
    
    
    if  ((left <= ownRight       && left >= ownLeft)          ||
        ((right >= ownLeft       &&  right <= ownRight)       ||
         (glassPos.x >= ownLeft  && glassPos.x <= ownRight)   ||
         (ownLeft >= left        && ownLeft <= right)         ||
         (ownRight >= left       && ownRight <= right))
       ){
           
           result = true;
       }
    
    return result;
}

void Customer::changeJudgeAreaWidth()
{
    auto parent = dynamic_cast<MainScene*>(getParent());
    auto score = parent->getScore();
    
    float width = (1 / ((1 / (JUDGE_MAX_WIDTH - JUDGE_MIN_WIDTH)) + (score/SHRINK_DEGREE))) + JUDGE_MIN_WIDTH;
    
    _acceptWidth = width;
    _judgeArea->setTextureRect(Rect(0,0,_acceptWidth,90));
}

void Customer::changePosition()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    float min = origin.x + (_acceptWidth / 2.0f);
    float max = GLASS_FIRST_POS.x - 100 - (_acceptWidth / 2.0f);
    
    Vec2 nextPos = Vec2(random(min, max),getPositionY());
    
    auto move = MoveTo::create(0.5f, nextPos);
    this->runAction(move);
}

void Customer::setSpecialArea(int score)
{
    if((score % 5 == 0) && (score != 0))
    {
        _specialArea->setOpacity(100);
        
        Vec2 ownPos = this->getPosition();
        
        float min = -(_acceptWidth/2.0f) + (SPECIAL_AREA_WIDTH/2.0f);
        float max = (_acceptWidth/2.0f) - (SPECIAL_AREA_WIDTH/2.0f);
        
        Vec2 pos = Vec2(random(min, max),
                        _specialArea->getPosition().y);
        _specialArea->setPosition(pos);
    }
    else
    {
        _specialArea->setOpacity(0);
    }
}

bool Customer::judgeSpecialArea()
{
    
    auto glass = dynamic_cast<MainScene*>(getParent())->getGlass();
    bool result = false;
    
    auto parent = dynamic_cast<MainScene*>(getParent());
    auto score = parent->getScore();
    
    if((score % 5 == 0) && (score != 0))
    {
        Vec2 glassPos = glass->getPosition();
        float glassWidthHalf = glass->getContentSize().width / 2.0f;
        
        float left = glassPos.x - glassWidthHalf;
        float right = glassPos.x + glassWidthHalf;
        
        Vec2 ownPos = getPosition() + _specialArea->getPosition();
        float ownLeft = ownPos.x - (SPECIAL_AREA_WIDTH / 2.0f);
        float ownRight = ownPos.x + (SPECIAL_AREA_WIDTH / 2.0f);
        
        
        if ((left <= ownRight       &&  left >= ownLeft)        ||
            ((right >= ownLeft      &&  right <= ownRight)      ||
            (glassPos.x >= ownLeft  &&  glassPos.x <= ownRight) ||
            (ownLeft >= left        &&  ownLeft <= right)       ||
            (ownRight >= left       &&  ownRight <= right))
           ){
               
               auto particle = ParticleSystemQuad::create("Particles/excellent.plist");
               particle->setAutoRemoveOnFinish(true);
               particle->resetSystem();
               particle->setPosition(getPosition());
               parent->addChild(particle,12);
               
               result = true;
           }
    }
    
    return result;
}






