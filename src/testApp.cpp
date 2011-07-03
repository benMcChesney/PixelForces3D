#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground ( 0 , 0 , 0 ) ;
    image.loadImage( "grandTetons_small.jpg" ) ; 

    sampling = 2 ; 

    unsigned char * pixels = image.getPixels();
    int w = image.width ; 
    int h = image.height ; 
    int xOffset = (ofGetWidth() - image.width) /2 ; 
    int yOffset = (ofGetHeight() - image.height) /2 ; 
    for ( int x = 0; x < w ; x+=sampling )
    {
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
            int index = (y * w + x) * 3;
            ofColor color ; 
            color.r = pixels[index] ; 
            color.g = pixels[index+1] ; 
            color.b = pixels[index+2] ; 
            particles.push_back( Particle( ofPoint( x + xOffset , y + yOffset ) , color ) );
        }
    }
    
    numParticles = ( image.width * image.height ) / sampling ; 

    ofSetFrameRate(30) ;
    
    //Set spring and sink values
    cursorMode = 0 ; 
    forceRadius = 45 ; 
    velocityDampingFactor = 0.85 ; 
    springConstant = 0.12 ; 
    springEnabled = true ; 
    
}

//--------------------------------------------------------------
void testApp::update(){

    ofxVec2f diff ;
    float dist , ratio ;
    const ofPoint mousePosition = ofxVec2f( mouseX , mouseY ) ; 
    
    std::vector<Particle>::iterator p ;
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    {
       
        ratio = 1.0f ; 
        p->velocity *= velocityDampingFactor ; 
        p->acceleration = ofPoint() ; 
        diff = mousePosition - p->position ;  
        dist = ofDist( 0 , 0 , diff.x , diff.y ) ;
        if ( dist < forceRadius )  
        {
            ratio = -1 + dist / forceRadius ; 
            //Repulsion
            if ( cursorMode == 0 ) 
                p->acceleration -= ( diff * ratio) ;
            //Attraction
            else
                p->acceleration += ( diff * ratio ) ; 
        }
        if ( springEnabled ) 
        {
            //Move back to the original position
            p->acceleration += springConstant * (p->spawnPoint - p->position) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 


    }
    
  }

//--------------------------------------------------------------
void testApp::draw(){
    
    ofEnableSmoothing() ; 
    glBegin(GL_POINTS);

    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    {
        glColor3ub((unsigned char)p->color.r,(unsigned char)p->color.g,(unsigned char)p->color.b);
        glVertex3f(p->position.x, p->position.y , 0 );
    }
    
    glEnd();
    
    ofSetColor ( 255 , 255 , 255 ) ; 
    
    string output = "S :: Springs on/off : " + ofToString(springEnabled) + 
                    "\n C :: CursorMode repel/attract " + ofToString( cursorMode ) +
                    "\n # of particles : " + ofToString( numParticles ) +
                    " \n fps:" +ofToString( ofGetFrameRate() ) ;  ; 
	ofDrawBitmapString(output ,20,666);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch ( key ) 
    {
        case 'c':
        case 'C':
            cursorMode = ( cursorMode + 1 > 1 ) ? 0 : 1 ; 
            break ; 
            
        case 's':
        case 'S':
            springEnabled = !springEnabled ; 
            break ; 
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

