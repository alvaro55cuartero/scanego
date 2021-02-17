#pragma once

#include <vector>


#include "../../json.hpp"
#include "../../Utils.h"

#include "../Widget/ItemWidget.h"
#include "../Widget/CharacteristicWidget.h"

#include "../Widget/types/Item/WidgetFilter.h"
#include "../Widget/types/Item/WidgetThreshold.h"
#include "../Widget/types/Item/WidgetConnected.h"
#include "../Widget/types/Item/WidgetMask.h"
#include "../Widget/types/Item/WidgetChannel.h"
#include "../Widget/types/Item/WidgetDrawRects.h"
#include "../Widget/types/Item/WidgetOtsu.h"
#include "../Widget/types/Item/WidgetErode.h"
#include "../Widget/types/Item/WidgetDilate.h"
#include "../Widget/types/Item/WidgetMeanFilter.h"
#include "../Widget/types/Item/WidgetSobel.h"
#include "../Widget/types/Item/WidgetArea.h"
#include "../Widget/types/Item/WidgetDetectRects.h"
#include "../Widget/types/characteristic/WidgetCountHoles.h"
#include "../Widget/types/characteristic/WidgetAspectRatio.h"
#include "../Widget/types/characteristic/WidgetHist.h"
#include "../Widget/types/characteristic/WidgetCountCircles.h"
#include "../Widget/types/conversions/WidgetConversion.h"
#include "../Widget/types/conversions/WidgetToGray.h"
#include "../Widget/types/Item/WidgetCanny.h"


class Pipeline : public QWidget
{
	Q_OBJECT
public:
	Pipeline(std::string, cv::Mat*, QWidget* parent = 0);

	void append(ItemWidget* itemWidget);
	void parse(nlohmann::json json);
	void openFromJson(std::string path);
	void reset();
	void setName(std::string name);
	void setOriginal(cv::Mat* img);
	void save();
	void test();

	nlohmann::json toJson();

protected:
	float process(std::vector<cv::Mat>& out);
	std::string name;
	std::vector<ItemWidget*> list;
	QWidget* inner;

	cv::Mat* m_original;

signals:

public slots:
	void delWidget(QWidget*);
};

