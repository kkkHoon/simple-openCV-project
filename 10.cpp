
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string imageName("./data/Lena_color.png");

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat src,Y,Cb,Cr;	
	src = imread(imageName.c_str(), IMREAD_COLOR);

	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	printf("rows = %d, cols = %d\n", src.rows, src.cols);
	Y = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Cb = Y.clone();
	Cr = Y.clone();

	for (int height = 0; height < src.rows; height++)
	{
		for (int width = 0; width < src.cols; width++)
		{
			float BGR[3];
			for (int i = 0; i <= 2; i++)
				BGR[i] = src.at<Vec3b>(height, width)[i] / 255.0;
			Y.at<uchar>(height, width) = saturate_cast<uchar>(BGR[0] * 24.966 + BGR[1] * 128.533 + BGR[2] * 24.966 + 16);
			Cb.at<uchar>(height, width) = saturate_cast<uchar>(BGR[0] * 112 + BGR[1] * -74.203 + BGR[2] * -37.797 + 128);
			Cr.at<uchar>(height, width) = saturate_cast<uchar>(BGR[0] * -18.214 + BGR[1] * -93.786 + BGR[2] * 112 + 128);
		}
	}


	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("Y", WINDOW_AUTOSIZE);
	imshow("Y", Y);
	namedWindow("Cb", WINDOW_AUTOSIZE);
	imshow("Cb", Cb);
	namedWindow("Cr", WINDOW_AUTOSIZE);
	imshow("Cr", Cr);

	waitKey(0);

	return 0;
}
