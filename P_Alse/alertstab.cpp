/// @file alertstab.cpp
/// @brief Implementación de la clase AlertsTab que muestra componentes con cantidades bajas.

#include "alertstab.h"
#include <QVBoxLayout>
#include <QTableWidgetItem>

/**
 * @brief Constructor de AlertsTab.
 *
 * Crea una tabla y la inicializa con los componentes cuya cantidad está por debajo del umbral.
 *
 * @param manager Puntero al InventoryManager que maneja los componentes.
 * @param parent Widget padre, por defecto nullptr.
 */
AlertsTab::AlertsTab(InventoryManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager)
{
    // Layout vertical principal
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Crear tabla de alertas
    alertTable = new QTableWidget(this);
    alertTable->setColumnCount(5);
    alertTable->setHorizontalHeaderLabels(QStringList()
                                          << "Nombre"
                                          << "Tipo"
                                          << "Cantidad"
                                          << "Ubicación"
                                          << "Fecha");

    mainLayout->addWidget(alertTable);

    // Mostrar componentes con cantidad baja
    refreshAlerts();
}

/**
 * @brief Actualiza la tabla con los componentes cuya cantidad es menor o igual al umbral.
 */
void AlertsTab::refreshAlerts()
{
    // Obtener todos los componentes desde el administrador
    QList<Component> all = m_manager->getAllComponents();
    QList<Component> alerts;

    // Filtrar por componentes con cantidad menor o igual al umbral
    for (const Component& c : all) {
        if (c.getCantidad() <= threshold) {
            alerts.append(c);
        }
    }

    // Configurar filas de la tabla según la cantidad de alertas
    alertTable->setRowCount(alerts.size());

    // Llenar tabla con los datos de componentes en alerta
    for (int i = 0; i < alerts.size(); ++i) {
        const Component& comp = alerts.at(i);
        alertTable->setItem(i, 0, new QTableWidgetItem(comp.getNombre()));
        alertTable->setItem(i, 1, new QTableWidgetItem(comp.getTipo()));
        alertTable->setItem(i, 2, new QTableWidgetItem(QString::number(comp.getCantidad())));
        alertTable->setItem(i, 3, new QTableWidgetItem(comp.getUbicacion()));
        alertTable->setItem(i, 4, new QTableWidgetItem(comp.getFechaAdquisicion().toString("yyyy-MM-dd")));
    }
}
