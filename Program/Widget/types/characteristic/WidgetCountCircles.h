#pragma once

#include "../../CharacteristicWidget.h"


class WidgetCountCircles : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetCountCircles(cv::Mat* original, QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	float characteristic(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;


	void setOriginal(cv::Mat*);
	cv::Mat* ref;

signals:

public slots:
};
