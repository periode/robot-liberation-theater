#pragma once

#include "ofMain.h"

class Bubble
{
	Bubble();

public:
	Bubble(string message, int index);
	~Bubble();

	void update();
	void draw(ofTrueTypeFont *f = NULL);

	float scale;
	string msg;
	ofVec2f pos;
	ofColor col;
};

