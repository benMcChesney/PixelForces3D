//
//  Particle.h
//  ImageBreak
//
//  Created by Ben McChesney on 7/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#ifndef _PARTICLE
#define _PARTICLE


#include "ofMain.h" 
#include "ofxVec2f.h"

class Particle
{
    public :
    
        Particle() ; 
        Particle( ofPoint _position , ofColor _color ) 
        {
            position = _position ; 
            color = _color ; 
            spawnPoint = _position ; 
        }
        
        ofPoint position, velocity, acceleration, spawnPoint ;
        ofColor color ;  
    
};

#endif