
#include "stdafx.h"
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string imageName("./data/rena.jpg");

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat image, result;
	
	image = imread(imageName.c_str(), IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cvtColor(image, image, CV_BGR2GRAY);
	equalizeHist(image, result);

	namedWindow("Original window", WINDOW_AUTOSIZE);
	imshow("Original window", image);

	namedWindow("Result window", WINDOW_AUTOSIZE);
	imshow("Result window", result);
	waitKey(0);
	return 0;
}
