#pragma once

#include "../../CharacteristicWidget.h"

class WidgetHist : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetHist(cv::Mat* m_mask, QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	float characteristic(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;


	void setMask(cv::Mat* mask);

	cv::Mat* m_mask;
private:

signals:

public slots:
};


