//
//  Sprite.cpp
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 11/7/14.
//  Copyright (c) 2014 Seung Youp Baek. All rights reserved.
//

#include <iostream>

#include "Sprite.h"
#include <cmath>

Sprite::Sprite()
        :SpriteObject(){
    spriteID = ID_COUNTER;
    ID_COUNTER++;
    texture = 0;

    std::cout << "Sprite created with ID#" << spriteID << std::endl;
}

Sprite::Sprite(Program *ptr)
        :SpriteObject(ptr){
    texture = 0 ;
}

Sprite::~Sprite(){
    spriteID = -1;
    GLuint textureObj = texture->getObject();
    glDeleteTextures(1, &textureObj);
    if(texture)
        delete texture;
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &uvbo);
    glDeleteBuffers(1, &ibo);
    
    for (std::list<SpriteActionSchedule *>::const_iterator ci = spriteActionScheduleList.begin(); ci != spriteActionScheduleList.end(); ++ci){
        delete (*ci);
    }
    
    actionRunning = false;
    
    std::cout << "Sprite deleted" << std::endl;
}

void Sprite::initSpriteWithTexture(GLenum _textureTarget, const std::string& _fileName){
    std::cout << "init sprite with texture with path of " << _fileName << std::endl;
    texture = new Texture(_textureTarget, _fileName);
    texture->load(progPtr->getObject());
    texture->getImageSize(w, h);

    position = glm::vec2(640, 360);
    z = GLOBAL_Z_VALUE;
    
    createVertexData();
    loadVertexData();
    
    boundingBox.x = vertexData.at(0).x;
    boundingBox.y = vertexData.at(0).y;
    boundingBox.w = w;
    boundingBox.h = h;
}

void Sprite::render(){
    if(visible){
        texture->bind(GL_TEXTURE0);
        
        GLint modelUniformLocation = glGetUniformLocation(progPtr->getObject(), "modelMat");
        if(modelUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "modelMat");
        if(actionRunning)
            updateFromSpriteAction();
        updateMatrix();
        glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &modelMat[0][0]);
        
        GLint opacityUniformLocation = glGetUniformLocation(progPtr->getObject(), "opacity");
        if(opacityUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
        glUniform1fv(opacityUniformLocation, 1, &opacity);
        
        GLint particleUniformLocation = glGetUniformLocation(progPtr->getObject(), "particle");
        if(particleUniformLocation == -1)
            throw std::runtime_error( std::string("Program uniform not found: " ) + "opacity");
        glUniform1i(particleUniformLocation, 0);
            
        //bind vertex array.
        glBindVertexArray(vao);
        
        //enable attribs
        glEnableVertexAttribArray(progPtr->attrib("vert"));
        glEnableVertexAttribArray(progPtr->attrib("uvVert"));
        
        //draw based on indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    }
}

void Sprite::updateMatrix(){
    glm::mat4 result = glm::mat4();
    translateMat = glm::translate(glm::mat4(), glm::vec3((position.x - 640) / 10, (position.y - 360) / 10, 0));
    rotateMat = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));
    scaleMat = glm::mat4();
    modelMat = result * translateMat * rotateMat * scaleMat;
}

void Sprite::createVertexData(){
    float width = (float)w / SCREEN_TO_WORLD_SCALE;
    float height = (float)h / SCREEN_TO_WORLD_SCALE;
    
    vertexData.push_back(glm::vec3(-(width/2), -(height/2), GLOBAL_Z_VALUE));
    vertexData.push_back(glm::vec3(-(width/2), height/2, GLOBAL_Z_VALUE));
    vertexData.push_back(glm::vec3(width/2, -(height/2), GLOBAL_Z_VALUE));
    vertexData.push_back(glm::vec3(width/2, height/2, GLOBAL_Z_VALUE));
    
    uvVertexData.push_back(glm::vec2(0, 0));
    uvVertexData.push_back(glm::vec2(0, 1));
    uvVertexData.push_back(glm::vec2(1, 0));
    uvVertexData.push_back(glm::vec2(1, 1));
    
    indicesData.push_back(0);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(1);
    indicesData.push_back(2);
    indicesData.push_back(3);
}

void Sprite::loadVertexData(){
    //generate vertex array object and bind it
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}