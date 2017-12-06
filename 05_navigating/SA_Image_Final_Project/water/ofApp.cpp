#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofDisableArbTex();
    ofLoadImage(texture,"water_texture.jpg");
    
    gui.setup("gui");  //cretae the gui object and give it a title
    gui.add(time_scale.setup("time_scale", 0.001, 0.1, 1.0));
    gui.add(displacement.setup("displacement", 0.1, 0, 150));
    scl = 25; // Set Scale of grids
    
    terrainW = 2200;
    terrainH = 1692;
    
    
    cols = terrainW / scl; // set rows per scl
    rows = terrainH / scl; // set columns per scl
    
    
    cout << "columns numbers: " << cols << endl;
    cout << "rows numbers: " << cols << endl;

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    
    for (int j = 0; j < rows; j++) {
        xoff = 0;
        for (int i = 0 ; i < cols; i++) {
            
            float x = i*scl;
            float y = j*scl;
            //float z = ofRandom(-10,10);
            float z = ofMap(ofNoise(yoff, xoff),0,1,-50,50);
            mesh.addVertex(ofVec3f(x,y,z));
            startPositions.push_back(ofVec3f(x,y,z));
            offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            mesh.addColor(ofFloatColor(1,1,1));

            
            xoff += 0.1;
        }
        yoff += 0.1;
    }
    
    
    
    
    // Generate order of indices to set triangles per rows and column
    for (int j = 0; j < rows - 1 ; j++) {
        for (int i = 0 ; i < cols - 1; i++) {
            
            mesh.addIndex(i+j*cols);         // 0
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex(i+(j+1)*cols);     // 6
            
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex((i+1)+(j+1)*cols); // 7
            mesh.addIndex(i+(j+1)*cols);     // 6
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = time_scale;
        float displacementScale = displacement;
        ofVec3f start = startPositions[i];
        ofVec3f timeOffsets = offsets[i];
        
//        vert.x = start.x + (ofSignedNoise(time*timeScale,start.x*0.0001)) * displacementScale;
        vert.y = start.y + (ofSignedNoise(time*timeScale, start.x*0.0000000000001)) * displacementScale;
        vert.z = start.z + (ofSignedNoise(time*timeScale, i*0.001)) * displacementScale;
        mesh.setVertex(i, vert);
    }
    
    if(state=="time_scale"){
        time_scale = ofMap(ofGetMouseX(),0.001,ofGetWindowWidth(),0.1,1.0);
    }
    
    if(state=="displacement"){
        displacement = ofMap(ofGetMouseX(),0.1,ofGetWindowWidth(),0,150);
    }

    
        
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5 - terrainW*0.5 + scl*0.5, ofGetHeight()*0.5 - terrainH*0.5 + scl*0.5);
    

    
    
    ofEnableLighting();
    light.enable();
    
    texture.bind();
    mesh.draw();
    texture.unbind();
    
    light.disable();
    ofDisableLighting();
    
    ofSetColor(255);
    mesh.drawWireframe();
    
    

    ofPopMatrix();
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '1':
            state = "time_scale";
            break;
        case '2':
            state = "displacement";
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
