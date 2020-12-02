#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace cv;
using namespace std;


class Card {
private:
	Mat img_scr;
	int width;
	int height;

	Mat img_suit;
	Mat img_num;
	string suit;
	string num;

public:
	Card(Mat img);
	void preprocess();
	string match_suit();
	string match_number();
};

bool cmp_contour(const vector<Point> cnt1, const vector<Point> cnt2);
int composite(Mat train, Mat query);
void sharpen(const cv::Mat& image, cv::Mat& result);