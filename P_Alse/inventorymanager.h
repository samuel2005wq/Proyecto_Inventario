#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QList>
#include <QString>
#include "component.h"
#include "databasemanager.h"

/**
 * @class InventoryManager
 * @brief Clase que gestiona la lógica del inventario, interfaciando con DatabaseManager.
 *
 * Esta clase proporciona funciones para agregar, consultar, buscar, actualizar y eliminar
 * componentes en un inventario. Internamente utiliza una instancia de DatabaseManager para
 * manejar operaciones relacionadas con la base de datos.
 */
class InventoryManager
{
public:
    /**
     * @brief Constructor de InventoryManager.
     * Inicializa la base de datos y prepara el entorno para gestionar el inventario.
     */
    InventoryManager();

    /**
     * @brief Destructor de InventoryManager.
     * Cierra la base de datos y libera los recursos utilizados.
     */
    ~InventoryManager();

    /**
     * @brief Agrega un nuevo componente al inventario.
     * @param comp El componente a agregar.
     * @return true si se agrega correctamente, false si ocurre un error.
     */
    bool addComponent(const Component& comp);

    /**
     * @brief Recupera todos los componentes almacenados en el inventario.
     * @return Lista de todos los componentes.
     */
    QList<Component> getAllComponents();

    /**
     * @brief Busca componentes en el inventario según un criterio y palabra clave.
     * @param keyword Palabra clave a buscar.
     * @param criteria Criterio de búsqueda (Nombre, Tipo, Cantidad, Ubicación, Fecha).
     * @return Lista de componentes que coinciden con la búsqueda.
     */
    QList<Component> searchComponents(const QString& keyword, const QString& criteria);

    /**
     * @brief Actualiza un componente existente en el inventario.
     * @param id ID del componente a actualizar.
     * @param comp El componente actualizado.
     * @return true si la operación fue exitosa, false si falla.
     */
    bool updateComponent(int id, const Component& comp);

    /**
     * @brief Elimina un componente del inventario por su ID.
     * @param id ID del componente a eliminar.
     * @return true si se elimina correctamente, false en caso contrario.
     */
    bool deleteComponent(int id);

    /**
     * @brief Devuelve un puntero al administrador de base de datos.
     * @return Puntero a DatabaseManager, útil para otras clases como ReportGenerator.
     */
    DatabaseManager* getDatabaseManager() const;

private:
    DatabaseManager* m_dbManager; /**< Puntero a la instancia de DatabaseManager utilizada. */
};

#endif // INVENTORYMANAGER_H
