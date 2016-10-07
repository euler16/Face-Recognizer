//reading writing image
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

#include <string>

using namespace cv;
using namespace std;

int main()
{
	string imagename = "ragini.jpg";
	Mat image;
	image = imread(imagename,0);
	cout<<image;
	cvNamedWindow("Display Window",WINDOW_AUTOSIZE);
	imshow("Display Window",image);
	return 0;
} 