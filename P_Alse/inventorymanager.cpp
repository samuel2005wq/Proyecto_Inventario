#include "inventorymanager.h"

/**
 * @class InventoryManager
 * @brief Clase que maneja la lógica de inventario utilizando una base de datos.
 */
InventoryManager::InventoryManager()
{
    m_dbManager = new DatabaseManager("inventory.db");
    m_dbManager->openDatabase();
}

/**
 * @brief Destructor de InventoryManager.
 * Cierra la base de datos y libera memoria.
 */
InventoryManager::~InventoryManager()
{
    m_dbManager->closeDatabase();
    delete m_dbManager;
}

/**
 * @brief Agrega un componente a la base de datos.
 * @param comp El componente a agregar.
 * @return true si se agregó correctamente, false en caso contrario.
 */
bool InventoryManager::addComponent(const Component& comp)
{
    return m_dbManager->addComponent(comp);
}

/**
 * @brief Recupera todos los componentes del inventario.
 * @return Una lista de todos los componentes.
 */
QList<Component> InventoryManager::getAllComponents()
{
    return m_dbManager->getAllComponents();
}

/**
 * @brief Busca componentes en base a una palabra clave y un criterio.
 * @param keyword La palabra clave para buscar.
 * @param criteria El criterio por el cual se va a buscar (Nombre, Tipo, Cantidad, Ubicación, Fecha).
 * @return Una lista de componentes que coinciden con la búsqueda.
 */
QList<Component> InventoryManager::searchComponents(const QString& keyword, const QString& criteria)
{
    QList<Component> results;
    QList<Component> allComponents = getAllComponents();

    for (const Component& comp : allComponents) {
        if (criteria == "Nombre" && comp.getNombre().contains(keyword, Qt::CaseInsensitive)) {
            results.append(comp);
        } else if (criteria == "Tipo" && comp.getTipo().contains(keyword, Qt::CaseInsensitive)) {
            results.append(comp);
        } else if (criteria == "Cantidad" && QString::number(comp.getCantidad()) == keyword) {
            results.append(comp);
        } else if (criteria == "Ubicación" && comp.getUbicacion().contains(keyword, Qt::CaseInsensitive)) {
            results.append(comp);
        } else if (criteria == "Fecha" && comp.getFechaAdquisicion().toString("yyyy-MM-dd") == keyword) {
            results.append(comp);
        }
    }

    return results;
}

/**
 * @brief Actualiza un componente existente en la base de datos.
 * @param id El ID del componente a actualizar.
 * @param comp El componente con los nuevos datos.
 * @return true si se actualizó correctamente, false en caso contrario.
 */
bool InventoryManager::updateComponent(int id, const Component& comp)
{
    return m_dbManager->updateComponent(id, comp);
}

/**
 * @brief Elimina un componente de la base de datos.
 * @param id El ID del componente a eliminar.
 * @return true si se eliminó correctamente, false en caso contrario.
 */
bool InventoryManager::deleteComponent(int id)
{
    return m_dbManager->deleteComponent(id);
}

/**
 * @brief Obtiene un puntero al administrador de base de datos.
 * @return Puntero a la instancia de DatabaseManager utilizada.
 */
DatabaseManager* InventoryManager::getDatabaseManager() const
{
    return m_dbManager;
}
