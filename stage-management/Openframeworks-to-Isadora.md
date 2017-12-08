### OpenFrameworks to Isadora

In order to project your OF project to Isadora, we need to use **Syphon**. Syphon is a protocol that allows you to share graphical frames between applications *on OSX*. Essentially, it allows to send your OF output and use it as an input somewhere else.

---

For the purposes of this document, I've included all the steps necessary. However, I've already done it on all of your projects. This is just for you to understand how it works and to possibly expand on it.

---

#### Using Syphon in OF
1. You need to **include the ofxSyphon addon** into your project. Make sure you have downloaded it from [this repo](https://github.com/astellato/ofxSyphon), and that you have put the downloaded folder in your addons folder.

**image**

2. In order to send frames, you need two objects. One is the actual Syphon server that will send our frames `ofxSyphonServer`. The other one is the object inside which we will draw everything, and which will then be sent, `ofFbo` (FBO stands for *Frame Buffer Object*).

```
# in ofApp.h

ofxSyphonServer mySyphonServer;
ofFbo myFbo;

--------
# in ofApp.cpp

void ofApp::setup(){
  mySyphonServer.setName("OF output");
  myFbo.allocate(1024, 768, GL_RGBA);
}
```

3. You then need to write all of the drawing code inside the FBO, and then tell the server to send the FBO as a texture.

```
void ofApp::draw(){
  myFbo.begin(); //--------- here we begin
  
  ofBackground(0);
  ofSetColor(255);
  ofTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5);
  ofDrawRectangle(-100, -100, 200, 200);
  // ...
  // ...and any other drawing instructions you might have
  
  myFbo.end(); //---------- here we end
  
  mySyphonServer.publishTexture(&myFbo.getTexture());
}
```

4. **What you draw into the FBO will not be drawn to the screen**. Anything that you write *after* you've closed the FBO and you've sent it via the Syphon Server can and will be drawn to your screen. To see the contents of what is in your FBO, simply write:
```
myFbo.draw(0, 0);
```

5. Run your app! If you've added step 4, you should have something on your OF window. Otherwise it should be grey.

6. In order to see what we're sending, we can use [Syphon Simple Client](https://github.com/Syphon/Simple/releases/tag/version-3). It's an application that allows us to look at the frames currently being shared. Open it and, with your OF app running, select the appropriate stream from the top left.

**image of simple client alone**

**image of OF and simple client**

7. Now that we've see we send frames, we can *close Simple Client* and use it as an input source in Isadora!

**isa1**
**isa2**
**isa3**
