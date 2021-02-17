#include "Program.h"

Program::Program() {}


void Program::trainInit(nlohmann::json json) {

	nlohmann::json names = { "holes", "aspectRatio", "color", "circles" };
	cv::Mat trainData, trainLabels;


	for (int i = 1; i < json.size() +1; i++) {
		std::string index = std::to_string(i);
		for (int k = 0; k < 40; k++) {
				trainLabels.push_back(i);
				float a = json[index]["holes"][k];
				float b = json[index]["aspectRatio"][k];
				float c = json[index]["color"][k];
				float d = json[index]["circles"][k];
				trainData.push_back(a);
				trainData.push_back(b);
				trainData.push_back(c);
				trainData.push_back(d);
		}
	}

	trainData = trainData.reshape(0, 280);

		std::cout << trainData << std::endl;
		std::cout << trainLabels << std::endl;

	knn = cv::ml::TrainData::create(trainData, cv::ml::ROW_SAMPLE, trainLabels);
}




std::vector<std::vector<float>> Program::execute(cv::Mat input, std::vector<cv::Mat>& output) {
	std::vector<cv::Mat> masks;
	cv::Mat testData, testLabels;
	std::vector<std::vector<float>> characteristicVector;
	
	
	setOriginal(input);
	executeSegmentation(masks);
	
	if (masks.size() == 0) {
		return std::vector<std::vector<float>>{ {0, 0, 0, 0} };
	}


	for (int i = 0; i < masks.size(); i++) {
		characteristicVector.push_back(executeAllCharacteristics(masks[i], output));
		characteristicVector[i][0] /= normalization[0];
		characteristicVector[i][1] /= normalization[1];
		characteristicVector[i][2] /= normalization[2];
		characteristicVector[i][3] /= normalization[3];

		testData.push_back(characteristicVector[i][0]);
		testData.push_back(characteristicVector[i][1]);
		testData.push_back(characteristicVector[i][2]);
		testData.push_back(characteristicVector[i][3]);


	}

	
	testData = testData.reshape(0, masks.size());


	knn1 = cv::ml::StatModel::train<cv::ml::KNearest>(knn);
	knn1->findNearest(testData, 5, testLabels);
	
	if (testLabels.size > 0) {}
		std::cout << testData << std::endl;
		std::cout << testLabels << std::endl;
	
	output.clear();
	
	cv::Mat current = m_mat_r.clone();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> currentContours;
	std::vector<cv::Vec4i> hierarchy;

	for (int i = 0; i < masks.size(); i++) {
		cv::findContours(masks[i], currentContours, hierarchy, 0, 1, cv::Point(0, 0));
		contours.insert(contours.end(), currentContours.begin(), currentContours.end());
	}
	for (int i = contours.size() - 1; i >= 0; i--)
	{
		int area = cv::contourArea(contours[i]);
		if (area > 500) continue;
		contours.erase(contours.begin() + i);
	}

	std::vector<cv::RotatedRect> minRect(contours.size());


	for (int i = 0; i < contours.size(); i++)
	{

		minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));

		cv::Point2f vertices[4];
		minRect[i].points(vertices);

		for (int j = 0; j < 4; j++) {
			cv::line(current, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
		}

		float lab = testLabels.at<float>(i, 0);
		//if (vector.size() > i)
			//cv::putText(current, std::to_string(), vertices[2], cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(118, 20, 0), 2);
			cv::putText(current, std::to_string(lab), vertices[2], cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(118, 20, 0), 2);

	}

	output.push_back(current);

	//executeOut(masks, output, characteristicVector);
	return characteristicVector;
}

std::vector<float> Program::executeTest(cv::Mat in , std::vector<cv::Mat>& out) {
	setOriginal(in);
	std::vector<cv::Mat> masks;
	executeSegmentation(masks);


	if (masks.size() == 0) {
		return std::vector<float>{0, 0, 0, 0};
	}

	QString ruta = QString("./res/A/B/%1.png").arg(time(0));
	cv::imwrite(ruta.toLatin1().data(), masks[0]);
	std::vector<float> characteristicVector;
	float _dist = 0, minDist = 10000, pieceIndex = 0;

	characteristicVector = executeAllCharacteristics(masks[0], out);

	return characteristicVector;
}



float Program::dist(std::vector<float> r, std::vector<float> o) {
	if (r.size() != o.size()) return 0;

	float value = 0;

	for (int i = 0; i < r.size(); i++) {
		o[i] = o[i] / normalization[i];
		value += (r[i] - o[i]) * (r[i] - o[i]);
	}

	return std::sqrt(value);
}


void Program::executeSegmentation(std::vector<cv::Mat>& output) {

	m_segmentation->execute(m_mat_r, output);
}


float Program::executeCharacteristic(int i, std::vector<cv::Mat>& output) {
	m_segmentation->execute(m_mat_r, output);
	return m_characteristics[i]->execute(output[0], output);
}


std::vector<float> Program::executeAllCharacteristics(cv::Mat in, std::vector<cv::Mat>& output) {
	std::vector<float> characteristicVector;
    for (int i = 0; i < m_characteristics.size(); i++) {
		characteristicVector.push_back(m_characteristics[i]->execute(in, output));
    }
	return characteristicVector;
}

void Program::executeOut(std::vector<cv::Mat> in, std::vector<cv::Mat>& output, std::vector<std::vector<float>> vector) {

	cv::Mat current = m_mat_r.clone();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> currentContours;
	std::vector<cv::Vec4i> hierarchy;

	for (int i = 0; i < in.size(); i++) {
		cv::findContours(in[i], currentContours, hierarchy, 0, 1, cv::Point(0, 0));
		contours.insert(contours.end(), currentContours.begin(), currentContours.end());
	}
	for (int i = contours.size() - 1 ; i >= 0; i--)
	{
		int area = cv::contourArea(contours[i]);
		if (area > 500) continue;
		contours.erase(contours.begin() + i);
	}
	
	std::vector<cv::RotatedRect> minRect(contours.size());



	for (int i = 0; i < contours.size(); i++)
	{

		minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));

		cv::Point2f vertices[4];
		minRect[i].points(vertices);

		for (int j = 0; j < 4; j++) {
			cv::line(current, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
		}

		if (vector.size() > i)
			//cv::putText(current, std::to_string(), vertices[2], cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(118, 20, 0), 2);
			cv::putText(current, std::to_string(vector[i][0]), vertices[2], cv::FONT_HERSHEY_DUPLEX, 1, CV_RGB(118, 20, 0), 2);

	}

	

	output.push_back(current);
}

void Program::addSegmentationPipe(std::string name) {
	m_segmentation = new SegmentationPipeline(name, &m_mat_r);
}


void Program::appendCharacteristicPipeline(std::string path) {
	m_characteristics.push_back(new CharacteristicPipeline(path, &m_mat_r));
}

void Program::addOutPipeline(std::string path) {
	m_out = new OutPipeline(path, &m_mat_r);
}

void Program::setOriginal(cv::Mat original) {
	m_mat_r = original.clone();
}

SegmentationPipeline* Program::getSegmentationPipe() {
	return nullptr;
}

CharacteristicPipeline* Program::getCharacteristicPipe(int pipe) {
	return m_characteristics[pipe];
}