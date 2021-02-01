#include "WidgetHist.h"

WidgetHist::WidgetHist(QWidget* parent)
	: CharacteristicWidget(parent)
{
	QLabel* pb = new QLabel(this);
	pb->setText("Hist");
	QHBoxLayout* lay = new QHBoxLayout(this);

	lay->addWidget(pb);
	this->setLayout(lay);
}

void WidgetHist::modificador(std::vector<cv::Mat>& out) {
    std::vector<cv::Mat> bgr_planes;
    m_mask.copyTo(img);

    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);


    cv::split(img, bgr_planes);
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, out[0], b_hist, 1, &histSize, &histRange, uniform, accumulate);
    //calcHist(&bgr_planes[1], 1, 0, out[0], g_hist, 1, &histSize, &histRange, uniform, accumulate);
    //calcHist(&bgr_planes[2], 1, 0, out[0], r_hist, 1, &histSize, &histRange, uniform, accumulate);
    int hist_w = 640, hist_h = 480;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    //normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    //normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    int count = 0;
    int color = 0;
    for (int i = 1; i < histSize; i++)
    {
        if (i > 50 && count < b_hist.at<float>(i)) {
            count =  b_hist.at<float>(i);
            color = i;
        }
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0);
        //line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
        //    cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
        //    cv::Scalar(0, 255, 0), 2, 8, 0);
        //line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
        //    cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
        //    cv::Scalar(0, 0, 255), 2, 8, 0);
    }
    histImage.copyTo(out[0]);
    std::cout << count << " " << color << std::endl;

	//for (int i = 0; i < out.size(); i++) {
	//	calcHist(&out[i], 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
	//	std::cout << i << mean(hist) << std::endl;
	//}
}

float WidgetHist::characteristic(std::vector<cv::Mat>& out) {
    std::vector<cv::Mat> bgr_planes;
    int histSize = 256, count = 0, color = 0;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    int hist_w = 640, hist_h = 480;
    cv::Mat b_hist, g_hist, r_hist;
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    m_mask.copyTo(img);

    //cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
    cv::split(img, bgr_planes);
    calcHist(&bgr_planes[2], 1, 0, out[0], b_hist, 1, &histSize, &histRange, uniform, accumulate);
    int bin_w = cvRound((double)hist_w / histSize);
    normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    for (int i = 1; i < histSize; i++)
    {
        if (i > 50 && count < b_hist.at<float>(i)) {
            count = b_hist.at<float>(i);
            color = i;
        }

        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0);
    }

    bgr_planes[2].copyTo(out[0]);

    return color;
}


void WidgetHist::setMask(cv::Mat mask) {
	this->m_mask = mask;
}