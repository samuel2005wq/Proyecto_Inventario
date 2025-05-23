#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QList>
#include <QDate>
#include <QSqlQuery>
#include "component.h"

/// @file databasemanager.h
/// @brief Declaración de la clase DatabaseManager para gestionar la base de datos del inventario.

/**
 * @class DatabaseManager
 * @brief Clase encargada de manejar la conexión con una base de datos SQLite
 * y realizar operaciones CRUD sobre objetos de tipo Component.
 */
class DatabaseManager {
public:
    /**
     * @brief Constructor de la clase.
     * @param path Ruta del archivo de base de datos SQLite.
     */
    explicit DatabaseManager(const QString& path);

    /**
     * @brief Destructor. Cierra la base de datos si está abierta.
     */
    ~DatabaseManager();

    /**
     * @brief Abre la base de datos y crea la tabla si no existe.
     * @return true si se abre correctamente, false si hay error.
     */
    bool openDatabase();

    /**
     * @brief Cierra la base de datos si está abierta.
     */
    void closeDatabase();

    /**
     * @brief Inserta un nuevo componente en la base de datos.
     * @param comp Componente a insertar.
     * @return true si la operación fue exitosa.
     */
    bool addComponent(const Component& comp);

    /**
     * @brief Recupera todos los componentes almacenados.
     * @return Lista de Component.
     */
    QList<Component> getAllComponents();

    /**
     * @brief Busca componentes según palabra clave (en nombre, tipo o ubicación).
     * @param keyword Palabra clave a buscar.
     * @return Lista de coincidencias.
     */
    QList<Component> searchComponents(const QString& keyword);

    /**
     * @brief Proporciona una consulta SQL lista para exportar componentes (por ejemplo, en reportes).
     * @return QSqlQuery con los resultados.
     */
    QSqlQuery getAllComponentQuery();

    /**
     * @brief Actualiza un componente existente.
     * @param id ID del componente a actualizar.
     * @param comp Datos actualizados.
     * @return true si la operación fue exitosa.
     */
    bool updateComponent(int id, const Component& comp);

    /**
     * @brief Elimina un componente por su ID.
     * @param id ID del componente a eliminar.
     * @return true si la operación fue exitosa.
     */
    bool deleteComponent(int id);

private:
    QSqlDatabase m_db; ///< Instancia de la base de datos SQLite.
};

#endif // DATABASEMANAGER_H
