#include "header/Brain.h"
#include "header/helper.h"
#include "facedetect"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define NUM_BASES 20
#define ROWS 112
#define COLS 92
using namespace std;
using namespace cv;

int main()
{

	// USE THIS TO FIND FACES IN A GENERALISED IMAGE
	/*Mat image = imread("ragini.jpg");
	detect(image);*/


	char num[8];
	string _str_;
	int start, end;

	cout<<"Enter start: ";
	cin>>start;

	cout<<"Enter end: ";
	cin>>end;

	//loading images
	vector<Mat> images;
	vector<int> labels;

	string dir = "./face_database/s";
	string _currdir_ = dir;
	for(int i=start;i<=end;i++)
	{
		sprintf(num,"%d",i);
		_str_ = num;
		_currdir_ = dir+_str_+"/";
		get_images(_currdir_,images);
		for(int j=0;j<10;j++)
			labels.push_back(i);
	}
	Mat dst = image_matrix(images);
	normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	Mat test = imread("./face_database/s1/1.pgm");
	//cvtColor(test,test,CV_BGR2GRAY);
	//cout<<type_2str(images[0].type())<<" "<<type_2str(test.type())<<endl;

	/*Recognizer nilay;
	nilay.train(dst,labels);
	int prediction = nilay.recognize_face(test);
	cout<<prediction<<endl;
*/

	cvtColor(test,test,CV_BGR2GRAY);
	//cout<<images.size()<<" "<<labels.size()<<endl;
	Recognizer nilay;
	nilay.train(dst,images,labels);
	cout<<nilay.recognize_face(test);
	return 0;
}
