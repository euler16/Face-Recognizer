#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 0.0, double beta = 0.0) {
    // number of samples
    size_t n = src.size();
    // return empty matrix if no matrices given
    if(n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src[0].total();
    // create data matrix
    Mat data(n, d, rtype);
    // now copy data
    for(int i = 0; i < n; i++) {
        // make sure data can be reshaped, throw exception if not!
        if(src[i].total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // get a hold of the current row
        Mat xi = data.row(i);
        // make reshape happy by cloning for non-continuous matrices
        if(src[i].isContinuous()) {
            src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        } else {
            src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        }
    }
    return data;
}

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
	vector<Mat> images;
	images.push_back(imread("ragini.jpg"));
	images.push_back(imread("Am.jpg"));

	cvtColor(images[0],images[0],CV_BGR2GRAY);
	cvtColor(images[1],images[1],CV_BGR2GRAY);
	cout<<type2str(images[0].type())<<endl;
}