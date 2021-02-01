#pragma once

#include "../../CharacteristicWidget.h"

class WidgetHist : public CharacteristicWidget
{
	Q_OBJECT
public:

	explicit WidgetHist(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;
	float characteristic(std::vector<cv::Mat>& out) override;

	void setMask(cv::Mat mask);

	cv::Mat img;
private:
	cv::Mat m_mask;

signals:

public slots:
};


