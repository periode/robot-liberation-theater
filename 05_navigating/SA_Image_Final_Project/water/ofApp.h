#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
    string state = "NONE";
    
    ofxPanel gui;
    ofxSlider<float> time_scale;
    ofxSlider<float> displacement;
    vector<ofVec3f> startPositions;
    vector<ofVec3f> offsets;

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
    
    float xoff,yoff;
    int cols,rows;
    int terrainW,terrainH;
    int scl;
    
    ofImage texture;
    ofMesh mesh;
    
    float terrainZPos;
    float terrainZPosOff;
    
    //light
    ofLight light;
		
};
