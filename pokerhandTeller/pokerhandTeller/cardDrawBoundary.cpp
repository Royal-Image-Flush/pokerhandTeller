#include "cardDrawBoundary.h"
void setLabel(Mat& image, string str, vector<Point>& contour)
{
    int fontface = FONT_HERSHEY_SIMPLEX;
    double scale = 0.5;
    int thickness = 1;
    int baseline = 0;

    Size text = getTextSize(str, fontface, scale, thickness, &baseline);
    Rect r = boundingRect(contour);

    Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
    putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

void drawCard(Mat& img, vector<vector<Point>>& ccontours, vector<string>& text) {
    vector<Point2f> approx;
    for (int i = 0; i < ccontours.size(); i++) {
        approxPolyDP(Mat(ccontours[i]), approx, arcLength(Mat(ccontours[i]), true) * 0.02, true);
        line(img, approx[0], approx[1], Scalar(0, 255, 0), 3, 8);
        line(img, approx[1], approx[2], Scalar(0, 255, 0), 3, 8);
        line(img, approx[2], approx[3], Scalar(0, 255, 0), 3, 8);
        line(img, approx[3], approx[0], Scalar(0, 255, 0), 3, 8);

        setLabel(img, text[i], ccontours[i]);
    }
}