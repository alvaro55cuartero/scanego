#include "WidgetDrawRects.h"


WidgetDrawRects::WidgetDrawRects(cv::Mat* original, QWidget* parent)
	: MultiWidget(parent, "Drawing Rects"), m_original(original)
{}


void WidgetDrawRects::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
	cv::Mat current = m_original->clone();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> currentContours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(in, currentContours, hierarchy, 0, 1, cv::Point(0, 0));  	
	contours.insert(contours.end(), currentContours.begin(), currentContours.end());
	
	std::vector<cv::RotatedRect> minRect(contours.size());



	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));

		cv::Point2f vertices[4];
		minRect[i].points(vertices);

		for (int j = 0; j < 4; j++) {
			cv::line(current, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0), 2);
		}

		cv::putText(current, std::to_string(i), //text
			vertices[2], //top-left position
			cv::FONT_HERSHEY_DUPLEX,
			1.0,
			CV_RGB(118, 20, 0), //font color
			2);

	}

	out.clear();
	out.push_back(current);
}
float WidgetDrawRects::multi(std::vector<cv::Mat> in, std::vector<cv::Mat>& out) {
	cv::Mat current = m_original->clone();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<std::vector<cv::Point>> currentContours;
	std::vector<cv::Vec4i> hierarchy;

	for ( int i = 0; i < in.size(); i++)
	{
		cv::findContours(in[i], currentContours, hierarchy, 0, 1, cv::Point(0, 0));
		contours.insert(contours.end(), currentContours.begin(), currentContours.end());
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

		cv::putText(current, std::to_string(i), vertices[2], cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 20, 0), 2);
	}

	out.clear();
	out.push_back(current);
	return 0;
}

void WidgetDrawRects::jsonParse(nlohmann::json json) {
	std::string type;
	int value;

	for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
		type = it.key();
		value = it.value();
	}
}

nlohmann::json WidgetDrawRects::toJson() {
	nlohmann::json json;
	json["type"] = "drawRects";
	return json;
}

