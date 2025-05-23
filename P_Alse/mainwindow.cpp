#include "mainwindow.h"
#include "inventorytab.h"
#include "searchtab.h"
#include "alertstab.h"
#include "reportstab.h"

/**
 * @brief Constructor de MainWindow.
 *
 * Inicializa la ventana principal, crea las pestañas (Inventario, Buscar, Alertas, Reportes)
 * y las agrega al QTabWidget central. También inicializa el InventoryManager que se
 * comparte entre las pestañas.
 *
 * @param parent Widget padre (por defecto nullptr).
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_inventoryManager = new InventoryManager();

    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    InventoryTab* inventoryTab = new InventoryTab(m_inventoryManager, this);
    SearchTab* searchTab = new SearchTab(m_inventoryManager, this);
    AlertsTab* alertsTab = new AlertsTab(m_inventoryManager, this);
    ReportTab* reportsTab = new ReportTab(m_inventoryManager, this);

    m_tabWidget->addTab(inventoryTab, "Inventario");
    m_tabWidget->addTab(searchTab, "Buscar");
    m_tabWidget->addTab(alertsTab, "Alertas");
    m_tabWidget->addTab(reportsTab, "Reportes");
}

/**
 * @brief Destructor de MainWindow.
 *
 * Libera la memoria del InventoryManager.
 */
MainWindow::~MainWindow()
{
    delete m_inventoryManager;
}
