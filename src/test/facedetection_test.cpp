/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
 *
 * This file is an example of how to use SeetaFace engine for face detection, the
 * face detection method described in the following paper:
 *
 *
 *   Funnel-structured cascade for multi-view face detection with alignment awareness,
 *   Shuzhe Wu, Meina Kan, Zhenliang He, Shiguang Shan, Xilin Chen.
 *   In Neurocomputing (under review)
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developed by Shuzhe Wu (a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include "face_detection.h"
#include "face_detectionImp.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
      cout << "Usage: bin videoIndex"<< endl;
      return -1;
  }

  //const char* img_path = argv[1];
  cv::VideoCapture capture(1);
  capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
  capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  

  while(1){
    cv::Mat img;// = cv::imread(img_path, cv::IMREAD_UNCHANGED);
    cv::Mat img_gray;
    capture>>img;
    if(img.empty()) break;
    if (img.channels() != 1)
      cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    else
      img_gray = img;

      
      processFrame((char *)img_gray.data,img_gray.cols,img_gray.rows,false);
      int xLeft,xRight,yTop,yBottom;
      getFacesExternalRegion(&xLeft,&xRight,&yTop,&yBottom);

      if(xLeft >= 0 && xRight > xLeft && yTop >= 0 && yBottom > yTop){
          cv::rectangle(img, cv::Rect(xLeft,yTop,xRight - xLeft,yBottom - yTop), CV_RGB(0, 0, 255), 4, 8, 0);
      }
    cv::imshow("disp",img);
    cv::waitKey(10);
  }
}
