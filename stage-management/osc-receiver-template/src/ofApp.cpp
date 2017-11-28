#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(port_to_listen_to);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(receiver.hasWaitingMessages()){
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        
        if ( msg.getAddress() == "/position/front") {
            front.x = msg.getArgAsInt32( 0 );
            front.y = msg.getArgAsInt32( 1 );
        }
        
        if ( msg.getAddress() == "/position/back" ) {
            back.x = msg.getArgAsInt32( 0 );
            back.y = msg.getArgAsInt32( 1 );
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("front light position:" + ofToString(front), 10, 20);
    ofDrawBitmapString("back led position" + ofToString(back), 10, 40);
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
