//
//  BattleScene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 4/16/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "BattleScene.h"

BattleScene::BattleScene():
bg(0)
{
    cout << "BattleScene()" << endl;
}

BattleScene::~BattleScene(){
    cout << "~BattleScene()" << endl;
}

void BattleScene::init(){
    bg = new Sprite();
    bg->initSpriteWithTexture("battle scene/battle_scene_bg.png");
    bg->setPosition(glm::vec3(0, 0, 0));
    this->addObject("battleSceneBg", bg);
    
    //create hud layer
    HUD_Layer = new BattleHUDLayer();
    this->addLayer(HUD_Layer);
}

void BattleScene::update(){
    Scene::update();
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

void BattleScene::injectKey(){
    
}

void BattleScene::injectMouseMove(){
    
}

void BattleScene::exit(){
    cout << "BattleScene::init" << endl;
}