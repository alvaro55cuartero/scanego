#pragma once

#include "../../ItemWidget.h"

class WidgetChannel : public ItemWidget {
	Q_OBJECT
public:

	explicit WidgetChannel(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;

	void setChannel(int ch);

private:
	QSpinBox* spinBox;
	int channel;

signals:

public slots:
};


