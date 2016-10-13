#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("0.png");
	cout<<image.rows<<" "<<image.cols;
	
	return 0;
}