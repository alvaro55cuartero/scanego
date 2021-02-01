#include "WidgetMask.h"

WidgetMask::WidgetMask(QWidget* parent)
	: ItemWidget(parent)
{
	QLabel* pb = new QLabel(this);
	pb->setText("Mask");
	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetMask::modificador(std::vector<cv::Mat>& out) {
	for (int i = 0; i < out.size(); i++) {
		img.copyTo(out[i], out[i]);
	}
}
