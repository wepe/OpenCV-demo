#include<iostream>
#include"opencv2\core\core.hpp"
#include"opencv2\highgui\highgui.hpp"
using namespace cv;
using namespace std;
/*
命令行模式程序
argc为参数个数，argv[0]表示函数本身的地址，argv[1]表示第一个参数，argv[2]表示第二个参数
比如本程序编译后生成imgRead_Show.exe文件，则可以在命令行模式下运行：
imgRead_Show.exe D:\\1.jpg D:\\2.jpg
*/
int main(int argc,char** argv){
	/*opencv2版本，矩阵结构Mat，函数imread(),nameWindow(),imshow()*/
	Mat img1=imread(argv[1]);  
	if(!img1.data) {cout<<"error1";return -1;}  
	namedWindow("图片1");
	imshow("图片1",img1);
        waitKey(10);

	/*opencv老版本，数据结构IplImage，函数cvLoadImage(),cvNamedWindow(),cvShowImage()*/
	IplImage* img2=cvLoadImage(argv[2]);
	if(!img2)  {cout<<"error2";return -1;} 
	cvNamedWindow("图片2");
	cvShowImage("图片2",img2);
        cvWaitKey(10);
	cvReleaseImage(&img2);
	cvDestroyWindow("图片2");  
	
	return 0;
}