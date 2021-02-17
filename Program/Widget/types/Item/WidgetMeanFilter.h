#pragma once
#include "../../ItemWidget.h"


class WidgetMeanFilter : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetMeanFilter(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;

signals:

public slots:
};

