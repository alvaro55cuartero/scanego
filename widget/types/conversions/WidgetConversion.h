#pragma once
#include "../../ItemWidget.h"

class WidgetConversion : public ItemWidget
{
Q_OBJECT
public:

	explicit WidgetConversion(QWidget* parent = 0);
	void modificador(std::vector<cv::Mat>& out) override;

private:
	enum cv::ColorConversionCodes type;

signals:

public slots:
	void update(int);
};

