#pragma once

#include <QGraphicsScene>

#include "grid.hpp"
#include "tiling.hpp"

class QPainter;
class QPixmap;

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject* = nullptr);

signals:
    void stepped(int);

public slots:
    void ant();
    void step();

protected:
    void drawBackground(QPainter*, const QRectF&);
    void drawForeground(QPainter*, const QRectF&);

private:
    std::map<int, int> m_colors;
    QPixmap m_default_tile;
    QPixmap m_current_tile;
    QPixmap m_toggled_tile;

    Grid m_grid;
};
