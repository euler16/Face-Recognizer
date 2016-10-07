#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	/*Mat A;
	A = imread("ragini.jpg");
	Mat gray_image;
	cvtColor(A,gray_image,CV_BGR2GRAY);
	//cout<<gray_image<<endl;
	imwrite("gray_image.jpg",gray_image);
	imshow("ragini.jpg",A);
	Mat B = A.clone();
	Mat C(A,Rect(10,10,100,100));*/
	/*int size[3] = {2,2,2};
	Mat B(3,size,CV_8UC(1),Scalar::all(0));
	*///imwrite("test.jpg",B);
	//cout<<B;


/*	Mat R = Mat(78,78,CV_8UC3);
	randu(R,Scalar::all(0),Scalar::all(255));
	imwrite("test.jpg",R);*/
	Mat image = Mat(2,3,CV_8UC3,Scalar(1,2,3));//imread("test.jpg",CV_BGR2GRAY);
	cout<<image.channels();
	cout<<endl<<format(image,"python");

	// traversing the matrix

	int nRows = image.rows;
	int nCols = image.cols*image.channels();
	cout<<endl;
	for(int i=0;i<nRows;++i)
	{
		uchar* p = image.ptr<uchar>(i);				//pointer to the ith row of the image matrix
		for(int j=0;j<nCols;j++)
			cout<<(int)p[j]<<" ";
		cout<<endl;
	}

	cout<<"In the end"<<endl;
	/*Mat_ <uchar> _img = image;				// note the method
	cout<<(int)_img(0,0);*/

	/*Mat_ <Vec3b> _img = image;
	cout<<(int)_img(0,0)[1];*/

	cout<<image.at<Vec3b>(0,0)<<endl;
	cout<<(int)image.at<uchar>(0,0)<<endl;

	/*ALSO STUDY THE LUT() GIVEN AT http://docs.opencv.org/2.4/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html#howtoscanimagesopencv*/

	return 0;
}