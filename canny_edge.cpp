#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
	int low = 20;

	Mat frame = imread(argv[1],1);
	namedWindow("win",WINDOW_NORMAL);
	createTrackbar("track1","win",&low,255);

	cvtColor(frame,frame,CV_RGB2GRAY);
	Mat nim(frame.rows,frame.cols,CV_8UC1,Scalar(0));
	while(1){
		Canny(frame,nim,low,low*3,5);
		imshow("win",nim);
		if((char)waitKey(1) == 27) break;;
	}

	waitKey(0);

	return 0;
}