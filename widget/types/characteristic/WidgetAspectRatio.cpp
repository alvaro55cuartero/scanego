#include "WidgetAspectRatio.h"

WidgetAspectRatio::WidgetAspectRatio(QWidget* parent)
    : CharacteristicWidget(parent)
{
    QLabel* pb = new QLabel(this);
    pb->setText("Count Holes");
    QHBoxLayout* lay = new QHBoxLayout(this);

    lay->addWidget(pb);
    this->setLayout(lay);
}

void WidgetAspectRatio::modificador(std::vector<cv::Mat>& out) {
}

float WidgetAspectRatio::characteristic(std::vector<cv::Mat>& out) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::RotatedRect> minRect;
    float aspectRatio;
    for (cv::Mat mat: out) {


        findContours(mat, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
        minRect = std::vector<cv::RotatedRect>(contours.size());

        for (size_t i = 0; i < contours.size(); i++)
        {
            minRect[i] = minAreaRect(contours[i]);
            if (minRect[i].size.area() > 20) {
                aspectRatio = minRect[i].size.aspectRatio();
                if (aspectRatio == 0) { return 0; }
                if (aspectRatio > 1) {
                    return aspectRatio;
                }
                return 1 / aspectRatio;
            }
        }

        contours.clear();
        minRect.clear();
    }
}
