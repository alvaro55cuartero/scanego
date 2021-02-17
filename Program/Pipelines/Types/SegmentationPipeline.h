#pragma once

#include "../Pipeline.h"

class SegmentationPipeline : public Pipeline
{
public:
	explicit SegmentationPipeline(std::string path, cv::Mat* img, QWidget* parent = 0) : Pipeline(path, img,  parent) {}

	float execute(cv::Mat in, std::vector<cv::Mat>& out);



};