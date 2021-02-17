#include "WidgetMask.h"

WidgetMask::WidgetMask(QWidget* parent)
	: ItemWidget(parent, "Mask")
{}

void WidgetMask::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat temp;
	img.copyTo(in, temp);
	out.push_back(temp);
}

void WidgetMask::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetMask::toJson() {
	nlohmann::json json;
	json["type"] = "mask";
	return json;
}
