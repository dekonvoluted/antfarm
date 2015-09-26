#ifndef AF_MAINWINDOW_H
#define AF_MAINWINDOW_H

#include <QMainWindow>

class AntFarmView;
class AntFarmScene;

class AntFarmMainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    AntFarmMainWindow( QWidget* = 0 );

    private:
    AntFarmView* view;
    AntFarmScene* scene;
};

#endif

