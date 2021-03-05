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
    image_result = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);
    loadVideo("./Downloads/video.mp4", false, 0);
}

void FrameObject::draw(){
    drawMat(image_result, 0, 0 );
}

void FrameObject::update(){
    
//    if(initImageSize < 3){
//        string path = "./Downloads";
//        ofDirectory dir(path);
//        dir.allowExt("JPG");
//        dir.allowExt("jpg");
//        dir.allowExt("jpeg");
//        dir.allowExt("JPEG");
//        dir.allowExt("png");
//        dir.allowExt("PNG");
//        dir.allowExt("tiff");
//        dir.allowExt("TIFF");
//
//        dir.listDir();
//
//        if(!imageLoader.isThreadRunning() && imageLoader.loaded == false){
//            load(dir.getPath((int)ofRandom(0,dir.size())),false);
//            initImageSize++;
//        }
//    }
    
//    cout<<videoLoader.isVideoLoaded<<endl;
    if(videoLoader1.isVideoLoaded){
            videoLoader1.player.update();

        if(videoLoader1.isPixelsloaded == true){
            
            Mat new_mat = ROI(videoLoader1.popMat());
            
            
            if(new_mat.rows > 0 && new_mat.cols > 0){
                
                try{
                    mat_vector[videoLoader1.index] = new_mat.clone();
                    
                    if(mat_vector[videoLoader1.index].cols > 0 && mat_vector[videoLoader1.index].rows > 0)
                        isNewImageAdd = true;
                    currentImageSize = mat_vector.size();
                }catch(cv::Exception& e){
                    cout<<"videoLoader1 update new frame error"<<endl;
                }
            }
            
            new_mat.release();
        }
    }
    
//    if(videoLoader2.isVideoLoaded){
//        videoLoader2.player.update();
//
//        if(videoLoader2.isPixelsloaded == true){
//
//            Mat new_mat = ROI(videoLoader2.popMat());
//
//            if(new_mat.rows > 0 && new_mat.cols > 0){
//
//                try{
//                    mat_vector[videoLoader2.index] = new_mat.clone();
//
//                    if(mat_vector[videoLoader2.index].cols > 0 && mat_vector[videoLoader2.index].rows > 0)
//                        isNewImageAdd = true;
//                    currentImageSize = mat_vector.size();
//                }catch(cv::Exception& e){
//                    cout<<"videoLoader2 update new frame error"<<endl;
//                }
//            }
//            new_mat.release();
//        }
//    }
//
//    if(videoLoader3.isVideoLoaded){
//        videoLoader3.player.update();
//
//        if(videoLoader3.isPixelsloaded == true){
//
//            Mat new_mat = ROI(videoLoader3.popMat());
//
//            if(new_mat.rows > 0 && new_mat.cols > 0){
//
//                try{
//                    mat_vector[videoLoader3.index] = new_mat.clone();
//                    if(mat_vector[videoLoader3.index].cols > 0 && mat_vector[videoLoader3.index].rows > 0)
//                        isNewImageAdd = true;
//
//                    currentImageSize = mat_vector.size();
//
//                }catch(cv::Exception& e){
//                    cout<<"videoLoader3 update new frame error"<<endl;
//                }
//            }
//            new_mat.release();
//        }
//    }
    
    if(imageLoader.loaded == true){
        
        bool isFromCue = imageLoader.isFromCue;
        Mat new_mat = ROI(imageLoader.popMat());
        
        if(mat_vector.size() == 10){
            mat_vector.pop_back();
            mat_vector.push_back(new_mat.clone());
        }else{
            mat_vector.push_back(new_mat.clone());
        }
        
//        if(initImageSize <3)
//            image_result = mat_vector.back().clone();
        
        if(isFromCue)
            new_image_timer = ofGetElapsedTimeMillis();
        isNewImageAdd = true;
        currentImageSize = mat_vector.size();
        
        new_mat.release();
    }
    
    combine();
    
}

