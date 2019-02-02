#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){

	if(argc != 2){
		cout << "No image selected!" << endl;
		return -1;
	}

	Mat img;


	img = imread(argv[1],0);

	if(img.empty()){
		cout << "Failed to load image!" << endl;
		return -1;
	}

	vector<int> inten;
	inten.assign(250,0);

	for(int i = 0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			inten[img.at<uchar>(i,j)]++;
		}
	}

	int mx = *max_element(inten.begin(),inten.end());
	int mn = *min_element(inten.begin(),inten.end());

	Mat dim(512,mx-mn+1,CV_8UC1,Scalar(255));



	for(int i = 0;i!=inten.size();++i){
		line(dim,Point(0,2*i),Point(inten[i],2*i),Scalar(0),2);
	}
	
	namedWindow("win3",WINDOW_NORMAL);
	imshow("win3",img);
	namedWindow("win4",WINDOW_NORMAL);
	imshow("win4",dim);



	vector<double> prob;
	for(int i = 0;i!=inten.size();++i){
		double x =  ((float)inten[i])/(img.rows*img.cols);
		prob.push_back(x);
	}

	for(int i = 0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			double cf = 0;
			for(int k = 0;k!=img.at<uchar>(i,j);++k){
				cf += prob[k];
			}
			img.at<uchar>(i,j) = 255*cf;
		}
	}

	inten.clear();
	inten.assign(256,0);

	for(int i = 0;i!=img.rows;++i){
		for(int j = 0;j!=img.cols;++j){
			inten[img.at<uchar>(i,j)]++;
		}
	}

	mx = *max_element(inten.begin(),inten.end());
	mn = *min_element(inten.begin(),inten.end());

	Mat nim(512,mx-mn+1,CV_8UC1,Scalar(255));

	for(int i = 0;i!=inten.size();++i){
		line(nim,Point(0,2*i),Point(inten[i],2*i),Scalar(0),2);
	}
	
	namedWindow("win",WINDOW_NORMAL);
	imshow("win",img);
	namedWindow("win2",WINDOW_NORMAL);
	imshow("win2",nim);
	waitKey(0);

	return 0;
}