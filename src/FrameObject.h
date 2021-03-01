//
//  Created by Fish on 2021/1/12.
//
#include "ofMain.h"
#include "ofVideoPlayer.h"
#include "ofGstVideoPlayer.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;

#ifndef FrameObject_h
#define FrameObject_h

string type2str(int type);
bool matIsEqual(const cv::Mat Mat1, const cv::Mat Mat2);

class ImageLoader: public ofThread{
    
public:
    void setup(string imagePath,bool _isFromCue){
        this->path = imagePath;
        isFromCue = _isFromCue;
        loaded = false;
        
        try{
            if(!isThreadRunning())
                startThread();
        }catch(...){
            cout<< "start image thread fail"<<endl;
        }
    }
    
    void threadedFunction(){
        
        if(ofFile::doesFileExist(path)){
            
            if(ofLoadImage(image, path)){
                
                try{
                    image_mat = toCv(image);
                    cvtColor(image_mat, image_mat, CV_BGRA2BGR);
                    
                    if(type2str(image_mat.type()) == "8UC3"){
                        loaded = true;
                        
                        cout<<"add new image " + path<<endl;
                    }
                }catch(...){
                    cout<<"cv error in thread"<<endl;
                }
            }
        }
    }
    
    
    Mat popMat(){
        Mat new_mat = image_mat.clone();
        loaded = false;
        isFromCue = false;
        return new_mat;
    }
    
    ofImage image;
    Mat image_mat;
    string path;
    bool loaded;
    bool isFromCue;
};

class VideoLoader: public ofThread{
public:
    void setup(string videoPath, bool _isFromCue, int _index){
        
        try{
            if(!isThreadRunning()){
                index = _index;
                player = *new ofVideoPlayer();
                player.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
                this->path = videoPath;
                
                isPixelsloaded = false;
                isFromCue = _isFromCue;
                if(player.isLoaded())
                    player.close();
                
                
                
                startThread();
            }
            
        }catch(...){
            cout<< "start video thread fail"<<endl;
        }
        
    }
    
    void threadedFunction(){
        
        if(!player.isLoaded()){
            cout<<"hi ~~~"<<endl;
            if(ofFile::doesFileExist(path) && player.load(path)){
                
                player.setVolume(0);
                player.play();
                
                waitTimer = ofGetElapsedTimeMillis();
                isVideoLoaded = true;
                cout<< "load video good"<<endl;
            }else{
                cout<< "load video not good" <<endl;
                return;
            }
        }
        
        while(isThreadRunning() &&player.isLoaded() && isVideoLoaded == true){
            if(player.isFrameNew()){
                
                try{
                    lock();
                    video_mat = toCv(player.getPixels());
                    unlock();
                    isPixelsloaded = true;
                }catch(...){
                    cout<<"cv error in video thread"<<endl;
                }
            }else{
                isPixelsloaded = false;
            }
            
        }
        
    }
    
    Mat popMat(){
        lock();
        Mat new_mat;
        new_mat = video_mat.clone();
        unlock();
        
        return new_mat;
    }
    
    bool isLoaded(){
        return player.isLoaded();
    }
    
    void clean(){
        
        lock();
        isVideoLoaded = false;
        path = "";
        player.stop();
        player.closeMovie();
        video_mat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);
        unlock();
        waitForThread(true);
    }
    
    void exit(){

        stopThread();
    }

    
    ofVideoPlayer player;
    
    bool isVideoLoaded = false;
    ofImage image;
    Mat video_mat;
    string path;
    bool isPixelsloaded = false;
    int index;
    int waitTimer = 0;
    bool isFromCue =false;
    
};

class FrameObject{
    
public:
    FrameObject();
    
    void setup();
    void draw();
    void update();
    void load(string path, bool isFromCue);
    void combine();
    bool isEnableRefresh = false;
    
    ofImage newImage;
    
    int count = 0;
    Mat image_result;
    
    vector<Mat> mat_vector;
    
    void popImage();
    
    ImageLoader imageLoader;
    
    uint64_t new_image_timer = -100000;
    bool isNewImageAdd = false;
    bool isInteractiveImageAdd = false;
    
    bool isRandomResizeVector = false;
    int currentImageSize = 0;
    void randomResizeVector();
    
    bool isRandomReverse = false;
    //    void superFastBlur(unsigned char *pix, int w, int h, int radius);
    
    int initImageSize = 0;
    
    VideoLoader videoLoader1;
    VideoLoader videoLoader2;
    VideoLoader videoLoader3;
    
    void loadVideo(string path, bool isFromCue, int id);
    
    
    void exit();
};

Mat ROI(Mat);


#endif /* FrameObject_h */
