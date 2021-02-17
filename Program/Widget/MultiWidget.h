#pragma once
#include "ItemWidget.h"

class MultiWidget: public ItemWidget 
{

public:
	explicit MultiWidget(QWidget* parent, std::string name) : ItemWidget(parent, name) {};

	virtual void modificador(cv::Mat in, std::vector<cv::Mat>& out) = 0;
	virtual float multi(std::vector<cv::Mat> in, std::vector<cv::Mat>& out) = 0;


};