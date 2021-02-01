#include "WidgetToGray.h"


WidgetToGray::WidgetToGray(QWidget* parent)
	: ItemWidget(parent)

{
	QLabel* pb = new QLabel(this);
	pb->setText("Color conversion");
	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(pb);
	this->setLayout(lay);

}

void WidgetToGray::modificador(std::vector<cv::Mat>& out) {
	int type;
	for (int i = 0; i < out.size(); i++) {
	
		switch (out[i].type()) {
		case CV_8UC1:
			type = cv::COLOR_GRAY2BGR;
		case CV_8UC3:
			type = cv::COLOR_BGR2GRAY;
		}
		
		cv::cvtColor(out[i], out[i], type);
		out[i].type();
	}
}
