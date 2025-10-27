#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>

#include "scene.hpp"
#include "view.hpp"
#include "window.hpp"
#include "zoombar.hpp"

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    this->resize(800, 600);

    m_scene = new Scene();
    m_view = new View(m_scene);
    this->setCentralWidget(m_view);

    auto* timer = new QTimer(this);
    timer->setInterval(100);

    m_toolbar = new QToolBar("Main");

    auto* resetButton = new QToolButton(this);
    resetButton->setText("Reset");
    connect(resetButton, &QToolButton::clicked, [this]() { m_view->resetTransform(); });

    auto* resetMenu = new QMenu(this);
    auto* squareAction = new QAction("Square", this);
    // connect(squareAction, &QAction::triggered, this, &Window::...);
    resetMenu->addAction(squareAction);

    auto* hexagonAction = new QAction("Hexagon", this);
    resetMenu->addAction(hexagonAction);

    auto* triangleAction = new QAction("Triangle", this);
    resetMenu->addAction(triangleAction);

    resetButton->setMenu(resetMenu);
    resetButton->setPopupMode(QToolButton::MenuButtonPopup);

    m_toolbar->addWidget(resetButton);

    auto* antButton = new QPushButton("Add Ant");
    // connect(antButton, &QPushButton::clicked, [this](){m_scene->grid().add ant();});
    m_toolbar->addWidget(antButton);

    auto* playButton = new QPushButton("Start/Pause");
    playButton->setCheckable(true);
    connect(playButton, &QPushButton::toggled, [playButton](bool toggled) {
        if (toggled) {
            playButton->setText("Pause");
        } else {
            playButton->setText("Start");
        };
    });
    connect(playButton, &QPushButton::toggled, [timer](bool toggled) {
        if (toggled) {
            timer->start();
        } else {
            timer->stop();
        }
    });
    m_toolbar->addWidget(playButton);

    auto* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolbar->addWidget(spacer);

    auto* fpsLabel = new QLabel("fps:");
    m_toolbar->addWidget(fpsLabel);

    auto* fpsWidget = new QSpinBox;
    fpsWidget->setRange(5, 100);
    fpsWidget->setSingleStep(5);
    fpsWidget->setValue(10);
    connect(fpsWidget, &QSpinBox::valueChanged, [timer](int value) {
        const auto interval = (1000.0 / value);
        timer->setInterval(static_cast<int>(interval));
    });
    m_toolbar->addWidget(fpsWidget);

    this->addToolBar(m_toolbar);

    auto* statusbar = this->statusBar();
    auto* counter = new QLabel("Generations: 0");
    connect(timer, &QTimer::timeout, [this, counter]() {
        const auto generations = QString("Generations: %1").arg(++m_generations);
        counter->setText(generations);
    });
    statusbar->addPermanentWidget(counter);
    statusbar->showMessage("Ready");
}

#include "moc_window.cpp"
