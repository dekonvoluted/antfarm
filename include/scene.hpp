#pragma once

#include <QGraphicsScene>

#include "tiling.hpp"

class QPainter;
class QPixmap;

class Scene : public QGraphicsScene {
public:
    Scene(QObject* = nullptr);

protected:
    void drawBackground(QPainter*, const QRectF&);
    void drawForeground(QPainter*, const QRectF&);

private:
    std::map<int, int> m_colors;
    QPixmap m_default_tile;
    QPixmap m_current_tile;
    QPixmap m_toggled_tile;
};
