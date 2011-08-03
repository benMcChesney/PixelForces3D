#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    //Set the background to black
    ofBackground( 0 , 0 , 0 ) ; 
    //load our image inside bin/data
    image.loadImage ( "images/text.png" ) ;
    image2.loadImage ( "images/smileyFace.png" ) ; 
    //if the app performs slowly raise this number
    sampling = 1 ; 
    curImageIndex = 0 ; 
    
    //Retrieve the pixels from the loaded image
    unsigned char * pixels = image.getPixels() ;
    //store width and height for optimization and clarity
    int w = image.width ; 
    int h = image.height ; 
    
    //offsets to center the particle son screen
    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    numParticles= 0 ; 
    
    r = ofRandom ( 45 , 255 ) ; 
    g = ofRandom ( 45 , 255 ) ; 
    b = ofRandom ( 45 , 255 ) ; 
    
    ofxVec3f origin ( ofGetWidth() /2 , ofGetWidth() /2 , 0 ) ; 
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling ) 
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 4 ; 
            ofColor color ; 
            if ( pixels[index+3] > 0 ) 
            {
                color.r = r ; //pixels[index+0] ;       //red pixel
                color.g = g ; //pixels[index+1] ;     //blue pixel
                color.b = b ; //pixels[index+2] ;     //green pixel
                ofxVec3f spawnPoint = ofPoint ( x + xOffset , y + yOffset , ofRandom ( -400, 400 ) ) ;
//                spawnPoint.z =  ; //origin.distance ( spawnPoint )  * 200.0f ; 
                particles.push_back( Particle ( spawnPoint , color ) ) ; 
                numParticles++ ; 
            }
        }
    }
    
    ofSetFrameRate( 30 ) ; 
  //  numParticles = ( image.width * image.height ) / sampling ; 
    
    //Set spring and sink values
    cursorMode = 0 ; 
    forceRadius = 45 ; 
    friction = 0.85 ; 
    springFactor = 0.12 ; 
    springEnabled = true ; 
   
    //setup openGL
    ofSetFrameRate(30) ;
    ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);
	ofSetVerticalSync(false);

    
    // enable depth testing
	glEnable(GL_DEPTH_TEST);
	
	// select normal blend mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// preallocate space for 5000 vertices.
	myObj.reserve(5000);	
    
    //Directory Lists
    DIR.setVerbose(false);
    nImages = DIR.listDir("images/");
 	images = new ofImage[nImages];
    //you can now iterate through the files as you like
    for(int i = 0; i < nImages; i++)
    {
        images[i].loadImage(DIR.getPath(i));
    }
}



//--------------------------------------------------------------
void testApp::update(){
    
    ofxVec3f diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofxVec3f mousePosition = ofxVec3f( mouseX , mouseY , 0 ) ; //Allocate and retrieve mouse values once.
    const ofxVec3f origin = ofxVec3f(0,0,0);
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofxVec3f() ; 
        diff = mousePosition - p->position ;  
        dist = mousePosition.distance( p->position ) ; 
        //If within the zone of interaction
        if ( dist * .5 < forceRadius )  
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
            p->acceleration += springFactor * (p->spawnPoint - p->position );
         //   p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
    }
    
    if ( ofGetFrameNum() % 300 == 0 ) 
    {
        curImageIndex++ ;
        setupParticles() ;
    }
}

