#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>

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
	cv::imshow("img_1",img_1);


	cv::namedWindow("img_2",cv::WINDOW_AUTOSIZE);
	cv::imshow("img_2",img_2);

	cv::waitKey(0);
	return 0;
}

