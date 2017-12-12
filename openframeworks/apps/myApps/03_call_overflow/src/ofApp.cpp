#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {


    fbo.allocate(1024, 768, GL_RGBA);
    server.setName("call overflow");
    
    

	// set up the OSC receiver to listen for port
	receiver.setup(R_PORT);

	ofLogNotice("Listening on port " + ofToString(R_PORT));

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
	
	// Load recordings
	vector<string> filenames = {
		"ring_ring.mp3", // 0 - RING
		"calling_q_1.mp3", // 1- CALLING / STASIS
		"calling_a_1.mp3",
		"calling_q_2.mp3",
		"calling_a_2.mp3",
		"calling_q_3.mp3",
		"calling_a_3.mp3",
		"motivation_q_1.mp3", // 7 - MOTIVATION
		"crisis_a_1.mp3", // 8 - CRISIS
		"support_q_1.mp3", // 9 - SUPPORT
		"support_a_1.mp3",
		"support_q_2.mp3",
		"support_a_2.mp3",
		"decline_q_1.mp3", // 13 - DECLINE
		"decline_a_1.mp3"
	};

	for (int i = 0; i < filenames.size(); ++i) {
		ofSoundPlayer *player = new ofSoundPlayer();
		player->load(filenames[i]);
		clips.push_back(player);
	}

	ofBackground(255);
}

// --------- ### ------- ### ---------
bool ofApp::gotOscMessage() {
	bool ret = false;
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage message;

		// receive the message yay
		receiver.getNextMessage(message);

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
			ofLogNotice("GOTS SOMETHING");

			//int index = -1;
			vector<int> indices = vector<int>();
			vector<string> texts = vector<string>();
			vector<string> states = vector<string>();

			bool esc = false;
			for (int i = 0; i < message.getNumArgs(); ++i) {
				if (esc) {
					break;
				}
				ofLogNotice(message.getArgTypeName(i));
				switch (i % 3) {
				case 0:
					switch (message.getArgType(i)) {
					case OFXOSC_TYPE_INT32:
						indices.push_back(message.getArgAsInt(i));
						break;
					case OFXOSC_TYPE_STRING:
						states.push_back(ofToString(message.getArgAsString(i)));
						esc = true;
						break;
					}
					break;
				case 1:
					texts.push_back(ofToString(message.getArgAsString(i)));
				case 2:
					states.push_back(ofToString(message.getArgAsString(i)));
					break;
					/*switch (message.getArgType(i)) {
					case OFXOSC_TYPE_INT32:
						index = message.getArgAsInt32(i);
						break;
					case OFXOSC_TYPE_FLOAT:
						index = int(message.getArgAsFloat(i));
						break;
					case OFXOSC_TYPE_STRING:
						if (i == 0) {
							state = ofToString(message.getArgAsString(i));
							esc = true;
							break;
						}
						if (text == "") {
							text = ofToString(message.getArgAsString(i));
						}
						else {
							state = ofToString(message.getArgAsString(i));
						}
						break;
					default:
						continue;
					}*/
				}
			}

			if (states.size() > 0) {
				checkState(states[states.size()-1]);
				ofLogNotice("GOT STATE");
			}

			if (indices.size() == 0 || texts.size() == 0){//|| state == "") {
				ofLogError("NO MESSAGE");
				return false;
			}

			for (int i = 0; i < indices.size(); ++i) {
				ofLogNotice(ofToString(indices[i]) + " : " + texts[i]);

				Bubble bub = Bubble(texts[i], indices[i]);

				messages[indices[i]].push_back(bub);

				ofLogNotice(ofToString(messages[indices[i]].size()));

				ret = true;
			}
		}
		else if (address == "/reset") {
			messages[0].clear();
			messages[1].clear();
		}
		else if (address == "/ready") {
			started = true;
		}
	}

	return ret;
}

void ofApp::checkState(string state) {
	if (state == "") {
		return;
	}
	char st = state[0];
	int nextState = st - 141; // 'a' should be 141 -> 0; 'b' : 142 -> 1S

	if (nextState != ovrState) {
		ofLogNotice("CHANGING STATE");
		setState(nextState);
	}
}

void ofApp::setState(int state) {
	ofLogNotice(ofToString(state));

	messages[0].clear();
	messages[1].clear();

//	for each (ofSoundPlayer* cp in clips) {
//		cp->stop();
//	}
    
    for (int i = 0; i < clips.size(); ++i) {
        clips[i]->stop();
    }

	switch (state) {
	case 0:
		curClip = 1;
		break;
	case 1:
		curClip = 7;
		break;
	case 2:
		curClip = 8;
		break;
	case 3:
		curClip = 9;
		break;
	case 4:
		curClip = 1;
		break;
	case 5:
		curClip = 13;
		break;
	}

	ovrState = state;
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
	// fbo
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
		ofTranslate(w*0.5, h*0.5);
		ofScale(0.3, 0.3, 1);
		ofTranslate(-fw, -fh);

		ofSetColor(0);

		font.drawString(siteUrl, 0, 0);

		ofPopMatrix();
	}

    fbo.end();
    server.publishTexture(&fbo.getTexture());

	// draw fbo
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	int index = 0;
	string text = "";

	switch (key) {
	case 'w':
	case 'W':
		index = 0;
		break;
	case 's':
	case 'S':
		index = 1;
		break;
	case 'a':
	case 'A':
//		for each (ofSoundPlayer* cp in clips) {
//			cp->stop();
//		}
        for (int i = 0; i < clips.size(); ++i) {
            clips[i]->stop();
        }
		clips[0]->setVolume(0.5);
		clips[0]->play();
		return;
	case 'd':
	case 'D':
//		for each (ofSoundPlayer* cp in clips) {
//			cp->stop();
//		}
        for (int i = 0; i < clips.size(); ++i) {
            clips[i]->stop();
        }
		clips[curClip]->play();
		++curClip;
		return;
	case 'c':
	case 'C':
		setState(ovrState + 1);
		return;
	case ' ':
		setState(0);
		started = true;
		return;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		setState(key - 49);
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
