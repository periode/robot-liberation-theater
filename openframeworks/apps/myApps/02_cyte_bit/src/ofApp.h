#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
    ofxSyphonServer syphon_server_dock;
    ofFbo fbo_dock;
    ofxSyphonServer syphon_server_cyte;
    ofFbo fbo_cyte;


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
		ofxPanel gui;
		
        float * fftSmooth;
        float * fftSmoothClap;
        bool isSaving = false;
    
        int bands;
    
        ofSoundPlayer Beat;
        ofSoundPlayer other;
    
        bool isReact = false;
    
        bool isRedReact = false;
        bool isBlueReact = false;
        bool isGreenReact = false;
        bool isGrayReact = false;

};
