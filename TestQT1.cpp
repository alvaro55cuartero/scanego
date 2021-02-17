#include "TestQT1.h"


TestQT1::TestQT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(ui.actionREC, SIGNAL(toggled(bool)), this, SLOT(startStopCap(bool)));
    QObject::connect(ui.actionCAP, SIGNAL(triggered(void)), this, SLOT(capture(void)));
    QObject::connect(ui.actionRES, SIGNAL(triggered(void)), this, SLOT(resetSlot(void)));
    QObject::connect(ui.actionPRO, SIGNAL(triggered(void)), this, SLOT(trainSlot(void)));
    QObject::connect(ui.actionUPD, SIGNAL(triggered(void)), this, SLOT(updateSlot(void)));
    QObject::connect(ui.actionTEST, SIGNAL(triggered(void)), this, SLOT(testSlot(void)));
    QObject::connect(ui.actionTrain, SIGNAL(triggered(void)), this, SLOT(trainSlot(void)));
    QObject::connect(ui.actionRight, SIGNAL(triggered(void)), this, SLOT(rightSlot(void)));
    QObject::connect(ui.actionLeft, SIGNAL(triggered(void)), this, SLOT(leftSlot(void)));
    QObject::connect(ui.actionCamera, SIGNAL(triggered(void)), this, SLOT(cameraOptions(void)));
    
    QObject::connect(ui.actionSegmentation, SIGNAL(triggered(void)), this, SLOT(segmentSlot(void)));

    QObject::connect(ui.actionAbrir, SIGNAL(triggered(void)), this, SLOT(dialogAbrir(void)));

    QObject::connect(ui.actionFilter, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetFilter()); });
    QObject::connect(ui.actionConversion, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetConversion()); });
    QObject::connect(ui.actionThresh, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetThreshold()); });
    QObject::connect(ui.actionConnected, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetConnected());});
    QObject::connect(ui.actionChannel, &QAction::triggered, this, [this] {addWidgetToMenu(new WidgetChannel());});

    QObject::connect(ui.actionDispersion, &QAction::triggered, this, [this] {dispersionFiles();});


    openImg("./res/set3/1/0.png");
    openCamera();
    meanData = utils::readJsonFile("./json/Train/MeanData.json");
    normalizedData = utils::readJsonFile("./json/Train/NormalizeData.json");

    
    program = new Program();
    program->trainInit(normalizedData);
    program->addSegmentationPipe("segmentation2");
    
    for (int i = 0; i < pathCount; i++) {

        program->appendCharacteristicPipeline(paths[i]);
        QAction* action = ui.menuPipelines->addAction(paths[i].c_str());
        QObject::connect(action, &QAction::triggered, [this, i] { pipeSlot(i); });
    }

    program->addOutPipeline("out");

}




void TestQT1::segmentSlot(void) {
    std::vector<cv::Mat> output;
    program->setOriginal(m_mat_r);
    program->executeSegmentation(output);
    drawOut(output[0]);
    addWidgetToMenu(program->getSegmentationPipe());
}


void TestQT1::pipeSlot(int pipe) {
    std::vector<cv::Mat> output;
    program->setOriginal(m_mat_r);
    float result = program->executeCharacteristic(pipe, output);
    std::cout << result << std::endl;
    drawOut(output[0]);
    addWidgetToMenu(program->getCharacteristicPipe(pipe));
}



void TestQT1::addWidgetToMenu(QWidget* a) {
    QLayout* layout = ui.sideMenu->layout();
    clearLayout(layout);
         
    layout->addWidget(a);
    //m_modifiers.append(a);
    //updateSlot();
}

void TestQT1::clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void TestQT1::addWidgetToPipeline(ItemWidget* a) {
    QLayout* layout = ui.sideMenu->layout();
    while (layout->count() > 0) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)))
            delete item;
    }
    ui.sideMenu->layout()->addWidget(a);
    //m_modifiers.append(a);
    //updateSlot();
}

