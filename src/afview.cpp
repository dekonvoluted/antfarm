#include "afview.hpp"
#include "afscene.hpp"

AntFarmView::AntFarmView(AntFarmScene* afscene, QWidget* parent)
    : QGraphicsView(afscene, parent)
    , scene(afscene)
{
}
