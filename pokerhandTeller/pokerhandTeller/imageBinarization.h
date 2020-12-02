#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <limits>

using namespace cv;
using namespace std;

Mat removeShadow(Mat src_Image);
