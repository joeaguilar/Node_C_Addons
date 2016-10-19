// opencvexample.cpp

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>



void affectGamma (std::string infile, std::string outfile, double num) 
{
  cv::Mat image = cv::imread(infile, CV_LOAD_IMAGE_COLOR);
  if (image.empty()) {
    return;
  }

  image = image + cv::Scalar(num, num, num);


  cv::imwrite(outfile, image);
}

// void darken (double num)
// {

// }