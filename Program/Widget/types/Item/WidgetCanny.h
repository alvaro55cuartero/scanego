#pragma once

#include "../../ItemWidget.h"


class WidgetCanny : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetCanny(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;

signals:

public slots:
};

