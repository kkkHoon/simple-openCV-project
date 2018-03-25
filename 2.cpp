// ForOpenCV.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	float a = 0.4, b = 0.6;
	int row_max, col_max;
	string imageName("./data/rena.jpg");
	string imageName2("./data/dog.jpg");

	if (argc > 2)
	{
		imageName = argv[1];
		imageName2 = argv[2];
	}

	Mat image, image2, mixed_image;
	
	image = imread(imageName.c_str(), IMREAD_COLOR);
	image2 = imread(imageName2.c_str(), IMREAD_COLOR);

	if (image.empty() || image2.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// get common area from two images.
	(image.rows <= image2.rows) ? row_max = image.rows : row_max = image2.rows;
	(image.cols <= image2.cols) ? col_max = image.cols : col_max = image2.cols;

	//mixed_image = Mat::zeros(row_max, col_max, IMREAD_COLOR);  <- caused Assersion error, because IMREAD_COLOR = (int)1 so, dimension is only 'one'
	mixed_image = Mat::zeros(row_max, col_max, image.type());
		
	int channel_num = mixed_image.channels();
	for (int ch = 0; ch < channel_num; ch++)
	{
		for (int col = 0; col < col_max; col++)
		{
			for (int row = 0; row < row_max; row++)
			{
				int result = a * image.at<Vec3b>(row, col)[ch] + b * image2.at<Vec3b>(row, col)[ch];
				mixed_image.at<Vec3b>(row, col)[ch] = saturate_cast<uchar>(result);
			}
		}
	}

	namedWindow("Original window", WINDOW_AUTOSIZE);
	imshow("Original window", image);
	namedWindow("Original window2", WINDOW_AUTOSIZE);
	imshow("Original window2", image2);
	namedWindow("Result window", WINDOW_AUTOSIZE);
	imshow("Result window", mixed_image);
	waitKey(0);
	return 0;
}
