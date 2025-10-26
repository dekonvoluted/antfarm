#include <QWheelEvent>

#include "scene.hpp"
#include "view.hpp"

View::View(Scene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , m_scene(scene)
{
    this->setRenderHints(QPainter::Antialiasing);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::setZoom(int stepping)
{
    const auto maximum_zoom = 25;
    if (stepping < -maximum_zoom) {
        stepping = -maximum_zoom;
        return;
    }

    if (stepping > maximum_zoom) {
        stepping = maximum_zoom;
        return;
    }

    m_zoom = stepping;
    const auto factor = qPow(1.1, m_zoom);
    this->resetTransform();
    this->scale(factor, factor);
}

void View::wheelEvent(QWheelEvent* event)
{
    const auto degrees = event->angleDelta();

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    if (degrees.y() > 0) {
        setZoom(++m_zoom);
    } else {
        setZoom(--m_zoom);
    }
    emit zoomChanged(m_zoom);

    QGraphicsView::wheelEvent(event);
}

#include "moc_view.cpp"
