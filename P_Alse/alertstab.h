#ifndef ALERTSTAB_H
#define ALERTSTAB_H

#include <QWidget>
#include <QTableWidget>
#include "inventorymanager.h"

/// @file alertstab.h
/// @brief Declaración de la clase AlertsTab que representa la pestaña de alertas de bajo stock.

/**
 * @class AlertsTab
 * @brief Widget que muestra una tabla con los componentes cuyo stock está por debajo de un umbral predefinido.
 *
 * Esta clase se encarga de visualizar alertas de inventario basadas en la cantidad mínima establecida
 * (por defecto 5 unidades). Muestra nombre, tipo, cantidad, ubicación y fecha de adquisición.
 */
class AlertsTab : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor de la pestaña de alertas.
     * @param manager Puntero al InventoryManager para obtener los datos del inventario.
     * @param parent Widget padre (por defecto nullptr).
     */
    AlertsTab(InventoryManager* manager, QWidget* parent = nullptr);

    /**
     * @brief Refresca la tabla de alertas mostrando únicamente los componentes con cantidad baja.
     */
    void refreshAlerts();

private:
    InventoryManager* m_manager; ///< Puntero al administrador de inventario.
    QTableWidget* alertTable;    ///< Tabla donde se muestran los componentes en alerta.
    const int threshold = 5;     ///< Umbral de alerta (cantidad mínima para mostrar advertencia).
};

#endif // ALERTSTAB_H
