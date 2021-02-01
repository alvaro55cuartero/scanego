#include "WidgetConversion.h"


WidgetConversion::WidgetConversion(QWidget* parent)
	: ItemWidget(parent)

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

void WidgetConversion::modificador(std::vector<cv::Mat>& out) {
	for (int i = 0; i < out.size(); i++) {
		cv::cvtColor(out[i], out[i], type);
	}
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
