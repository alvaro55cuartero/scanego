#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QCombobox>
#include <QtWidgets/QCheckbox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFrame>

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/hal/interface.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "../../json.hpp"

#include <vector>
#include <iostream>

class ItemWidget : public QWidget
{

Q_OBJECT
public:
	explicit ItemWidget(QWidget* parent, std::string name);

	virtual void modificador(cv::Mat in, std::vector<cv::Mat>& out) = 0;
	
	virtual void jsonParse(nlohmann::json json) = 0;

	std::string getName() { return name; }

	virtual nlohmann::json toJson() = 0;

private:
	std::string name;

protected:

signals:

public slots:
};