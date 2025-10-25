#pragma once

#include <QGraphicsView>

class Scene;

class View : public QGraphicsView {
public:
    View(Scene* = nullptr, QWidget* = nullptr);

private:
    Scene* m_scene;
};
