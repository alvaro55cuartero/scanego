#include "WidgetInversor.h"

WidgetInversor::WidgetInversor(QWidget* parent)
	: ItemWidget(parent, "Inversor")
{
	QLabel* pb = new QLabel(this);
	pb->setText("Filter");
	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetInversor::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	//cv::Mat temp;

	//out.push_back(temp);
}

void WidgetInversor::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetInversor::toJson() {
	nlohmann::json json;
	json["type"] = "inversor";
	return json;
}
