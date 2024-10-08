#pragma once

#include <QMainWindow>

class AntFarmView;
class AntFarmScene;

class AntFarmMainWindow : public QMainWindow {
public:
    AntFarmMainWindow(QWidget* = 0);

private:
    AntFarmView* view;
    AntFarmScene* scene;
};
