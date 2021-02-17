#include "WidgetDilate.h"

WidgetDilate::WidgetDilate(QWidget* parent)
	: ItemWidget(parent, "dilate")
{
}

void WidgetDilate::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7), cv::Point(5, 5));
	dilate(in, in, element);
	out.push_back(in);
}

void WidgetDilate::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetDilate::toJson() {
	nlohmann::json json;
	json["type"] = "dilate";
	return json;
}