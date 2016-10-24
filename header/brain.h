#ifndef __BRAIN_H__
#define __BRAIN_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include "helper.h"
#include "classifier.h"

using namespace cv;
using namespace std;

class Recognizer
{
	private:
		int k_neighbours;
		bool is_regression;
		int NUM_BASES;

		Mat _eigen_space_; 
		Mat _training_data_; 
		vector<Mat> _images_;
		Mat labels;
		PCA pca;
		//void preprocessing();			// Need to decide parameter

	public:
		Recognizer();
		Recognizer(int,int,bool);
		~Recognizer(){}

		//ASSUMPTION GETTING PREPROCESSED DATA
		//ONLY INTEGER LABELS SUPPORTED
		bool train(Mat, vector<int>&);
		int recognize_face(Mat &face);

		void save(){};
		void load(){};
};

Recognizer::Recognizer()
{
		k_neighbours = 5;
		NUM_BASES = 20;
		is_regression = false;
}

Recognizer::Recognizer(int k_neighbours, int num_eigen = 20, bool is_regression = false)
{
		Recognizer::k_neighbours = k_neighbours;
		Recognizer::NUM_BASES = num_eigen;
		Recognizer::is_regression = is_regression;
}

bool Recognizer::train(Mat training_data, vector<int>&classes, vector<Mat>&images)
{
		//Recognizer::training_data = data.clone();
		Recognizer::labels = Mat(classes, CV_8UC1).t();
		Recognizer::_images_ = images;
		//cout<<labels.rows<<" "<<labels.cols<<endl;
		normalize(training_data, training_data, 0, 255, NORM_MINMAX, CV_8UC1);
		pca = PCA(training_data,Mat(),CV_PCA_DATA_AS_COL,NUM_BASES);	//eigenspace created
		_eigen_space_ = pca.eigenvectors.clone();
		//normalize(_eigen_space_,_eigen_space_, 0, 255, NORM_MINMAX, CV_8UC1);

		//projecting data to facespace
		Mat mat1, mat2, mat3;
		_eigen_space_.convertTo(mat1,CV_32FC1);		//MULTIPLICATION ALLOWED IN CV_32FC1
		training_data.convertTo(mat2,CV_32FC1);
		mat3 = mat1 * mat2;
		mat3.convertTo(_training_data_,CV_32FC1);
		//cout<<_training_data_.rows<<" "<<_training_data_.cols<<endl;
}

int Recognizer::recognize_face(Mat &face)//row
{
		int num_elements = face.rows * face.cols;
		cvtColor(face,face,CV_BGR2GRAY)
		normalize(face, face, 0, 255, NORM_MINMAX, CV_8UC1);
		face.convertTo(face,CV_32FC1);
		Mat _input_;
		//Mat input = pca.project(face.reshape(0,num_elements));
		Mat input = _eigen_space_ * face.reshape(0,num_elements);			//_input_ is a col vector
		input.convertTo(_input_,CV_32FC1);
		//cout<<type_2str(_input_.type())<<endl;
		normalize(_input_, _input_, 0, 255, NORM_MINMAX, CV_32FC1);			//_training_data_ is 20 X 200
		KNearest clf(_training_data_,labels);
		return clf.predict(face);
}

#endif