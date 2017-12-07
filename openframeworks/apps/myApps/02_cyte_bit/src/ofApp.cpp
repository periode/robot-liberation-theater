#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(1024, 768, GL_RGBA);
    syphon_server.setName("cyte-bit - syphon");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    
    
	ofBackground(255);
	ofSetColor(150, 0, 0);
	ofDrawRectangle(300,100,100,100);
	ofSetColor(255);
	ofDrawRectangle(310, 110, 80, 80);

	ofSetColor(0, 0, 150);
	ofDrawRectangle(600, 600, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(610, 810, 80, 80);

	ofSetColor(0, 150, 0);
	ofDrawRectangle(650, 700, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(660, 110, 80, 80);

	ofSetColor(0);
	ofDrawRectangle(700, ofGetHeight()/2, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(710, ofGetHeight() / 2 + 10, 80, 80);
    
    
    fbo.end();
    
    syphon_server.publishTexture(&fbo.getTexture());
    
    fbo.draw(0, 0);
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
