#pragma once

#include "../ItemWidget.h"

class WidgetMask : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetMask(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;

	cv::Mat img;

signals:

public slots:
};


