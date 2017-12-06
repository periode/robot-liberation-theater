#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetWindowShape(600,600);
    angle = 0;
    speed = 100;
    vertices = 2;
    radius = 300;
    maxradius = 1000;
    minradius = 50;
    
    
    ofBackground(10);
    ofSetColor(234,84,84,150);
    
}
//--------------------------------------------------------------
void ofApp::update(){
    speed+=3;
}


void ofApp::draw(){
    

    
    for(int j = 0; j < 1; j++){
        
        ofPushMatrix();
        
        ofBeginShape();
        ofTranslate(ofGetWidth()/2, ofGetHeight()*0.5);
        
        ofNoFill();
        ofRotateX(speed+(j*50));
        
        for(int i = 0; i < vertices; i++){
            ofVertex(cos(i*vertices)*radius,sin(i*vertices)*radius,i);

        }
        
        ofEndShape();
        
        ofPopMatrix();
    }
    
    
    for(int j = 0; j < 1; j++){
        
        
        ofPushMatrix();
        ofBeginShape();
        ofTranslate(ofGetWidth()/2, ofGetHeight()*0.5);

        ofNoFill();
        ofRotateY(speed+(j*50));
        
        for(int i = 0; i < vertices; i++){
            ofVertex(cos(i*vertices)*radius,sin(i*vertices)*radius,i);
            
                   }
        

        ofEndShape();
        ofPopMatrix();
    }
    
    
    
    
    if(isSaving){
        ofBeginSaveScreenAsPDF("print-"+ofToString(ofGetElapsedTimeMicros())+".pdf");
    }
    if(isSaving){
        ofEndSaveScreenAsPDF();
        isSaving = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        isSaving = true;
    }
    
    if(key == 'q'){
        vertices=ofRandom(1,10);
    }
    
    if(key == 'w'){
        vertices=ofRandom(1,100);
    }
    
    if(key == 'p'){
        vertices=0;
    }
    
    
    if(key == 'c'){
        ofSetColor(ofRandom(1,255),ofRandom(1,255),ofRandom(1,255) ,100);
    }

    
    
    if(key == 'z'){
        
        verticescount = ofRandom(1,500);
        
        for(int i = 0; i <verticescount; i++){
            
            if(vertices>verticescount){
                vertices-=i*1.1;
            }
            
            if(vertices<verticescount){
                vertices+=i*1.1;
            }
            
        }
    }
    
    if(key == OF_KEY_RIGHT){
        radius += 100;
    }
    
    if(key == OF_KEY_LEFT){
        radius -= 100;
    }
    
    if(key == OF_KEY_UP){
        vertices += 10;
    }
    
    if(key == OF_KEY_DOWN){
        vertices -= 10;
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
    radius = 300;
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

