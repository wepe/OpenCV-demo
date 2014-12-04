#include<iostream>
#include"opencv2\core\core.hpp"
#include"opencv2\highgui\highgui.hpp"
using namespace cv;
using namespace std;

int main(){
	/*opencv2版本，矩阵结构Mat，函数imread(),nameWindow(),imshow()*/
	Mat img1=imread("D:\\1.jpg");   //注意是双反斜杠,否则读不到图片
	if(!img1.data) {cout<<"error1";return -1;}   //检查有没有读到图片
	namedWindow("图片1");//有两个参数，第二个有默认形参
	imshow("图片1",img1);

	/*opencv老版本，数据结构IplImage，函数cvLoadImage(),cvNamedWindow(),cvShowImage()*/
	IplImage* img2=cvLoadImage("D:\\2.jpg");
	if(!img2)  {cout<<"error2";return -1;} 
	cvNamedWindow("图片2");
	cvShowImage("图片2",img2);

	waitKey(0);
	return 0;
}

