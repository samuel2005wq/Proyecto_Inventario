/**
 * @file searchtab.h
 * @brief Declaración de la clase SearchTab que representa una pestaña de búsqueda de componentes en el inventario.
 */

#ifndef SEARCHTAB_H
#define SEARCHTAB_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include "inventorymanager.h"

/**
 * @class SearchTab
 * @brief Clase que proporciona una interfaz para buscar componentes dentro del inventario.
 *
 * Permite realizar búsquedas por diferentes criterios y muestra los resultados en una tabla.
 */
class SearchTab : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase SearchTab.
     *
     * Inicializa los elementos de la interfaz gráfica y conecta señales y slots.
     *
     * @param manager Puntero al InventoryManager para acceder a los componentes.
     * @param parent Widget padre (por defecto es nullptr).
     */
    SearchTab(InventoryManager* manager, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Realiza la búsqueda de componentes en el inventario según los criterios seleccionados.
     */
    void performSearch();

private:
    InventoryManager* m_manager;      /**< Puntero al gestor del inventario. */
    QLineEdit* searchEdit;            /**< Campo de texto para ingresar la palabra clave de búsqueda. */
    QPushButton* searchButton;        /**< Botón para iniciar la búsqueda. */
    QTableWidget* resultTable;        /**< Tabla para mostrar los resultados de la búsqueda. */
    QComboBox* searchCriteriaCombo;   /**< ComboBox para seleccionar el criterio de búsqueda. */
};

#endif // SEARCHTAB_H
