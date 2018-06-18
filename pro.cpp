#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>

void draw_rectangle(cv::Mat,int,int,int,int);

int main(int argc,char** argv){
	cv::Mat img_1;
	cv::Mat img_2;

	img_1 = cv::imread("Fish/img/0001.jpg");
	img_2 = cv::imread("Fish/img/0199.jpg");

	if((! img_1.data) || (! img_2.data)){
		std::cout << "image not found" << std::endl;
		return -1;
	}

	cv::namedWindow("img_1",cv::WINDOW_AUTOSIZE);
	//cv::Rect RectFor_img1=cv::Rect(134,55,60,88);
	//rectangle(img_1,RectFor_img1,cv::Scalar(0,255,255),1,8,0);
	draw_rectangle(img_1,134,55,60,88);
	cv::imshow("img_1",img_1);


	cv::namedWindow("img_2",cv::WINDOW_AUTOSIZE);
	cv::imshow("img_2",img_2);

	cv::waitKey(0);
	return 0;
}


void draw_rectangle(cv::Mat img,int x, int y,int width,int height){
	cv::Rect RectForImg=cv::Rect(x,y,width,height);
	rectangle(img,RectForImg,cv::Scalar(255,0,255),1,8,0);

}



