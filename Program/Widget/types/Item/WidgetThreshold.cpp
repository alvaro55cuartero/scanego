#include "WidgetThreshold.h"

WidgetThreshold::WidgetThreshold(QWidget* parent)
	: ItemWidget(parent, "Threshold")
{
	
	spinBox = new QSpinBox();
	spinBox->setMaximum(255);
	spinBox->setMinimum(0);
	spinBox->setValue(120);

	checkbox = new QCheckBox();
	setInversion(false);


	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow(tr("Thresh Point"), spinBox);
	formLayout->addRow(tr("Inversion"), checkbox);
	setLayout(formLayout);
	setMinimumHeight(100);
}

void WidgetThreshold::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	type = checkbox->isChecked() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
		
	cv::Mat temp;
	double thres = cv::threshold(in, temp, spinBox->value(), 255, type);
	out.push_back(temp);
}

void WidgetThreshold::setThresh(int a) {
	spinBox->setValue(a);
}

void WidgetThreshold::setInversion(bool value) {
	checkbox->setChecked(value);
	
}

void WidgetThreshold::jsonParse(nlohmann::json json) {
	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		std::string type = it.key();
		
		if (type == "thresh") 
		{
			setThresh(it.value());
		}
		else if (type=="inversion") 
		{
			setInversion(it.value());
		}
	}
}

nlohmann::json WidgetThreshold::toJson() {
	nlohmann::json json;
	json["type"] = "threshold";
	json["arg"]["thresh"] = spinBox->value();
	json["arg"]["inversion"] = checkbox->isChecked();
	
	return json;
}
