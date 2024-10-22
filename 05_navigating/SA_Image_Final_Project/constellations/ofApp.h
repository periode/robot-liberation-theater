#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
    string state = "NONE";
    
    ofxPanel gui;
    ofxSlider<int> numberOfStars;
    ofxSlider<float> starRadius;
    ofxSlider<float> colorHue;
    ofxSlider<float> colorSaturation;
    ofxSlider<float> colorBrightness;
    ofxSlider<float> speed;
    ofxSlider<float> lerp1;
    ofxSlider<float> lerp2;
    ofxSlider<float> distanceBetweenStars;
    ofxSlider<int> linesAppearing;
    ofxSlider<float> starColorHue;
    ofxSlider<float> starColorSaturation;
    ofxSlider<float> starColorBrightness;
    
    
    ofColor backgroundColor;

    vector<ofVec3f> positionStars;
    vector<float> lineWidth;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