void TestQT1::updateSlot() {
    reset();
    program->setOriginal(m_mat_r);
    std::vector<cv::Mat> out;
    program->executeSegmentation(out);
    drawOut(out[0]);
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



void TestQT1::segTest(std::vector<cv::Mat>& out) {
    float result = 0;
    CharacteristicWidget* ch;
    MultiWidget* ml;

    std::vector<ItemWidget*> list;
    list.push_back(new WidgetFilter());
    list.push_back(new WidgetToGray());
    list.push_back(new WidgetCanny());
    list.push_back(new WidgetDilate());
    list.push_back(new WidgetArea());
    list.push_back(new WidgetErode());
    std::vector<cv::Mat> temp;

    for (ItemWidget* value : list) {
        ch = dynamic_cast<CharacteristicWidget*>(value);
        ml = dynamic_cast<MultiWidget*>(value);

        if (ch != nullptr) {
            for (int i = 0; i < out.size(); i++)
                result = (ch)->characteristic(out[i], temp);
        }
        else if (ml != nullptr) {
            (ml)->multi(out, temp);
        }
        else {
            for (int i = 0; i < out.size(); i++)
                (value)->modificador(out[i], temp);
        }

        out = temp;
        temp.clear();
    }
}

float TestQT1::holesTest(std::vector<cv::Mat>& out) {
    float result = 0;
    CharacteristicWidget* ch;
    MultiWidget* ml;

    std::vector<ItemWidget*> list;
    list.push_back(new WidgetCountHoles(&m_mat_r));
    std::vector<cv::Mat> temp;

    for (ItemWidget* value : list) {
        ch = dynamic_cast<CharacteristicWidget*>(value);
        ml = dynamic_cast<MultiWidget*>(value);

        if (ch != nullptr) {
            for (int i = 0; i < out.size(); i++)
                result = (ch)->characteristic(out[i], temp);
        }
        else if (ml != nullptr) {
            (ml)->multi(out, temp);
        }
        else {
            for (int i = 0; i < out.size(); i++)
                (value)->modificador(out[i], temp);
        }

        out = temp;
        temp.clear();
    }
    return result;
}

float TestQT1::cirlcesTest(std::vector<cv::Mat>& out) {
    float result = 0;
    CharacteristicWidget* ch;
    MultiWidget* ml;

    std::vector<ItemWidget*> list;
    list.push_back(new WidgetHist(&m_mat_r));
    std::vector<cv::Mat> temp;

    for (ItemWidget* value : list) {
        ch = dynamic_cast<CharacteristicWidget*>(value);
        ml = dynamic_cast<MultiWidget*>(value);

        if (ch != nullptr) {
            for (int i = 0; i < out.size(); i++)
                result = (ch)->characteristic(out[i], temp);
        }
        else if (ml != nullptr) {
            (ml)->multi(out, temp);
        }
        else {
            for (int i = 0; i < out.size(); i++)
                (value)->modificador(out[i], temp);
        }

        out = temp;
        temp.clear();
    }
    return result;
}


float TestQT1::test() {
    /*
    
    std::vector<cv::Mat> out;
    program->setOriginal(m_mat_r);
    program->executeSegmentation(out);
    std::cout << cirlcesTest(out) << std::endl;

    cv::Mat a = cv::Mat::zeros(cv::Size(640,480), CV_8UC1);
    

    drawOut(out[0]);
    */
    /*
    /**/
    
    std::vector<cv::Mat> out;
    std::vector<std::vector<float>> characteristicVector = program->execute(m_mat_r, out);
    if (out.size() > 0) 
        drawOut(out[0]);
    /**/
    return 0;
}

float TestQT1::testPorPieza(nlohmann::json json, float* media) {
    return 1;
}


float TestQT1::percentil(std::vector<float> arr) {
    float alpha = 0.90;
    float out = 0.;
    std::sort(arr.begin(), arr.end());
    int idx = std::ceil((alpha)*arr.size());
    for (int i = 0; i < idx; i++) {
        out += arr[idx];
    }
    out /= idx;
    return out;
}


void TestQT1::testSlot() {
    test();
}


void TestQT1::trainSlot() {
    train();
}

void TestQT1::train() {
    QString ruta;
    nlohmann::json jsonRawData, jsonNormalizedData, jsonMeanData;
    std::vector<float> vector;
    std::vector<cv::Mat> out;

    nlohmann::json ideal = utils::readJsonFile("./json/Train/ideal.json");
    nlohmann::json last = utils::readJsonFile("./json/Train/MeanData.json");
    nlohmann::json lastTrain;
    nlohmann::json current;

    float currentErrorCircles = 0;
    float lastErrorCircles = 0;
    float change = 0;

    for (int i = 1; i < 8; i++) {
        float temp[4] = { 0 ,0 , 0, 0};

        for (int j = 0; j < 40; j++) {
            ruta = QString("./res/set3/%1/%2.png").arg(i).arg(j);
            openImg(ruta.toLatin1().data());
            vector = program->executeTest(m_mat_r, out);
            
            for (int k = 0; k < pathCount; k++) {
                jsonRawData[std::to_string(i)][paths[k]].push_back(vector[k]);
                jsonNormalizedData[std::to_string(i)][paths[k]].push_back(vector[k] / normalization[k]);
                temp[k] += (vector[k] / normalization[k]) / 40;


                //float a = ideal[std::to_string(i)][k].get<float>();
                //float b = last[std::to_string(i)].at(k);
                //last[std::to_string(i)][k] = a - b;
                //current[std::to_string(i)][k] = ideal[std::to_string(i)][k].get<float>() - temp[k];

            }
        }

        float a = ideal[std::to_string(i)][3].get<float>();
        float b = last[std::to_string(i)][3].get<float>();

        lastTrain.push_back(std::abs(a - b));
        lastErrorCircles += std::abs(a- b);
        current.push_back(std::abs(a - temp[3]));
        currentErrorCircles += std::abs(a- temp[3]);
        

        jsonMeanData[std::to_string(i)] = temp;
    
    }

    //QString ruta = QString("./res/A/%1%2.png").arg().arg();

    std::cout << lastTrain << std::endl;
    std::cout << current << std::endl;

    std::cout << lastErrorCircles / 7 << " - " << currentErrorCircles / 7 << " = " << (lastErrorCircles / 7) - (currentErrorCircles / 7) << std::endl;



    
    utils::writeJsonFile("./json/Train/RawData.json", jsonRawData);
    utils::writeJsonFile("./json/Train/NormalizeData.json", jsonNormalizedData);
    utils::writeJsonFile("./json/Train/MeanData.json", jsonMeanData);
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
    cap->read(m_mat_r);
    cv::flip(m_mat_r, m_mat_r, 1);
    if (m_mat_r.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
    }
    

    test();

    /*std::vector<cv::Mat>* x = new std::vector<cv::Mat>();
    program->setOriginal(m_mat_r);
    x->clear();
    program->executeSegmentation(*x);
    drawOut((*x)[0]);

    /*std::vector<cv::Mat> out;
    std::vector<std::vector<float>> characteristicVector = program->execute(m_mat_r, out, meanData);
    if (out.size() > 0) drawOut(out[0]);
    else drawOut(m_mat_r);
    /**/


    drawIn(m_mat_r);


    if (recording) {
        QTimer::singleShot(10, this, SLOT(frame()));
    }
}

void TestQT1::capture() {
    time_t now = time(NULL);
    //char* dt = ctime(&now);

    QString ruta = QString("./res/A/%1%2.png").arg(ui.spinBox1->value()).arg(ui.spinBox2->value());
    ui.spinBox2->setValue(ui.spinBox2->value()+ 1);
    std::cout << ruta.toLatin1().data() << std::endl;
    cv::imwrite(ruta.toLatin1().data(), m_mat_r);
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
    m_mat_r = m.clone();
    drawIn(m);
}


void TestQT1::dialogGuardar(void) {
    QDialog* tempDialog = new QDialog();
    if (tempDialog->exec()) {
        //std::string a = qPrintable(b);
        //cv::imwrite(a, m_mat_o);
    }
}

void TestQT1::drawBuffer(QLabel* label, cv::Mat mat, QImage::Format type) {
    label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)mat.data, mat.cols, mat.rows, type)));
}

