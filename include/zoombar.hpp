#pragma once

#include <QWidget>

class QBoxLayout;
class QLabel;
class QSlider;

class ZoomBar : public QWidget {
    Q_OBJECT

public:
    ZoomBar(QWidget* = nullptr);

public slots:
    void setOrientation(Qt::Orientation);

private:
    QLabel* m_label;
    QSlider* m_slider;
    QBoxLayout* m_layout;
};
