#pragma once

#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<cstdio>
#include<math.h>
#include<algorithm>
#include<vector>

using namespace cv;
using namespace std;
void setLabel(Mat& image, string str, vector<Point>& contour);
void drawCard(Mat& img, vector<vector<Point>>& ccontours, vector<string>& text);