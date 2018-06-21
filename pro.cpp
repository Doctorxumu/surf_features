#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <fstream>
using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void draw_rectangle(Mat,int,int,int,int);
cv::Mat crop_image(Mat,int,int,int,int);
void display_image(const char *,Mat);
void vector_to_csv(vector<KeyPoint>,const char *);

int main(int argc,char** argv){
	Mat img_1;
	Mat img_2;

	img_1 = imread("Fish/img/0001.jpg");
	img_2 = imread("Fish/img/0199.jpg");

	if((! img_1.data) || (! img_2.data)){
		std::cout << "image not found" << std::endl;
		return -1;
	}


	display_image("img_1",img_1);
	display_image("img_2",img_2);

	Mat image1_crop=crop_image(img_1,134,55,60,88);
	draw_rectangle(img_1,134,55,60,88);
	display_image("image1_crop",image1_crop);

	int minHessian=400;
	Ptr<SURF> detector = SURF::create(minHessian);

	std::vector<KeyPoint> keypoints_1,keypoints_2;
	detector->detect(img_1,keypoints_1);
	detector->detect(img_2,keypoints_2);
	
	vector_to_csv(keypoints_1,"features0001.csv");
	vector_to_csv(keypoints_2,"features0199.csv");

	//-- step 6
	Ptr<SURF>  extractor = SURF::create();
	Mat descriptors_1,descriptors_2;
	extractor->compute(img_1,keypoints_1,descriptors_1);

	waitKey(0);
	return 0;
}

void display_image(const char * name,Mat img){
	namedWindow(name,WINDOW_AUTOSIZE);
	imshow(name,img);
}


void draw_rectangle(cv::Mat img,int x, int y,int width,int height){
	Rect RectForImg=cv::Rect(x,y,width,height);
	rectangle(img,RectForImg,Scalar(255,0,255),1,8,0);

}

Mat crop_image(Mat img,int x,int y,int width,int height){
	Rect RectForImg=Rect(x,y,width,height);
	Mat croppedImage=img(RectForImg).clone();
	return croppedImage;

}

void vector_to_csv(vector<KeyPoint> keypoints,const char * filename){
	ofstream features;
        features.open(filename);

        for(int n=0;n<keypoints.size();n++){
                features << keypoints[n].pt.x << "," << keypoints[n].pt.y  << endl;
        }       

        features.close();

}


