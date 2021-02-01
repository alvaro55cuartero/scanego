#pragma once

#include "../ItemWidget.h"


class WidgetFilter : public ItemWidget
{
Q_OBJECT
public:
	
	explicit WidgetFilter(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	 

signals:

public slots:
};

