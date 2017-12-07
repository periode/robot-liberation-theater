#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    //-------- SYPHON
    tex_water_server.setName("05 - Water");
    tex_constellations_server.setName("05 - Constellations");
    
    tex_water.allocate(1024, 768, GL_RGBA);
    tex_constellations.allocate(1024, 768, GL_RGBA);
    
    //-------- CONSTELLATIONS
    
    gui.setup("variables");
    gui.add(numberOfStars.setup("numberOfStars", 50, 20, 500));
    gui.add(starRadius.setup("starRadius", 3, 0.1, 5.1));
    gui.add(colorHue.setup("colorHue", 100, 0, 255));
    gui.add(colorSaturation.setup("colorSaturation", 128, 0, 255));
    gui.add(colorBrightness.setup("colorBrightness", 0, 0, 255));
    gui.add(speed.setup("speed", 1, 1, 8));
    gui.add(lerp1.setup("lerp1", 1, 0, 1));
    gui.add(lerp2.setup("lerp2", 0, 0, 1));
    gui.add(distanceBetweenStars.setup("distanceBetweenStars", 125, 40, 450));
    gui.add(linesAppearing.setup("linesAppearing", 2000, 100, 10000));
    gui.add(starColorHue.setup("starColorHue", 255, 0, 255));
    gui.add(starColorSaturation.setup("starColorSaturation", 255, 0, 255));
    gui.add(starColorBrightness.setup("starColorBrightness", 255, 0, 255));
    
    
    for (int i = 0; i < 500; i++) {
        ofVec3f p;
        p.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), -ofRandom(30000));
        positionStars.push_back(p);
        
    }
    
    //-------- WATER
    
    ofDisableArbTex();
    ofLoadImage(texture,"water_texture.jpg");
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
    
    // ------ CONSTELLATIONS
    
    backgroundColor.setHsb(colorHue, colorSaturation, colorBrightness);
    
    for (int i = 0; i < numberOfStars; i++) {
        
        for (int s = 0; s < speed; s++){
            float starSpeed = 6+s;
            positionStars[i].z += starSpeed += 0.5;
        }
        
        if (positionStars[i].z > 1000){
            positionStars[i].z = -10000-ofRandom(20000);
        }
    }
    
    // ------ WATER
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

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //------- CONSTELLATIONS
    tex_constellations.begin();
    ofBackground(0);
    
    for (int i = 0; i < numberOfStars; i++) {
        
        //draw star
        for (float j = 0; j < starRadius; j+=0.05) {
            float bright = pow(2-log2(j*0.5)*2, 2);
            float pulsate = ofNoise(ofGetElapsedTimef()*0.3, i)*5;
            ofSetColor(starColorHue,starColorSaturation,starColorBrightness, bright+pulsate);
            
            ofDrawEllipse(positionStars[i], 1+exp(j*1.1), 1+exp(j*1.1));
            
        }
        
        if(positionStars[i].z > -linesAppearing){
            for (int k = 0; k < numberOfStars; k++) {
                ofVec2f star1;
                ofVec2f star2;
                
                
                star1.set(positionStars[i].x, positionStars[i].y);
                star2.set(positionStars[k].x, positionStars[k].y);
                float distance = positionStars[i].distance(positionStars[k]);
                
                
                if (distance < distanceBetweenStars) {
                    
                    ofVec3f v3 = positionStars[i].getInterpolated(positionStars[k], lerp1);
                    ofVec3f v4 = positionStars[i].getInterpolated(positionStars[k], lerp2);
                    float lineWidth;
                    float minLineWidth = 0.01;
                    float maxLineWidth = 3.0;
                    ofSetLineWidth(lineWidth);
                    lineWidth = ofRandom(minLineWidth, maxLineWidth);
                    float alpha = ofMap(lineWidth, minLineWidth, maxLineWidth, 120, 3);
                    ofSetColor(starColorHue,starColorSaturation,starColorBrightness, alpha);
                    
                    ofDrawLine(v3, v4);
                    
                    
                }
            }
        }
        
    }
    
    tex_constellations.end();
    tex_constellations_server.publishTexture(&tex_constellations.getTexture());
    
    
    //------------------------------------ WATER
    
    tex_water.begin();
    
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
    
    tex_water.end();
    tex_water_server.publishTexture(&tex_water.getTexture());
    
    tex_water.draw(0, 0);
    
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
