#include "WidgetMeanFilter.h"

WidgetMeanFilter::WidgetMeanFilter(QWidget* parent)
	: ItemWidget(parent, "meanFilter")
{
}

void WidgetMeanFilter::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	
	int media = (int)cv::mean(in)[0];
	in = in.mul((in > media) / 255);
	out.push_back(in);
}

void WidgetMeanFilter::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetMeanFilter::toJson() {
	nlohmann::json json;
	json["type"] = "meanFilter";
	return json;
}