void FrameObject::combine(){
    
    
    Mat image_add_mat = cv::Mat::zeros(cv::Size(1920,1080), CV_32F);
    float beta;
    int mat_size = currentImageSize;
    
    if(isNewImageAdd){
        if(ofGetElapsedTimeMillis() - new_image_timer < 10000){
            if(mat_size>0){
                
                if(mat_vector.size()-1 == videoLoader1.index && ofGetElapsedTimeMillis()-videoLoader1.waitTimer <500){
                    
                }else if(mat_vector.size()-1 == videoLoader2.index && ofGetElapsedTimeMillis()-videoLoader2.waitTimer <500){
                    
                }else if(mat_vector.size()-1 == videoLoader3.index && ofGetElapsedTimeMillis()-videoLoader3.waitTimer <500){
                    
                }else{
                    
                    image_result = mat_vector.back().clone();
                }
                
            }
            
        }else if(ofGetElapsedTimeMillis() - new_image_timer >= 10000 && ofGetElapsedTimeMillis() - new_image_timer <= 15000){
            
            for(int i = 0; i < mat_size-1 ; i++){
                try{
                    addWeighted(image_result, 1-1.0/mat_size, mat_vector[i], 1.0/mat_size, 0,image_add_mat);
                    image_result = image_add_mat.clone();
                }catch(cv::Exception& e){
                    cout<<"add weighted error 1"<<endl;
                }
            }
            
            beta = ofMap(mat_size, 0,20,0,50);
            image_result.convertTo(image_result, -1,1.3,beta);
            
            float ratio = ofMap(ofGetElapsedTimeMillis() - new_image_timer,10000,15000, 1,1.0/mat_vector.size());
            
            try{
                addWeighted(image_result, 1-ratio , mat_vector.back(), ratio, 0,image_add_mat);
                image_result = image_add_mat.clone();
            }catch(cv::Exception& e){
                cout<<"add weighted error 2"<<endl;
            }
            
        }else{
            for(int i = 0; i < mat_size-1; i++){
                
                try{
                    addWeighted(image_result, 1-1.0/mat_size, mat_vector[i], 1.0/mat_size, 0,image_add_mat);
                    image_result = image_add_mat.clone();
                }catch(cv::Exception& e){
                    cout<<"add weighted error 3"<<endl;
                }
            }
            
            beta = ofMap(mat_size, 0,20,0,50);
            image_result.convertTo(image_result, -1,1.3,beta);
            
            try{
//                cout<<mat_size<<endl;
                if(mat_size >= 1){
                    addWeighted(image_result, 1-1.0/mat_size , mat_vector.back(), 1.0/mat_size, 0, image_add_mat);
                
                    image_result = image_add_mat.clone();
                }else{
                    image_result = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);
                }
            }catch(cv::Exception& e){
                cout<<"add weighted error 4"<<endl;
            }
            isNewImageAdd = false;
        }
    }
    
    image_add_mat.release();
    
}

void FrameObject::load(string path, bool isFromCue){
    
    imageLoader.setup(path, isFromCue);
    
}

void FrameObject::loadVideo(string path, bool isFromCue, int id){
    
    Mat emptyMat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);;
    mat_vector.push_back(emptyMat.clone());
    videoLoader1.setup(path, isFromCue, mat_vector.size()-1);
    
//    cout<<path<<endl<<videoLoader1.path<<endl<<videoLoader2.path<<endl<<videoLoader3.path<<endl;;
    
//    if(path == videoLoader1.path || path == videoLoader2.path || path == videoLoader3.path)
//        return;
    
//    if(ofFile::doesFileExist(path)){
//        switch(id){
//            case 0:
//            {
//                if(videoLoader1.isVideoLoaded){
//                    cout<<"video 1" << mat_vector.size() <<","<< videoLoader1.index<<endl;
//
//                    if(mat_vector.size() > videoLoader1.index){
////                        mat_vector[videoLoader1.index].release();
//                        mat_vector.erase(mat_vector.begin() + videoLoader1.index);
//                        currentImageSize = mat_vector.size();
//                    }
//                    cout<<"video 1" << mat_vector.size()<<endl;
//                    videoLoader1.clean();
//                }
//
//                Mat emptyMat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);;
//                mat_vector.push_back(emptyMat.clone());
//
//                videoLoader1.setup(path, isFromCue, mat_vector.size()-1);
//                if(videoLoader1.isFromCue == true)
//                    new_image_timer = ofGetElapsedTimeMillis();
//                break;
//            }
//            case 1:
//            {
//                if(videoLoader2.isVideoLoaded){
//                    cout<<"video 2" << mat_vector.size() <<","<< videoLoader2.index<<endl;
//                    if(mat_vector.size() > videoLoader2.index){
////                        mat_vector[videoLoader2.index].release();
//                        mat_vector.erase(mat_vector.begin() + videoLoader2.index);
//                        currentImageSize = mat_vector.size();
//                    }
//                    cout<<"video 2" << mat_vector.size()<<endl;
//                    videoLoader2.clean();
//                }
//
//                Mat emptyMat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);;
//                mat_vector.push_back(emptyMat.clone());
//
//                videoLoader2.setup(path, isFromCue, mat_vector.size());
//
//                if(videoLoader2.isFromCue == true)
//                    new_image_timer = ofGetElapsedTimeMillis();
//                break;
//            }
//            case 2:
//            {
//                if(videoLoader3.isVideoLoaded){
//                    cout<<"video 3" << mat_vector.size()<<","<< videoLoader3.index<<endl;
//                    if(mat_vector.size() > videoLoader3.index){
////                        mat_vector[videoLoader3.index].release();
//                        mat_vector.erase(mat_vector.begin() + videoLoader3.index);
//                        currentImageSize = mat_vector.size();
//                    }
//                    cout<<"video 3" << mat_vector.size()<<endl;
//                    videoLoader3.clean();
//                }
//
//                Mat emptyMat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);
//                mat_vector.push_back(emptyMat.clone());
//
//                videoLoader3.setup(path, isFromCue, mat_vector.size()-1);
//
//                if(videoLoader3.isFromCue == true)
//                    new_image_timer = ofGetElapsedTimeMillis();
//
//                break;
//            }
//
//        }
//    }
}

