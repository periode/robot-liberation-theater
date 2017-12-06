#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// set up the OSC receiver to listen for port
	receiver.setup(PORT);

	ofLogNotice("Listening on port " + ofToString(PORT));

	messages = vector<vector<Bubble>>();
	messages.push_back(vector<Bubble>());
	messages.push_back(vector<Bubble>());

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
	float w = ofGetWidth();
	float h = ofGetHeight();

	for each (Bubble b in messages[0]) {
		b.draw(&font);
	}

	for each (Bubble b in messages[1]) {
		b.draw(&font);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
