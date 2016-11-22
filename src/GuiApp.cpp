//
//  GuiApp.cpp
//  ThomasAndFriends_faceSwap_Test_01
//
//  Created by Oscar David Bravo Pe√±a on 11/15/16.
//
//

#include "GuiApp.h"

//--------------------------------------------------------------
void GuiApp::setup(){
    logIn=true;
    onePerson=false;
    TwoPersons=false;
    ofSetFullscreen(false);
    ofBackground(0);
    ofSetVerticalSync(false);

    // 1080 X 1920
    
    vidImg.allocate(360, 640, OF_IMAGE_COLOR);
    
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
        if(DEBUG_MODE) {
            logInScene_debug();
        } else {
            logInScene();
        }
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
       if (x < ofGetWidth()/5 && y > ofGetWidth()/5) {
           onePerson=false;
           logIn=true;
           TwoPersons=false;
       }
    }
}

//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void GuiApp::logInScene(){
    ofBackground(120,200,255);
    ofSetColor(255);
    ofTrueTypeFont font;
    font.load("Arial.ttf", 90);
    font.drawString("Bienvenido", 30, 200);
    font.load("Arial.ttf", 55);
    font.drawString("rescoja la cantidad de personas", 30, 300);

    font.load("Arial.ttf", 30);
    btnOnePerson.draw(0, ofGetHeight()/3 * 2 + 20 ,ofGetWidth()/2-30,ofGetWidth()/2-30);
    font.drawString("una Persona pulse aqui", 0 + 50, ofGetHeight() / 3 * 2);
    btnTwoPeople.draw(ofGetWidth()/2, ofGetHeight() / 3 * 2 + 20,ofGetWidth()/2-30,ofGetWidth()/2-30);
    font.drawString("dos Personas pulse aqui", ofGetWidth()/2 + 50, ofGetHeight() / 3 * 2);
    
}

void GuiApp::logInScene_debug(){
    ofBackground(120,200,255);
    ofSetColor(255);
    ofTrueTypeFont font;
    font.load("Arial.ttf", 18);
    font.drawString("Bienvenido \n\rescoja la cantidad de personas", 10, 50);
    //    ofDrawBitmapString("Bienvenido \n\r escoja la cantidad de personas", 0, 10);
    
    
    font.load("Arial.ttf", 13);
    btnOnePerson.draw(0, ofGetHeight()/3 * 2 - 10 ,ofGetWidth()/2-10,ofGetWidth()/2-10);
    font.drawString("una Persona pulse aqui", 0 + 10, ofGetHeight() / 3 * 2 - 20);
    btnTwoPeople.draw(ofGetWidth()/2, ofGetHeight() / 3 * 2 - 10 ,ofGetWidth()/2-10,ofGetWidth()/2-10);
    font.drawString("dos Personas pulse aqui", ofGetWidth()/2 + 10, ofGetHeight() / 3 * 2 - 20);
    
}

//--------------------------------------------------------------
void GuiApp::onePersonScene(){
    ofBackground(0, 0, 0);
    ofSetColor(255);
    
    //vidImg.load("something.jpg");
    vidImg.draw(0, 0);
    
   btnBack.draw(10, ofGetHeight() - 50 - ofGetWidth()/5, ofGetWidth()/5, ofGetWidth()/5);
}

//--------------------------------------------------------------
void GuiApp::twoPersonsScene(){
    ofBackground(128, 0, 0);
    ofSetColor(255);
    
    vidImg.load("something.jpg");
    vidImg.draw(0, 0);
    
    btnBack.draw(10, ofGetHeight() - 50 - ofGetWidth()/5, ofGetWidth()/5, ofGetWidth()/5);
}