#pragma once

#include "../Pipeline.h"

class CharacteristicPipeline : public Pipeline
{

public:
	explicit CharacteristicPipeline(std::string path, cv::Mat* img, QWidget* parent = 0) : Pipeline(path, img, parent) {}

	float execute(cv::Mat in, std::vector<cv::Mat>& out);

};

