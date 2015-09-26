#include <QGridLayout>
#include <QLabel>
#include <QSlider>

#include "fpswidget.h"

FPSWidget::FPSWidget( QWidget* parent ) : QWidget( parent )
{
    // Set up the slider
    slider = new QSlider;

    slowerLabel = new QLabel( "Slower" );
    fasterLabel = new QLabel( "Faster" );

    layout = new QGridLayout( this );

    // Initially set orientation to horizontal
    setOrientation( Qt::Horizontal );
}

void FPSWidget::setOrientation( Qt::Orientation orientation )
{
    slider->setOrientation( orientation );

    layout->removeWidget( slider );
    layout->removeWidget( slowerLabel );
    layout->removeWidget( fasterLabel );

    switch ( orientation ) {
        case Qt::Horizontal:
            slowerLabel->setAlignment( Qt::AlignLeft );
            layout->addWidget( slowerLabel, 0, 0 );

            fasterLabel->setAlignment( Qt::AlignRight );
            layout->addWidget( fasterLabel, 0, 1 );

            layout->addWidget( slider, 1, 0, 1, 2 );

            layout->setRowStretch( 1, 0 );
            layout->setColumnStretch( 0, 1 );
            layout->setColumnStretch( 1, 1 );
            break;
        case Qt::Vertical:
            fasterLabel->setAlignment( Qt::AlignTop );
            layout->addWidget( fasterLabel, 0, 0 );

            layout->addWidget( slider, 1, 0 );

            slowerLabel->setAlignment( Qt::AlignBottom );
            layout->addWidget( slowerLabel, 2, 0 );

            layout->setRowStretch( 1, 1 );
            layout->setColumnStretch( 0, 0 );
            layout->setColumnStretch( 1, 0 );
            break;
    }
    layout->update();
}

