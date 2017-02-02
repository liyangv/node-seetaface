#include <pthread.h>
#include <cstring>
#include "face_detectionImp.h"
#include "face_detection.h"
#include <vector>
#include <iostream>
#include <cmath>
//using namespace std;

seeta::FaceDetection *g_faceDetector = NULL;

int processFrame(uint8_t* inputFrame,int width,int height)
{

    if (g_faceDetector == NULL) {
        std::cout<<"create g_faceDetector"<<std::endl;
        g_faceDetector = new seeta::FaceDetection("");
        g_faceDetector->SetMinFaceSize(40);
        g_faceDetector->SetScoreThresh(2.f);
        g_faceDetector->SetImagePyramidScaleFactor(0.8f);
        g_faceDetector->SetWindowStep(4, 4);
    }
    std::cout<<"process Frame here"<<std::endl;
        
    seeta::ImageData img_data;
    img_data.data = inputFrame;
    img_data.width = width;
    img_data.height = height;
    img_data.num_channels = 1;
    
    std::vector<seeta::FaceInfo> faces = g_faceDetector->Detect(img_data);
    std::cout<<faces.size()<<" faces detected!"<<std::endl;
    return faces.size();
}
