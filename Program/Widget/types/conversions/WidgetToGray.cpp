#include "WidgetToGray.h"


WidgetToGray::WidgetToGray(QWidget* parent)
	: ItemWidget(parent, "Gray Conversion")
{

}

void WidgetToGray::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	int type;
	
	switch (in.type()) {
	case CV_8UC1:
		type = cv::COLOR_GRAY2BGR;
	case CV_8UC3:
		type = cv::COLOR_BGR2GRAY;
	}
		
	cv::cvtColor(in, in, type);
	out.push_back(in);
}


void WidgetToGray::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetToGray::toJson() {
	nlohmann::json json;
	json["type"] = "gray";
	return json;
}
