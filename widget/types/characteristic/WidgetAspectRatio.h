#pragma once

#include "../../CharacteristicWidget.h"


class WidgetAspectRatio : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetAspectRatio(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	float characteristic(std::vector<cv::Mat>& out) override;

signals:

public slots:
};
