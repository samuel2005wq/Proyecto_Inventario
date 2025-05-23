#include <QApplication>
#include "mainwindow.h"

/**
 * @brief Función principal del programa.
 *
 * Crea una aplicación Qt, instancia la ventana principal y la muestra.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de argumentos de línea de comandos.
 * @return Código de salida de la aplicación.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}
