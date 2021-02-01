#pragma once

#include "../ItemWidget.h"


class WidgetInversor : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetInversor(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;


signals:

public slots:
};
