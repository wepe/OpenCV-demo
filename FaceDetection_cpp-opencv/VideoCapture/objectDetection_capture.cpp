/**
 * @file objectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";  //xml文件保存训练好的haar特征  
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;   //定义两个级联分类器，分别用于检测faces、eyes
string window_name = "Capture - Face detection";
RNG rng(12345);


/**
 * @function main
 */
int main( void )
{
  VideoCapture capture;    //摄像头
  Mat frame;               //frame用于保存摄像头获取的每帧画面

  //-- 1. 用xml文件初始化级联分类器
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  //-- 2. 打开摄像头
  capture.open( -1 );
  if( capture.isOpened() )
  {
    for(;;)   //每隔10ms检测一帧画面，除非用户按下键"C"
    {
      capture >> frame;   //capture >> frame将帧画面赋给frame

      //-- 3. 对该帧画面进行faces、eyes检测
      if( !frame.empty() )
       { detectAndDisplay( frame ); }
      else
       { printf(" --(!) No captured frame -- Break!"); break; }

      int c = waitKey(20);
      if( (char)c == 'c' ) { break; }

    }
  }
  return 0;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;     //容器faces，数据类型为矩形Rect，包括左上顶点(x,y)，宽度width，高度heigth。
   Mat frame_gray;

   cvtColor( frame, frame_gray, COLOR_BGR2GRAY );    //cvtColor函数，将frame转化为灰度图，保存于frame_gray
   equalizeHist( frame_gray, frame_gray );           //equalizeHist函数，直方图均衡化，增强对比度
   //-- 用分类器face_cascade检测出人类，存于容器faces里。detectMultiScale多尺寸检测。
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

   for( size_t i = 0; i < faces.size(); i++ )
    {
      Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );          //人脸矩形的中心坐标
      ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );   //在frame上画椭圆，框出人脸区域

      Mat faceROI = frame_gray( faces[i] );     //faceROI存储的是人脸部分，直接在faceROI上检测eyes，比起在整张图片上检测eyes会更精准和节省计算量
      std::vector<Rect> eyes;

      //-- In each face, detect eyes
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < eyes.size(); j++ )
       {
         Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
         circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );    //在frame上画圆形，框出眼睛。
       }
    }
   //-- Show what you got
   imshow( window_name, frame );
}
