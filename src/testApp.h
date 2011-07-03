#ifndef _TEST_APP
#define _TEST_APP

/*
 Created by Ben McChesney 2011
 
 Based off of the example from FlashAndMath.com @ www.flashandmath.com/advanced/rgbsinks/index.html
 Big thanks to them for releasing their example.
 
 Feel free to use this code but please acknowledge where you recieved it from 
*/
#include "ofMain.h"
#include "Particle.h"

class testApp : public ofBaseApp
{

	public:
    
        ofImage image ; 
    
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
    
        vector<Particle> particles; 
        int sampling ;              // # of pixels to skip
        int cursorMode ;            // attract or repel
        int numParticles ; 
        bool springEnabled ;        //toggle whether particles return to their origin
    
        //Spring and Sink Factors
        float forceRadius , velocityDampingFactor, springConstant ; 

};

#endif
