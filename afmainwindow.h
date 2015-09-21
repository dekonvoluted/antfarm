#ifndef AF_MAINWINDOW_H
#define AF_MAINWINDOW_H

#include <QMainWindow>

class AntFarmView;

class AntFarmMainWindow : public QMainWindow
{
    public:
    AntFarmMainWindow( QWidget* = 0 );

    private:
    AntFarmView* view;
};

#endif

