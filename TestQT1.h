#pragma once

#include <QtWidgets/qlabel.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qfiledialog.h>
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


#include "ui_TestQT1.h"
#include "ui_GuardarArchivo.h"
#include "ui_WidgetBOX.h"

#include "widget/Pipeline.h"
#include "widget/ItemWidget.h"
#include "widget/types/WidgetFilter.h"
#include "widget/types/WidgetThreshold.h"
#include "widget/types/WidgetConnected.h"
#include "widget/types/WidgetMask.h"
#include "widget/types/WidgetChannel.h"
#include "widget/types/characteristic/WidgetCountHoles.h"
#include "widget/types/characteristic/WidgetAspectRatio.h"
#include "widget/types/characteristic/WidgetHist.h"
#include "widget/types/characteristic/WidgetCountCircles.h"
#include "widget/types/conversions/WidgetConversion.h"
#include "widget/types/conversions/WidgetToGray.h"


class TestQT1 : public QMainWindow
{
    Q_OBJECT

public:
    TestQT1(QWidget *parent = Q_NULLPTR);

    void drawBuffer(QLabel* label, cv::Mat mat, QImage::Format type);
    void drawBuffer(QLabel* label, cv::Mat mat);
    void drawOut();
    void drawRect(cv::RotatedRect rect);


    void openImg(std::string);

    std::string writeFile(std::string);
    std::string readFile(std::string);

    void openCamera();
    void reset();

    float test();

    void holesPipe();
    void aspectRatioPipe();
    void colorPipe();
    void circlePipe();

    float dist(float x, float xo, float y, float yo, float z, float zo, float w, float wo);
    float percentil(std::vector<float> arr);

    void openRandom();
    void testRandom();

    QImage::Format type2Format(int type);


public slots:    
    void addWidgetToMenu(ItemWidget*);

    void dialogAbrir(void);
    void dialogGuardar(void);
    void frame(void);
    void resetSlot(void);
    void startStopCap(bool);
    void rightSlot(void);
    void leftSlot(void);
    void updateSlot(void);
    void trainSlot();

    void holesSlot(void);
    void aspectRatioSlot(void);
    void colorsSlot(void);
    void circlesSlot(void);

    void contourSlot(void);
    void testSlot(void);


private:
    bool recording = false;

    int currentMat = 0;

    Ui::TestQT1Class ui;
    Ui::GuardarArchivo* ga;
    QLabel* wBOX;

    Pipeline m_modifiers;
    Pipeline m_holes;
    Pipeline m_aspectRatio;
    Pipeline m_colors;
    Pipeline m_circles;

    std::vector<cv::Mat> m_mats_o;

    cv::Mat labels;

    cv::Mat m_mat_r;

    QImage::Format m_mat_o_t;
    cv::VideoCapture* cap;

    WidgetFilter* widgetFilter = new WidgetFilter();
    WidgetThreshold* widgetThreshold = new WidgetThreshold();
    WidgetConnected* widgetConnected = new WidgetConnected();
    WidgetCountHoles* widgetCountHoles = new WidgetCountHoles();
    WidgetAspectRatio* widgetAspectRatio = new WidgetAspectRatio();
    WidgetCountCircles* widgetCountCircles = new WidgetCountCircles();
    WidgetMask* widgetMask = new WidgetMask();
    WidgetChannel* widgetChannel = new WidgetChannel();
    WidgetHist* widgetHist = new WidgetHist();
    WidgetConversion* widgetConversion = new WidgetConversion();
    WidgetToGray* widgetToGray = new WidgetToGray();
};
