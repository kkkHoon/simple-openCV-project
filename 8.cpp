
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
	string imageName("./data/lena_gray.jpg");
	int mask_size = 3;
	int x_mask[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	int y_mask[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat src, gradient_x, gradient_y, result;	
	src = imread(imageName.c_str(), IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	//gradient_x = Mat::zeros(src.size(), src.type());
	//gradient_y = Mat::zeros(src.size(), src.type());
	result = Mat::zeros(src.size(), src.type());
	printf("max : rows, cols = (%d , %d)\n\n", src.rows, src.cols);
	

	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			int old_value = src.at<uchar>(row, col);
			float x_result = 0, y_result = 0;
			int range = (int)(mask_size / 2);
			int mask_x = 0;
			for (int x = -range; x <= range; x++)
			{
				int mask_y = 0;
				for (int y = -range; y <= range; y++)
				{
					if ((col + y >= 0 && col + y < src.cols) && (row + x >= 0 && row + x < src.rows))
					{
						x_result += src.at<uchar>(row + x, col + y) * x_mask[mask_x][mask_y];
						y_result += src.at<uchar>(row + x, col + y) * y_mask[mask_x][mask_y];
					}
					mask_y += 1;
				}
				mask_x += 1;
			}
			//printf("%f, %f\n", x_result, y_result);
			result.at<uchar>(row, col) = sqrt(pow(x_result,2)+pow(y_result,2));
		}
	}
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);

	return 0;
}
