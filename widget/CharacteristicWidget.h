#pragma once

#include "ItemWidget.h"

class CharacteristicWidget : public ItemWidget
{

public:
	explicit CharacteristicWidget(QWidget* parent = 0) : ItemWidget(parent) {};

	virtual void modificador(std::vector<cv::Mat>& out) = 0;
	virtual float characteristic(std::vector<cv::Mat>& out) = 0;
};

