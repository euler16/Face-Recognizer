#ifndef __HELPER_H__
#define __HELPER_H__

#include <opencv2/opencv.hpp>

#include <sys/types.h>     // required for file management
#include <dirent.h>		   // required for file management

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

#define ROWS 112
#define COLS 92

using namespace std;
using namespace cv;


int count_files(const char* dir)
{
	DIR *dr = opendir(dir);
	dirent *ed;
	if(dr != NULL)
	{
		int i = 0;
		while(ed = readdir(dr))
			++i;

		(void)closedir(dr);
		return i;
	} 
	else
		return 0;
}

/*bool fileExists(const char* name)
{
	return (FILE *f = fopen(name,"r"));
}*/


//did not work
void get_files(char*, vector<const char*> &files)
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("c:\\src\\")) != NULL)
	{
  		while ((ent = readdir (dir)) != NULL) 
    		files.push_back(ent->d_name);
 
  		closedir (dir);
	} 
    else 
    {
  		perror ("");
  		//return EXIT_FAILURE;
	}
}

/*==========================================================
     CONSTRUCTS A VECTOR OF MATs FROM A PARTICULAR FOLDER
  ==========================================================*/

void get_images(string dir,vector<Mat>&images)
{

	// dir must end with /
	fstream files;
	string line;
	const char* cmd = ("ls "+dir+" >output.txt").data();
	system(cmd);
	files.open("output.txt");
	while(getline(files,line))
	{
		string image_name = dir+line;
		Mat image = imread(image_name);
		cvtColor(image,image,CV_BGR2GRAY);
		images.push_back(image);
	}
}

/*=======================================================
  	CONVERTS A VECTOR OF MATs INTO A LARGE MAT WITH ALL 
  	image_mats CONVERTED TO COLUMN VECTORS STACKED 
  	SIDE-BY-SIDE
  =======================================================*/

Mat image_matrix(vector<Mat>& src)
{

	//ASSUMTION -> ALL MATRICES HAVE SAME NUMBER OF DIMENSIONS ... NEED TO IMPROVE THIS
	//make use of resize()
	int num_dim2 = src[0].rows * src[0].cols;
	//Mat temp(static_cast<int>(src.size()),num_dim2,CV_8UC1);
	Mat dst(num_dim2,static_cast<int>(src.size()),CV_8UC1);
	/*for(int i=0;i<src.size();++i)
	{
		Mat image_row = src[i].clone().reshape(1,1);
		Mat row_i = temp.row(i);
		image_row.convertTo(row_i,CV_8UC1);
	}
	dst = temp.t();
*/
	for(int i=0;i<src.size();++i)
	{
		Mat image_ = src[i].clone().reshape(1,num_dim2);
		Mat col_i = dst.col(i);
		image_.convertTo(col_i,CV_8UC1);
	}
	return dst;
}

/********************************************
	function to convert images to vectors
********************************************/

Mat as_row_matrix(const vector<Mat>& src, int rtype, double alpha = 0.0, double beta = 0.0)
{
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

void load_eigenvectors(vector<Mat>& eigenvectors,string dir, int num_bases)
{
	char num[8];
	string _str_;
	string _curr_;

	for(int i=0;i<num_bases;++i)
	{
		sprintf(num,"%d",i);
		_str_ = num;
		_curr_ = dir + _str_;
		Mat eigen = imread(_curr_);
		eigenvectors.push_back(eigen);
	}
}

string type_2str(int type) 
{
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

#endif