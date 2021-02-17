#pragma once

#include "../../ItemWidget.h"

class WidgetMask : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetMask(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;

	cv::Mat img;

signals:

public slots:
};


