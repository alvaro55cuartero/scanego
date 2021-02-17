#include "WidgetFilter.h"

WidgetFilter::WidgetFilter(QWidget* parent)
	: ItemWidget(parent, "Filter")
{
}

void WidgetFilter::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat temp;
	cv::GaussianBlur(in, temp, cv::Size(5, 5), 0, 0);
	out.push_back(temp);
}

void WidgetFilter::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetFilter::toJson() {
	nlohmann::json json;
	json["type"] = "filter";
	return json;
}