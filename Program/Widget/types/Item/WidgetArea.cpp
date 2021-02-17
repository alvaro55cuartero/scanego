#include "WidgetArea.h"


WidgetArea::WidgetArea(QWidget* parent)
	: ItemWidget(parent, "area")
{
}

void WidgetArea::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat o = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);

    cv::findContours(in, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    for (int i = contours.size() - 1; i > 0; i--) {
        int area = cv::contourArea(contours[i]);

        if (hierarchy[i][3] != -1 || area < 200 && area < 5000) {
            contours.erase(contours.begin() + i);
        }
    }

    drawContours(o, contours, (int)-1, cv::Scalar(255,0, 0), -1, cv::LINE_8);


    std::vector<cv::Mat> planes;

    cv::split(o, planes);

	out.push_back(planes[0]);
}

void WidgetArea::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetArea::toJson() {
	nlohmann::json json;
	json["type"] = "area";
	return json;
}