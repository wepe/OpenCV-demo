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

#include<sstream>
#include<string>

using namespace cv;
using namespace std;

/*---- detectFaces函数 -------
检测灰度图片中的人脸，返回人脸矩形坐标(x,y,width,height)
因为可能检测出多个人脸，所以返回类型为vetor<Rect>
------------------------------------------------------*/
vector<Rect> detectFaces(Mat img_gray){
	CascadeClassifier faces_cascade;
	faces_cascade.load("haarcascade_frontalface_alt.xml");
	vector<Rect> faces;
	faces_cascade.detectMultiScale(img_gray,faces,1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
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
		ellipse(img,center,Size(faces[i].width/2,faces[i].height/1.5),0,0,360,Scalar(0,255,0),2,8,0);
	}
	imshow("draw faces",img);
}


/*----  saveFaces函数 -------
用detectFaces函数检测出人脸区域，然后保存这些人脸。
保存路径以及保存文件名设置为saveName，按序号依次命名，
存于D盘的faces文件夹下（faces文件夹需事先创建）。
------------------------------------------------------*/
void saveFaces(Mat img,Mat img_gray){
	vector<Rect> faces = detectFaces(img_gray);
	for(size_t i=0; i<faces.size();i++){
		stringstream buffer;
		buffer<<i;
		string saveName = "D:/faces/"+ buffer.str() + ".jpg";
		Rect roi = faces[i];
		imwrite(saveName,img(roi));
	}
}


/*----  detectDrawEyes函数 -------
检测并用圆形画出眼睛区域。
先用detectFaces函数检测出人脸区域，然后再在这些人脸区域检测眼睛，
这样做既可以增加精确度又可以节省计算量。
------------------------------------------------------*/
void detectDrawEyes(Mat img,Mat img_gray){
	vector<Rect> faces = detectFaces(img_gray);
	for(size_t i=0; i<faces.size();i++){
		Mat faceROI = img_gray(faces[i]);
		CascadeClassifier eyes_cascade;
		eyes_cascade.load("haarcascade_eye.xml");
		vector<Rect> eyes;
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
		//用圆形框出眼睛区域
		for(size_t j=0;j<eyes.size();j++){
			Point eyes_center(faces[i].x+eyes[j].x+eyes[j].width/2,faces[i].y+eyes[j].y+eyes[j].height/2);
			int r = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(img,eyes_center,r,Scalar(255,0,0),1,8,0);
		}
	}
	namedWindow("detect and draw eyes");
	imshow("detect and draw eyes",img);
}



int main(){
	//读取图像，转化为灰度图，再进行直方图均衡化
	Mat img = imread("obama.jpg");
	Mat img_gray;
	cvtColor(img,img_gray,COLOR_BGR2GRAY );
	equalizeHist(img_gray,img_gray);
	//检测人脸，保存人脸,画出人脸,画出眼睛
	vector<Rect> faces = detectFaces(img_gray);
	saveFaces(img,img_gray);
	drawFaces(img,faces);
	detectDrawEyes(img,img_gray);
	waitKey(0);
	return 0;
}







