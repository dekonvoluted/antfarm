#include <QToolBar>

#include "scene.hpp"
#include "view.hpp"
#include "window.hpp"
#include "zoombar.hpp"

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{

    auto* toolbar = new QToolBar("Zoom");
    auto* zoombar = new ZoomBar;
    toolbar->addWidget(zoombar);
    connect(toolbar, SIGNAL(orientationChanged(Qt::Orientation)), zoombar, SLOT(setOrientation(Qt::Orientation)));
    this->addToolBar(Qt::BottomToolBarArea, toolbar);

    m_scene = new Scene();
    m_view = new View(m_scene);
    connect(m_view, SIGNAL(zoomChanged(int)), zoombar, SLOT(setValue(int)));
    connect(zoombar, SIGNAL(valueChanged(int)), m_view, SLOT(setZoom(int)));

    this->setCentralWidget(m_view);

    this->resize(800, 600);
}
