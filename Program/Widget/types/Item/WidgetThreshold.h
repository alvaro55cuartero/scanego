#pragma once

#include "../../ItemWidget.h"


class WidgetThreshold : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetThreshold(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;

	void setThresh(int a);
	void setInversion(bool a);

	nlohmann::json toJson() override;

private:
	QSpinBox* spinBox;
	QCheckBox* checkbox;
	cv::ThresholdTypes type;
	

signals:

public slots:
};