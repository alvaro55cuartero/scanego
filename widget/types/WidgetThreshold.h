#pragma once

#include "../ItemWidget.h"


class WidgetThreshold : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetThreshold(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;

	void setThresh(int a);

private:
	QSpinBox* slider = new QSpinBox();
	int thresh = 120;
	

signals:

public slots:
};