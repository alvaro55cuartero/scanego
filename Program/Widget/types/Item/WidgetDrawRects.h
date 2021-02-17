#pragma once

#include "../../MultiWidget.h"

class WidgetDrawRects : public MultiWidget {
	Q_OBJECT
public:

	explicit WidgetDrawRects(cv::Mat* original, QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	float multi(std::vector<cv::Mat> in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;


private:
	cv::Mat* m_original;

signals:

public slots:
};


