#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp{
    
    ofColor backgroundColor;
    
    vector<float> offsets;
    int vertices;
    int radius;
    int speed;
    int maxradius;
    int minradius;
    int verticescount;
    bool isSaving = false;
    bool radiuscount = false;
    float translatedx;
    float translatedy;
    vector<float> pattern;
    
    float rotationX;
    float rotationY;
    float rotationZ;
    
    int angle = 0;
    
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
    
};
