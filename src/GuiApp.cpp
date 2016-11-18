//
//  GuiApp.cpp
//  ThomasAndFriends_faceSwap_Test_01
//
//  Created by Oscar David Bravo Pe√±a on 11/15/16.
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

    //-------------VIDEO----------------------------------------
    camWidth  = 640;
    camHeight = 480;

    //------------TRACKER---------------------------------------
    tracker.setup();
    
    //------------BUTTON---------------------------------------
    btnOnePerson.load("thomas1.png");
    btnTwoPeople.load("thomas2.png");
    btnCamera.load("camera.png");
    btnBack.load("back.png");

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
    } else {
       if (x < ofGetWidth()/5 && y < ofGetWidth()/5) {
           onePerson=false;
           logIn=true;
           TwoPersons=false;
       }
    }
}

// Oscar comment
//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void GuiApp::logInScene(){
    ofBackground(120,200,255);
    ofSetColor(255);
    ofTrueTypeFont font;
    font.load("Arial.ttf", 18);
    font.drawString("Bienvenido \n\rescoja la cantidad de personas", 10, 50);
//    ofDrawBitmapString("Bienvenido \n\r escoja la cantidad de personas", 0, 10);
    

    font.load("Arial.ttf", 12);
    btnOnePerson.draw(0, ofGetHeight()/3 * 2 + 10,180,180);
    font.drawString("una Persona pulse aqui", 0 + 5, ofGetHeight() / 3 * 2);
    btnTwoPeople.draw(ofGetWidth()/2, ofGetHeight() / 3 * 2 + 10 ,180,180);
    font.drawString("dos Personas pulse aqui", ofGetWidth()/2 + 5, ofGetHeight() / 3 * 2);
    
}

//--------------------------------------------------------------
void GuiApp::onePersonScene(){
    ofBackground(0, 0, 0);
    ofSetColor(255);
    
    //vidImg.load("something.jpg");
    vidImg.draw(0, 0);
    
    btnBack.draw(10, 10, 50, 50);
}

//--------------------------------------------------------------
void GuiApp::twoPersonsScene(){
    ofBackground(128, 0, 0);
    ofSetColor(255);
    
    vidImg.load("something.jpg");
    vidImg.draw(0, 0);
    
    btnBack.draw(10, 10, 50, 50);
}