#pragma once

#include "ItemWidget.h"

class CharacteristicWidget : public ItemWidget
{

public:
	explicit CharacteristicWidget(QWidget* parent, std::string name) : ItemWidget(parent, name) {};

	virtual void modificador(cv::Mat in, std::vector<cv::Mat>& out) = 0;
	virtual float characteristic(cv::Mat in, std::vector<cv::Mat>& out) = 0;
};

