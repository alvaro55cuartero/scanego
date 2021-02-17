#include "WidgetChannel.h"

WidgetChannel::WidgetChannel(QWidget* parent)
	: ItemWidget(parent, "Channel Selection")
{
	QLabel* pb = new QLabel(this);
	pb->setText("Channel");
	spinBox = new QSpinBox(this);
	spinBox->setValue(0);
	spinBox->setMaximum(3);
	spinBox->setMinimum(1);

	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(spinBox);
	lay->addWidget(pb);
	this->setLayout(lay);
}


void WidgetChannel::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	std::vector<cv::Mat> planes;
	
	split(in, planes);
	out.push_back(planes[channel]);
}

void WidgetChannel::setChannel(int ch) {
	if (ch <= 2 && ch >= 0) {
		spinBox->setValue(ch);
		channel = ch;
	}
}


void WidgetChannel::jsonParse(nlohmann::json json) {
	std::string type;
	int value;

	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		type = it.key();
		value = it.value();

		if (type == "channel") {
			setChannel(value);
		}
	}
}

nlohmann::json WidgetChannel::toJson() {
	nlohmann::json json;
	json["type"] = "channel";
	return json;
}
