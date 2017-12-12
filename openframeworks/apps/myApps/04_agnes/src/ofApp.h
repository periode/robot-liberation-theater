#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

//particle class
class Particle {

public:

	//particle constructor
	Particle();

	//main functions
	void setup();
	void update(float dt);
	void drawBlue();
	void drawPurple();
	void drawYellow();

	//variables
	ofPoint pos;
	ofPoint vel;
	float time;
	float lifetime;
	bool live;
};

//parameters class
class Params {

public:

	//function
	void setup();

	//variables
	ofPoint center;
	float distance;
	float velocity;
	float lifetime;
	float rotate;
	bool blue;
	bool purple;
	bool yellow;
};

extern Params params;

//ofApp class
class ofApp : public ofBaseApp {

public:

	//add syphon server
	ofxSyphonServer server;

	//add sound
	ofSoundPlayer sound;

	//main functions
	void setup();
	void update();
	void draw();

	//vector array of blue/purple particles
	vector<Particle> blues;
	vector<Particle> purples;

	//yellow particle
	Particle yellow;

	//fbo initialization
	ofFbo fbo;

	//variable for alpha
	float history;

	//variables for lifetime
	float time0;
	float bornRateB;
	float bornRateP;
	float bornCount;

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

