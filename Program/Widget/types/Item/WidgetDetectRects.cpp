#include "WidgetDetectRects.h"

WidgetDetectRects::WidgetDetectRects(QWidget* parent)
	: ItemWidget(parent, "detectRect")
{
}

void WidgetDetectRects::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
    std::vector<cv::Mat> planes;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat stats, centroids, mask, labels, mat(cv::Size(640, 480), CV_8UC3);
    int nLabels;
    
    nLabels = cv::connectedComponentsWithStats(in, labels, stats, centroids);
    for (int j = 1; j < nLabels; j++) {
        mat = cv::Mat::zeros(cv::Size(640,480), CV_8UC3);
        contours.clear();
        planes.clear();
        mask = (labels == j);
        findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        int area = cv::contourArea(contours[0]);
        if (area > 500) {
            cv::RotatedRect box = cv::minAreaRect(contours[0]);
            cv::Point2f vertices2f[4];
            cv::Point vertices[4];

            box.points(vertices2f);
            
            for (int i = 0; i < 4; ++i) {
                vertices[i] = vertices2f[i];
            }

            cv::fillConvexPoly(mat, vertices, 4, cv::Scalar(255, 0, 0));

            cv::split(mat, planes);
	        out.push_back(planes[0]);
            
        }
    }
}

void WidgetDetectRects::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetDetectRects::toJson() {
	nlohmann::json json;
	json["type"] = "detectRect";
	return json;
}