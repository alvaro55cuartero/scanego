#include "WidgetCountCircles.h"

WidgetCountCircles::WidgetCountCircles(QWidget* parent)
    : CharacteristicWidget(parent)
{
    QLabel* pb = new QLabel(this);
    pb->setText("Count Holes");
    QHBoxLayout* lay = new QHBoxLayout(this);

    lay->addWidget(pb);
    this->setLayout(lay);
}

void WidgetCountCircles::modificador(std::vector<cv::Mat>& out) {
}

float WidgetCountCircles::characteristic(std::vector<cv::Mat>& out) {
    double min, max;
    int count;
    cv::Point minp, maxp;
    cv::Mat gray = ref.clone();
    cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Mat> planes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    //split(gray, planes);
    //lanes[2].copyTo(gray);

    cv::findContours(out[0], contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    if (contours.size() == 0) return 0;

    cv::minMaxLoc(gray, &min, &max, &minp, &maxp, out[0]);
    gray.copyTo(out[0], out[0]);
    out[0] = (out[0] - min) / (max - min) * 255;
   


    std::vector<cv::Vec3f> circles;

    cv::HoughCircles(out[0], circles, cv::HOUGH_GRADIENT, 1, 25, 5, 20, 3, 15);


    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);


        double r = cv::pointPolygonTest(contours[0], center, false);

        if (r) {
            count++;
            cv::circle(out[0], center, 3, cv::Scalar(0, 255, 255), -1);
            cv::circle(out[0], center, radius, cv::Scalar(0, 0, 255), 1);
        }
    }

  

    return count;
}
