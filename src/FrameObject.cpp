//
//
//  Created by Fish on 2021/1/12.
//

#include <stdio.h>
#include <algorithm>
#include <random>
#include "FrameObject.h"
using namespace cv;
using namespace ofxCv;



FrameObject::FrameObject(){
}

void FrameObject::setup(){
    videoLoader.setup("./Downloads/video.mp4");
    
    Mat emptyMat;
    mat_vector.push_back(emptyMat);
}

void FrameObject::draw(){
    drawMat(image_result, 0, 0 );
//
//    videoLoader.lock();
//    drawMat(videoLoader.video_mat,0,0);
//    videoLoader.unlock();
}

void FrameObject::update(){
    
    if(initImageSize < 3){
        string path = "./Downloads";
        ofDirectory dir(path);
        dir.allowExt("jpg");
        dir.listDir();

        if(!imageLoader.isThreadRunning() && imageLoader.loaded ==false){
            load(dir.getPath(initImageSize));
            initImageSize++;
        }
    }
    
    videoLoader.player.update();
    
    if(videoLoader.loaded == true  && !isRandomResizeVector){
        
        Mat new_mat;
        videoLoader.popMat(new_mat);
        
        int width = ofGetScreenWidth();
        int height = ofGetScreenHeight();
        
        float width_ratio = (float)ofGetScreenWidth() / new_mat.cols;
        float height_ratio = (float)ofGetScreenHeight() / new_mat.rows;
        
        cv::Size dsize;
        cv::Rect roi;
        
        if(width_ratio >= 1 && height_ratio >= 1){
            
            if(width_ratio > height_ratio){
                dsize = cv::Size((int)(new_mat.cols * width_ratio)+1, (int)(new_mat.rows * width_ratio)+1);
                
                roi.x = 0;
                roi.y = ((int)abs(new_mat.rows * width_ratio+1) - height) /2;
            }else{
                dsize = cv::Size((int)(new_mat.cols * height_ratio)+1, (int)(new_mat.rows * height_ratio)+1);
                
                roi.x = ((int)abs(new_mat.cols * height_ratio+1) - width) /2;
                roi.y = 0;
            }
            
        }else if(width_ratio >= 1 && height_ratio <= 1){
            dsize = cv::Size((int)(new_mat.cols * width_ratio)+1,(int)( new_mat.rows * width_ratio)+1);
            
            roi.x = 0;
            roi.y = ((int)abs(new_mat.rows * width_ratio) - height) /2;
            
        }else if(width_ratio <= 1 && height_ratio >= 1){
            dsize = cv::Size((int)(new_mat.cols * height_ratio)+1, (int)(new_mat.rows * height_ratio)+1);
            
            roi.x = ((int)abs(new_mat.cols * height_ratio+1) - width) /2;;
            roi.y = 0;
            
            
        }else if(width_ratio <= 1 && height_ratio <= 1){
            
            if(width_ratio >= height_ratio){
                dsize = cv::Size((int)(new_mat.cols * width_ratio), (int)(new_mat.rows * width_ratio));
                roi.x = 0;
                roi.y = ((int)abs(new_mat.rows * width_ratio - height)) /2;
            }else{
                dsize = cv::Size((int)(new_mat.cols * height_ratio), (int)(new_mat.rows * height_ratio));
                
                roi.x = ((int)abs(new_mat.cols * height_ratio - width)) /2;
                roi.y = 0;
                
            }
        }
        
        roi.width = width;
        roi.height = height;
        
        
        if(new_mat.rows > 0 && new_mat.cols > 0){
            resize(new_mat, new_mat, dsize);
            
            new_mat = new_mat(roi);
            
            mat_vector[0] = new_mat;
            
//            if(mat_vector.size() == 20){
//                mat_vector.pop_back();
//                mat_vector.push_back(new_mat);
//            }else{
//                mat_vector.push_back(new_mat);
//            }
            
            //new_image_timer = ofGetElapsedTimeMillis();
            isNewImageAdd = true;
            currentImageSize = mat_vector.size();
        }
    }
    
    if(imageLoader.loaded == true  && !isRandomResizeVector){
        
        Mat new_mat;
        if(imageLoader.loaded)
            imageLoader.popMat(new_mat);
        else if(videoLoader.loaded)
            videoLoader.popMat(new_mat);
        
        int width = ofGetScreenWidth();
        int height = ofGetScreenHeight();
        
        float width_ratio = (float)ofGetScreenWidth() / new_mat.cols;
        float height_ratio = (float)ofGetScreenHeight() / new_mat.rows;
        
        cv::Size dsize;
        cv::Rect roi;
        
        if(width_ratio >= 1 && height_ratio >= 1){
            
            if(width_ratio > height_ratio){
                dsize = cv::Size((int)(new_mat.cols * width_ratio)+1, (int)(new_mat.rows * width_ratio)+1);
                
                roi.x = 0;
                roi.y = ((int)abs(new_mat.rows * width_ratio+1) - height) /2;
            }else{
                dsize = cv::Size((int)(new_mat.cols * height_ratio)+1, (int)(new_mat.rows * height_ratio)+1);
                
                roi.x = ((int)abs(new_mat.cols * height_ratio+1) - width) /2;
                roi.y = 0;
            }
            
        }else if(width_ratio >= 1 && height_ratio <= 1){
            dsize = cv::Size((int)(new_mat.cols * width_ratio)+1,(int)( new_mat.rows * width_ratio)+1);
            
            roi.x = 0;
            roi.y = ((int)abs(new_mat.rows * width_ratio) - height) /2;
            
        }else if(width_ratio <= 1 && height_ratio >= 1){
            dsize = cv::Size((int)(new_mat.cols * height_ratio)+1, (int)(new_mat.rows * height_ratio)+1);
            
            roi.x = ((int)abs(new_mat.cols * height_ratio+1) - width) /2;;
            roi.y = 0;
            
            
        }else if(width_ratio <= 1 && height_ratio <= 1){
            
            if(width_ratio >= height_ratio){
                dsize = cv::Size((int)(new_mat.cols * width_ratio), (int)(new_mat.rows * width_ratio));
                roi.x = 0;
                roi.y = ((int)abs(new_mat.rows * width_ratio - height)) /2;
            }else{
                dsize = cv::Size((int)(new_mat.cols * height_ratio), (int)(new_mat.rows * height_ratio));
                
                roi.x = ((int)abs(new_mat.cols * height_ratio - width)) /2;
                roi.y = 0;
                
            }
        }
        
        roi.width = width;
        roi.height = height;
        

        resize(new_mat, new_mat, dsize);
    
        new_mat = new_mat(roi);
        
        if(mat_vector.size() == 20){
            mat_vector.pop_back();
            mat_vector.push_back(new_mat);
        }else{
            mat_vector.push_back(new_mat);
        }
        
        new_image_timer = ofGetElapsedTimeMillis();
        isNewImageAdd = true;
        currentImageSize = mat_vector.size();
    }
    
    combine();
    
}

