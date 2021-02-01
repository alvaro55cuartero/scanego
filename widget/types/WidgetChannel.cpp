#include "WidgetChannel.h"

WidgetChannel::WidgetChannel(QWidget* parent)
	: ItemWidget(parent)
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


void WidgetChannel::modificador(std::vector<cv::Mat>& out) {
	//channel = spinBox->value();
	std::vector<cv::Mat> planes;
	
	//channel--;
	for (int i = 0; i < out.size(); i++) {
		split(out[i], planes);
		planes[channel].copyTo(out[i]);
	}
}
