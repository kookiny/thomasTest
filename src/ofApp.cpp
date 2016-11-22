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
    //------------TRACKER---------------------------------------
    tracker.setup();
    temporal.allocate(360, 640, OF_IMAGE_COLOR);
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
    cloneShader.load("","CloneModified.frag");
    multiplier=1.0;
    //------------Image--------------------
    thomas.load("thomas360x640.jpg");
    thomas.setImageType(OF_IMAGE_COLOR);

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
            videoImg.setImageType(OF_IMAGE_COLOR);
            videoImg.save("myFace.jpg");
            tracker.update(toCv(temporal));
        }
    }
    if (gui->TwoPersons) {
        vidGrabber.update();
        if(vidGrabber.isFrameNew()) {
            for (int i = 0; i < temporal.getWidth(); i++) {
                for (int j = 0; j < temporal.getHeight(); j++) {
                    temporal.setColor(i, j, vidGrabber.getPixels().getColor(i+459 , j+39) );
                }
            }
            temporal.mirror(0, 1);
            videoImg.setFromPixels(temporal);
            videoImg.setImageType(OF_IMAGE_COLOR);
            videoImg.save("myFace.jpg");
            tracker.update(toCv(temporal));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (tracker.getFound() && gui->onePerson ) {
        onePersonProcess();
    }
    if (tracker.getFound() && gui->TwoPersons) {
        twoPersonsProcess();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            
            break;
        case OF_KEY_UP:
            multiplier += 0.1;
            multiplier=ofClamp(multiplier, 0.5, 1.6);
            cout<<multiplier<<endl;
            break;
        case OF_KEY_DOWN:
            multiplier -= 0.1;
            multiplier = ofClamp(multiplier, 0.5, 1.6);
            cout<<multiplier<<endl;
            break;
        case OF_KEY_LEFT:
            multiplier -= 0.01;
            multiplier=ofClamp(multiplier, 0.5, 1.6);
            cout<<multiplier<<endl;
            break;
        case OF_KEY_RIGHT:
            multiplier += 0.01;
            multiplier = ofClamp(multiplier, 0.5, 1.6);
            cout<<multiplier<<endl;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::maskedBlur(ofImage& tex, ofImage& mask, ofImage& result) {
    Mat texMat = toCv(tex);
    Mat resultMat = toCv(result);
    Mat maskMat = toCv(mask);
    integral(texMat, sum, CV_32S);
    distanceTransform(maskMat, dist, CV_DIST_L2, 3); // what does CV_DIST_C do?
    dist *= (1 / sqrt(2)); // normalize to the square corner
    resultMat = Scalar(0);
    int rows = resultMat.rows;
    int cols = resultMat.cols;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(maskMat.at<uchar>(row, col) > 0) {
                int k = dist.at<float>(row, col);
                if(k > 0) {
                    int row1 = row - k;
                    int row2 = row + k;
                    int col1 = col - k;
                    int col2 = col + k;
                    Vec3i curResult =
                    sum.at<Vec3i>(row2, col2) -
                    sum.at<Vec3i>(row2, col1) -
                    sum.at<Vec3i>(row1, col2) +
                    sum.at<Vec3i>(row1, col1);
                    float norm = k * 2;
                    norm *= norm;
                    curResult *= 1 / norm;
                    resultMat.at<Vec3b>(row, col) = (Vec3b) curResult;
                } else {
                    resultMat.at<Vec3b>(row, col) = texMat.at<Vec3b>(row, col);
                }
            }
        }
    }
    result.update();
}

//--------------------------------------------------------------
void ofApp::onePersonProcess(){
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
        ofTranslate(190  -  facePosition.x , 260 - facePosition.y);
        ofSetColor(ofColor::white);
        faceMesh.draw();
    ofPopMatrix();
    imageMask.grabScreen(0, 0, 360, 640);
    imageMask.setImageType(OF_IMAGE_GRAYSCALE);
    imageMask.save("mask.png");
    videoImg.draw(360 + 190 -facePosition.x , 260 -facePosition.y );
    src.grabScreen(360, 0, 360, 640);
    src.setImageType(OF_IMAGE_COLOR);
    mask.load("mask.png");
    mask.setImageType(OF_IMAGE_GRAYSCALE);
    imitate(srcBlur, src);
    imitate(thomasBlur, thomas);
    imitate(dist, mask, CV_32FC1);
    maskedBlur(src, mask, srcBlur);
    maskedBlur(thomas, mask, thomasBlur);
    ofEnableAlphaBlending();
    thomas.draw(720, 0,360,640);
    cloneShader.begin();
        cloneShader.setUniformTexture("src", src, 1);
        cloneShader.setUniformTexture("srcBlur", srcBlur, 2);
        cloneShader.setUniformTexture("thomasBlur", thomasBlur, 3);
        cloneShader.setUniform1f("multiplier", multiplier);  //mi linea
        thomas.draw(720, 0,360,640);
        ofImage souvenir;
        souvenir.grabScreen(720, 0, 360, 640);
        souvenir.save("souvenirPicture.jpg");
    cloneShader.end();
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::twoPersonsProcess(){
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
        ofTranslate(190  -  facePosition.x , 260 - facePosition.y);
        ofSetColor(ofColor::white);
        faceMesh.draw();
    ofPopMatrix();
    imageMask.grabScreen(0, 0, 360, 640);
    imageMask.setImageType(OF_IMAGE_GRAYSCALE);
    imageMask.save("mask.png");
    videoImg.draw(360 + 190 -facePosition.x , 260 -facePosition.y );
    src.grabScreen(360, 0, 360, 640);
    src.setImageType(OF_IMAGE_COLOR);
    mask.load("mask.png");
    mask.setImageType(OF_IMAGE_GRAYSCALE);
    imitate(srcBlur, src);
    imitate(thomasBlur, thomas);
    imitate(dist, mask, CV_32FC1);
    maskedBlur(src, mask, srcBlur);
    maskedBlur(thomas, mask, thomasBlur);
    ofEnableAlphaBlending();
    thomas.draw(720, 0,360,640);
    cloneShader.begin();
        cloneShader.setUniformTexture("src", src, 1);
        cloneShader.setUniformTexture("srcBlur", srcBlur, 2);
        cloneShader.setUniformTexture("thomasBlur", thomasBlur, 3);
        cloneShader.setUniform1f("multiplier", multiplier);  //mi linea
        cout<<multiplier<<endl;
        thomas.draw(720, 0,360,640);
        ofImage souvenir;
        souvenir.grabScreen(720, 0, 360, 640);
        souvenir.save("souvenirPicture.jpg");
    cloneShader.end();
    ofDisableAlphaBlending();
}