#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

Mat gblur(Mat& img){
	Mat nim(img.rows,img.cols,CV_8UC1,Scalar(255));

	for(int i =  0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			double sum = 0.25*img.at<uchar>(i,j);
			for(auto p:{2,-2}){
				for(auto q:{2,-2}){
					sum += 0.0625*img.at<uchar>(i+p,j+q);
				}
			}
			for(auto p:{1,-1}){
				for(auto q:{1,-1}){
					sum += 0.125*img.at<uchar>(i+p,j+q);
				}
			}
			nim.at<uchar>(i,j) = (int)sum;
		}
	}

	return nim;
}

Mat edge(Mat& img){
	Mat nim(img.rows,img.cols,CV_8UC1,Scalar(255));

	int th = 30;

	for(int i = 0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			int gx = 0,gy = 0,g;
			for(auto k:{1,0,-1}){
				gx += img.at<uchar>(i+k,j+1) - img.at<uchar>(i+k,j-1);
			}
			for(auto k:{1,0,-1}){
				gy += img.at<uchar>(i+1,j+k) - img.at<uchar>(i-1,j+k);
			}
			g = sqrt(gx*gx+gy*gy);
			if(g>th){
				nim.at<uchar>(i,j) = 0;
			}
			else{
				nim.at<uchar>(i,j) = 255;
			}
		}
	}
	return gblur(nim);
	//return nim;
}

int main(int argc,char* argv[]){
	VideoCapture cap(0);

	if(!cap.isOpened()) return -1;

	namedWindow("win",WINDOW_NORMAL);

	while(1){
		Mat frame;
		cap >> frame;
		cvtColor(frame,frame,CV_RGB2GRAY);
		imshow("win",edge(frame));
		if(((char)waitKey(1)) == 27) break;
	}

	return 0;
}