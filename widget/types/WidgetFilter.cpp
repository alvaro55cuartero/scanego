#include "WidgetFilter.h"

WidgetFilter::WidgetFilter(QWidget* parent)
	: ItemWidget(parent)
{
	QLabel* pb = new QLabel(this);
	pb->setText("Filter");
	QHBoxLayout* lay = new QHBoxLayout(this);
	
	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetFilter::modificador(std::vector<cv::Mat>& out) {
	for (int i = 0; i < out.size(); i++) {
		cv::GaussianBlur(out[i], out[i], cv::Size(5, 5), 0, 0);
	}
}
