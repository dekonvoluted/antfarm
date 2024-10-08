#pragma once

#include <QGraphicsView>

class AntFarmScene;

class AntFarmView : public QGraphicsView {
public:
    AntFarmView(AntFarmScene* = 0, QWidget* = 0);

private:
    AntFarmScene* scene;
};
