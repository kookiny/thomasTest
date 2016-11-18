//
//  GuiApp.cpp
//  ThomasAndFriends_faceSwap_Test_01
//
//  Created by Oscar David Bravo Peña on 11/15/16.
//
//

#include "GuiApp.h"

///Sam's Comment
//--------------------------------------------------------------
void GuiApp::setup(){
    logIn=true;
    onePerson=false;
    TwoPersons=false;
    ofSetFullscreen(false);
    ofBackground(0);
    ofSetVerticalSync(false);
    vidImg.allocate(360, 640, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void GuiApp::update(){
    
}

//--------------------------------------------------------------
void GuiApp::draw(){
    if (logIn) {
        logInScene();
    }
    if (onePerson) {
        onePersonScene();
    }
    if(TwoPersons){
        twoPersonsScene();
    }
}

//--------------------------------------------------------------
void GuiApp::exit(){
    
}

//--------------------------------------------------------------
void GuiApp::mousePressed(int x, int y, int button){
    if (logIn) {
        if (x<ofGetWidth()/2) {
            onePerson=true;
            logIn=false;
            TwoPersons=false;
        }
        else{
            TwoPersons=true;
            logIn=false;
            onePerson=false;
        }
    }
}

// Oscar comment
//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void GuiApp::logInScene(){
    ofBackground(0,0,128);
    ofSetColor(255);
    ofDrawBitmapString("Bienvenido \n\r escoja la cantidad de personas", 0, 10);
    ofDrawBitmapString("una Persona", 0, ofGetHeight()/2);
    ofDrawBitmapString("dos Personas", ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
void GuiApp::onePersonScene(){
    ofBackground(0, 0, 0);
    ofSetColor(255);
    //vidImg.load("something.jpg");
    vidImg.draw(0, 0);
}

//--------------------------------------------------------------
void GuiApp::twoPersonsScene(){
    ofBackground(128, 0, 0);
    ofSetColor(255);
    vidImg.load("something.jpg");
    vidImg.draw(0, 0);
}