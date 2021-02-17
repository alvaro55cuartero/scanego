#include "WidgetErode.h"

WidgetErode::WidgetErode(QWidget* parent)
	: ItemWidget(parent, "erode")
{
}

void WidgetErode::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7), cv::Point(5, 5));
	erode(in, in, element);
	out.push_back(in);
}

void WidgetErode::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetErode::toJson() {
	nlohmann::json json;
	json["type"] = "erode";
	return json;
}