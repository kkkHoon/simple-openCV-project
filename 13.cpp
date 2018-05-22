
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int get_closerX(int scaled_x, float scale, int max_x);
int get_closerY(int scaled_y, float scale, int max_y);

int main(int argc, char** argv)
{
	string imageName("./data/rena.jpg");
	float scale;

	printf("Please type scale factor\n");
	scanf("%f", &scale);
	if (scale <= 0)
		return 0;

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat input_image, scaled_image;
	input_image = imread(imageName.c_str(), IMREAD_COLOR);

	if (input_image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	int col_max = input_image.cols, row_max = input_image.rows;
	int scaled_col = (int)(col_max * scale), scaled_row = (int)(row_max * scale);
	scaled_image = Mat::zeros(scaled_row, scaled_col, input_image.type());

	printf("row, col = %d %d\n", row_max, col_max);
	printf("scaled row, col = %d %d\n", scaled_row, scaled_col);
	for (int row = 0; row < scaled_row; row++)
	{
		int closer_y = get_closerY(row, scale, row_max);
		for (int col = 0; col < scaled_col; col++)
		{
			int closer_x = get_closerX(col, scale, col_max);
			scaled_image.at<Vec3b>(row, col) = input_image.at<Vec3b>(closer_y, closer_x);
		}
	}

	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", input_image);

	namedWindow("scaled", WINDOW_AUTOSIZE);
	imshow("scaled", scaled_image);

	waitKey(0);
	return 0;
}

int get_closerX(int scaled_x, float scale, int max_x)
{
	int closer_x = scaled_x / scale;  // 항상 내린 값 얻음.
	if (closer_x + 1 == max_x)
		return closer_x;
	else
		return (scaled_x - closer_x * scale <= (closer_x + 1) * scale - scaled_x) ? closer_x : closer_x + 1;
}

int get_closerY(int scaled_y, float scale, int max_y)
{
	int closer_y = scaled_y / scale;  // 항상 내린 값 얻음.
	if (closer_y + 1 == max_y)
		return closer_y;
	else
		return (scaled_y - closer_y * scale <= (closer_y + 1) * scale - scaled_y) ? closer_y: closer_y + 1;
}