#include<iostream>
#include"opencv2\core\core.hpp"
#include"opencv2\highgui\highgui.hpp"
using namespace cv;
using namespace std;
/*
this is for command line:
imgRead_Show.exe D:\\1.jpg D:\\2.jpg
*/
int main(int argc,char** argv){
	/*Version:opencv2;Use:Mat,imread(),nameWindow(),imshow()*/
	Mat img1=imread(argv[1]);  
	if(!img1.data) {cout<<"error1";return -1;}  
	namedWindow("image1");
	imshow("image1",img1);
        waitKey(10);

	/*Version:opencv; Use:IplImage,cvLoadImage(),cvNamedWindow(),cvShowImage()*/
	IplImage* img2=cvLoadImage(argv[2]);
	if(!img2)  {cout<<"error2";return -1;} 
	cvNamedWindow("image2");
	cvShowImage("image2",img2);
        cvWaitKey(10);
	cvReleaseImage(&img2);
	cvDestroyWindow("image2");  
	
	return 0;
}