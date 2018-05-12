
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

int getMaxIndex(vector<int> temp);

int main(int argc, char** argv)
{
	string fore_imageName("./data/chroma_trump.jpg");
	String back_imageName("./data/background.jpg");
	float inner_threshold, outer_threshold;
	int Cb_key, Cr_key;

	printf("Please type inner, outer threshold( 0 <= x <= 1 )\n");
	scanf("%f %f", &inner_threshold, &outer_threshold);
	if (!((0 <= inner_threshold && inner_threshold <= 1) || (0 <= outer_threshold && outer_threshold <= 1)))
		return 0;

	if (argc > 2)
	{
		fore_imageName = argv[1];
		back_imageName = argv[2];
	}

	Mat fore_image, back_image, fore_convert, result_image;
	fore_image = imread(fore_imageName.c_str(), IMREAD_COLOR);
	back_image = imread(back_imageName.c_str(), IMREAD_COLOR);

	if (fore_image.empty() || back_image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	if (fore_image.rows * fore_image.cols >= back_image.rows * back_image.cols)
		cv::resize(back_image, back_image, fore_image.size(), 0, 0, CV_INTER_NN);	// 이미지가 큰 것이 기준이 되게
	else
		cv::resize(fore_image, fore_image, back_image.size(), 0, 0, CV_INTER_NN);
	result_image = Mat::zeros(fore_image.size(), fore_image.type());
	fore_convert = Mat::zeros(fore_image.size(), fore_image.type());
	cvtColor(fore_image, fore_convert, CV_BGR2YCrCb);

	vector<int> hist_Cb(256, 0), hist_Cr(256, 0);
	for (int row = 0; row < fore_image.rows; row++)
	{
		for (int col = 0; col < fore_image.cols; col++)
		{
			hist_Cb[fore_convert.at<Vec3b>(row, col)[1]]++;
			hist_Cr[fore_convert.at<Vec3b>(row, col)[2]]++;
		}
	}
	Cb_key = getMaxIndex(hist_Cb);
	Cr_key = getMaxIndex(hist_Cr);

	float distance, alpha;
	inner_threshold = 90;
	outer_threshold = 100;
	for (int row = 0; row < fore_image.rows; row++)
	{
		for (int col = 0; col < fore_image.cols; col++)
		{
			cv::Vec3f pixel = fore_convert.at<Vec3b>(row, col);
			distance = sqrt(pow(Cb_key - pixel[1], 2) + pow(Cr_key - pixel[2], 2));

			if (distance < inner_threshold)
				alpha = 0.0;
			else if (distance > outer_threshold)
				alpha = 1.0;
			else {
				alpha = (distance - inner_threshold) / (outer_threshold - inner_threshold);
			}
			result_image.at<Vec3b>(row, col) = fore_image.at<Vec3b>(row, col) * (alpha) + back_image.at<Vec3b>(row, col) * (1 - alpha);
		}
	}

	imwrite("result.png", result_image);

	namedWindow("foreground", WINDOW_AUTOSIZE);
	imshow("foreground", fore_image);

	namedWindow("background", WINDOW_AUTOSIZE);
	imshow("background", back_image);

	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result_image);

	waitKey(0);

	return 0;
}

int getMaxIndex(vector<int> temp)
{
	int max = -1, max_index = -1;
	for (int i = 0; i <= 255; i++)
	{
		if (temp[i] > max) {
			max = temp[i];
			max_index = i;
		}
	}
	printf("max_index = %d, max = %d\n", max_index, max);
	return max_index;
}