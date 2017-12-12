#include "ofApp.h"

//--------------------------------------------------------------
Params param;

void Params::setup() {
	eCenter = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
	eRad = 5;
	velRad = 10;
	lifeTime = 0.5;
	rotate = 90;
}

//--------------------------------------------------------------
Particle::Particle() {
	live = false;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle(float maxRad) {
	ofPoint pnt;
	float rad = ofRandom(0, maxRad);
	float angle = ofRandom(0, M_TWO_PI);
	pnt.x = cos(angle) * rad;
	pnt.y = sin(angle) * rad;
	return pnt;
}

//--------------------------------------------------------------
void Particle::setup() {
	pos = param.eCenter + randomPointInCircle(param.eRad);
	vel = randomPointInCircle(param.velRad);
	time = 0;
	lifeTime = param.lifeTime;
	live = true;
}

//--------------------------------------------------------------
void Particle::update(float dt) {
	if (live) {
		vel.rotate(0, 0, param.rotate * dt);
		pos += vel * dt;
		time += dt;
		if (time >= lifeTime) {
			live = false;
		}
	}
}

//--------------------------------------------------------------
void Particle::draw() {
	if (live) {
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime / 2, 3, 1);
		ofSetColor(ofColor(0, 0, ofRandom(128, 255)));
		ofCircle(pos, size);
	}
}

//--------------------------------------------------------------
//----------------------  testApp  -----------------------------
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	int w = ofGetWidth();
	int h = ofGetHeight();
	fbo.allocate(w, h, GL_RGB32F_ARB);

	fbo.begin();
	ofBackground(255, 255, 255);
	fbo.end();

	param.setup();
	history = 0.995;
	bornRate = 10;

	bornCount = 0;
	time0 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time - time0, 0, 0.1);
	time0 = time;

	int i = 0;
	while (i > p.size()) {
		if (!p[i].live) {
			p.erase(p.begin() + i);
		}
		else {
			i--;
		}
	}

	bornCount += dt * bornRate;
	if (bornCount >= 1) {
		int bornN = int(bornCount);
		bornCount -= bornN;
		for (int i = 0; i<bornN; i++) {
			Particle newP;
			newP.setup();
			p.push_back(newP);
		}
	}

	for (int i = 0; i<p.size(); i++) {
		p[i].update(dt);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255, 255, 255);

	fbo.begin();

	ofEnableAlphaBlending();

	float alpha = (1 - history) * 255;
	ofSetColor(0, 0, 0, alpha);
	ofFill();
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	ofDisableAlphaBlending();

	ofFill();
	for (int i = 0; i<p.size(); i++) {
		p[i].draw();
	}

	fbo.end();

	ofSetColor(255, 255, 255);
	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		param.eRad = 25;
		param.velRad = 50;
	}
	if (key == '2') {
		param.eRad = 100;
		param.velRad = 200;
		bornRate = 100;
	}
	if (key == '3') {
		param.eRad = 200;
		param.velRad = 300;
		bornRate = 400;
	}
	if (key == '4') {
		param.eRad = 400;
		param.velRad = 600;
		bornRate = 800;
	}
	if (key == '5') {
		param.eRad = 1000;
		param.velRad = 400;
		bornRate = 1000;
	}
	if (key == '6') {
		bornRate = 0;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}