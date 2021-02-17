#include "SegmentationPipeline.h"

float SegmentationPipeline::execute(cv::Mat in, std::vector<cv::Mat>& out)
{
    out.clear();
    out.push_back(in);
    return process(out);
}
