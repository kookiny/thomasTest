#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    videoImg.load("vidImgBuffer.jpg");
    if (gui->logIn) {
        cout<<"LogInScene";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    videoImg.draw(0,0);
    ofImage buffer;
    buffer.grabScreen(159, 0, 480, 480);
    buffer.save("vidImg.jpg");
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