void FrameObject::randomResizeVector(){
    //    random_shuffle(mat_vector.begin(). mat_vector.end());
    cout << currentImageSize <<","<< isRandomResizeVector <<","<< isNewImageAdd<< endl;
    if(isNewImageAdd == false){
        
        if(isRandomReverse){
            currentImageSize = currentImageSize -1;
            
            if(mat_vector.size()-1 == videoLoader1.index){
                mat_vector.pop_back();
                videoLoader1.clean();
            }else if(mat_vector.size()-1 == videoLoader2.index){
                mat_vector.pop_back();
                videoLoader2.clean();
            }else if(mat_vector.size()-1 == videoLoader3.index){
                mat_vector.pop_back();
                videoLoader3.clean();
            }else{
                mat_vector.pop_back();
            }
            
            isNewImageAdd = true;
            
        }else{
            
            
            int randomImageOrVideo = (int)ofRandom(0,100);
            
            if(randomImageOrVideo >20){
                //load image
                ofDirectory dir("./Downloads");
                dir.allowExt("JPG");
                dir.allowExt("jpg");
                dir.allowExt("jpeg");
                dir.allowExt("JPEG");
                dir.allowExt("png");
                dir.allowExt("PNG");
                dir.allowExt("tiff");
                dir.allowExt("TIFF");
                dir.listDir();
                
                int randomNumber = (int)ofRandom(0,dir.size());
                if(!imageLoader.isThreadRunning() && imageLoader.loaded ==false)
                    load(dir.getPath(randomNumber),false);
            }/*else{
                //load video
                ofDirectory dir("./Downloads");
                dir.allowExt("mp4");
                dir.allowExt("MP4");
                dir.allowExt("m4v");
                dir.allowExt("M4V");
                dir.listDir();
                int randomNumber = (int)ofRandom(0,dir.size());
                int randomVideoLoader = (int)ofRandom(0,3);
                if(!imageLoader.isThreadRunning() && imageLoader.loaded ==false)
                    loadVideo(dir.getPath(randomNumber), false, randomVideoLoader);
            }*/
        }
        
        
        if(currentImageSize > 10-1){
            isRandomReverse = true;
            std::reverse(mat_vector.begin()+1, mat_vector.end());
        }
        else if(currentImageSize ==1){
            isRandomReverse = false;
        }
    }
}

void FrameObject::popImage(){
    if(mat_vector.size()>1){
        mat_vector.pop_back();
    }
}

void FrameObject::exit(){
    videoLoader1.exit();
    videoLoader2.exit();
    videoLoader3.exit();
}


Mat ROI(Mat new_mat){
    
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
    }else{
        new_mat = cv::Mat::zeros(cv::Size(ofGetScreenWidth(),ofGetScreenHeight()), CV_8UC3);
    }
    
    return new_mat;
    
}

string type2str(int type) {
    string r;
    
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);
    
    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }
    
    r += "C";
    r += (chans+'0');
    
    return r;
}

bool matIsEqual(const cv::Mat Mat1, const cv::Mat Mat2)
{
    if( Mat1.dims == Mat2.dims &&
       Mat1.size == Mat2.size &&
       Mat1.elemSize() == Mat2.elemSize())
    {
        if( Mat1.isContinuous() && Mat2.isContinuous())
        {
            return 0==memcmp( Mat1.ptr(), Mat2.ptr(), Mat1.total()*Mat1.elemSize());
        }
        else
        {
            const cv::Mat* arrays[] = {&Mat1, &Mat2, 0};
            uchar* ptrs[2];
            cv::NAryMatIterator it( arrays, ptrs, 2);
            for(unsigned int p = 0; p < it.nplanes; p++, ++it)
                if( 0!=memcmp( it.ptrs[0], it.ptrs[1], it.size*Mat1.elemSize()) )
                    return false;
            
            return true;
        }
    }
    
    return false;
}
