#include "WidgetThreshold.h"

WidgetThreshold::WidgetThreshold(QWidget* parent)
	: ItemWidget(parent)
{
	QHBoxLayout* lay = new QHBoxLayout(this);
	
	QLabel* pb = new QLabel(this);
	pb->setText("Threshold");
	slider->setMaximum(255);
	slider->setMinimum(0);
	slider->setValue(thresh);
	lay->addWidget(slider);
	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetThreshold::modificador(std::vector<cv::Mat>& out) {
	for (int i = 0; i < out.size(); i++) {
		double thres = cv::threshold(out[i], out[i], slider->value(), 250, cv::THRESH_BINARY);
		//double thres = cv::threshold(out[i], out[i], slider->value(), 255, cv::THRESH_BINARY_INV );
		//int a = cv::countNonZero(out[i]);
		/*if ( a > 640 * 480 / 2) {
			cv::bitwise_not(out[i], out[i]);
		}
		a = cv::countNonZero(out[i]);

		if (a > 640 * 480 / 2) {
			std::cout << "error";
		}*/
	}
}

void WidgetThreshold::setThresh(int a) {
	thresh = a;
	slider->setValue(a);
}

