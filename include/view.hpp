#pragma once

#include <QGraphicsView>

class Scene;

class View : public QGraphicsView {
    Q_OBJECT

public:
    View(Scene* = nullptr, QWidget* = nullptr);

protected:
    void wheelEvent(QWheelEvent*);

private:
    Scene* m_scene;
};
