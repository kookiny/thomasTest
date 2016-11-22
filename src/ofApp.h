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
    //--------Video----------
    ofVideoGrabber vidGrabber;
    int camWidth,camHeight;
    //----------FaceTracker---------------------
    ofxFaceTracker tracker;
    ofPixels temporal;
    ofVec2f facePosition;
    ofImage imageMask;
    ofImage image, imageBlur;
    //----------shaders-------------------------
    ofShader shader;
    ofImage videoImg;
    void maskedBlur(ofImage& tex, ofImage& mask, ofImage& result);
    
    ofImage src, thomas, mask;
    ofImage srcBlur, thomasBlur;
    cv::Mat dist, sum;
    ofShader cloneShader;
    float multiplier;
    
    void onePersonProcess();
    void twoPersonsProcess();
    
};
