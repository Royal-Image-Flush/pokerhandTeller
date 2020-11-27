#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int videoncapture_camera();
int videoncapture_basic();