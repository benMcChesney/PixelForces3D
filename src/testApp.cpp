#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    //Set the background to black
    ofBackground( 0 , 0 , 0 ) ; 
    //load our image inside bin/data
    image.loadImage ( "grandTetons_small.jpg" ) ; 
    //if the app performs slowly raise this number
    sampling = 2 ; 
    
    //Retrieve the pixels from the loaded image
    unsigned char * pixels = image.getPixels() ;
    //store width and height for optimization and clarity
    int w = image.width ; 
    int h = image.height ; 
    
    //offsets to center the particle son screen
    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling ) 
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 3 ; 
            ofColor color ; 
            color.r = pixels[index] ;       //red pixel
            color.g = pixels[index+1] ;     //blue pixel
            color.b = pixels[index+2] ;     //green pixel
            particles.push_back( Particle ( ofPoint ( x + xOffset , y + yOffset ) , color ) ) ;  
        }
    }
    
    ofSetFrameRate( 30 ) ; 
    numParticles = ( image.width * image.height ) / sampling ; 
    
    //Set spring and sink values
    cursorMode = 0 ; 
    forceRadius = 45 ; 
    friction = 0.85 ; 
    springFactor = 0.12 ; 
    springEnabled = true ; 
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofPoint diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofPoint mousePosition = ofPoint( mouseX , mouseY ) ; //Allocate and retrieve mouse values once.

    
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofPoint() ; 
        diff = mousePosition - p->position ;  
        dist = ofDist( 0 , 0 , diff.x , diff.y ) ;
        //If within the zone of interaction
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
            p->acceleration.x += springFactor * (p->spawnPoint.x - p->position.x);
            p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
    }
}

//--------------------------------------------------------------
void testApp::draw() {
   
    //Begin the openGL Drawing Mode
    glBegin(GL_POINTS);
    
    //Triangles look Cool too 
    //glBegin(GL_TRIANGLES);

    //Create an iterator to cycle through the vector
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
    
    " \n fps:" +ofToString( ofGetFrameRate() ) ;
    
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

