#include <QWheelEvent>

#include "scene.hpp"
#include "view.hpp"

View::View(Scene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , m_scene(scene)
{
    setRenderHints(QPainter::Antialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::wheelEvent(QWheelEvent* event)
{
    const auto degrees = event->angleDelta();
    const auto factor = (degrees.y() > 0) ? 1.1 : (1.0 / 1.1);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    scale(factor, factor);
}

#include "moc_view.cpp"
