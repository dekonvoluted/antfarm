#pragma once

#include <QMainWindow>

class QTimer;
class QToolBar;

class Scene;
class View;

class Window : public QMainWindow {
    Q_OBJECT

public:
    Window(QWidget* = nullptr);

public slots:
    void update();

private:
    QToolBar* m_toolbar;

    Scene* m_scene;
    View* m_view;
};
