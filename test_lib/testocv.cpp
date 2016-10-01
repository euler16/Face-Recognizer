#include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <opencv2/core/core.hpp>
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main()
{
    // Read image from file
    // Make sure that the image is in grayscale
    Mat img = imread("Windows_Vs_Mac_Vs_Linux_10.jpg",0);
     
    Mat planes[] = {Mat_<float>(img), Mat::zeros(img.size(), CV_32F)};
    Mat complexI;    //Complex plane to contain the DFT coefficients {[0]-Real,[1]-Img}
    merge(planes, 2, complexI);
    dft(complexI, complexI);  // Applying DFT
 
    // Reconstructing original imae from the DFT coefficients
    Mat invDFT, invDFTcvt;
    idft(complexI, invDFT, DFT_SCALE | DFT_REAL_OUTPUT ); // Applying IDFT
    invDFT.convertTo(invDFTcvt, CV_8U); 
    imshow("Output", invDFTcvt);
 
    //show the image
    imshow("Original Image", img);
     
    // Wait until user press some key
    waitKey(0);
    return 0;
}