void TestQT1::drawBuffer(QLabel* label, cv::Mat mat) {
    label->setPixmap(QPixmap::fromImage(QImage((unsigned char*)mat.data, mat.cols, mat.rows, type2Format(mat.type()))));
}

void TestQT1::drawOut(cv::Mat out) {
    drawBuffer(ui.labelOut, out, type2Format(out.type()));
}

void TestQT1::drawIn(cv::Mat out) {
    drawBuffer(ui.labelIn, out, type2Format(out.type()));
}

void TestQT1::drawOut() {
    drawBuffer(ui.labelOut, m_mat_r, type2Format(m_mat_r.type()));
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


void TestQT1::dispersionFiles() {
    nlohmann::json rawData = utils::readJsonFile("./json/Train/NormalizeData.json");
    std::string data = "";
    std::string classData = "";
    std::string index = "";

    std::ofstream values;
    values.open("./out/values.csv");
    
    std::ofstream classes;
    classes.open("./out/classes.csv");


    for (int i = 0; i < 7; i++) {
        index = std::to_string(i + 1);
        for (int j = 0; j < 40; j++) {
            classes << index << std::endl;

            values << std::to_string(rawData[index]["holes"].get<std::vector<float>>()[j]) << ",";
            values << std::to_string(rawData[index]["aspectRatio"].get<std::vector<float>>()[j]) << ",";
            values << std::to_string(rawData[index]["color"].get<std::vector<float>>()[j]) << ",";
            values << std::to_string(rawData[index]["circles"].get<std::vector<float>>()[j]) << std::endl;
            
        }
    }


    values.close();
    classes.close();
}


void TestQT1::resetSlot() {
    reset();
    drawOut();
}

void TestQT1::cameraOptions() {
    cap->set(cv::CAP_PROP_SETTINGS, 1);

}

