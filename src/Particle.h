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

class Particle
{
    public : 
        Particle() ; 
        Particle( ofPoint _position , ofColor _color ) 
        {
            position = _position ; 
            color = _color ; 
            velocity = ofPoint ( ofRandom ( -5 , 5 ) , ofRandom ( -5 , 5 ) ) ; 
            spawnPoint = _position ; 
        }
    
        ofPoint position , velocity ; 
        ofPoint acceleration ;          //smoothing applied to velocity
        ofPoint spawnPoint ;            //original location to line up the picture
        ofColor color ; 
};
#endif