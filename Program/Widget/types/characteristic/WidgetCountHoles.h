#pragma once

#include "../../CharacteristicWidget.h"


class WidgetCountHoles : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetCountHoles(cv::Mat* original, QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	float characteristic(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;

private:
	cv::Mat* original;

signals:

public slots:
};
