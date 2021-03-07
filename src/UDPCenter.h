//
//  UDPCenter.hpp
//
//
//  Created by Fish on 2020/12/30.
//

#ifndef UDPCenter_h
#define UDPCenter_h

#include "ofMain.h"
#include "ofxNetwork.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>

using namespace std;


class UDPCenter{
    
public:
    
    void setup();
    void update();
    void exit();
    
    ofxUDPManager udp_cue;
    bool is_new_message_enable = false;
    string new_image_name;
    
    void popCueMessage(string &current_cue_message);
    
    bool getImageName(string &image_name);
    
    regex reg_standard;
    
    ofxUDPManager udp_watch_dog;
    int watch_dog_timer;
    
    
    
};

#endif /* UDPCenter_h */
