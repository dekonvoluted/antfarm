#include "view.hpp"
#include "scene.hpp"

View::View(Scene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , m_scene(scene)
{
}
