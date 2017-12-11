#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo_dock.allocate(1024, 768, GL_RGBA);
    syphon_server_dock.setName("dock - syphon");
    fbo_cyte.allocate(1024, 768, GL_RGBA);
    syphon_server_cyte.setName("cyte - syphon");
    
    Beat.loadSound("openCyte.wav");
    other.loadSound("scriptRevised.wav");

    fftSmooth = new float[8192];
    for (int i = 0; i<8192; i++) {
        fftSmooth[i] = 0;
    }
    
    bands = 64;
    Beat.setLoop(true);
    Beat.setVolume(.5);
    
    //Beat.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    float * value = ofSoundGetSpectrum(bands);
    for (int i = 0; i<bands; i++) {
        fftSmooth[i] *= 0.79f;
        if (fftSmooth[i] < value[i]) {
            fftSmooth[i] = value[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo_cyte.begin();
    ofBackground(0);
    for (int i = 0; i < 5; i++) {
        ofSetColor(173, 255, 47);
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 + i*10, ofGetHeight() / 2 +i*10);
        ofNoFill();
        ofBeginShape();
        for (int i = 0; i < 512; i++) {
            ofVertex(i * 20, 100 * -(fftSmooth[i] * 10));
            
        }
        ofEndShape();
        ofPopMatrix();
    }
    for (int i = 0; i < 5; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 + i * 10, ofGetHeight() / 2 + i * 10);
        ofRotate(180);
        ofNoFill();
        ofSetColor(0, 255, 127);
        ofBeginShape();
        for (int i = 0; i < 512; i++) {
            ofVertex(i * 20, 100 * -(fftSmooth[i] * 10));
        }
        ofEndShape();
        ofPopMatrix();
    }
    for (int i = 0; i < 5; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 + i * 10, ofGetHeight() / 2 + i * 10);
        ofRotate(90);
        ofNoFill();
        ofSetColor(0, 100, 0);
        ofBeginShape();
        for (int i = 0; i < 512; i++) {
            ofVertex(i * 20, 100 * -(fftSmooth[i] * 10));
            
        }
        ofEndShape();
        ofPopMatrix();
    }
    for (int i = 0; i < 5; i++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() / 2 + i * 10, ofGetHeight() / 2 + i * 10);
        ofRotate(270);
        ofNoFill();
        ofSetColor(0, 255, 0);
        ofBeginShape();
        for (int i = 0; i < 512; i++) {
            ofVertex(i * 20, 100 * -(fftSmooth[i] * 10));
            
        }
        ofEndShape();
        ofPopMatrix();
    }
    fbo_cyte.end();
    
    syphon_server_cyte.publishTexture(&fbo_cyte.getTexture());
    
    fbo_cyte.draw(0, 0);
    
    fbo_dock.begin();
    
    
	ofBackground(0);
	ofSetColor(150, 0, 0);
	ofDrawRectangle(300,100,100,100);
	ofSetColor(255);
	ofDrawRectangle(310, 110, 80, 80);

	ofSetColor(0, 0, 150);
	ofDrawRectangle(600, 600, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(610, 610, 80, 80);

	ofSetColor(0, 150, 0);
	ofDrawRectangle(650, 700, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(660, 710, 80, 80);

	ofSetColor(0);
	ofDrawRectangle(700, ofGetHeight()/2, 100, 100);
	ofSetColor(255);
	ofDrawRectangle(710, ofGetHeight() / 2 + 10, 80, 80);
    
    
    fbo_dock.end();
    
    syphon_server_dock.publishTexture(&fbo_dock.getTexture());
    
    //fbo_dock.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            Beat.play();
            break;
        case '2':
            Beat.stop();
            break;
    }
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
