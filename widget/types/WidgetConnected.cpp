#include "WidgetConnected.h"


WidgetConnected::WidgetConnected(QWidget* parent)
	: ItemWidget(parent)

{
	QLabel* pb = new QLabel(this);
	pb->setText("current image");
	QHBoxLayout* lay = new QHBoxLayout(this);



	lay->addWidget(pb);
	lay->addWidget(spinBox);
	this->setLayout(lay);

}

void WidgetConnected::modificador(std::vector<cv::Mat>& out) {
	cv::Mat stats, centroids, mask, labels, m_mat_r;
	int i, nLabels;
	std::vector<cv::Mat> temp;
	for (int i = 0; i < out.size(); i++) {
		out[i].type();
		nLabels = cv::connectedComponentsWithStats(out[i], labels, stats, centroids);
		for (i = 0; i < nLabels; i++) {
			mask = (labels == i) / i;
			//result = cv::Mat(mask.size(), CV_8UC3, cv::Scalar(0));
			//m_mat_r.copyTo(result, mask);
			
			if (i != 0 && stats.at<int>(i, cv::CC_STAT_AREA) > 1400) {
				cv::Mat result = cv::Mat();
				mask.copyTo(result);
				temp.push_back(result);
			}
		}
	}

	out.clear();
	out = temp;
}

