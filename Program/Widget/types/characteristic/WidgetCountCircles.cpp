#include "WidgetCountCircles.h"

WidgetCountCircles::WidgetCountCircles(cv::Mat* original, QWidget* parent)
    : CharacteristicWidget(parent, "Counting Circles")
{
    ref = original;
    
}

void WidgetCountCircles::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
}

float WidgetCountCircles::characteristic(cv::Mat in,  std::vector<cv::Mat>& out) {
    double min = 0, max = 0;
    int count = 0;
    cv::Point minp(0,0), maxp(0,0);
    std::vector<cv::Mat> planes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat gray;

    ref->copyTo(gray, in);
    cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);

    int u = gray.type();
    cv::minMaxLoc(gray, &min, &max, &minp, &maxp, in);
    gray.copyTo(gray, in);
    gray = (gray - min) / (max - min) * 255;

    std::vector<cv::Vec3f> circles;

    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, 25, 130, 9, 4, 15);

    cv::findContours(in, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::drawContours(gray,contours,0,cv::Scalar(255));

    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        double r = cv::pointPolygonTest(contours[0], center, false);

        if (r) {
            count++;
            cv::circle(gray, center, 3, cv::Scalar(0, 255, 255), -1);
            cv::circle(gray, center, radius, cv::Scalar(0, 0, 255), 1);
        }
    }

    cv::findContours(in, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    if (contours.size() == 0) return 0;
  
    out.push_back(gray);
    return count;
}

void WidgetCountCircles::jsonParse(nlohmann::json json) {
}

void WidgetCountCircles::setOriginal(cv::Mat* original) {
    ref = original;
}

nlohmann::json WidgetCountCircles::toJson() {
    nlohmann::json json;
    json["type"] = "circles";
    return json;
}