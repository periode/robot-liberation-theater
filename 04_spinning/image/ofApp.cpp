#include "ofApp.h"

//--------------------------------------------------------------
Particle::Particle() {
	live = false;
	state = true;
	size = 50;
	angle = 70;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle(float max) {
	ofPoint pnt;
	float rad = ofRandom(0, max);
	float angle = ofRandom(0, TWO_PI);
	pnt.x = cos(angle) * rad;
	pnt.y = sin(angle) * rad;
	return pnt;
}

void Particle::state1() {
	gui.setup();
	gui.add(color.setup("Color", ofColor(10, 125, 255), ofColor(0, 0), ofColor(255, 255)));
	pos = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2) + randomPointInCircle(50);
	vel = randomPointInCircle(size);
	time = 0;
	lifeTime = 1.0;
	rotate = angle;
	live = true;
}

void Particle::state2() {
	gui.setup();
	gui.add(color.setup("Color", ofColor(196, 114, 34), ofColor(0, 0), ofColor(255, 255)));
	pos = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2) + randomPointInCircle(100);
	vel = randomPointInCircle(size);
	time = 0;
	lifeTime = 1.0;
	rotate = angle;
	live = true;
}

//--------------------------------------------------------------
void Particle::setup() {
	if (state) {
		state1();
	}
	else {
		state2();
	}
}

//--------------------------------------------------------------
void Particle::update(float dt) {
	if (live) {
		vel.rotate(0, 0, rotate * dt);
		pos += vel * dt;
		time += dt;
		if (time >= 2) {
			live = false;
		}
	}
}

//--------------------------------------------------------------
void Particle::draw() {	
	if (live) {
		float size = ofMap(fabs(time - lifeTime / 2), 0, lifeTime / 2, 3, 1);
		ofSetColor(color);
		ofCircle(pos, size);
	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(2100, 1200);
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);
	fbo.begin();
	ofBackground(0);
	fbo.end();
	history = 0.995;
	time0 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float time = ofGetElapsedTimef();
	float dt = ofClamp(time - time0, 0, 0.1);
	time0 = time;
	if (!p.live) {
		p.setup();
	}
	p.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw() {
	fbo.begin();
	ofFill();
	p.draw();
	fbo.end();
	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'q') {
		p.size += 5.0;
	} 
	if (key == 'w') {
		p.size -= 5.0;
	}
	
	if (key == 'a') {
		p.angle += 1.0;
	}
	if (key == 's') {
		p.angle -= 1.0;
	}

	if (key == 'z') {
		p.state = false;
	}
	if (key == 'x') {
		p.state = true;
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