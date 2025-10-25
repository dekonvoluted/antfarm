#include "window.hpp"
#include "scene.hpp"
#include "view.hpp"

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    m_scene = new Scene();
    m_view = new View(m_scene);
    this->setCentralWidget(m_view);
}
