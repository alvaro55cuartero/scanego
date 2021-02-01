#pragma once

#include "../../ItemWidget.h"

class WidgetToGray : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetToGray(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;

signals:

public slots:
};


