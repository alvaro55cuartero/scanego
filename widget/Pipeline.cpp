#include "Pipeline.h"


void Pipeline::append(ItemWidget* itemWidget) {
	list.push_back(itemWidget);
}

void Pipeline::reset() {
	list.clear();
}

float Pipeline::execute(std::vector<cv::Mat> &out)
{
    float result = 0;
    CharacteristicWidget* ch;

    for (ItemWidget* value : list) {
        ch = dynamic_cast<CharacteristicWidget*>(value);
        if (ch != nullptr) {
            result = (ch)->characteristic(out);
        }
        else {
            (value)->modificador(out);
        }
    }

    return result;
}

