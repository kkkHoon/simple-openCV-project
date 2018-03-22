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
	string imageName("./data/rena.jpg");
	float a = 2.2, b = 50;
	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat image, new_image;
	
	image = imread(imageName.c_str(), IMREAD_COLOR);
	//printf("%d, %d, %d", image.rows, image.cols, image.channels());

	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	new_image = Mat::zeros(image.size(), image.type());

	int channel_num = image.channels();
	for (int ch = 0; ch < channel_num; ch++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			for (int row = 0; row < image.rows; row++)
			{
				int result = image.at<Vec3b>(row, col)[ch] * a + b;
				new_image.at<Vec3b>(row, col)[ch] = saturate_cast<uchar>(result);
			}
		}
	}

	namedWindow("Original window", WINDOW_AUTOSIZE);
	imshow("Original window", image);
	namedWindow("Changed window", WINDOW_AUTOSIZE);
	imshow("Changed window", new_image);
	waitKey(0);
	return 0;
}
