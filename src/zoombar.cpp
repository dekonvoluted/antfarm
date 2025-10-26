#include <QBoxLayout>
#include <QLabel>
#include <QSlider>

#include "zoombar.hpp"

ZoomBar::ZoomBar(QWidget* parent)
    : QWidget(parent)
{
    m_label = new QLabel("Zoom");
    m_slider = new QSlider;
    m_layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    m_layout->addWidget(m_label);
    m_layout->addWidget(m_slider);

    setOrientation(Qt::Horizontal);
}

void ZoomBar::setOrientation(Qt::Orientation orientation)
{
    m_slider->setOrientation(orientation);
    switch (orientation) {
    case Qt::Horizontal:
        m_layout->setDirection(QBoxLayout::LeftToRight);
        break;
    case Qt::Vertical:
        m_layout->setDirection(QBoxLayout::TopToBottom);
        break;
    }
    m_layout->update();
}

#include "moc_zoombar.cpp"
