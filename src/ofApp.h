#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFacetracker.h"
#include "GuiApp.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    //-------------------GUI--------------------
    shared_ptr<GuiApp> gui;
    
    //--------IMAGE----------
    ofImage videoImg;
    //--------Video----------
    ofVideoGrabber vidGrabber;
    ofFbo fboFromVideo;
    int camWidth,camHeight;
    
    //----------FaceTracker---------------------
    ofxFaceTracker tracker;
    ofPixels temporal,temporal2;
};
