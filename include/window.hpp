#pragma once

#include <QMainWindow>

class View;
class Scene;

class Window : public QMainWindow {
public:
    Window(QWidget* = nullptr);

private:
    View* m_view;
    Scene* m_scene;
};
