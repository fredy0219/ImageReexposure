#pragma once

#include "ofMain.h"
#include "FrameObject.h"
#include "ofxCv.h"
#include "UDPCenter.h"
#include "ofVideoPlayer.h"
#include "ofGstVideoPlayer.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    FrameObject frameObject;
    UDPCenter udpCenter;
    string image_name;
    
    
    uint64 randomResizeTimer;
    uint64 nextRandomResizeTime;
    
    ofVideoPlayer vp;
    
    
};
