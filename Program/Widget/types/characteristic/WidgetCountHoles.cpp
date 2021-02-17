#include "WidgetCountHoles.h"

WidgetCountHoles::WidgetCountHoles(cv::Mat* original, QWidget* parent)
	: CharacteristicWidget(parent, "Counting Holes"), original(original)
{}

void WidgetCountHoles::modificador(cv::Mat in, std::vector<cv::Mat>& out) {}

float WidgetCountHoles::characteristic(cv::Mat in, std::vector<cv::Mat>& out) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat ref, singleLevelHoles, multipleLevelHoles, labels, stats, centroids;
    int nLabels, count = 0;

    (*original).copyTo(in,in);

    cv::cvtColor(in,in,cv::COLOR_BGR2GRAY);
    cv::threshold(in, in, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::dilate(in, in, cv::Mat());

    findContours(in, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    singleLevelHoles = cv::Mat::zeros(in.size(), in.type());
    multipleLevelHoles = cv::Mat::zeros(in.size(), in.type());


    for (std::vector<cv::Vec4i>::size_type idx = 0; idx < hierarchy.size(); ++idx)
    {
        if (hierarchy[idx][3] != -1)
            drawContours(singleLevelHoles, contours, idx, cv::Scalar::all(255), cv::FILLED, 8, hierarchy);
    }

    nLabels = cv::connectedComponentsWithStats(singleLevelHoles, labels, stats, centroids);    //Inverse source image.

    for (int j = 1; j < nLabels; j++) {
        if (stats.at<int>(j, cv::CC_STAT_AREA) > 50) {
            count++;
        }
    }

    nLabels--;
    out.push_back(in);
    return count;
}

void WidgetCountHoles::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetCountHoles::toJson() {
    nlohmann::json json;
    json["type"] = "holes";
    return json;
}