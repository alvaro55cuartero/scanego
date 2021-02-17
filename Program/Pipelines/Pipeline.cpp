#include "Pipeline.h"


Pipeline::Pipeline(std::string name, cv::Mat* img, QWidget* parent)
    : QWidget(parent), name(name)
{
    QLabel* nameLabel = new QLabel(std::string("Pipeline: " + name).c_str());

    
    


    QWidget* menu = new QWidget();
    menu->setLayout(new QHBoxLayout());

    QPushButton* saveButton = new QPushButton("Save");
    QObject::connect(saveButton, &QPushButton::clicked, [this] { save(); });
    menu->layout()->addWidget(saveButton);
    
    QPushButton* testButton = new QPushButton("test");
    QObject::connect(testButton, &QPushButton::clicked, [this] { test(); });
    menu->layout()->addWidget(testButton);


    QScrollArea* scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scroll->setWidgetResizable(true);
    scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    
    inner = new QWidget();
    inner->setMaximumHeight(100);
    inner->setLayout(new QVBoxLayout());
    inner->layout()->setSizeConstraint(QLayout::SetMinAndMaxSize);

    scroll->setWidget(inner);

    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(nameLabel);
    this->layout()->addWidget(menu);
    this->layout()->addWidget(scroll);

    setOriginal(img);
    openFromJson("./json/pipelines/" + name +".json");
    
}


void Pipeline::append(ItemWidget* itemWidget) {


    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QWidget* header = new QWidget();
    QHBoxLayout* topBar = new QHBoxLayout();
    
    QLabel* title = new QLabel();
    title->setText(itemWidget->getName().c_str());
    topBar->addWidget(title);
    
    QPushButton* delButton = new QPushButton();
    delButton->setMaximumSize(15, 15);
    delButton->setText("X");
    int index = list.size();
    QObject::connect(delButton, &QPushButton::clicked, [this, widget, index] { delWidget(widget); });
    topBar->addWidget(delButton);
    
    
    header->setLayout(topBar);
    layout->addWidget(header);

    widget->setStyleSheet("QWidget#Box {border-radius: 5px; border: 1px solid black;}");
    widget->setObjectName(QString("Box"));
    layout->addWidget(itemWidget);
    widget->setLayout(layout);
    inner->layout()->addWidget(widget);
	
    list.push_back(itemWidget);
}

void Pipeline::save() {
   utils::writeJsonFile("./json/pipelines/" + name + ".json" ,this->toJson());
}

void Pipeline::test() {

}


void Pipeline::reset() {
	list.clear();
}

void Pipeline::setName(std::string name) {
    this->name = name;
}

void Pipeline::delWidget(QWidget* itemWidget) {
    
    int index = inner->layout()->children().indexOf(itemWidget);
    list.erase(list.begin() + index);
    inner->layout()->removeWidget(itemWidget);
    delete itemWidget;
}

void Pipeline::openFromJson(std::string path) {
    parse(utils::readJsonFile(path));
}

void Pipeline::parse(nlohmann::json json) {
    ItemWidget* widget = nullptr;
    std::string type;

    for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
        type = it.value()["type"];
        auto& arg = it.value()["arg"];
        if (type == "filter")
        {
            widget = new WidgetFilter();
        }
        else if (type == "threshold")
        {
            widget = new WidgetThreshold();
        }
        else if (type == "otsu") 
        {
            widget = new WidgetOtsu();
        }
        else if (type == "gray")
        {
            widget = new WidgetToGray();
        }
        else if (type == "connected")
        {
            widget = new WidgetConnected();
        }
        else if (type == "holes")
        {
            widget = new WidgetCountHoles(m_original);
        }
        else if (type == "histogram")
        {
            widget = new WidgetHist(m_original);
        }
        else if (type == "aspectRatio")
        {
            widget = new WidgetAspectRatio();
        }
        else if (type == "circles") 
        {
            widget = new WidgetCountCircles(m_original);
        }
        else if (type == "drawRects")
        {
            widget = new WidgetDrawRects(m_original);
        }
        else if (type == "erode")
        {
            widget = new WidgetErode();
        }
        else if (type == "dilate")
        {
            widget = new WidgetDilate();
        }
        else if (type == "meanFilter")
        {
            widget = new WidgetMeanFilter();
        }
        else if (type == "sobel")
        {
            widget = new WidgetSobel();
        }
        else if (type == "canny")
        {
            widget = new WidgetCanny();
        }
        else if (type == "area")
        {
            widget = new WidgetArea();
        }
        else if (type == "detectRect") 
        {
            widget = new WidgetDetectRects();
        }

        widget->jsonParse(arg);
        this->append(widget);
    }
}


void Pipeline::setOriginal(cv::Mat* img) {
    m_original = img;
}


float Pipeline::process(std::vector<cv::Mat>& out) {
    float result = 0;
    CharacteristicWidget* ch;
    MultiWidget* ml;

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


nlohmann::json Pipeline::toJson() {
    nlohmann::json json;
    for (ItemWidget* value : list) {
        json.push_back(value->toJson());
    }
    return json;
}
