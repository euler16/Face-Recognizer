#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
 
int main(int argc, char *argv[])
{
    cv::Mat image = cv::imread("lena.jpg");
    //cv::namedWindow("My Image");
    cv::imshow("My Image", image);
    cv::waitKey(-1);
    return 0;
}