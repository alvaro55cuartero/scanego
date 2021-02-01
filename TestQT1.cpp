#include "TestQT1.h"


TestQT1::TestQT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ga = new Ui::GuardarArchivo();


    QObject::connect(ui.actionREC, SIGNAL(toggled(bool)), this, SLOT(startStopCap(bool)));
    QObject::connect(ui.actionRES, SIGNAL(triggered(void)), this, SLOT(resetSlot(void)));
    QObject::connect(ui.actionPRO, SIGNAL(triggered(void)), this, SLOT(trainSlot(void)));
    QObject::connect(ui.actionUPD, SIGNAL(triggered(void)), this, SLOT(updateSlot(void)));
    QObject::connect(ui.actionTEST, SIGNAL(triggered(void)), this, SLOT(testSlot(void)));
    QObject::connect(ui.actionRight, SIGNAL(triggered(void)), this, SLOT(rightSlot(void)));
    QObject::connect(ui.actionLeft, SIGNAL(triggered(void)), this, SLOT(leftSlot(void)));
    
    QObject::connect(ui.actionHoles, SIGNAL(triggered(void)), this, SLOT(holesSlot(void)));
    QObject::connect(ui.actionAspectRatio, SIGNAL(triggered(void)), this, SLOT(aspectRatioSlot(void)));
    QObject::connect(ui.actionColors, SIGNAL(triggered(void)), this, SLOT(colorsSlot(void)));
    QObject::connect(ui.actionCircles, SIGNAL(triggered(void)), this, SLOT(circlesSlot(void)));

    QObject::connect(ui.actionAbrir, SIGNAL(triggered(void)), this, SLOT(dialogAbrir(void)));
    QObject::connect(ui.actionGuardar, SIGNAL(triggered(void)), this, SLOT(dialogGuardar(void)));

    QObject::connect(ui.actionFilter, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetFilter()); });
    QObject::connect(ui.actionConversion, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetConversion()); });
    QObject::connect(ui.actionThresh, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetThreshold()); });
    QObject::connect(ui.actionConnected, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetConnected());});
    QObject::connect(ui.actionChannel, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetChannel());});



    openImg("./res/otro/2/2.png");
    openCamera();

    holesPipe();
    aspectRatioPipe();
    colorPipe();
    circlePipe();

}


void TestQT1::testRandom() {
    openRandom();
}

void TestQT1::holesPipe() {
    m_holes.append(widgetFilter);
    m_holes.append(widgetToGray);
    m_holes.append(widgetThreshold);
    m_holes.append(widgetConnected);
    m_holes.append(widgetCountHoles);
}

void TestQT1::aspectRatioPipe() {
    m_aspectRatio.append(widgetFilter);
    m_aspectRatio.append(widgetToGray);
    m_aspectRatio.append(widgetThreshold);
    m_aspectRatio.append(widgetConnected);
    m_aspectRatio.append(widgetAspectRatio);
}

void TestQT1::colorPipe() {
    m_colors.append(widgetFilter);
    m_colors.append(widgetToGray);
    m_colors.append(widgetThreshold);
    m_colors.append(widgetConnected);
    m_colors.append(widgetHist);
}

void TestQT1::circlePipe() {
    m_circles.append(widgetFilter);
    m_circles.append(widgetToGray);
    m_circles.append(widgetThreshold);
    m_circles.append(widgetConnected);
    widgetCountCircles->ref = m_mat_r;
    m_circles.append(widgetCountCircles);
}

void TestQT1::holesSlot(void) {
    reset();
    widgetThreshold->setThresh(ui.spinBoxThresh->value());
    std::cout << m_holes.execute(m_mats_o) << "\n";
    drawOut();
}

void TestQT1::aspectRatioSlot(void) {
    reset();
    widgetThreshold->setThresh(ui.spinBoxThresh->value());
    std::cout << m_aspectRatio.execute(m_mats_o) << "\n";
    drawOut();
}

void TestQT1::colorsSlot(void) {
    reset();
    widgetHist->setMask(m_mat_r);
    widgetThreshold->setThresh(ui.spinBoxThresh->value());
    std::cout << m_colors.execute(m_mats_o) << "\n";
    drawOut();
}

void TestQT1::circlesSlot(void) {
    reset();
    widgetThreshold->setThresh(ui.spinBoxThresh->value());
    std::cout << m_circles.execute(m_mats_o) << "\n";
    drawOut();
}


void TestQT1::addWidgetToMenu(ItemWidget* a) {
    ui.sideMenu->layout()->addWidget(a);
    m_modifiers.append(a);
    updateSlot();
}

void TestQT1::updateSlot() {
    reset();
    m_modifiers.execute(m_mats_o);
    drawOut();
}

