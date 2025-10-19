#include "afmainwindow.hpp"
#include "afscene.hpp"
#include "afview.hpp"

AntFarmMainWindow::AntFarmMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    scene = new AntFarmScene();
    view = new AntFarmView(scene);

    this->setCentralWidget(view);
}
