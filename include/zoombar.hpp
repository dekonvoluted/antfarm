#pragma once

#include <QWidget>

class QGridLayout;
class QLabel;
class QSlider;

class ZoomBar : public QWidget {
    Q_OBJECT

public:
    ZoomBar(QWidget* = nullptr);

public slots:
    void setOrientation(Qt::Orientation);

private:
    QSlider* m_slider;
    QLabel* m_slow;
    QLabel* m_fast;
    QGridLayout* m_layout;
};
