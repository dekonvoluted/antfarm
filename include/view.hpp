#pragma once

#include <QGraphicsView>

class Scene;

class View : public QGraphicsView {
    Q_OBJECT

public:
    View(Scene* = nullptr, QWidget* = nullptr);

signals:
    void zoomChanged(int);

public slots:
    void setZoom(int);

protected:
    void wheelEvent(QWheelEvent*);

private:
    Scene* m_scene;
    int m_zoom { 0 };
};
