#include <QGridLayout>
#include <QLabel>
#include <QSlider>

#include "zoombar.hpp"

ZoomBar::ZoomBar(QWidget* parent)
    : QWidget(parent)
{
    m_slider = new QSlider;
    m_slow = new QLabel("Slow");
    m_fast = new QLabel("Fast");
    m_layout = new QGridLayout(this);

    setOrientation(Qt::Horizontal);
}

void ZoomBar::setOrientation(Qt::Orientation orientation)
{
    m_slider->setOrientation(orientation);

    m_layout->removeWidget(m_slider);
    m_layout->removeWidget(m_slow);
    m_layout->removeWidget(m_fast);

    switch (orientation) {
    case Qt::Horizontal:
        m_slow->setAlignment(Qt::AlignLeft);
        m_layout->addWidget(m_slow, 0, 0);

        m_fast->setAlignment(Qt::AlignRight);
        m_layout->addWidget(m_fast, 0, 1);

        m_layout->addWidget(m_slider, 1, 0, 1, 2);

        m_layout->setRowStretch(1, 0);
        m_layout->setColumnStretch(0, 1);
        m_layout->setColumnStretch(1, 1);
        break;
    case Qt::Vertical:
        m_slow->setAlignment(Qt::AlignBottom);
        m_layout->addWidget(m_slow, 2, 0);

        m_fast->setAlignment(Qt::AlignTop);
        m_layout->addWidget(m_fast, 0, 0);

        m_layout->addWidget(m_slider, 1, 0);

        m_layout->setRowStretch(1, 1);
        m_layout->setColumnStretch(0, 0);
        m_layout->setColumnStretch(1, 0);
        break;
    }
    m_layout->update();
}
