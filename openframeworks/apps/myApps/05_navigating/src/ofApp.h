#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
    //-----------------WATER
    
    ofFbo tex_water;
    ofxSyphonServer tex_water_server;
    
    string state = "NONE";
    
    ofxPanel gui;
    ofxSlider<float> time_scale;
    ofxSlider<float> displacement;
    vector<ofVec3f> startPositions;
    vector<ofVec3f> offsets;
    
    float xoff,yoff;
    int cols,rows;
    int terrainW,terrainH;
    int scl;
    
    ofMesh mesh;
    
    ofSoundPlayer dialogue1;
    ofSoundPlayer dialogue2;
    ofSoundPlayer dialogue3;
    ofSoundPlayer dialogue4;
    ofSoundPlayer dialogue5;
    ofSoundPlayer dialogue6;
    ofSoundPlayer dialogue7;
    ofSoundPlayer backgroundSound;
    
    
    float terrainZPos;
    float terrainZPosOff;
    
    //light
    ofLight light;
    
    //-----------------CONSTELLATIONS
    
    ofFbo tex_constellations;
    ofxSyphonServer tex_constellations_server;
    
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
