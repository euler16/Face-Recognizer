#include <opencv2/opencv.hpp>
#include "header/helper.h"

#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main()
{
	/*Mat image = imread("face_database/s1/1.pgm");
	cout<<image.rows<<" "<<image.cols<<endl;
	cout<<type2str(image.type())<<endl;*/     //testing of type2str

	const char* dir = "face_database/s1/";
	cout<<countFiles(dir)<<endl;
	return 0;
}