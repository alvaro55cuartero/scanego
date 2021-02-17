#pragma once
#include "../../ItemWidget.h"

class WidgetConnected : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetConnected(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;

	nlohmann::json toJson() override;

private:
	QSpinBox *spinBox = new QSpinBox();

signals:

public slots:
};


