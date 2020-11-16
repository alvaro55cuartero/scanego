#include "TestQT1.h"


TestQT1::TestQT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.widgetBOX->setVisible(false);
    ui.widgetFLIP->setVisible(false);

    aa = new Ui::AbrirArchivo();
    ga = new Ui::GuardarArchivo();

    QObject::connect(ui.actionBOX, SIGNAL(triggered(bool)), this, SLOT(frame(void)));
    QObject::connect(ui.actionAbrir, SIGNAL(triggered(void)), this, SLOT(dialogAbrir(void)));
    QObject::connect(ui.actionGuardar, SIGNAL(triggered(void)), this, SLOT(dialogGuardar(void)));
    QObject::connect(ui.pushButtonWidgetBOX, SIGNAL(clicked(void)), this, SLOT(drawBox(void)));
    QObject::connect(ui.pushButton_H, SIGNAL(clicked(void)), this, SLOT(flipX(void)));
    QObject::connect(ui.pushButton_V, SIGNAL(clicked(void)), this, SLOT(flipY(void)));

    openFile("./res/Captura.PNG");

    cap = new cv::VideoCapture();
    int deviceID = 1;
    int apiID = cv::CAP_ANY;
   
    cap->open(deviceID, apiID);
    
    if (!cap->isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
    }

    
}

void TestQT1::frame(void) {
    //wBOX = new Ui::widgetBOX();
    //ui.widget->layout()->addWidget(wBOX);
    cap->read(m_mat_i);
    if (m_mat_i.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
    }

    drawBuffer();
    
    QTimer::singleShot(20, this, SLOT(frame()));
}


void TestQT1::dialogAbrir(void) {
    QDialog* tempDialog = new QDialog();
    aa->setupUi(tempDialog);
    if (tempDialog->exec()) {
        QString b = aa->lineEditIn->text();
        std::string a = qPrintable(b);
        openFile(a);
    }
}

void TestQT1::openFile(std::string path) {
    m_mat_i = cv::imread(path);
    m_mat_o = m_mat_i.clone();
    drawBuffer();
}


void TestQT1::dialogGuardar(void) {
    QDialog* tempDialog = new QDialog();
    aa->setupUi(tempDialog);
    if (tempDialog->exec()) {
        QString b = ga->lineEditOut->text();
        std::string a = qPrintable(b);
        cv::imwrite(a, m_mat_o);
    }
}

void TestQT1::drawBox(void) {
    int x = ui.spinBox_X->value();
    int y = ui.spinBox_Y->value();
    int w = ui.spinBox_W->value();
    int h = ui.spinBox_H->value();


    cv::Mat mask = m_mat_o(cv::Range(x, x + w), cv::Range(y, y + h));
    mask.setTo(cv::Scalar(255, 255, 0));

    drawBuffer();
}

void TestQT1::flipX() {
    cv::flip(m_mat_o, m_mat_o, 0);

    drawBuffer();
}

void TestQT1::flipY() {
    cv::flip(m_mat_o, m_mat_o, 1);

    drawBuffer();
}

void TestQT1::gray() {

}
void TestQT1::drawBuffer(void) {
    ui.labelIn->setPixmap(QPixmap::fromImage(QImage((unsigned char*)m_mat_i.data, m_mat_i.cols, m_mat_i.rows, QImage::Format_BGR888)));
    ui.labelOut->setPixmap(QPixmap::fromImage(QImage((unsigned char*)m_mat_o.data, m_mat_o.cols, m_mat_o.rows, QImage::Format_BGR888)));
}