void TestQT1::openCamera() {
    cap = new cv::VideoCapture();
    int deviceID = 0;
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

void TestQT1::reset() {
    m_mats_o.clear();
    m_mats_o.push_back(m_mat_r.clone());
}

float TestQT1::test() {
    std::string holes = readFile("./json/holes.json");
    std::string aspectRatio = readFile("./json/aspectRatio.json");
    std::string color = readFile("./json/color.json");
    std::string circle = readFile("./json/circle.json");

    nlohmann::json jHoles = nlohmann::json::parse(holes);
    nlohmann::json jAspectRatio = nlohmann::json::parse(aspectRatio);
    nlohmann::json jColor = nlohmann::json::parse(color);
    nlohmann::json jCircle = nlohmann::json::parse(circle);

    float mediaHoles[7] = { 0, 0, 0, 0, 0, 0, 0 };
    float mediaAspectRatio[7] = { 0, 0, 0, 0, 0, 0, 0 };
    float mediaColor[7] = { 0, 0, 0, 0, 0, 0, 0 };
    float mediaCircle[7] = { 0, 0, 0, 0, 0, 0, 0 };

    float _dist = 0, minDist = 10000, pieceIndex = 0;

    widgetThreshold->setThresh(ui.spinBoxThresh->value());

    reset();
    float a = m_holes.execute(m_mats_o);
    
    reset();
    float b = m_aspectRatio.execute(m_mats_o);
    
    reset();
    widgetHist->setMask(m_mat_r);
    float c = m_colors.execute(m_mats_o);

    reset();
    float d = m_circles.execute(m_mats_o);


    a /= 3;
    b /= 4;
    c /= 255;
    d /= 12;

    std::string index;

    for (int i = 0; i < 7; i++) {
        index = std::to_string(i + 1);

        mediaHoles[i] = percentil(jHoles[index]);
        mediaAspectRatio[i] = percentil(jAspectRatio[index]);
        mediaColor[i] = percentil(jColor[index]);
        mediaCircle[i] = percentil(jCircle[index]);

        mediaHoles[i] /= 3;
        mediaAspectRatio[i] /= 4;
        mediaColor[i] /=  255;
        mediaCircle[i] /= 12;

        _dist = dist(mediaHoles[i], a/3, mediaAspectRatio[i],  b/4, mediaColor[i], c/255 , mediaCircle[i], d /12);
        if (minDist > _dist) {
            pieceIndex = i + 1;
            minDist = _dist;
        }

        QString ruta = QString("%1 : %2 \t %3 : %4  \t %5 : %6 \t %7 : %8\t || %9").arg(mediaHoles[i]).arg(a).arg(mediaAspectRatio[i]).arg(b).arg(mediaColor[i]).arg(c).arg(mediaCircle[i]).arg(d).arg(_dist);
        std::cout  << ruta.toLatin1().data() << std::endl;
    }

    std::cout << pieceIndex << std::endl;
}

float TestQT1::dist(float x, float xo, float y, float yo, float z, float zo, float w, float wo) {
    float _x = (x - xo) * (x - xo);
    float _y = (y - yo) * (y - yo);
    float _z = (z - zo) * (z - zo);
    float _w = (w - wo) * (w - wo);

    return std::sqrt(_x +_y + _z + _w);
}

float TestQT1::percentil(std::vector<float> arr) {
    float alpha = 0.90;
    float out = 0.;
    std::sort(arr.begin(), arr.end());
    int idx = std::ceil((alpha) * arr.size());
    for (int i = 0; i < idx; i++) {
        out += arr[idx];
    }
    out /= idx;
    return out;
}


void TestQT1::testSlot() {
    test();
    //label();
}


void TestQT1::trainSlot() {
    QString ruta, name;
    nlohmann::json holesOut, aspectRatioOut, colorOut, circleOut;
    nlohmann::json js = { {"1", 120},{"2", 85} ,{"3", 120},{ "4", 120}, {"5",120}, {"6",130},{"7", 120} };
    for (int i = 1; i < 8; i++) {
        name = QString("%1").arg(i);
        widgetThreshold->setThresh(js[name.toLatin1().data()].get<int>());
        for (int j = 0; j < 19; j++)
        {

            ruta = QString("./res/otro/%1/%2.png").arg(i).arg(j);
            openImg(ruta.toLatin1().data());
            reset();           
            holesOut[name.toLatin1().data()].push_back(m_holes.execute(m_mats_o));
            reset();
            aspectRatioOut[name.toLatin1().data()].push_back(m_aspectRatio.execute(m_mats_o));
            reset();
            widgetHist->setMask(m_mat_r);
            colorOut[name.toLatin1().data()].push_back(m_colors.execute(m_mats_o));
            reset();
            widgetCountCircles->ref = m_mat_r;
            circleOut[name.toLatin1().data()].push_back(m_circles.execute(m_mats_o));
        }
    }
    
    std::ofstream file;
    file.open("./json/holes.json");
    file << std::setw(4) << holesOut;
    file.close();
    file.open("./json/aspectRatio.json");
    file << std::setw(4) << aspectRatioOut;
    file.close();
    file.open("./json/color.json");
    file << std::setw(4) << colorOut;
    file.close();
    file.open("./json/circle.json");
    file << std::setw(4) << circleOut;
    file.close();

}

void TestQT1::rightSlot(void) {
    if (currentMat + 1 >= m_mats_o.size()) {
        currentMat = 0;
    }
    else {
        currentMat++;
    }
    ui.actionCount->setText(QString("%1").arg(currentMat));
}

void TestQT1::leftSlot(void) {
    if (currentMat - 1 < 0) {
        currentMat = m_mats_o.size() - 1;
    }
    else {
        currentMat--;
    }
    ui.actionCount->setText(QString("%1").arg(currentMat));
}

void TestQT1::frame(void) {
    cap->read(m_mats_o[0]);
    m_mats_o[0].copyTo(m_mat_r);
    cv::flip(m_mats_o[0], m_mats_o[0], 1);
    if (m_mats_o[0].empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
    }

    float a = test();
    

    drawOut();
    
    if (recording) {
        QTimer::singleShot(10, this, SLOT(frame()));
    }
}


void TestQT1::dialogAbrir(void) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), tr("./res"), tr("Image Files (*.png *.jpg *.jpeg *.bmp * .tif)"));
    std::string a = qPrintable(fileName);
    openImg(a);
}

