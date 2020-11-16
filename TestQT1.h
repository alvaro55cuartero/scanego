#pragma once

#include <QtWidgets/qlabel.h>
#include <QtWidgets/QMainWindow>
#include <qtimer.h>

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

#include "ui_TestQT1.h"
#include "ui_AbrirArchivo.h"
#include "ui_GuardarArchivo.h"
#include "ui_WidgetBOX.h"

class TestQT1 : public QMainWindow
{
    Q_OBJECT

public:
    TestQT1(QWidget *parent = Q_NULLPTR);

    
    void drawBuffer(void);
    void openFile(std::string );

public slots:
    void flipX(void);
    void flipY(void);
    void dialogAbrir(void);
    void dialogGuardar(void);
    void drawBox(void);
    void gray(void);
    void frame(void);
    void capture(void);

private:
    Ui::TestQT1Class ui;
    Ui::AbrirArchivo* aa;
    Ui::GuardarArchivo* ga;
    QLabel* wBOX;

    cv::Mat m_mat_i;
    cv::Mat m_mat_o;
    cv::VideoCapture* cap;
};
