#include "ofApp.h"
#include <regex>
#include <boost/lexical_cast.hpp>
using namespace cv;
using namespace ofxCv;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFullscreen(1);
//    ofHideCursor();
    udpCenter.setup();
    randomResizeTimer = 0;
    nextRandomResizeTime = 0;
    frameObject.setup();
    
    
    
    //vp.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
    //vp.load("led.mp4");
    //vp.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    udpCenter.update();
    
//    cout<<isOnlyBackground << "," << frameObject.currentImageSize<<endl;
    if(isOnlyBackground == false && frameObject.currentImageSize == 1/*0*/ /*&& frameObject.initImageSize == 3*/){
        isOnlyBackground = true;
        backgroundTimer = ofGetElapsedTimeMillis();
    }else if(frameObject.currentImageSize != 1/*0*/ /*&& frameObject.initImageSize == 3*/){
        isOnlyBackground = false;
    }
    
    if(udpCenter.getImageName(image_name)){
        
        if(hasEnding(image_name, ".jpg")||
           hasEnding(image_name, ".JPG")||
           hasEnding(image_name, ".jpeg")||
           hasEnding(image_name, ".JPEG")||
           hasEnding(image_name, ".png")||
           hasEnding(image_name, ".PNG")||
           hasEnding(image_name, ".tiff")||
           hasEnding(image_name, ".TIFF")){
            frameObject.load("./Downloads/" + image_name, true);
            isOnlyBackground = false;
            randomResizeTimer = ofGetElapsedTimeMillis();
        }/*else if(hasEnding(image_name, ".mp4")||
                 hasEnding(image_name, ".MP4")||
                 hasEnding(image_name, ".m4v")||
                 hasEnding(image_name, ".M4V")){
            frameObject.loadVideo("./Downloads/" + image_name, true, (int)ofRandom(0,3));
            isOnlyBackground = false;
            randomResizeTimer = ofGetElapsedTimeMillis();
        }*/
        
    }
    
    if(ofGetElapsedTimeMillis() - backgroundTimer > 60000*2/*5000*/){
        isOnlyBackground = false;
    }
    
    if(ofGetElapsedTimeMillis() - randomResizeTimer > 5000 && isOnlyBackground == false){
        frameObject.randomResizeVector();
        randomResizeTimer = ofGetElapsedTimeMillis();
    }
    
    //
    frameObject.update();
    
    //vp.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    frameObject.draw();
}

void ofApp::exit(){
    frameObject.exit();
    udpCenter.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

bool ofApp::hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
