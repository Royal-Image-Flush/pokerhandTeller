#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

using namespace cv;
using namespace std;


class Card {
private:
	Mat img_src;
	int width;
	int height;

	Mat img_suit;
	Mat img_num;
	string suit;
	string num;

public:
	Card(Mat img);
	bool preprocess();
	string match_suit();
	string match_number();
	Mat getImgSrc() { return img_src; };
};

bool cmp_contour(const vector<Point> cnt1, const vector<Point> cnt2);
int composite(Mat train, Mat query);
void sharpen(const cv::Mat& image, cv::Mat& result);