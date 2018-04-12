
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
	float **mask;
	int mask_size;
	float gausian_factor;

	if (argc > 1)
	{
		imageName = argv[1];
	}

	printf("Input gausian filtering mask size(NxN) :\n");
	scanf("%d", &mask_size);

	printf("Input distribution value :\n");
	scanf("%f", &gausian_factor);

	mask = (float **)malloc(sizeof(float) * mask_size);
	for (int row = 0; row < mask_size; row++)
	{
		mask[row] = (float *)malloc(sizeof(float) * mask_size);
	}
	int range = (int)(mask_size / 2);
	int mask_x = 0;
	for (int x = -range; x <= range; x++)
	{
		int mask_y = 0;
		for (int y = -range; y <= range; y++)
		{
			// (x*x + y*y) causes wrong results. Use pow().
				//mask[mask_x][mask_y] = (float)( exp(-1 * (x*x + y*y) / 2 * gausian_factor * gausian_factor) / (2 * 3.14 * gausian_factor * gausian_factor));
			mask[mask_x][mask_y] = exp((-(pow(x, 2) + pow(y, 2))) / (2 * gausian_factor*gausian_factor)) / (2 * 3.14 * gausian_factor * gausian_factor);
			printf("x = %d , y = %d, value = %f\n", mask_x, mask_y, mask[mask_x][mask_y]);
			mask_y += 1;
		}
		mask_x += 1;
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
			int range = (int)(mask_size / 2);
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
			result.at<uchar>(row, col) = sum;
		}
	}


	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);

	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);

	free(mask);
	return 0;
}
