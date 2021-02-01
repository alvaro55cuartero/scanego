#pragma once

#include "../ItemWidget.h"

class WidgetChannel : public ItemWidget {
	Q_OBJECT
public:

	explicit WidgetChannel(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	QSpinBox* spinBox;

	int channel;

signals:

public slots:
};


