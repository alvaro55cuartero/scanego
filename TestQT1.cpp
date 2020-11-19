#include "TestQT1.h"

/*
    
    struct pieza {

        cv::RotatedRect ROI;
        int id;

    }


    ExtraerPiezas(cv::Mat Img) {
        
        int N = SegmentaImagen(cv::Mat m, cv:Mat* VM);

        for(int i = 0; i < N; i++) {
        
            
        
        }

        
    }





*/



TestQT1::TestQT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.widgetBOX->setVisible(false);
    ui.widgetFLIP->setVisible(false);

    aa = new Ui::AbrirArchivo();
    ga = new Ui::GuardarArchivo();

    QObject::connect(ui.toolButtonREC, SIGNAL(toggled(bool)), this, SLOT(startStopCap(bool)));
    QObject::connect(ui.toolButtonCAP, SIGNAL(clicked(void)), this, SLOT(capture(void)));

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

void TestQT1::startStopCap(bool b) {
    recording = b;
    if (b) {
        frame();
    }
}

void TestQT1::capture(void) {
    m_mat_o = m_mat_i.clone();
    //cv::Mat hist;
    //float range[] = { 0,255 };
    //float* histRange[] = { range, range, range };
    //int histSize[] = { 255, 255, 255 };
    //const int channels = 3;
    //
    //cv::calcHist(&m_mat_o, 1, &channels, cv::Mat(), hist, 3, histSize, histRange);
    //cv::cvtColor(m_mat_o, m_mat_o, cv::COLOR_BGR2HSV);

    //cv::threshold(m_mat_o, );
    drawBuffer();
 
    int tipo = ui.comboBoxTipos->currentIndex();
    int c = ui.spinBoxCounter->value();
    QString ruta = QString("./res/%1/%1-%2.png").arg(tipo).arg(c);
    cv::imwrite(ruta.toLatin1().data(), m_mat_o);
    c++;
    ui.spinBoxCounter->setValue(c);
    //cv::calcHist(&m_mat_o, 1, &channels, cv::Mat(), hist, 3, histSize, histRange);
//    hist = cv::calcHist();
//    hist_norm = hist.ravel() / hist.sum()
//    Q = hist_norm.cumsum()
//    bins = np.arange(256)
//    fn_min = np.inf
//    thresh = -1
//    for i in xrange(1, 256) :
//        p1, p2 = np.hsplit(hist_norm, [i]) # probabilities
//        q1, q2 = Q[i], Q[255] - Q[i] # cum sum of classes
//        if q1 < 1.e-6 or q2 < 1.e-6:
//continue
//    b1, b2 = np.hsplit(bins, [i]) # weights
//    # finding means and variances
//    m1, m2 = np.sum(p1 * b1) / q1, np.sum(p2 * b2) / q2
//    v1, v2 = np.sum(((b1 - m1) * *2) * p1) / q1, np.sum(((b2 - m2) * *2) * p2) / q2
//    # calculates the minimization function
//    fn = v1 * q1 + v2 * q2
//    if fn < fn_min:
//fn_min = fn
//    thresh = i
//    # find otsu's threshold value with OpenCV function
//    ret, otsu = cv.threshold(blur, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
//    print("{} {}".format(thresh, ret))
}

void TestQT1::frame(void) {
    cap->read(m_mat_i);
    if (m_mat_i.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
    }

    drawBuffer();
    
    if (recording) {
        QTimer::singleShot(10, this, SLOT(frame()));
    }
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


