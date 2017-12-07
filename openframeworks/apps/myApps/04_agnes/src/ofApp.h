#pragma once

#include "ofMain.h"
#include "ofXGui.h"
#include "ofxSyphon.h"

class Particle {

	public:
		ofxPanel gui;
		ofxColorSlider color;

		Particle();

		void setup();
		void state1();
		void state2();
		void update(float dt);
		void draw();

		ofPoint pos;
		ofPoint vel;

		float state;
		float size;
		float angle;
		float time;
		float lifeTime;
		float rotate;
		bool live;
};

class ofApp : public ofBaseApp {
    
    ofxSyphonServer tex_server;

	public:
		void setup();
		void update();
		void draw();

		Particle p;
		ofFbo fbo;
		float history;
		float time0;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
}; 
