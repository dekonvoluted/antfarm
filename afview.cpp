#include "afview.h"
#include "afscene.h"

AntFarmView::AntFarmView( AntFarmScene* afscene, QWidget* parent ) : QGraphicsView( afscene, parent ), scene( afscene )
{}

