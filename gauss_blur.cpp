#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc,char* argv[]){

	if(argc != 2){
		cout << "Image not selected!" << endl;
		return -1;
	}

	Mat img = imread(argv[1],0);

	if(img.empty()){
		cout << "Image could not be opened!" << endl;
		return -1;
	}

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

	namedWindow("win",WINDOW_NORMAL);
	imshow("win",img);
	namedWindow("win2",WINDOW_NORMAL);
	imshow("win2",nim);
	waitKey(0);

	return 0;
}