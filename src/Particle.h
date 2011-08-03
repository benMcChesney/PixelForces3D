//
//  Particle.h
//  PixelForces
//
//  Created by Ben McChesney on 7/2/11.
//  Copyright 2011 Helios Interactive. All rights reserved.
//
//  A Simple Particle Class

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h" 
#include "ofxVec3f.h"

class Particle
{
    public : 
        Particle() ; 
        Particle( ofxVec3f _position , ofColor _color ) 
        {
            position = _position ; 
            color = _color ; 
            velocity = ofxVec3f ( ofRandom ( -2 , 2 ) , ofRandom ( -2 , 2 ) , ofRandom ( -2 , -2 ) ) ; 
            spawnPoint = _position ; 
        }
    
        ofxVec3f position , velocity ; 
        ofxVec3f acceleration ;          //smoothing applied to velocity
        ofxVec3f spawnPoint ;            //original location to line up the picture
        ofColor color ; 
        
};
#endif