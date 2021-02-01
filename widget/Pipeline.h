#pragma once

#include <vector>
#include "../json.hpp"
#include "ItemWidget.h"
#include "CharacteristicWidget.h"

class Pipeline
{
public:
	void append(ItemWidget* itemWidget);
	void reset();
	float execute(std::vector<cv::Mat> &out);
private:
	std::vector<ItemWidget*> list;
	

};

