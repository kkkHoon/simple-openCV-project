
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
	string imageName("./data/lena_gray.jpg");
	int histSize = 256, hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	MatND src_hist_info, dst_hist_info;

	float range[] = { 0, 256 };
	const float* histRange = { range };

	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat src, dst, src_hist, dst_hist;
	src_hist = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	dst_hist = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	
	src = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	equalizeHist(src, dst);
	calcHist(&src, 1, 0, Mat(), src_hist_info, 1, &histSize, &histRange, true, true);
	calcHist(&dst, 1, 0, Mat(), dst_hist_info, 1, &histSize, &histRange, true, true);

	normalize(src_hist_info, src_hist_info,0, src_hist.rows, NORM_MINMAX,-1, Mat());
	normalize(dst_hist_info, dst_hist_info,0, dst_hist.rows, NORM_MINMAX,-1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(src_hist, Point(bin_w*(i - 1), hist_h - cvRound(src_hist_info.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(src_hist_info.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(dst_hist, Point(bin_w*(i - 1), hist_h - cvRound(dst_hist_info.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(dst_hist_info.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	namedWindow("Source", WINDOW_AUTOSIZE);
	imshow("Source", src);
	namedWindow("Source_Hist", WINDOW_AUTOSIZE);
	imshow("Source_Hist", src_hist);

	namedWindow("Dst", WINDOW_AUTOSIZE);
	imshow("Dst", dst);
	namedWindow("Dst_Hist", WINDOW_AUTOSIZE);
	imshow("Dst_Hist", dst_hist);
	waitKey(0);
	return 0;
}
