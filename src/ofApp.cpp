#include "ofApp.h"

using namespace cv;
using namespace ofxCv;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFullscreen(1);
    
    udpCenter.setup();
    randomResizeTimer = 0;
    nextRandomResizeTime = 0;
    frameObject.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    udpCenter.update();
    
    if(ofGetElapsedTimeMillis() - randomResizeTimer > nextRandomResizeTime ){
        frameObject.randomResizeVector();
        nextRandomResizeTime = (int)ofRandom(10000,20000);
        randomResizeTimer = ofGetElapsedTimeMillis();
    }
    
    
    
    if(udpCenter.getImageName(image_name)){
        frameObject.load(image_name);
    }
    //
    frameObject.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    
    frameObject.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
