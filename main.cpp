#include <QApplication>
#include "src/UI/SimulatorUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimulatorUI window;
    window.resize(800, 400);
    window.show();
    return app.exec();
}
