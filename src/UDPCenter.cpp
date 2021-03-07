//
//  UDPCenter.cpp
//
//
//  Created by Fish on 2020/12/30.
//

#include "UDPCenter.h"
#include "ofMain.h"
#include <boost/lexical_cast.hpp>
//using namespace std;

void UDPCenter::setup(){
    
    udp_cue.Create();
    udp_cue.Bind(11999);
    udp_cue.SetNonBlocking(true);
    
    udp_watch_dog.Create();
    udp_watch_dog.Connect("127.0.0.1", 54000);
    udp_watch_dog.SetNonBlocking(true);
    
    
    
    reg_standard = regex("\/(add)\/([a-zA-Z0-9\-_. ]+)\/");
}

void UDPCenter::update(){
    char udp_message[100];
    int message_length = udp_cue.Receive(udp_message,100);
    
    smatch cue_match;
    
    
    //put message into cue_queue
    if(message_length > 0){
        new_image_name = string(udp_message);
        
        if(regex_match(new_image_name, cue_match, reg_standard)){
            cout<<"match"<<endl;
            cout<<new_image_name<<endl;
            
            new_image_name = cue_match[2];
            is_new_message_enable = true;
        }else{
            cout<<"not match"<<endl;
        }
    }
    
    if(ofGetElapsedTimeMillis() - watch_dog_timer > 5000){
        
        string alive = "I'm alive.";
        udp_watch_dog.Send(alive.c_str(),alive.size());
        watch_dog_timer = ofGetElapsedTimeMillis();
    
    }
    
}

bool UDPCenter::getImageName(string &image_name){
    
    if(is_new_message_enable){
        image_name = new_image_name;
        is_new_message_enable = false;
        return true;
    }else{
        return false;
    }
    
}
//void UDPCenter::popCueMessage(string &current_cue_message){
//
//    if(cue_queue.size() > 0){
//        current_cue_message = cue_queue.front();
//        cue_queue.pop();
//    }else
//        current_cue_message = "";
//}

void UDPCenter::exit(){
    
    udp_cue.Close();
}
