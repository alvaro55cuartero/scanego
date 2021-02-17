#pragma once

#include "vector"

#include "./Pipelines/Pipeline.h"
#include "./Pipelines/Types/SegmentationPipeline.h"
#include "./Pipelines/Types/CharacteristicPipeline.h"
#include "./Pipelines/Types/OutPipeline.h"
#include "opencv2/ml.hpp"

class Program
{
public:
	Program();

	void trainInit(nlohmann::json json);

	std::vector<std::vector<float>> execute(cv::Mat, std::vector<cv::Mat>&);
	std::vector<float>executeTest(cv::Mat, std::vector<cv::Mat>&);

	void setOriginal(cv::Mat);
	void executeSegmentation(std::vector<cv::Mat>& output);
	float executeCharacteristic(int i, std::vector<cv::Mat>& output);

	std::vector<float> executeAllCharacteristics(cv::Mat in, std::vector<cv::Mat>& output);
	void executeOut(std::vector<cv::Mat> in, std::vector<cv::Mat>& output, std::vector<std::vector<float>> vector);

	void addSegmentationPipe(std::string);
	void appendCharacteristicPipeline(std::string);
	void addOutPipeline(std::string);

	float dist(std::vector<float> r, std::vector<float> o);

	SegmentationPipeline* getSegmentationPipe();
	CharacteristicPipeline* getCharacteristicPipe(int pipe);

private:
	SegmentationPipeline* m_segmentation;
	std::vector<CharacteristicPipeline*> m_characteristics;
	OutPipeline* m_out;

	cv::Ptr<cv::ml::TrainData> knn;
	cv::Ptr<cv::ml::KNearest> knn1;

	cv::Mat m_mat_r;

	int normalization[4] = { 3, 4, 255, 12 };


};

