#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

Mat canny_edge(Mat& img){
	const int th = 20;
	Mat nim(img.rows,img.cols,CV_8UC1,Scalar(255));
	cvtColor(img,img,CV_RGB2GRAY);

	for(int i = 0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			int gx = 0,gy = 0, g;
			for(auto p : {1,-1}){
				gy += img.at<uchar>(i+p,j-1) - img.at<uchar>(i+p,j+1);
			}
			for(auto p : {1,-1}){
				gx += img.at<uchar>(i+1,j+p) - img.at<uchar>(i-1,j+p);
			}
			gx += 2*(img.at<uchar>(i+1,j) - img.at<uchar>(i-1,j));
			gy += 2*(img.at<uchar>(i,j+1) - img.at<uchar>(i,j+1));

			g = sqrt(gx*gx+gy*gy);

			if(g>th){
				nim.at<uchar>(i,j) = 0;
			}
			else{
				nim.at<uchar>(i,j) = 255;
			}
		}
	}
	return nim;
}

int main(int argc, char* argv[]){

	VideoCapture cap(0);

	while(1){
		Mat frame;
		cap >> frame;

		namedWindow("win",WINDOW_NORMAL);
		imshow("win",canny_edge(frame));

		if((char)waitKey(1) == 27) break;
	}	
	
	return 0;
}