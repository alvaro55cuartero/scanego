#include "WidgetOtsu.h"

WidgetOtsu::WidgetOtsu(QWidget* parent)
	: ItemWidget(parent, "Threshold")
{

	slider = new QSpinBox();
	slider->setMaximum(255);
	slider->setMinimum(0);
	slider->setValue(thresh);


	checkbox = new QCheckBox();
	setInversion(false);


	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow(tr("Thresh Point"), slider);
	formLayout->addRow(tr("Inversion"), checkbox);
	setLayout(formLayout);
	setMinimumHeight(600);
}

void WidgetOtsu::modificador(cv::Mat in, std::vector<cv::Mat>& out) 
{	
	int nLabels;
	float area = 0;
	std::vector<std::vector<cv::Point>> contours;
	cv::Mat stats, centroids, mask, labels, m_mat_r;
	cv::Mat result, temp;
	
	cv::threshold(in, temp, slider->value(), 250, cv::THRESH_BINARY | cv::THRESH_OTSU);
	
	nLabels = cv::connectedComponentsWithStats(temp, labels, stats, centroids);

	for (int j = 0; j < nLabels; j++) {
		mask = (labels == j) / j;

		findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
		area = cv::contourArea(contours[0]);
		
		if (area > 100) {
			result += mask;
		}
	}
	
	in -= in * result;
	
	cv::threshold(in, temp, slider->value(), 250, cv::THRESH_BINARY | cv::THRESH_OTSU);

	result += temp;


	out.push_back(result);
}

void WidgetOtsu::setThresh(int a) {
	thresh = a;
	slider->setValue(a);
}

void WidgetOtsu::setInversion(bool value) {
	inversion = value;
	checkbox->setChecked(value);
	if (inversion) {
		type = cv::THRESH_BINARY_INV;
	}
	else {
		type = cv::THRESH_BINARY;
	}
}

void WidgetOtsu::jsonParse(nlohmann::json json) {
	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		std::string type = it.key();

		if (type == "double")
		{
			setThresh(it.value());
		}
		else if (type == "inversion")
		{
			setInversion(it.value());
		}
	}
}

nlohmann::json WidgetOtsu::toJson() {
	nlohmann::json json;
	json["type"] = "otsu";
	return json;
}

