/**
* @file objectDetection_img.cpp
* @author:wepon 
* @blog: http://2hwp.com
* 这个demo使用opencv实现图片的人脸检测、以及绘画框出人脸、截取人脸等功能。
* 每个功能写成一个函数，方便移植使用。
* 参考：opencv基本绘画、物体检测模块文档。
*/

#include "opencv2\core\core.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include"opencv2\highgui\highgui.hpp"
#include "opencv2\objdetect\objdetect.hpp"

using namespace cv;


/*---- detectFaces函数 -------
检测灰度图片中的人脸，返回人脸矩形坐标(x,y,width,height)
因为可能检测出多个人脸，所以返回类型为vetor<Rect>
------------------------------------------------------*/
vector<Rect> detectFaces(Mat img_gray){
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	vector<Rect> faces;
	face_cascade.detectMultiScale(img_gray,faces,1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
	return faces;
}


/*----  drawFaces函数 -------
在原始图片中用椭圆形圈出人脸
------------------------------------------------------*/
void drawFaces(Mat img,vector<Rect> faces){
	namedWindow("draw faces");
	for(size_t i=0;i<faces.size();i++){
		//先确定人脸矩形中心坐标,再根据该坐标画椭圆
		Point center(faces[i].x + faces[i].width/2,faces[i].y + faces[i].height/2);
		ellipse(img,center,Size(faces[i].width/2,faces[i].height/2),0,0,360,(255,0,0),2,8,0);
	}
	imshow("draw faces",img);
}



int main(){
	//读取图像，转化为灰度图，再进行直方图均衡化
	Mat img = imread("obama.jpg");
	Mat img_gray;
	cvtColor(img,img_gray,COLOR_BGR2GRAY );
	equalizeHist(img_gray,img_gray);
	//检测人脸，画出人脸
	vector<Rect> faces = detectFaces(img_gray);
	drawFaces(img,faces);
	waitKey(0);
	return 0;
}







