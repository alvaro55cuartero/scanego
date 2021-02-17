#include "WidgetConnected.h"


WidgetConnected::WidgetConnected(QWidget* parent)
	: ItemWidget(parent, "Connected Shapes")

{
	QLabel* pb = new QLabel();
	pb->setText("current image");
	QHBoxLayout* layout = new QHBoxLayout();

	layout->addWidget(pb);
	layout->addWidget(spinBox);
	this->setLayout(layout);

}

void WidgetConnected::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat stats, centroids, mask, labels, m_mat_r;
	int nLabels;
	std::vector<std::vector<cv::Point>> contours;
	float area  = 0 ;
	nLabels = cv::connectedComponentsWithStats(in, labels, stats, centroids);

	for (int j = 1; j < nLabels; j++) {
		mask = (labels == j);
		if (stats.at<int>(j, cv::CC_STAT_AREA) > 50) {
			cv::Mat result = cv::Mat();
			mask.copyTo(result);
			out.push_back(result);
		}
	}
}


void WidgetConnected::jsonParse(nlohmann::json json) {
	std::string type;
	int value;

	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		type = it.key();
		value = it.value();
	}
}

nlohmann::json WidgetConnected::toJson() {
	nlohmann::json json;
	json["type"] = "connected";
	return json;
}

