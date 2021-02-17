#include "WidgetCanny.h"

WidgetCanny::WidgetCanny(QWidget* parent)
    : ItemWidget(parent, "canny")
{
}

void WidgetCanny::modificador(cv::Mat in, std::vector<cv::Mat>& out) {
    cv::Canny(in, in, 100, 100);
    out.push_back(in);
}

void WidgetCanny::jsonParse(nlohmann::json json) {
}

nlohmann::json WidgetCanny::toJson() {
    nlohmann::json json;
    json["type"] = "canny";
    return json;
}