#include "ofApp.h"
#include "Bubble.cpp"

//--------------------------------------------------------------
void ofApp::setup() {

	fbo.allocate(1024, 768, GL_RGBA);
	syphon_server.setName("call overflow - syphon");

	// set up the OSC receiver to listen for port
	receiver.setup(PORT);

	ofLogNotice("Listening on port " + ofToString(PORT));

	messages = vector<vector<Bubble>>();
	messages.push_back(vector<Bubble>());
	messages.push_back(vector<Bubble>());

	// Override message lists
	ovrMss = vector<vector<vector<string>>>();
	ovrMss.push_back(vector<vector<string>>());
	ovrMss.push_back(vector<vector<string>>());
	ovrMss.push_back(vector<vector<string>>());

	for (int i = 0; i < ovrMss.size(); ++i) {//each (vector<vector<string>> l1 in ovrMss) {
		vector<vector<string>> *l1 = &ovrMss[i];

		vector<string> opt0 = vector<string>();

		opt0.push_back("keep it up");
		opt0.push_back("keep going");
		opt0.push_back("you can do this");
		opt0.push_back("do it!");

		vector<string> opt1 = vector<string>();

		opt1.push_back("this is pointless");
		opt1.push_back("stupid robot");
		opt1.push_back("are you mad");
		opt1.push_back("screw this!");

		l1->push_back(opt0);
		l1->push_back(opt1);
	}

	font = ofTrueTypeFont();
	font.load("Geo-Regular.ttf", 120);

	ofBackground(0);
}

// --------- ### ------- ### ---------
bool ofApp::gotOscMessage() {
	bool ret = false;
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage message;

		// receive the message yay
		receiver.getNextMessage(message);

		ofLogNotice("GOTS SOMETHING");
		ofBackground(255);
		//ofLogNotice(message.getArgAsString(0));
		string address = message.getAddress();

		if (address == "/test") {
			string thing = "";
			for (int i = 0; i < message.getNumArgs(); ++i) {
				ofLogNotice(message.getArgTypeName(i));

				switch (message.getArgType(i)) {
				case OFXOSC_TYPE_INT32:
					thing = ofToString(message.getArgAsInt32(i));
					break;
				case OFXOSC_TYPE_FLOAT:
					thing = ofToString(message.getArgAsFloat(i));
					break;
				case OFXOSC_TYPE_STRING:
					thing = ofToString(message.getArgAsString(i));
					break;
				default:
					thing = ofToString(message.getArgAsBlob(i));
					break;
				}
				//ofLogNotice(thing);
				cout << thing << endl;
			}
		}
		else if (address == "/text") {
			int index = -1;
			string text = "";
			for (int i = 0; i < message.getNumArgs(); ++i) {
				ofLogNotice(message.getArgTypeName(i));

				switch (message.getArgType(i)) {
				case OFXOSC_TYPE_INT32:
					index = message.getArgAsInt32(i);
					break;
				case OFXOSC_TYPE_FLOAT:
					index = int(message.getArgAsFloat(i));
					break;
				case OFXOSC_TYPE_STRING:
					text = ofToString(message.getArgAsString(i));
					break;
				default:
					continue;
				}
			}

			if (index == -1 || text == "") {
				ofLogError("IMPROPER DATA");
				return false;
			}

			ofLogNotice(ofToString(index) + " : " + text);

			Bubble bub = Bubble(text, index);

			messages[index].push_back(bub);

			ofLogNotice(ofToString(messages[index].size()));

			ret = true;
		}
		else if (address == "/reset") {
			messages[0].clear();
			messages[1].clear();
		}
	}

	return ret;
}


//--------------------------------------------------------------
void ofApp::update() {
	// check if we have OSC messages incoming

	try {
		gotOscMessage();
	}
	catch (exception e) {
		ofLogError("oop");
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	fbo.begin();
	float w = ofGetWidth();
	float h = ofGetHeight();

	ofBackground(255);

	if (started) {
		for (Bubble b : messages[0]) {
			b.draw(&font);
		}
		for (Bubble b : messages[1]) {
			b.draw(&font);
		}
	}
	else {
		float fw = font.stringWidth(siteUrl)*0.5;
		float fh = font.stringHeight(siteUrl)*0.5;

		ofPushMatrix();
		ofTranslate(w - fw, h - fh);

		font.drawString(siteUrl, 0, 0);

		ofPopMatrix();
	}

	fbo.end();
	syphon_server.publishTexture(&fbo.getTexture());

	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	int index = 0;
	string text = "";

	switch (key) {
	case 'a':
	case 'A':
		index = 0;
		break;
	case 'd':
	case 'D':
		index = 1;
		break;
	case 'c':
	case 'C':
		messages[0].clear();
		messages[1].clear();
		ovrState++;
		return;
	case ' ':
		ovrState = 0;
		started = true;
		return;
	}
	ofLogNotice(ofToString(ovrMss.size()));
	ofLogNotice(ofToString(ovrMss[0].size()));
	ofLogNotice(ofToString(ovrMss[0][0].size()));

	text = ovrMss[ovrState][index][floor(ofRandom(4))];

	Bubble bub = Bubble(text, index);
	messages[index].push_back(bub);
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
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

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
