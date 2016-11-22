#include "ofApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(12);
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
    
    //fboFromVideo.allocate(camWidth, camHeight);
    
    //------------TRACKER---------------------------------------
    tracker.setup();
    temporal.allocate(360, 640, OF_IMAGE_COLOR);
    temporal2.allocate(360, 640, OF_IMAGE_COLOR);
    
    //-------------SHADER---------------------------------------
#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
    cout<<"ES2"<<endl;
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shadersGL3/shader");
        cout<<"GL3"<<endl;
    }
    else{
        shader.load("shadersGL2/shader");
        cout<<"GL2"<<endl;
    }
#endif

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
            temporal.mirror(0, 1);
            videoImg.setFromPixels(temporal);
            //videoImg.save("something.jpg");
            tracker.update(toCv(temporal));
        }
    }
    if (gui->TwoPersons) {
        vidGrabber.update();
        if(vidGrabber.isFrameNew()) {
            tracker.update(toCv(vidGrabber));
        }
//        for (int i = 0; i < temporal.getWidth(); i++) {
//            for (int j = 0; j < temporal.getHeight(); j++) {
//                temporal.setColor(i, j, vidGrabber.getPixels().getColor(i+459 , j+39) );
//            }
//        }
//        videoImg.setFromPixels( temporal );
//        videoImg.save("something.jpg");
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (tracker.getFound()) {
        facePosition = tracker.getPosition();
        
        ofPolyline faceOutline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
        vector<ofPoint> facePoints = faceOutline.getVertices();
        ofMesh faceMesh;
        faceMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        faceMesh.setupIndicesAuto();
        for (int i=0; i<(int) facePoints.size(); i++) {
            faceMesh.addVertex(facePoints[i]);
        }
        ofSetColor(ofColor::black);
        ofDrawRectangle(0, 0, 360, 640);
        ofPushMatrix();
            ofTranslate(360/2  -  facePosition.x , 640/2 - facePosition.y);
            ofSetColor(255);
            faceMesh.draw();
        ofPopMatrix();
//        for (int i = 0; i < temporal2.getWidth(); i++) {
//            for (int j = 0; j < temporal2.getHeight(); j++) {
//                temporal2.set
//            }
//        }
    }
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