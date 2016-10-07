//trying pixel by pixel iteration

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("ragini.img");//Mat(2,3,CV_8UC3,Scalar(1,2,3));
	switch(image.channels())
	{
		case 1:
				{
					MatIterator_<uchar> it,end;
					for(it = image.begin<uchar>(),end = image.end<uchar>();it!=end;++it)
						(*it) += 100;
					break;
				}

		case 3:
				{
					MatIterator_<Vec3b> it = image.begin<Vec3b>(), end = image.end<Vec3b>();
					for(;it!=end;++it)
					{
						(*it)[0] += 100;
						(*it)[1] += 100;
						(*it)[2] += 100;
					}

				}
	}
	imwrite("newragini.jpg",image);
	cout<<format(image,"python");
	return 0;
}