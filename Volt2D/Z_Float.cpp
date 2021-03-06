//
//  Z_Float.cpp
//  Volt2D
//
//  Created by Seung Youp Baek on 7/9/15.
//  Copyright (c) 2015 Seung Youp Baek. All rights reserved.
//

#include "Z_Float.h"

using namespace Volt2D;

Z_Float::Z_Float():
z(0),
dirty(false)
{
    
}

void Z_Float::setZ(float z){
    this->z = z;
    this->dirty = true;
}

bool Z_Float::getZ(float& z){
    if(dirty){
        z = this->z;
        return true;
    }
    else{
        return false;
    }
}

bool Z_Float::isValid(){
    return this->dirty;
}