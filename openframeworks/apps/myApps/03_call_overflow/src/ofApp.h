#pragma once

#include "ofMain.h"
#include "../addons/ofxOsc/src/ofxOsc.h"
#include "ofxOsc.h"
#include "../Bubble.h"
//#include "ofxNetworkUtils.h"

#define R_PORT 2046
#define S_PORT 2056

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
		void checkState(string state);
		void setState(int state);
		
		ofxOscReceiver receiver;
		ofTrueTypeFont font;

		vector<ofSoundPlayer*> clips;
		int curClip = 1;

		vector<vector<Bubble>> messages;

		bool started = false;

		string siteUrl = "http://nyuad.im/call-overflow";

		int ovrState = 0;
		vector<vector<vector<string>>> ovrMss;

};