void TestQT1::openRandom() {
    int i = rand() % 6 + 1;
    int j = rand() % 19;
    QString ruta = QString("./res/otro/%1/%2.png").arg(i).arg(j);
    openImg(ruta.toLatin1().data());
}

void TestQT1::openImg(std::string path) {
    cv::Mat m = cv::imread(path);
    if (m_mats_o.size() == 0)
        m_mats_o.push_back(m.clone());
    else
        m_mats_o[0] = m.clone();
    m_mat_r = m_mats_o[0].clone();
    drawOut();
}

std::string TestQT1::readFile(std::string path) {
    std::string line;
    std::string out;
    std::ifstream file(path);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            out.append(line);
        }
        file.close();
    }
    else return "";

    return out;
}

std::string TestQT1::writeFile(std::string path) {
    std::string line;
    std::string out;
    std::ifstream file(path);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            out.append(line);
        }
        file.close();
    }
    else return "";

    return out;
}



void TestQT1::dialogGuardar(void) {
    QDialog* tempDialog = new QDialog();
    ga->setupUi(tempDialog);
    if (tempDialog->exec()) {
        QString b = ga->lineEditOut->text();
        std::string a = qPrintable(b);
        //cv::imwrite(a, m_mat_o);
    }
}

void TestQT1::drawBuffer(QLabel* label, cv::Mat mat, QImage::Format type) {
    label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)mat.data, mat.cols, mat.rows, type)));
}

void TestQT1::drawBuffer(QLabel* label, cv::Mat mat) {
    label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)mat.data, mat.cols, mat.rows, type2Format(mat.type()))));
}

void TestQT1::drawOut() {
    drawBuffer(ui.labelOut, m_mats_o[currentMat], type2Format(m_mats_o[0].type()));
}

QImage::Format TestQT1::type2Format(int type) {
    switch (type) {
    case CV_8UC1:
        return QImage::Format_Grayscale8;
    case CV_8UC3:
        return QImage::Format_BGR888;
    }
}

void TestQT1::drawRect(cv::RotatedRect rect) {
    cv::Point2f vertices[4];
    rect.points(vertices);
    for (int i = 0; i < 4; i++)
        cv::line(m_mats_o[0], vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 255, 255), 2);
    //cv::Rect brect = rect.boundingRect();
    //rectangle(m_mat_o, brect, cv::Scalar(255, 0, 0), 2);

    drawOut();
}


// slots

void TestQT1::contourSlot() {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(m_mats_o[0], contours, hierarchy, 0, 1, cv::Point(0, 0));

    std::vector<cv::RotatedRect> minRect(contours.size());

    for (int i = 0; i < contours.size(); i++)
    {
        minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));
        int area = cv::contourArea(contours[i]);
        if (area > 1000) {
            drawRect(minRect[i]);
            std::cout << area << "\t";
        }
    }

}

void TestQT1::resetSlot() {
    reset();
    drawOut();
}