void testApp::setupParticles() 
{
            
    if ( curImageIndex == nImages ) 
        curImageIndex = 0 ; 
    ofImage nextImage = images[curImageIndex] ; 
    
    
    ofxVec3f colors[2] ;
    ofxVec3f tint = ofxVec3f( 255 , 0 , 0 ) ; 
    colors[0] = ofxVec3f ( ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) ) ; 
    colors[1] = ofxVec3f ( 255 - colors[0].x , 255 - colors[0].y , 255 - colors[0].z ) ; 
    //colors[2] = ofxVec3f ( ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) ) ; 
    //colors[3] = ofxVec3f ( ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) , ofRandom ( 45 , 255 ) ) ; 
    
       ofColor newColor ; 
    newColor.r = r ; 
    newColor.g = g ; 
    newColor.b = b ; 
    int randomIndex ; 
    //Retrieve the pixels from the loaded image
    unsigned char * pixels = nextImage.getPixels() ;
    //store width and height for optimization and clarity
    int w = nextImage.width ; 
    int h = nextImage.height ; 
    
    //offsets to center the particle son screen
    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    numParticles= 0 ; 
    
    vector<ofPoint> newPoints ; 
   
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling ) 
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
           
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 4 ; 
            if ( pixels[index+3] > 1 ) 
            {
                //new position
                newPoints.push_back( ofPoint ( x + xOffset , y + yOffset , ofRandom( -200, 200 )) ) ; 
                numParticles++ ; 
            }
        }
    }
    
    int sizeDiff = numParticles +- particles.size() ; 
    int endLength = 0 ; 
    //less particles than before
    endLength = sizeDiff ; 
    if ( sizeDiff < 0 ) 
        endLength = particles.size() +- sizeDiff ; 
    //more particles than before
    else
        endLength = particles.size() ;
    
    int count = 0 ; 
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    {
        if ( count == endLength ) 
        {
            break ; 
        }
        
        randomIndex = (int) ofRandom(0,2) ; 
        newColor.r = colors[randomIndex].x ; 
        newColor.g = colors[randomIndex].y ; 
        newColor.b = colors[randomIndex].z ;
        
        p->spawnPoint = newPoints[count] ; 
        p->color = newColor ; 
        count++ ; 
    }
    
    if ( sizeDiff > 0 ) 
    {
        for ( int i = 0 ; i < endLength ; i++ ) 
        {
            int newIndex = ofRandom ( 0 , numParticles ) ; 
            randomIndex = (int) ofRandom(0,2) ; 
            newColor.r = colors[randomIndex].x ; 
            newColor.g = colors[randomIndex].y ; 
            newColor.b = colors[randomIndex].z ;

            particles[i].spawnPoint = newPoints[newIndex] ; 
            particles[i].color = newColor ; 
        }
    }

}

//--------------------------------------------------------------
void testApp::draw() {
    
    glClear(GL_DEPTH_BUFFER_BIT);
    
    // enable blending
	glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST); 
    ofPushMatrix() ; 

    //Offset by the center so that our openGL pivot point is in the center of the screen
    ofPoint center = ofPoint ( ofGetWidth() /2 , ofGetHeight() /2 ) ; 
    ofTranslate( ofGetWidth() * .5 , ofGetHeight() * .5 ); 
    ofRotateY( (mouseX / (float)ofGetWidth() +- .5 ) * 90.0f  ) ; 
    ofRotateX( (mouseY / (float)ofGetHeight() +- .5 ) * 90.0f  ) ;

    //Draw particles
    //Begin the openGL Drawing Mode
    glBegin(GL_POINTS);
    //glBegin(GL_LINES);
    //Triangles look Cool too 
   // glBegin(GL_TRIANGLES);
    
    ofEnableAlphaBlending() ; 
 
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    {
        glColor4ub((unsigned char)p->color.r,(unsigned char)p->color.g,(unsigned char)p->color.b , 215 );
        glVertex3f(p->position.x - center.x , p->position.y - center.y , p->position.z );
    }
    
    ofPopMatrix() ;
    glEnd();

    ofRotateX( (mouseY / (float)ofGetHeight() +- .5 ) * -90.0f  ) ;
    ofRotateY( (mouseX / (float)ofGetWidth() +- .5 ) * -90.0f  ) ; 
    ofTranslate( -ofGetWidth() * .5 , -ofGetHeight() * .5 ); 

    // choose semi-transparent black color
	myObj.setColor(0, 0, 0, 0.1f);
	
	// draw a black semi-transparent rectangle across whole screen to fade it out a bit
	myObj.drawRect( -2000, -2000 , 4000, 4000 ) ; 
	
	// disable blending
	glDisable(GL_BLEND);
    myObj.end();
    
    
    glDisable(GL_DEPTH_TEST);
    glColor4f(1, 1, 1, 1);
    
    string springString = ( springEnabled == 0 ) ? "on" : "off" ; 
    string repelString = (cursorMode == 0 ) ? "repulsion" : "attraction" ; 
    string output = " S :: Springs on/off : " + springString +
    "\n C :: CursorMode repel/attract " + repelString +
    "\n currently drawing " +  DIR.getName(curImageIndex)  +    
    "\n # of particles : " + ofToString( numParticles ) +
    " \n fps:" +ofToString( ofGetFrameRate() ) ;
    
    ofEnableAlphaBlending() ; 
    ofSetColor ( 255 , 255 , 255 , 255 ) ;
    images[curImageIndex].draw ( 10 , ofGetHeight() +- 325, images[curImageIndex].width/4 , images[curImageIndex].height/4 ) ; 
    ofDrawBitmapString(output ,20,ofGetHeight() +- 100 );
    
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
            
        case 'g':
        case 'G':
            gui.toggleDraw(); 
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

