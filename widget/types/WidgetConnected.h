#pragma once
#include "../ItemWidget.h"

class WidgetConnected : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetConnected(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;

private:
	QSpinBox *spinBox = new QSpinBox();

signals:

public slots:
};


