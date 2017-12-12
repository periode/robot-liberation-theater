#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofEnableDepthTest();
    
//------------SYPHON
    tex_server_view.setName("06_view");
    tex_server_map.setName("06_map");
    
    tex_view.allocate(1024, 768, GL_RGBA);
    tex_map.allocate(800, 605, GL_RGBA);

//-------VIEW
//set tracking
    receiver.setup(port_to_listen_to);
    
//set background
    backgroundc=255;
    ofBackground(backgroundc);
    
//set boxes
    
    for (int x=0; x<50; x++) {
        for (int y=0; y<50; y++) {
             ofVec3f cube_pos(int(ofRandom(0, ofGetWidth()/30))*30, int(ofRandom(0, ofGetHeight()/30))*30);
                
            cube_positions.push_back(cube_pos);
            
            float cube_sizex=ofRandom(0, 20);
            float cube_sizey=ofRandom(0, 20);
            float cube_sizez=ofRandom(0, 20);
            
            cube_sizesx.push_back(cube_sizex);
            cube_sizesy.push_back(cube_sizey);
            cube_sizesz.push_back(cube_sizez);

                
            float randomColor=ofRandom(30,240);
                
            color_bank.push_back(randomColor);
               
            
        }
    }
    

    
//set camera
    
   bOrbit = bRoll = false;
    angleH =90.f;
    roll = 90.f;

    depth = 1000.f;
    
    zaxis.set(0,0,1);
    
   
    cam.orbit(angleH, 0 , depth);
    cam.roll(roll);
    cam_rotation = 270.f;
    cam.rotate(cam_rotation,zaxis);
    
    cam.setGlobalPosition(100,0,5);
//    cam.setGlobalPosition(ofGetWindowWidth()/2,ofGetWindowHeight()/2,500);
//
    
   
    
//mapping
   manual=false;
    
    sites.load("Map-Pin.png");
    
    
    subway.load("subway.png");
    
    
    sites.setAnchorPoint(sites.getWidth()/2, 0);
    subway.setAnchorPoint(sites.getWidth()/2, sites.getHeight()/2);
    
  
    
   
    landmark1.set(105,200);
    landmark2.set(105,350);
    landmark3.set(230,350);
    landmark4.set(230,195);
    landmark5.set(410,195);
    landmark6.set(410,300);

    
//front
    myfont.loadFont("Arial Black.ttf", 64);

    
    
//-----MAP
    map.load( "map.png");

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(backgroundc);

    
////tracking
    if(receiver.hasWaitingMessages()){
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        

        if ( msg.getAddress() == "/position/front") {
            front.x = (msg.getArgAsFloat( 0 ));
            front.y = (msg.getArgAsFloat( 1 ));
            
           
        }

        if ( msg.getAddress() == "/position/back" ) {
            back.x = (msg.getArgAsFloat( 0 ));
            back.y = (msg.getArgAsFloat( 1 ));
        }

    }
   
    
//     if (manual==false){

//         position.interpolate(front, 0.1);
        
//         direction.set(front.x-back.x,front.y-back.y,0);
        
//         cam.setGlobalPosition(position[0],position[1],0);
        
// //        cam.setOrientation(direction);
        
// //        ofLog()<<ofToString(cam.getGlobalPosition());


//     }
    
ofLog()<<ofToString(cam.getGlobalPosition());

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //--------MAP
    tex_view.begin();
  
    ofClear(255,255,255, 0);
    ofBackground(backgroundc);
    cam.begin();
  
    ofSetColor(100,100,100);
    ofPushMatrix();
    ofRotate(90, 0, 1, 0);
    ofDrawGridPlane(2,10000,false);
    ofPopMatrix();

    ofEnableDepthTest();
     for(int i = 0; i < cube_positions.size(); i++){
        ofSetColor(color_bank[i],95);
        box.set(cube_sizesx[i],cube_sizesy[i],cube_sizesz[i]);
        box.setPosition(cube_positions[i].x, cube_positions[i].y, cube_positions[i].z+cube_sizesz[i]/2);
        box.draw();
    }
    
    ofPushMatrix();

    ofSetColor(255);
    

    ofPushMatrix();


    ofPushMatrix();
    ofTranslate(landmark1.x,landmark1.y, 0);
    ofRotate(90, 1, 0, 0);
    sites.draw(0,0,30);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(landmark2.x,landmark2.y, 0);
    ofRotate(90, 1, 0, 0);
    sites.draw(0,0,30);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(landmark3.x,landmark3.y, 0);
    ofRotate(90, 1, 0, 0);
    ofRotate(90, 0, 1, 0);
    sites.draw(0,0,30);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(landmark4.x,landmark4.y, 0);
    ofRotate(90, 1, 0, 0);
    sites.draw(0,0,30);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(landmark5.x,landmark5.y, 0);
    ofRotate(90, 1, 0, 0);
    ofRotate(90, 0, 1, 0);
    sites.draw(0,0,30);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(landmark6.x,landmark6.y, 0);
    ofRotate(90, 1, 0, 0);
    subway.draw(0,0,30);
    ofPopMatrix();
   
//    ofDrawIcoSphere(landmark1.x,landmark1.y, 10);
//    ofDrawIcoSphere(landmark2.x,landmark2.y, 10);
//    ofDrawIcoSphere(landmark3.x,landmark3.y, 10);
//    ofDrawIcoSphere(landmark4.x,landmark4.y, 10);
//    ofDrawIcoSphere(landmark5.x,landmark5.y, 10);
//    ofDrawIcoSphere(landmark6.x,landmark6.y, 10);
//
    
 
    cam.end();
    
    ofDisableDepthTest();
    tex_view.end();
    tex_server_view.publishTexture(&tex_view.getTexture());
    tex_view.draw(0, 0);
    
    
    
    
    
    
    //--------MAP
    tex_map.begin();
    map.draw(0, 0);
    tex_map.end();
    tex_server_map.publishTexture(&tex_map.getTexture());
    //tex_map.draw(0, 0);
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'm') {
        manual=!manual;
    }
    if (key == 'a') {
        manual=false;
    }
    if (key == OF_KEY_LEFT) {
        cam.rotate(5.f, zaxis);

    }
    else if (key == OF_KEY_RIGHT) {
        cam.rotate(-5.f, zaxis);

    }
    else if (key == OF_KEY_UP) {
        //find the forward vector
        ofVec3f fwd;
        float angle = 0;
        fwd.set(sin(-angle),cos(-angle), 0);
        
       
        
        cam.move(-cam.getZAxis()*5);
        
    }
    else if (key == OF_KEY_DOWN) {
        cam.move(cam.getZAxis()*5);
        
    }
    
    else if (key == 's') {
        cam.move(cam.getZAxis()*8);
        
    }
    
   
        
    
    else if(key == '1'){
        mysound.load("dumbo american F.mp3");
        mysound.play();
    }
    else if(key == '2'){
        mysound.load("brooklyn bridge chinese F.mp3");
        mysound.play();
    }
    else if(key == '3'){
        mysound.load("greenwood american F.mp3");
        mysound.play();
    }
    else if(key == '4'){
        mysound.load("prospect time chinese voice.mp3");
        mysound.play();
    }
    else if(key == '5'){
        mysound.load("wailliamsburg.mp3");
        mysound.play();
    }
    else if(key == '6'){
        mysound.load("subway.mp3");
        mysound.play();
    }
    else if(key == 'b'){
        backgroundc=0;
        
    }
    else if(key == 'w'){
        backgroundc=255;
       
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
