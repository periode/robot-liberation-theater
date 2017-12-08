#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //this is initializing your syphon server, that is going to send the frames
    mySyphonServer.setName("OF output");
    
    //we need to specify the size of the frame that we will send (1024x768) and the quantity of data (RGB + Alpha)
    myFbo.allocate(600, 600, GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    angle++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    myFbo.begin(); //we need to specify that we are now drawing INTO the FBO.
    
    ofBackground(0);
    ofSetColor(255);
    
    ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
    ofRotate(angle);
    ofDrawRectangle(0, 0, 200, 200);
    
    
    myFbo.end(); //and we need to specify that we're done drawing
    
    //finally we tell our Syphon Server to send the frames
    mySyphonServer.publishTexture(&myFbo.getTexture());

    
    //everything drawn after that will not be sent to syphon.
    //so we can even draw the contents of our FBO to the OF screen!
    
    myFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
