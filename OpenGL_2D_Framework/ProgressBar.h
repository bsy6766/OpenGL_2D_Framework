//
//  ProgressBar.h
//  OpenGL_2D_Framework
//
//  Created by Seung Youp Baek on 1/23/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#ifndef __OpenGL_2D_Framework__ProgressBar__
#define __OpenGL_2D_Framework__ProgressBar__

#include "ProgressObject.h"

/**
 *  @class ProgressBar
 *  @brief Textured progress bar
 */
class ProgressBar: public Volt2D::ProgressObject{
private:
    //private constructor
    ProgressBar();
    
    /**
     *  Initialize ProgressBar
     *  @param textureTarget GL_TEXTURE_2D
     */
    void initProgressBar(const std::string barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
public:
    /**
     *  Create ProgressBar
     *  @param objectName An object name for ProgressBar
     *  @param barTextureName Texture file name 
     *  @param textureTarget GL_TEXTURE_2D
     */
    static ProgressBar* createProgressBar(std::string objectName, const char* barTextureName, GLenum textureTarget = GL_TEXTURE_2D);
    
    //Destructor
    ~ProgressBar();
    
    /**
     *  Compute vertex and indices
     */
    void computeVertexData();
    
    /**
     *  Load computed vertex.
     */
    void loadVertexData();
    
    /**
     *  Overrides's Object::render();
     *  Render object
     */
    virtual void render() override;
};

#endif /* defined(__OpenGL_2D_Framework__ProgressBar__) */
