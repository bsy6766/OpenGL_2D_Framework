//
//  BattleScene.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BattleScene.h"

using namespace Volt2D;

BattleScene::BattleScene():
bg(0)
{
    cout << "BattleScene()" << endl;
}

BattleScene::~BattleScene(){
    cout << "~BattleScene()" << endl;
}

void BattleScene::init(){
    bg = Sprite::create("battleSceneBg", "battle scene/battle_scene_bg.png");
    bg->setPosition(glm::vec3(0, 0, 0));
    this->addChild(bg);
    
    playerFieldSlot = Sprite::create("playerFieldSlot", "battle scene/field_slot.png");
    playerFieldSlot->setOpacity(50);
    playerFieldSlot->setPosition(glm::vec3(-360, 0, 0));
    this->addChild(playerFieldSlot);
    
    enemyFieldSlot = Sprite::create("enemyFieldSlot", "battle scene/field_slot.png");
    enemyFieldSlot->setOpacity(50);
    enemyFieldSlot->setPosition(glm::vec3(360, 0, 0));
    this->addChild(enemyFieldSlot);
    
    //create hud layer
    HUD_Layer = new BattleHUDLayer(); 
    this->addChild(HUD_Layer);
}

void BattleScene::onEnter(){
    
}

void BattleScene::update(double dt){
    Scene::update(dt);
}

//void BattleScene::keyPressed(int key, int mods){
//    
//}
//
//void BattleScene::keyReleased(int key, int mods){
//    
//}
//
//void BattleScene::mouseButton(double x, double y, int button, int action){
//
//}
//
//void BattleScene::mouseMove(double x, double y){
//
//}

void BattleScene::exit(){
    cout << "BattleScene::init" << endl;
}