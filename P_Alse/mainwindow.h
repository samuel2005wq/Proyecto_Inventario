#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "inventorymanager.h"

/**
 * @class MainWindow
 * @brief Ventana principal que contiene las pestañas del aplicativo.
 *
 * Esta clase representa la interfaz principal del programa. Contiene un QTabWidget
 * que permite al usuario navegar entre las distintas funcionalidades como
 * Inventario, Buscar, Alertas y Reportes. También administra el objeto InventoryManager
 * compartido entre todas las pestañas.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor de MainWindow.
     * @param parent Widget padre (por defecto nullptr).
     */
    MainWindow(QWidget* parent = nullptr);

    /**
     * @brief Destructor de MainWindow.
     */
    ~MainWindow();

private:
    InventoryManager* m_inventoryManager; /**< Lógica central del inventario, compartida por todas las pestañas. */
    QTabWidget* m_tabWidget;              /**< Widget de pestañas para navegación entre módulos. */
};

#endif // MAINWINDOW_H

