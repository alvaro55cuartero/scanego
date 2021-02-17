#pragma once

#include "../Pipeline.h"

class OutPipeline : public Pipeline
{

public:
	explicit OutPipeline(std::string path, cv::Mat* img, QWidget* parent = 0) : Pipeline(path, img, parent) {}
	float execute(std::vector<cv::Mat>& out);

};


