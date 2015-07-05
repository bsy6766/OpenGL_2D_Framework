//
//  Scene.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/26/14.
//  Copyright (c) 2014-2015 Seung Youp Baek. All rights reserved.
//

#include "Scene.h"
#include <GLFW/glfw3.h>

Scene::Scene():
window(0)
{
    cout << "Scene()" << endl;
    spriteManager = new SpriteManager();
    textManager = new TextManager();
}

Scene::~Scene(){
    cout << "~Scene()" << endl;
    exit();
}

void Scene::boundWindow(GLFWwindow *window){
    this->window = window;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    
    prevMousePos = glm::vec2(x, y);
    curMousePos = glm::vec2(x, y);
}

void Scene::update(){
    //update scene stuff first
    spriteManager->update();
    
    //update layers
    for(auto it : layerMap){
        (it.second)->update();
    }
}

void Scene::render(){
    //render scene stuff first
    spriteManager->render();
    textManager->render();
    
    //render layers
    for(auto it : layerMap){
        (it.second)->render();
    }
}

void Scene::run(){
//    Timer::getInstance().recordTime();
    update();
    render();
}

void Scene::addSprite(SpriteObject* childSprite){
    spriteManager->addSprite(childSprite);
}

//void Scene::addText(TextObject* childText){
void Scene::addText(Text* text){
    textManager->addText(text);
}

void Scene::addLayer(Layer *childLayer){
//    int layerMapSize = layerMap.size();
    layerMap.insert(std::pair<int, Layer*>(childLayer->getZorder(), childLayer));
}

void Scene::exit(){
    delete spriteManager;
    delete textManager;
    
    for(auto it : layerMap){
        delete it.second;
    }
}
