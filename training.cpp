#include "header/Brain.h"
#include "header/helper.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define NUM_BASES 20
#define ROWS 112
#define COLS 
using namespace std;
using namespace cv;

int main()
{
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
		labels.push_back(i);
	}
	Mat dst = image_matrix(images);
	normalize(dst, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	//performing PCA
	PCA pca(dst,Mat(),CV_PCA_DATA_AS_COL,NUM_BASES);
	Mat mean_face = pca.mean.clone();//.reshape(1,112);
	normalize(mean_face,mean_face,0,255,NORM_MINMAX,CV_8UC1);
	/*Mat eigenvalues = pca.eigenvalues.clone();
	cout<<eigenvalues<<endl<<endl;
	cout<<eigenvalues.rows<<" "<<eigenvalues.cols<<endl;*/

	//GENERATION OF EIGEN-FACES
	Mat eigenvectors = pca.eigenvectors.clone();						//eigenvectors are stored as rows
	normalize(eigenvectors,eigenvectors,0,255,NORM_MINMAX,CV_8UC1);
	imwrite("./data/eigenmatrix.pgm",eigenvectors);	//SAVING EIGEN VECTORS FOR FURTHER USE
	/*for(int i=0;i<NUM_BASES;++i)
	{
		sprintf(num,"%d",i);
		_str_ = num;
		imwrite(_str_+".pgm",eigenvectors.row(i).reshape(0,112));
	}*/
	//GENERATION OF MEAN-FACES
	//imwrite("mean1.pgm",mean_face.reshape(1,112));


	//storing eigen-vectors and spaces to text file
	/*for(int i=0;i<NUM_BASES;i++)
    {
        ofstream myfile;
        string str = "./data/";
        string extension = ".txt";
        string Result;
        stringstream convert;
        convert << i+1;
        Result = convert.str();
        str.append(Result);
        str.append(extension);
        cout<<str<<endl;
        myfile.open(str.data());
        Mat mat = eigenvectors.row(i);//.t();
        cout<<"Rows = "<<mat.rows <<"columns = "<<mat.cols<<endl;
        myfile<<mat;
        myfile.close();

    }*/


	return 0;
}