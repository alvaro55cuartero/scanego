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

#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/hal/interface.h>
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <iostream>

class ItemWidget : public QWidget
{

Q_OBJECT
public:
	explicit ItemWidget(QWidget* parent = 0) : QWidget(parent) {};

	virtual void modificador(std::vector<cv::Mat>& out) = 0;

private:

signals:

public slots:
};