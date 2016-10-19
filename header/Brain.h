#ifndef __BRAIN_H__
#define __BRAIN_H__

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;

class Recognizer
{
	private:
		int k_neighbours;
		bool is_regression;
		int NUM_BASES;

		Mat _eigen_space_; 
		Mat _training_data_; 
		//vector<Mat> training_data;
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

bool Recognizer::train(Mat training_data, vector<int>&classes)
{
		//Recognizer::training_data = data.clone();
		Recognizer::labels = Mat(classes, CV_8UC1);
		normalize(training_data, training_data, 0, 255, NORM_MINMAX, CV_8UC1);
		pca = PCA(data,Mat(),CV_PCA_DATA_AS_COL,NUM_BASES);	//eigenspace created
		_eigen_space_ = pca.eigenvectors.clone();
		//normalize(_eigen_space_,_eigen_space_, 0, 255, NORM_MINMAX, CV_8UC1);

		//projecting data to facespace
		Mat mat1, mat2, mat3;
		_eigen_space_.convertTo(mat1,CV_32FC1);		//MULTIPLICATION ALLOWED IN CV_32FC1
		training_data.convertTo(mat2.CV_32FC1);
		mat3 = mat1 * mat2;
		mat3.convertTo(_training_data_,CV_32FC1);
}

int Recognizer::recognize_face(Mat &face)//row
{
		normalize(training_data, training_data, 0, 255, NORM_MINMAX, CV_8UC1);
		Mat input = pca.project(face);
		CvKNearest clf(_training_data_.t(),labels);
		return clf.find_nearest(face,k_neighbours);
}

#endif