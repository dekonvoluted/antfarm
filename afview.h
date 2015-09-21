#ifndef AF_VIEW_H
#define AF_VIEW_H

#include <QGraphicsView>

class AntFarmScene;

class AntFarmView : public QGraphicsView
{
    public:
    AntFarmView( AntFarmScene* = 0, QWidget* = 0 );

    private:
    AntFarmScene* scene;
};

#endif

