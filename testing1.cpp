#include <opencv2/opencv.hpp>
#include "header/helper.h"

#include <sys/types.h>
#include <dirent.h>

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

	vector<Mat> images;

	char *dir = "face_database/s1/";
	cout<<countFiles(dir)<<endl;
	DIR *dr = opendir(dir);
	dirent *ed;
	if(dr!=NULL)
	{
		int i = 0;
		while(ed = readdir(dr))
		{
			char a[1000];
			sprintf(a,"%s%d.pgm",dir,i+1);
			cout<<a<<endl;
			//cout<<fileExists(a)<<endl;
			//cout<<imread(a)<<endl;;
			images.push_back(imread(a));
			i++;
		}	
		cout<<images[0].rows<<endl;
	}
	else
		cout<<"NULL"<<endl;
	

	
	return 0;
}