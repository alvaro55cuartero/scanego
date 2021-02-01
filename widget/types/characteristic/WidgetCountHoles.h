#pragma once

#include "../../CharacteristicWidget.h"


class WidgetCountHoles : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetCountHoles(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	float characteristic(std::vector<cv::Mat>& out) override;

signals:

public slots:
};
