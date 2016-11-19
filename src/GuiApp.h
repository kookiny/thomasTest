//
//  GuiApp.h
//  ThomasAndFriends_faceSwap_Test_01
//
//  Created by Oscar David Bravo Peña on 11/15/16.
//
//

#ifndef GuiApp_h
#define GuiApp_h

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxFacetracker.h"

//////////////////////////////
// For size of screen
// if you want to show in a small window fits to small monitor DEBUG_MODE 1
// if you want to show in a big window fits to big TV DEBUG_MODE 0
//////////////////////////////

#define DEBUG_MODE 0

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    void mousePressed(int x, int y , int button);
    //-----------------Scenes-------------------
    void logInScene();
    void logInScene_debug();
    void onePersonScene();
    void twoPersonsScene();
    //------------Boolean Scenes----------------
    bool logIn,onePerson,TwoPersons;
    //--------------Video-----------------------
    ofImage vidImg;
    
    ofImage btnOnePerson;
    ofImage btnTwoPeople;
    ofImage btnCamera;
    ofImage btnBack;
    
    int camWidth,camHeight;
    //----------FaceTracker---------------------
    ofxFaceTracker tracker;

};

#endif /* GuiApp_h */
