#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    //-------------VIDEO----------------------------------------
    camWidth  = 1280;
    camHeight = 720;
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth, camHeight);
    vidGrabber.setVerbose(true);
    fboFromVideo.allocate(camWidth, camHeight);
    
    //------------TRACKER---------------------------------------
    tracker.setup();
    temporal.allocate(360, 640, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (gui->logIn) {
        
    }
    if (gui->onePerson) {
        vidGrabber.update();
        if(vidGrabber.isFrameNew()) {
            for (int i = 0; i < temporal.getWidth(); i++) {
                for (int j = 0; j < temporal.getHeight(); j++) {
                    temporal.setColor(i, j, vidGrabber.getPixels().getColor(i+459 , j+39) );
                }
            }
            gui->vidImg.setFromPixels(temporal);
            videoImg.setFromPixels(temporal);
            videoImg.save("something.jpg");
            tracker.update(toCv(temporal));
        }
    }
    if (gui->TwoPersons) {
        vidGrabber.update();
        if(vidGrabber.isFrameNew()) {
            tracker.update(toCv(vidGrabber));
        }
        temporal = vidGrabber.getPixels();
        videoImg.setFromPixels( vidGrabber.getPixels() );
        videoImg.save("something.jpg");
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    tracker.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}