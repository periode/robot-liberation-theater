#pragma once

#include "ofMain.h"
#include "../addons/ofxOsc/src/ofxOsc.h"
#include "ofxOsc.h"
#include "../Bubble.h"

#define PORT 2046

class ofApp : public ofBaseApp{

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

		bool gotOscMessage();
		
		ofxOscReceiver receiver;
		ofTrueTypeFont font;

		vector<vector<Bubble>> messages;

};
