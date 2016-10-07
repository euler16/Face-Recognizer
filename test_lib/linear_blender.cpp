#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>

using namespace cv;
using namespace std;


string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}


int main()
{
	Mat img1 = imread("Am.jpg");
	Mat img2 = imread("ragini.jpg");
	int row = img1.rows;
	int col = img1.cols;
	string type = type2str(img1.type());
	cout<<type<<endl;
	/*Size_<int> s1 = Size_<int>(img1.rows,img1.cols); //note this
	resize(img2,img2,s1);*/ // note this	///not working

	resize(img2,img2,img1.size());

	float alpha = 0.0;
	Mat blend = Mat(row,col,CV_8UC3);

	/*for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			blend.at<Vec3b>(i,j) = alpha*img1.at<Vec3b>(i,j) + (1-alpha)*img2.at<Vec3b>(i,j);
	}*/	//ALITER
	addWeighted(img1,alpha,img2,1-alpha,0.0,blend);


	imwrite("blend.jpg",img2);

	return 0;
}