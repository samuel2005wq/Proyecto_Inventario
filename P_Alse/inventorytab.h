#ifndef INVENTORYTAB_H
#define INVENTORYTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QMap>
#include "inventorymanager.h"

/**
 * @class InventoryTab
 * @brief Representa la pestaña de interfaz gráfica para la gestión de inventario.
 *
 * Permite al usuario visualizar, agregar, modificar y eliminar componentes del inventario
 * mediante una tabla y un formulario. Se conecta a la lógica de inventario a través de
 * InventoryManager.
 */
class InventoryTab : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor de InventoryTab.
     * @param manager Puntero al InventoryManager que se utiliza para operaciones con los datos.
     * @param parent Widget padre (por defecto nullptr).
     */
    InventoryTab(InventoryManager* manager, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Refresca el contenido de la tabla con los datos actuales del inventario.
     */
    void refreshTable();

    /**
     * @brief Agrega un nuevo componente o actualiza uno existente basado en el estado de edición.
     */
    void addOrUpdateComponent();

    /**
     * @brief Activa la edición de un componente cuando se hace doble clic en una celda.
     * @param row Fila seleccionada.
     * @param column Columna seleccionada.
     */
    void handleCellDoubleClicked(int row, int column);

    /**
     * @brief Elimina el componente seleccionado actualmente en la tabla.
     */
    void deleteSelectedComponent();

private:
    InventoryManager* m_manager; /**< Puntero al administrador del inventario. */

    QTableWidget* table;         /**< Tabla que muestra los componentes del inventario. */
    QLineEdit* nameEdit;         /**< Campo de entrada para el nombre del componente. */
    QLineEdit* typeEdit;         /**< Campo de entrada para el tipo del componente. */
    QSpinBox* quantitySpin;      /**< Campo de entrada para la cantidad del componente. */
    QLineEdit* locationEdit;     /**< Campo de entrada para la ubicación del componente. */
    QDateEdit* dateEdit;         /**< Campo de entrada para la fecha de adquisición. */
    QPushButton* addButton;      /**< Botón para agregar o actualizar un componente. */
    QPushButton* deleteButton;   /**< Botón para eliminar el componente seleccionado. */

    QMap<int, int> rowToIdMap;   /**< Mapa de fila a ID de componente para referencias rápidas. */
    int editingId = -1;          /**< ID del componente que se está editando, -1 si se está agregando uno nuevo. */
};

#endif // INVENTORYTAB_H
