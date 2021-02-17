#pragma once

#include <QtWidgets/qlabel.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/QStackedLayout>
#include <qtimer.h>

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/hal/interface.h>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "json.hpp"
#include "utils.h" 

#include "ui_TestQT1.h"

#include "Program/Program.h"

#include "Program/Pipelines/Pipeline.h"
#include "Program/Pipelines/Types/SegmentationPipeline.h"
#include "Program/Pipelines/Types/CharacteristicPipeline.h"

#include "Program/Widget/ItemWidget.h"
#include "Program/Widget/types/Item/WidgetFilter.h"
#include "Program/Widget/types/Item/WidgetThreshold.h"
#include "Program/Widget/types/Item/WidgetConnected.h"
#include "Program/Widget/types/Item/WidgetMask.h"
#include "Program/Widget/types/Item/WidgetChannel.h"
#include "Program/Widget/types/characteristic/WidgetCountHoles.h"
#include "Program/Widget/types/characteristic/WidgetAspectRatio.h"
#include "Program/Widget/types/characteristic/WidgetHist.h"
#include "Program/Widget/types/characteristic/WidgetCountCircles.h"
#include "Program/Widget/types/conversions/WidgetConversion.h"
#include "Program/Widget/types/conversions/WidgetToGray.h"



class TestQT1 : public QMainWindow
{
    Q_OBJECT

public:
    TestQT1(QWidget *parent = Q_NULLPTR);

    void drawBuffer(QLabel* label, cv::Mat mat, QImage::Format type);
    void drawBuffer(QLabel* label, cv::Mat mat);
    void drawIn(cv::Mat mat);
    void drawOut(cv::Mat mat);
    void drawOut();

    void drawRect(cv::RotatedRect rect);
    void drawInfo();

    void openImg(std::string);

    void clearLayout(QLayout* layout);
    void openCamera();
    void reset();

    void train();

    float test();
    float testPorPieza(nlohmann::json json, float* media);


    float percentil(std::vector<float> arr);

    void openRandom();

    QImage::Format type2Format(int type);

    void segTest(std::vector<cv::Mat>& out);
    float holesTest(std::vector<cv::Mat>& out);
    float cirlcesTest(std::vector<cv::Mat>& out);
    /*void segTest(std::vector<cv::Mat>& out);
    void segTest(std::vector<cv::Mat>& out);
    */

public slots:    
    void addWidgetToMenu(QWidget*);
    void addWidgetToPipeline(ItemWidget*);

    void dispersionFiles();

    void dialogAbrir(void);
    void dialogGuardar(void);
    void frame(void);
    void resetSlot(void);
    void startStopCap(bool);
    void rightSlot(void);
    void leftSlot(void);
    void updateSlot(void);
    void trainSlot();
    void cameraOptions();

    void segmentSlot(void);
    void pipeSlot(int);

    void testSlot(void);
    void capture(void);

private:
    bool recording = false;

    int currentMat = 0;

    const int pathCount = 4;
    std::string paths[4] = { "holes", "aspectRatio", "color", "circles" };
    int normalization[4] = { 3, 4, 255, 12 };
    nlohmann::json meanData;
    nlohmann::json normalizedData;


    Ui::mainWindow ui;

    //CharacteristicPipeline m_modifiers;

    Program* program;
    

    std::vector<cv::Mat> m_mats_o;
    cv::Mat m_mat_r;


    QImage::Format m_mat_o_t;
    cv::VideoCapture* cap;

    
};
