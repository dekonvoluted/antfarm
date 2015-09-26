#ifndef AF_FPS_WIDGET_H
#define AF_FPS_WIDGET_H

#include <QWidget>

class QGridLayout;
class QLabel;
class QSlider;

class FPSWidget : public QWidget
{
    Q_OBJECT

    public:
    FPSWidget( QWidget* = 0 );

    public slots:
    void setOrientation( Qt::Orientation );

    private:
    QSlider* slider;
    QLabel* slowerLabel;
    QLabel* fasterLabel;
    QGridLayout* layout;
};

#endif

