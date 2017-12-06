#include "Bubble.h"

Bubble::Bubble()
{
}

Bubble::Bubble(string _msg, int index) {
	float w = ofGetWidth();
	float h = ofGetHeight()*0.5;
	float a = index == 0 ? 0 : 1;

	msg = _msg;
	pos = ofVec2f(ofRandom(w), ofRandom(a*h, (a + 1)*h));
	scale = ofRandom(0.1, 0.5);

	ofLogNotice(ofToString(scale));
}

Bubble::~Bubble()
{
}

void Bubble::update() {

}

void Bubble::draw(ofTrueTypeFont* f) {
	ofSetColor(0);
	if (!f) {
		ofDrawBitmapString(msg, pos.x, pos.y);
	}
	else {
		float w = f->stringWidth(msg)*0.5;
		float h = f->stringHeight(msg)*0.5;

		ofPushMatrix();
		ofTranslate(pos.x - w, pos.y);// -h);
		ofScale(scale, scale, 1);

		f->drawString(msg, 0, 0);
		ofPopMatrix();
	}

}
