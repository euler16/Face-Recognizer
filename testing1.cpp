#include <opencv2/opencv.hpp>
#include "header/helper.h"

#include <sys/types.h>
#include <dirent.h>

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <string>

using namespace cv;
using namespace std;

int main()
{
	/*Mat image = imread("face_database/s1/1.pgm");
	cout<<image.rows<<" "<<image.cols<<endl;
	cout<<type2str(image.type())<<endl;*/     //testing of type2str

	/*const char* dir = "face_database/s1/";
	cout<<countFiles(dir)<<endl;*/

	//vector<Mat> images;

	/*char *dir = "face_database/s1/";
	cout<<countFiles(dir)<<endl;
	DIR *dr = opendir(dir);
	dirent *ed;
	vector<const char*> files;
	getFiles(dir,files);
	for(int i = 0;i<files.size();++i)
		///cout<<files[i]<<" ";
	cout<<files.size()<<endl;
	if(dr!=NULL)
	{
		int i = 0;
		while(ed = readdir(dr))
		{
			char a[1000];
			sprintf(a,"%s%d.pgm",dir,i+1);
			//cout<<a<<endl;
			//cout<<fileExists(a)<<endl;
			//cout<<imread(a)<<endl;;
			images.push_back(imread(a));
			i++;
		}	
		cout<<images[0].rows<<endl;
	}
	else
		cout<<"NULL"<<endl;
*/
	/*getImages("./face_database/s1/",images);
	cout<<images.size()<<endl;
	cout<<images[0].rows<<endl;*/ //getImages worked!!!

	/*Mat img = Mat(2,3,CV_8UC1);
	Mat image = Mat(3,3,CV_8UC1);
	cout<<img.rows<<" "<<img.cols<<endl;
	resize(img,img,image.size());
	//img = img.reshape(0,6);
	cout<<img.rows<<" "<<img.cols<<endl;*/

	/*vector<Mat> images;
	getImages("./face_database/s1/",images);
	cout<<images.size()<<endl;
	cout<<images[7].rows<<" "<<images[7].cols<<endl;
	Mat dst = image_Matrix(images);
	cout<<dst.rows<<" "<<dst.cols<<endl;*/

	/*char num[8];
	sprintf(num,"%d",1);
	string start_str = num;
	cout<<start_str<<endl;*/
	/*vector<int> a;
	a.push_back(1);
	a.push_back(2);
	Mat m(a,CV_8UC1);
	cout<<m<<endl;

	cout<<m.rows<<" "<<m.cols<<endl;*/	
	//Mat image = imread("./face_database/s1/1.pgm");
	//cout<<image.rows<<" "<<image.cols<<" "<<image.channels()<<endl;
	//cvtColor(image,image,CV_BGR2GRAY);
	//cout<<image.rows<<" "<<image.cols<<" "<<image.channels()<<endl;

	return 0;
}