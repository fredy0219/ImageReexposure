//
//  Created by Fish on 2021/1/12.
//
#include "ofMain.h"
#include "ofVideoPlayer.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;

#ifndef FrameObject_h
#define FrameObject_h

class ImageLoader: public ofThread{
    
public:
    void setup(string imagePath){
        this->path = imagePath;
        loaded = false;
        
        startThread();
    }
    
    void threadedFunction(){
        if(ofLoadImage(image, path)){
            image_mat = toCv(image);
            loaded = true;
            
            cout<<"add new image " + path<<endl;
        }
    }
    
    void popMat(Mat &new_mat){
        new_mat = image_mat.clone();
        loaded = false;
    }
    
    ofImage image;
    Mat image_mat;
    string path;
    bool loaded;
};

class FrameObject{
    
public:
    FrameObject();
    
    void setup();
    void draw();
    void update();
    void load(string path);
    void combine();
    bool isEnableRefresh = false;
    
    ofImage newImage;
    
    int count = 0;
    Mat image_result;
    
    vector<Mat> mat_vector;
    
    void popImage();
    
    ImageLoader imageLoader;
    
    uint64_t new_image_timer;
    bool isNewImageAdd = false;
    
    bool isRandomResizeVector = false;
    int currentImageSize = 0;
    void randomResizeVector();
    //    void superFastBlur(unsigned char *pix, int w, int h, int radius);
    
    int initImageSize = 0;
};

#endif /* FrameObject_h */
