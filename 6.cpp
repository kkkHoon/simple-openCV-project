
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
	string imageName("./data/lena_gray.jpg");
	int mask[3][3] = { {1,2,1},{2,4,2},{1,2,1} };
	const int mask_size = 3;
	float average_factor = 16;

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat src, result;
	
	src = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	printf("max : rows, cols = (%d , %d)\n\n", src.rows, src.cols);
	result = src.clone();

	for (int row = 0; row < result.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int old_value = src.at<uchar>(row, col);
			float sum = 0;
			int mask_x = 0;
			for (int x = -1; x <= 1; x++)
			{
				int mask_y = 0;
				for (int y = -1; y <=1; y++)
				{
					if ((col + y >= 0 && col + y < src.cols) && (row + x >= 0 && row + x < src.rows))
					{
						sum += src.at<uchar>(row + x, col + y) * mask[mask_x][mask_y] / average_factor;
					}
					mask_y += 1;
				}
				mask_x += 1;
			}
			result.at<uchar>(row, col) = sum;
		}
	}


	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);
	return 0;
}
