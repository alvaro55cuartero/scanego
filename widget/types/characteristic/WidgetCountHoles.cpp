#include "WidgetCountHoles.h"

WidgetCountHoles::WidgetCountHoles(QWidget* parent)
	: CharacteristicWidget(parent)
{
	QLabel* pb = new QLabel(this);
	pb->setText("Count Holes");
	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetCountHoles::modificador(std::vector<cv::Mat>& out) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat singleLevelHoles, multipleLevelHoles, labels, stats, centroids;
    int nLabels, count;

	for (int i = 0; i < out.size(); i++) {
        count = 0;

        findContours(out[i].clone(), contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

        singleLevelHoles = cv::Mat::zeros(out[i].size(), out[i].type());
        multipleLevelHoles = cv::Mat::zeros(out[i].size(), out[i].type());


        for (std::vector<cv::Vec4i>::size_type idx = 0; idx < hierarchy.size(); ++idx)
        {
            if (hierarchy[idx][3] != -1)
                drawContours(singleLevelHoles, contours, idx, cv::Scalar::all(255), cv::FILLED, 8, hierarchy);
        }


        //bitwise_not(mask, mask);
        //bitwise_and(mask, singleLevelHoles, multipleLevelHoles);

        nLabels = cv::connectedComponentsWithStats(singleLevelHoles, labels, stats, centroids);    //Inverse source image.
        for (int j = 1; j < nLabels; j++) {
            if (stats.at<int>(j, cv::CC_STAT_AREA) > 30) {
                count++;
            }
        }
        nLabels--;
        
        std::cout << count << ", ";
	}
}

float WidgetCountHoles::characteristic(std::vector<cv::Mat>& out) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat singleLevelHoles, multipleLevelHoles, labels, stats, centroids;
    int nLabels, count;

    for (int i = 0; i < out.size(); i++) {
        count = 0;

        findContours(out[i].clone(), contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

        singleLevelHoles = cv::Mat::zeros(out[i].size(), out[i].type());
        multipleLevelHoles = cv::Mat::zeros(out[i].size(), out[i].type());


        for (std::vector<cv::Vec4i>::size_type idx = 0; idx < hierarchy.size(); ++idx)
        {
            if (hierarchy[idx][3] != -1)
                drawContours(singleLevelHoles, contours, idx, cv::Scalar::all(255), cv::FILLED, 8, hierarchy);
        }


        //bitwise_not(mask, mask);
        //bitwise_and(mask, singleLevelHoles, multipleLevelHoles);

        nLabels = cv::connectedComponentsWithStats(singleLevelHoles, labels, stats, centroids);    //Inverse source image.
        for (int j = 1; j < nLabels; j++) {
            if (stats.at<int>(j, cv::CC_STAT_AREA) > 30) {
                count++;
            }
        }
        nLabels--;

        return count;
    }
}
