#include <QApplication>

#include "grid.hpp"
#include "tiling.hpp"
#include "window.hpp"

int main(int argc, char** argv)
{
    auto grid = Grid(Tiling::SQUARE, 2);
    grid.ant();
    for (auto count = 0; count < 100; ++count) {
        grid.update();
    }

    QApplication app(argc, argv);

    Window* window = new Window();
    window->show();

    return app.exec();
}
