#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>

using namespace cv;

void draw_rectangle(Mat,int,int,int,int);
cv::Mat crop_image(Mat,int,int,int,int);


int main(int argc,char** argv){
	Mat img_1;
	Mat img_2;

	img_1 = imread("Fish/img/0001.jpg");
	img_2 = imread("Fish/img/0199.jpg");

	if((! img_1.data) || (! img_2.data)){
		std::cout << "image not found" << std::endl;
		return -1;
	}

	namedWindow("img_1",WINDOW_AUTOSIZE);
	//cv::Rect RectFor_img1=cv::Rect(134,55,60,88);
	//rectangle(img_1,RectFor_img1,cv::Scalar(0,255,255),1,8,0);
	draw_rectangle(img_1,134,55,60,88);
	imshow("img_1",img_1);


	namedWindow("img_2",WINDOW_AUTOSIZE);
	imshow("img_2",img_2);

	Mat croppedImage=crop_image(img_1,134,55,60,88);
	namedWindow("image1_crop",WINDOW_AUTOSIZE);
	imshow("image1_crop",croppedImage);

	waitKey(0);
	return 0;
}


void draw_rectangle(cv::Mat img,int x, int y,int width,int height){
	Rect RectForImg=cv::Rect(x,y,width,height);
	rectangle(img,RectForImg,Scalar(255,0,255),1,8,0);

}

Mat crop_image(Mat img,int x,int y,int width,int height){
	Rect RectForImg=Rect(x,y,width,height);
	Mat croppedImage=img(RectForImg);
	return croppedImage;

}

