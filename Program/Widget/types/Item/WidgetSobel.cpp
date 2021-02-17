#include "WidgetSobel.h"

WidgetSobel::WidgetSobel(QWidget* parent)
	: ItemWidget(parent, "sobel")
{
}

void WidgetSobel::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
    cv::Mat a[3];
    cv::Mat1b b(480, 640);
    std::vector<cv::Mat> planes;
    cv::Mat1s cvsx, cvsy;

   
    cv::split(in, planes);

    for (int i = 0; i < planes.size(); i++) {
        Sobel(planes[i], cvsx, CV_16S, 1, 0);
        Sobel(planes[i], cvsy, CV_16S, 0, 1);
        absdiff(cvsx, cvsy, a[i]);
    }

    unsigned char* input1 = (unsigned char*)(a[0].data);
    unsigned char* input2 = (unsigned char*)(a[1].data);
    unsigned char* input3 = (unsigned char*)(a[2].data);

    for (int j = 0; j < a[0].rows; j++) {
        for (int i = 0; i < a[0].cols; i++) {
            unsigned char  temp = std::max(input1[(640 * 2 * j) + (i * 2)], input2[640 * 2 * j + i * 2]);
            b.at<uchar>(j, i) = std::max(temp, input3[640 * 2 * j + i * 2]);
        }
    }
	out.push_back(b);
}

void WidgetSobel::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetSobel::toJson() {
	nlohmann::json json;
	json["type"] = "sobel";
	return json;
}