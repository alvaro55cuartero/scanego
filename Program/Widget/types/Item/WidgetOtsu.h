#include "../../ItemWidget.h"


class WidgetOtsu : public ItemWidget
{
	Q_OBJECT
public:

	explicit WidgetOtsu(QWidget* parent = 0);
	void modificador(cv::Mat in, std::vector<cv::Mat>& out) override;
	void jsonParse(nlohmann::json json) override;
	nlohmann::json toJson() override;


	void setThresh(int a);
	void setInversion(bool a);


private:
	QSpinBox* slider;
	QCheckBox* checkbox;
	int thresh = 120;
	bool inversion = false;
	cv::ThresholdTypes type;


signals:

public slots:
};