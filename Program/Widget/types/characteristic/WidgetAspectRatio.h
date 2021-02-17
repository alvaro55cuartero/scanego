#pragma once

#include "../../CharacteristicWidget.h"


class WidgetAspectRatio : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetAspectRatio(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	float characteristic(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;


signals:

public slots:
};
