#include "ofApp.h"

//--------------------------------------------------------------
Params param; //initiate parameters class

void Params::setup() {
    
    //initial particle setup (location, distance, reach, lifetime, and  rotation)
    center = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
    distance = 5;
    velocity = 10;
    lifetime = 1;
    rotate = 360;
    
    //initial colors of particle
    blue = true;
    yellow = true;
    
}

//--------------------------------------------------------------
Particle::Particle() {
    
    //particle starts out dead
    live = false;
    
}

//--------------------------------------------------------------
ofPoint randomPoint(float maxRad) {
    
    //points are chosen at random at the beginning, according to the distance variable
    ofPoint pnt;
    float rad = ofRandom(0, maxRad);
    float angle = ofRandom(0, TWO_PI);
    pnt.x = cos(angle) * rad;
    pnt.y = sin(angle) * rad;
    return pnt;
    
}

//--------------------------------------------------------------
void Particle::setup() {
    
    //the position and velocity of the particle are defined according to the parameter variables
    pos = param.center + randomPoint(param.distance);
    vel = randomPoint(param.velocity);
    time = 0;
    lifetime = param.lifetime;
    
    //the status of the particle is changed to alive
    live = true;
    
}

//--------------------------------------------------------------
void Particle::update(float dt) {
    
    //if the particle is alive, rotate it, then change its live status
    if (live) {
        vel.rotate(0, 0, param.rotate * dt);
        pos += vel * dt;
        time += dt;
        if (time >= lifetime) {
            live = false;
        }
    }
    
}

//--------------------------------------------------------------
void Particle::drawBlue() {
    
    //if particle is alive, map the size of the particle using formula
    if (live) {
        float size = ofMap(fabs(time - lifetime / 2), 0, lifetime / 2, 3, 1);
        
        //color is blue
        if (param.blue) {
            ofSetColor(ofColor(0, 0, ofRandom(128, 255)));
        }
        //color is red
        else {
            ofSetColor(ofColor(ofRandom(40,80), 0, 130));
        }
        
        //draw the particle as a circle
        ofDrawCircle(pos, size);
    }
    
}

//--------------------------------------------------------------
void Particle::drawYellow() { //yellow particle
    
    //if the color is set to yellow
    if (param.yellow) {
        
        //map the size of the particle using formula
        float size = ofMap(fabs(time - lifetime / 2), 0, lifetime / 2, 3, 1);
        
        //set color to yellow
        ofSetColor(ofColor(170, ofRandom(150,255), 50));
        
        //draw particle as a circle
        ofDrawCircle(pos, size);
    }
    
}

//--------------------------------------------------------------
void ofApp::setup() {
    
    //name server agnes
    server.setName("agnes");
    
    //load sound and play
    sound.load("agnes_george_soundtrack.mp3");
    
    //set framerate
    ofSetFrameRate(60);
    
    //window size is 1024 by 768
    fbo.allocate(1024, 768, GL_RGB32F_ARB);
    
    fbo.begin();
    ofBackground(0);
    fbo.end();
    
    //initiate initial particle setup
    param.setup();
    
    //history will modify the alpha of the background
    history = 0.995;
    
    //how many particles will appear in the initial screen
    bornRate = 10;
    bornCount = 0;
    time0 = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //get time to determine life of particle
    float time = ofGetElapsedTimef();
    float dt = time - time0;
    time0 = time;
    
    //setup blue/red particles by adding them to array
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
    
    //update blue/red particles in p vector array
    for (int i = 0; i<p.size(); i++) {
        p[i].update(dt);
    }
    
    //setup yellow particle
    if (!y.live) {
        y.setup();
    }
    
    //update yellow particle
    y.update(dt);
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    //initiate draw
    fbo.begin();
    
    //setup fade using alpha
    float alpha = (1 - history) * 255;
    ofSetColor(0, 0, 0, alpha);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    //draw blue/red particles
    ofFill();
    for (int i = 0; i<p.size(); i++) {
        p[i].drawBlue();
    }
    
    //draw yellow particle
    y.drawYellow();
    
    fbo.end();
    
    //publish syphon server
    server.publishTexture(&fbo.getTexture());
    
    //draw fbo
    fbo.draw(0, 0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    //center distance
    if (key == '1') {
        param.distance += 0.2;
    }
    
    if (key == 'q') {
        param.distance -= 0.2;
    }
    
    //reach of particle
    if (key == '2') {
        param.velocity += 0.2;
    }
    
    if (key == 'w') {
        param.velocity += 0.2;
    }
    
    //amount of particles
    if (key == '3') {
        bornRate += 0.2;
    }
    
    if (key == 'e') {
        bornRate += 0.2;
    }
    
    //make particles stop blue/red and yellow
    if (key == '4') {
        bornRate = 0;
        param.yellow = false;
    }
    
    //test option
    if (key == 't') {
        param.distance = 200;
        param.velocity = 200;
        bornRate = 40;
    }
    
    //color change between blue and red
    if (key == 'b') {
        param.blue = true;
    }
    if (key == 'r') {
        param.blue = false;
    }
    
    //play sound
    if (key == 'p'){
        sound.play();
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
