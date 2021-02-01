#pragma once

#include "../../CharacteristicWidget.h"


class WidgetCountCircles : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetCountCircles(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	float characteristic(std::vector<cv::Mat>& out) override;

	cv::Mat ref;

signals:

public slots:
};
