#include "WidgetHist.h"

WidgetHist::WidgetHist(cv::Mat* mask, QWidget* parent)
	: CharacteristicWidget(parent,"Histogram")
{
    this->m_mask = mask;
}

void WidgetHist::modificador(cv::Mat in, std::vector<cv::Mat>& out) {}

float WidgetHist::characteristic(cv::Mat in, std::vector<cv::Mat>& out) {
    int histSize = 256, count = 0, color = 0, value = 0;
    float range[] = { 0, 256 }; 
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    int hist_w = 640, hist_h = 480;

    std::vector<cv::Mat> bgr_planes;
    cv::Mat hist;
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat temp(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    (*m_mask).copyTo(temp, in);

    cv::cvtColor(temp, temp, cv::COLOR_BGR2HSV);
    //cv::cvtColor(temp, temp, cv::COLOR_BGR2GRAY);
    cv::split(temp, bgr_planes);
    temp = bgr_planes[1];

    calcHist(&temp, 1, 0, in, hist, 1, &histSize, &histRange, uniform, accumulate);
    int bin_w = cvRound((double)hist_w / histSize);
    normalize(hist,hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    float pick, col = 0;

    for (int i = 1; i < histSize; i++) {
        if (i > 50 && pick < hist.at<float>(i) && i < 250) {
            pick = hist.at<float>(i);
            col = i;
            value += (hist.at<float>(i)) * i;
            count++;
        }
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0);

    }

    if(count !=0)
        value /= count;

    out.push_back(histImage);

    return col;
}


void WidgetHist::setMask(cv::Mat* mask) {
	m_mask = mask;
}

void WidgetHist::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetHist::toJson() {
    nlohmann::json json;
    json["type"] = "histogram";
    return json;
}