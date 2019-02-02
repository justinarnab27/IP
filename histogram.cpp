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