void FrameObject::combine(){
    
    
    Mat image_add_mat;
    float beta;
    int mat_size = currentImageSize;
    
    if(mat_size == 1 && isNewImageAdd)
        image_result = mat_vector.back().clone();
    else{
        
        if(isRandomResizeVector){
//            for(int i = 0; i < mat_size-1; i++){
//                addWeighted(image_result, 1-1.0/mat_size, mat_vector[i], 1.0/mat_size, 0,image_add_mat);
//                image_result = image_add_mat.clone();
//            }
//
//            beta = ofMap(mat_size, 0,20,0,50);
//            image_result.convertTo(image_result, -1,1.3,beta);
//
//            addWeighted(image_result, 1-1.0/mat_vector.size() , mat_vector.back(), 1.0/mat_vector.size(), 0,image_add_mat);
//
//            image_result = image_add_mat.clone();

            isRandomResizeVector = false;
        }
        
        if(isNewImageAdd){
            if(ofGetElapsedTimeMillis() - new_image_timer < 5000){
                if(mat_size>0)
                    image_result = mat_vector.back().clone();
            }else if(ofGetElapsedTimeMillis() - new_image_timer >= 5000 && ofGetElapsedTimeMillis() - new_image_timer <= 10000){
                for(int i = 0; i < mat_size-1 ; i++){
                    addWeighted(image_result, 1-1.0/mat_size, mat_vector[i], 1.0/mat_size, 0,image_add_mat);
                    image_result = image_add_mat.clone();
                }
                
                beta = ofMap(mat_size, 0,20,0,50);
                image_result.convertTo(image_result, -1,1.3,beta);
                
                float ratio = ofMap(ofGetElapsedTimeMillis() - new_image_timer,5000,10000, 1,1.0/mat_vector.size());
                addWeighted(image_result, 1-ratio , mat_vector.back(), ratio, 0,image_add_mat);
                image_result = image_add_mat.clone();
            }else{
                
                for(int i = 0; i < mat_size-1; i++){
                    addWeighted(image_result, 1-1.0/mat_size, mat_vector[i], 1.0/mat_size, 0,image_add_mat);
                    image_result = image_add_mat.clone();
                }
                
                beta = ofMap(mat_size, 0,20,0,50);
                image_result.convertTo(image_result, -1,1.3,beta);
                
                addWeighted(image_result, 1-1.0/mat_vector.size() , mat_vector.back(), 1.0/mat_vector.size(), 0,image_add_mat);
                
                image_result = image_add_mat.clone();
                isNewImageAdd = false;
            }
        }
    }
    
}

void FrameObject::load(string path){
    
    imageLoader.setup(path);
    
}

void FrameObject::randomResizeVector(){
    //    random_shuffle(mat_vector.begin(). mat_vector.end());
    
    if(isRandomResizeVector == false && isNewImageAdd == false){
        auto rng = std::default_random_engine{};

        std::shuffle(std::begin(mat_vector)+1, std::end(mat_vector), rng);
        int randomResizeNumber = (int)ofRandom(-2,2) + (mat_vector.size()-2);

        currentImageSize = randomResizeNumber;
        isRandomResizeVector = true;
    }
}

void FrameObject::popImage(){
    if(mat_vector.size()>1){
        mat_vector.pop_back();
    }
}

void FrameObject::exit(){
    videoLoader.exit();
}
