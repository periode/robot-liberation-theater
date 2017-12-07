#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    gui.setup("variables");
    gui.add(numberOfStars.setup("numberOfStars", 500, 20, 500));
    gui.add(starRadius.setup("starRadius", 3, 0.1, 5.1));
    gui.add(colorHue.setup("colorHue", 100, 0, 255));
    gui.add(colorSaturation.setup("colorSaturation", 128, 0, 255));
    gui.add(colorBrightness.setup("colorBrightness", 0, 0, 255));
    gui.add(speed.setup("speed", 1, 1, 8));
    gui.add(lerp1.setup("lerp1", 1, 0, 1));
    gui.add(lerp2.setup("lerp2", 0, 0, 1));
    gui.add(distanceBetweenStars.setup("distanceBetweenStars", 225, 40, 450));
    gui.add(linesAppearing.setup("linesAppearing", 2000, 100, 10000));
    gui.add(starColorHue.setup("starColorHue", 255, 0, 255));
    gui.add(starColorSaturation.setup("starColorSaturation", 255, 0, 255));
    gui.add(starColorBrightness.setup("starColorBrightness", 255, 0, 255));
    
    
    for (int i = 0; i < 500; i++) {
        ofVec3f p;
        p.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), -ofRandom(30000));
        positionStars.push_back(p);
        
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    backgroundColor.setHsb(colorHue, colorSaturation, colorBrightness);
    
    for (int i = 0; i < numberOfStars; i++) {
        
        for (int s = 0; s < speed; s++){
            float starSpeed = 6+s;
            positionStars[i].z += starSpeed += 0.5;
        }
        
        if (positionStars[i].z > 1000){
            positionStars[i].z = -10000-ofRandom(20000);
        }
    }
    
    if(state=="numberOfStars"){
        numberOfStars = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),2,500);
    }
    
    if(state=="starRadius"){
        starRadius = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0.1,5.1);
    }
    
    if(state=="colorHue"){
        colorHue = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
    if(state=="colorSaturation"){
        colorSaturation = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
    if(state=="colorBrightness"){
        colorBrightness = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
    if(state=="speed"){
        speed = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),1,8);
    }
    
    if(state=="lerp1"){
        lerp1 = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,1);
    }
    
    if(state=="lerp2"){
        lerp2 = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,1);
    }
    
    if(state=="distanceBetweenStars"){
        distanceBetweenStars = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),40,450);
    }
    
    if(state=="linesAppearing"){
        linesAppearing = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),100,10000);
    }
    
    if(state=="starColorHue"){
        starColorHue = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
    if(state=="starColorSaturation"){
        starColorSaturation = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
    if(state=="starColorBrightness"){
        starColorBrightness = ofMap(ofGetMouseX(),0,ofGetWindowWidth(),0,255);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(backgroundColor);

    for (int i = 0; i < numberOfStars; i++) {
        
        //draw star
        for (float j = 0; j < starRadius; j+=0.05) {
            float bright = pow(2-log2(j*0.5)*2, 2);
            float pulsate = ofNoise(ofGetElapsedTimef()*0.3, i)*5;
            ofSetColor(starColorHue,starColorSaturation,starColorBrightness, bright+pulsate);
            
            ofDrawEllipse(positionStars[i], 1+exp(j*1.1), 1+exp(j*1.1));
        
        }
        
        if(positionStars[i].z > -linesAppearing){
            for (int k = 0; k < numberOfStars; k++) {
                ofVec2f star1;
                ofVec2f star2;
                
                
                star1.set(positionStars[i].x, positionStars[i].y);
                star2.set(positionStars[k].x, positionStars[k].y);
                float distance = positionStars[i].distance(positionStars[k]);
                
                
                if (distance < distanceBetweenStars) {
                    
                    ofVec3f v3 = positionStars[i].getInterpolated(positionStars[k], lerp1);
                    ofVec3f v4 = positionStars[i].getInterpolated(positionStars[k], lerp2);
                    float lineWidth;
                    float minLineWidth = 0.01;
                    float maxLineWidth = 3.0;
                    ofSetLineWidth(lineWidth);
                    lineWidth = ofRandom(minLineWidth, maxLineWidth);
                    float alpha = ofMap(lineWidth, minLineWidth, maxLineWidth, 120, 3);
                    ofSetColor(starColorHue,starColorSaturation,starColorBrightness, alpha);

                    ofDrawLine(v3, v4);

                    
                }
            }
        }
        
    }
    //a = lerp(A, B, 0.5-length); play with 0.5-+length
    //b = lerp(A, B, 0.5+length);
    //line(a,b);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case '1':
            state = "numberOfStars";
            break;
        case '2':
            state = "starRadius";
            break;
        case '3':
            state = "colorHue";
            break;
        case '4':
            state = "colorSaturation";
            break;
        case '5':
            state = "colorBrightness";
            break;
        case '6':
            state = "speed";
            break;
        case '7':
            state = "lerp1";
            break;
        case '8':
            state = "lerp2";
            break;
        case '9':
            state = "distanceBetweenStars";
            break;
        case '0':
            state = "linesAppearing";
            break;
        case 'q':
            state = "starColorHue";
            break;
        case 'w':
            state = "starColorSaturation";
            break;
        case 'e':
            state = "starColorBrightness";
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
