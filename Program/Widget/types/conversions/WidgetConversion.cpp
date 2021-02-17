#include "WidgetConversion.h"


WidgetConversion::WidgetConversion(QWidget* parent)
	: ItemWidget(parent, "Conversion")

{
	update(0);
	QLabel* pb = new QLabel(this);
	pb->setText("Color conversion");
	QHBoxLayout* lay = new QHBoxLayout(this);


	QComboBox* cb = new QComboBox();
	cb->addItem("BGR2GRAY");
	cb->addItem("GRAY2BGR");
	cb->addItem("BGR2HSV");

	lay->addWidget(pb);
	lay->addWidget(cb);
	this->setLayout(lay);

	QObject::connect(cb, SIGNAL(activated(int)), this, SLOT(update(int)));
}

void WidgetConversion::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
		cv::cvtColor(in, in, type);
		out.push_back(in);
}

void WidgetConversion::update(int id) {
	switch (id) {
	case 0:
		type = cv::COLOR_BGR2GRAY;
		break;
	case 1:
		type = cv::COLOR_GRAY2BGR;
		break;

	case 2:
		type = cv::COLOR_BGR2HSV;
		break;

	}
}

void WidgetConversion::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetConversion::toJson() {
	nlohmann::json json;
	json["type"] = "conversion";
	return json;
}