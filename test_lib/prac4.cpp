#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat A = Mat(2,3,CV_8UC1);
	cout<<format(A,"python")<<endl;
	cout<<A.rows<<" "<<A.cols<<endl;
	Mat B = A.rows(0);
	cout<<format(B,"python")<<endl;
	cout<<B.rows<<" "<<B.cols<<endl;
	return 0;
}