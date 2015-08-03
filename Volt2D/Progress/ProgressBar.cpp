//
//  ProgressBar.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "ProgressBar.h"
#include "Director.h"

ProgressBar::ProgressBar():
ProgressObject()
{
    cout << "Creating Progress Bar" << endl;
}

ProgressBar::~ProgressBar(){
    cout << "Deleting Progress Bar" << endl;
}

ProgressBar* ProgressBar::createProgressBar(std::string objectName, const char *barTextureName, GLenum textureTarget){
    ProgressBar* newProgressBar = new ProgressBar();
    newProgressBar->initProgressBar(barTextureName);
    newProgressBar->setName(objectName);
    return newProgressBar;
}

void ProgressBar::initProgressBar(const std::string barTextureName, GLenum textureTarget){
    cout << "init progress bar with texture with path of " << barTextureName << endl;
    std::string textureDir = Volt2D::Director::getInstance().getWorkingDir() + "/../Texture/";
    this->texture = Volt2D::Texture::createTextureWithFile(barTextureName, textureTarget);
    texture->getImageSize(w, h);
    
    computeVertexData();
    loadVertexData();
    
    this->boundingBox = new Volt2D::BoundingBox(-this->w/2, -this->h/2, this->w/2, this->h/2);
}

void ProgressBar::computeVertexData(){
    this->Object::scaledWidth = w / Volt2D::SCREEN_TO_WORLD_SCALE;
    this->Object::scaledHeight = h / Volt2D::SCREEN_TO_WORLD_SCALE;
    
    float width = this->scaledWidth;
    float height = this->scaledHeight;
    
    /*
     
     Quad
     Vertex								UV coordinate
					(width, height)						(1,1)
     *------------*						*------------*
     |		     |						|			 |
     |			 |						|			 |
     |	 		 |						|			 |
     |			 |					  v	|			 |
     *------------*						*------------*
     (0,0)								(0,0)   u
     
     */
    
    int totalQuadNum = this->totalPercentage / this->percentageRate;
    
    float stepWidth = width / totalQuadNum;
    float startingWidth = -(width/2);
    float textureStepWidth = 1.0f / totalQuadNum;
    
    for(int i = 0; i<totalQuadNum; i++){
        vertexData.push_back(glm::vec3(startingWidth + (i * stepWidth), -(height/2), Volt2D::GLOBAL_Z_VALUE));	//bot left
        vertexData.push_back(glm::vec3(startingWidth + (i * stepWidth), height/2, Volt2D::GLOBAL_Z_VALUE));		//top left
        vertexData.push_back(glm::vec3(startingWidth + ((i+1) * stepWidth), -(height/2), Volt2D::GLOBAL_Z_VALUE));		//bot right
        vertexData.push_back(glm::vec3(startingWidth + ((i+1) * stepWidth), height/2, Volt2D::GLOBAL_Z_VALUE));			//top right
        
        //texture
        uvVertexData.push_back(glm::vec2(i * textureStepWidth, 0));	//bot left
        uvVertexData.push_back(glm::vec2(i * textureStepWidth, 1));	//top left
        uvVertexData.push_back(glm::vec2((i+1) * textureStepWidth, 0));	//bot right
        uvVertexData.push_back(glm::vec2((i+1) * textureStepWidth, 1));	//top right
        
        //indices
        indicesData.push_back(i * 4);
        indicesData.push_back(i * 4 + 1);
        indicesData.push_back(i * 4 + 2);
        indicesData.push_back(i * 4 + 1);
        indicesData.push_back(i * 4 + 2);
        indicesData.push_back(i * 4 + 3);
    }
}

void ProgressBar::loadVertexData(){
    //generate vertex array object and bind it
    glGenVertexArrays(1, &this->bufferObject.vao);
    glBindVertexArray(this->bufferObject.vao);
    
    //generate vertex buffer object for quad
    glGenBuffers(1, &this->bufferObject.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate texture uv buffer object for quad
    glGenBuffers(1, &this->bufferObject.uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->bufferObject.uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvVertexData.size(), &uvVertexData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(progPtr->attrib("uvVert"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //generate indices buffer
    glGenBuffers(1, &this->bufferObject.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferObject.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesData.size(), &indicesData[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void ProgressBar::render(){    
    glUseProgram(progPtr->getObject());
    
    const glm::mat4 cameraMat = Volt2D::Director::getInstance().getProjectiveViewMatrix();
    matrixUniformLocation("cameraMat", cameraMat);
    
    glm::mat4 parentMat;
    if(this->parent){
        parentMat = this->parent->getTransformMat();
    }
    
    matrixUniformLocation("parentMat", parentMat);
    matrixUniformLocation("modelMat", modelMat);
    matrixUniformLocation("rotateMat", rotateMat);
    matrixUniformLocation("translateMat", translateMat);
    matrixUniformLocation("scaleMat", scaleMat);
    floatUniformLocation("opacity", opacity);
    
    glBindVertexArray(this->bufferObject.vao);
    
    glEnableVertexAttribArray(progPtr->attrib("vert"));
    glEnableVertexAttribArray(progPtr->attrib("uvVert"));
    
    this->texture->bind(GL_TEXTURE0);
    
    for(int i = 0; i<this->currentPercentage; i+=this->percentageRate){
        glDrawRangeElements(
                            GL_TRIANGLES/*Rendering mode. draw 2 triangles for 1 quad*/,
                            //index * 0/*start*/,
                            //index * 0/*end*/,
                            //Not sure what start and end do. Gonna try static number
                            0/*start*/,
                            6/*end*/,
                            6/*Count. Number of elements to be rendered. Single quad contains 6 vertexes.*/,
                            GL_UNSIGNED_SHORT/*indices type*/,
                            VOID_OFFSET(i * 6 * sizeof(GLushort))/*offset of each char(6 vertexes)*/
                            );
    }
    
    glBindVertexArray(0);
    glUseProgram(0);
}
