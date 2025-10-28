#pragma once

#include <map>

#include <QGraphicsScene>
#include <QPixmap>

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
    std::map<int, QPixmap> m_tiles;
    QPixmap m_ant;

    Grid m_grid;
};
