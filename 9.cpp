
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
	string imageName("./data/blur_rena_gray.jpg");
	int mask_size = 3;
	int mask[3][3] = { {-1,-1,-1},{-1,8,-1},{-1,-1,-1} };

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat src, filtered, result;	
	src = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	filtered = Mat::zeros(src.size(), src.type());
	result = Mat::zeros(src.size(), src.type());
	printf("max : rows, cols = (%d , %d)\n\n", src.rows, src.cols);
	

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int old_value = src.at<uchar>(row, col);
			float sum = 0;
			int range = (int)(mask_size / 2);
			int mask_x = 0;
			for (int x = -range; x <= range; x++)
			{
				int mask_y = 0;
				for (int y = -range; y <= range; y++)
				{
					if ((col + y >= 0 && col + y < src.cols) && (row + x >= 0 && row + x < src.rows))
					{
						sum += src.at<uchar>(row + x, col + y) * mask[mask_x][mask_y];
					}
					mask_y += 1;
				}
				mask_x += 1;
			}
			//printf("%f\n", sum);
			//result.at<uchar>(row, col) = saturate_cast<uchar>(old_value + abs(sum));
			filtered.at<uchar>(row, col) = saturate_cast<uchar>(sum);
			result.at<uchar>(row, col) = saturate_cast<uchar>(sum + old_value);
		}
	}

	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("filtered", WINDOW_AUTOSIZE);
	imshow("filtered", filtered);

	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);

	return 0;
}
