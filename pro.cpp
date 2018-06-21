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
vector<DMatch> image_matcher(Mat&,Mat&);
void draw_image_matches(Mat&,vector<KeyPoint>&,Mat&,vector<KeyPoint>&,vector<DMatch>&,const char *);

int main(int argc,char** argv){
	Mat img_1;
	Mat img_2;

	// -- step 3 - load the images
	img_1 = imread("Fish/img/0001.jpg",IMREAD_GRAYSCALE);
	img_2 = imread("Fish/img/0199.jpg",IMREAD_GRAYSCALE);

	if((! img_1.data) || (! img_2.data)){
		std::cout << "image not found" << std::endl;
		return -1;
	}


	display_image("img_1",img_1);
	display_image("img_2",img_2);

	// step 4 - draw rectangle and crop the image
	Mat image1_crop=crop_image(img_1,134,55,60,88);
	draw_rectangle(img_1,134,55,60,88);
	display_image("image1_crop",image1_crop);

	// -- step 5 - keypoint calculate and write to csv
	int minHessian=400;
	Ptr<SURF> detector = SURF::create();
	detector->setHessianThreshold(minHessian);

	std::vector<KeyPoint> keypoints_1,keypoints_2,keypoints_1_crop;
	detector->detect(img_1,keypoints_1);
	detector->detect(img_2,keypoints_2);
	detector->detect(image1_crop,keypoints_1_crop);

	vector_to_csv(keypoints_1,"features0001.csv");
	vector_to_csv(keypoints_2,"features0199.csv");
	vector_to_csv(keypoints_1_crop,"features0001_crop.csv");
	//-- step 6 - create feature vector

	Ptr<SURF>  extractor = SURF::create();
	Mat descriptors_1,descriptors_2,descriptors_1_crop;
	extractor->compute(img_1,keypoints_1,descriptors_1);
	extractor->compute(img_2,keypoints_2,descriptors_2);
	extractor->compute(image1_crop,keypoints_1_crop,descriptors_1_crop);

	// -- step 7 - matching 2 images with brute force matcher
        vector<DMatch> matches_1_and_2=image_matcher(descriptors_1,descriptors_2);
	vector<DMatch> matches_1_and_1crop=image_matcher(descriptors_1_crop,descriptors_1);
	vector<DMatch> matches_1crop_and_2=image_matcher(descriptors_1_crop,descriptors_2);

	// -- step 8 - draw lines indicating matcher
	draw_image_matches(img_1,keypoints_1,img_2,keypoints_2,matches_1_and_2,"output/Matches_of_imag_1_and_img_2.jpg");
	draw_image_matches(image1_crop,keypoints_1_crop,img_1,keypoints_1,matches_1_and_1crop,"output/output_matching.jpg");
//	draw_image_matches(image1_crop,keypoints_1_crop,img_2,keypoints_2,matches_1crop_and_2);

	waitKey(0);
	return 0;
}

void draw_image_matches(Mat& img_1,vector<KeyPoint>& keypoints_1,Mat& img_2,vector<KeyPoint>& keypoints_2,vector<DMatch>& matches,const char * image_name){
	Mat img_matches;
        drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);
        imwrite(image_name,img_matches);
}

vector<DMatch> image_matcher(Mat& descriptors_1,Mat& descriptors_2){
	//BFMatcher matcher(NORM_L2);
	FlannBasedMatcher matcher;
        vector<DMatch> matches;
        matcher.match(descriptors_1,descriptors_2,matches);
	return matches;

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


