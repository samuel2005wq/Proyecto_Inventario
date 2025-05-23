/// @file databasemanager.cpp
/// @brief Implementación de la clase DatabaseManager encargada de la gestión de base de datos SQLite.

#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Constructor que inicializa la conexión con la base de datos SQLite.
 * @param path Ruta del archivo de base de datos.
 */
DatabaseManager::DatabaseManager(const QString& path)
    : m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_db.setDatabaseName(path);
}

/**
 * @brief Destructor. Cierra la base de datos al destruir el objeto.
 */
DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

/**
 * @brief Abre la base de datos y crea la tabla si no existe.
 * @return true si la operación fue exitosa, false en caso contrario.
 */
bool DatabaseManager::openDatabase() {
    if (!m_db.open()) {
        qWarning() << "Error al abrir la base de datos:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS components ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nombre TEXT, "
        "tipo TEXT, "
        "cantidad INTEGER, "
        "ubicacion TEXT, "
        "fechaAdquisicion TEXT)"
        );

    if (!ok)
        qWarning() << "Error al crear tabla:" << query.lastError().text();

    return ok;
}

/**
 * @brief Cierra la base de datos si está abierta.
 */
void DatabaseManager::closeDatabase() {
    if (m_db.isOpen())
        m_db.close();
}

/**
 * @brief Inserta un nuevo componente en la tabla de base de datos.
 * @param comp Objeto Component con los datos a insertar.
 * @return true si el insert fue exitoso, false en caso contrario.
 */
bool DatabaseManager::addComponent(const Component& comp) {
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO components (nombre, tipo, cantidad, ubicacion, fechaAdquisicion) "
        "VALUES (:nombre, :tipo, :cantidad, :ubicacion, :fecha)"
        );

    query.bindValue(":nombre", comp.getNombre());
    query.bindValue(":tipo", comp.getTipo());
    query.bindValue(":cantidad", comp.getCantidad());
    query.bindValue(":ubicacion", comp.getUbicacion());
    query.bindValue(":fecha", comp.getFechaAdquisicion().toString("yyyy-MM-dd"));

    bool success = query.exec();
    if (!success)
        qWarning() << "Error al agregar componente:" << query.lastError().text();
    return success;
}

/**
 * @brief Recupera todos los componentes de la base de datos como lista.
 * @return QList<Component> con todos los registros existentes.
 */
QList<Component> DatabaseManager::getAllComponents() {
    QList<Component> list;
    QSqlQuery query(m_db);
    query.exec("SELECT id, nombre, tipo, cantidad, ubicacion, fechaAdquisicion FROM components");

    while (query.next()) {
        Component c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt(),
            query.value(4).toString(),
            QDate::fromString(query.value(5).toString(), "yyyy-MM-dd")
            );
        list.append(c);
    }

    return list;
}

/**
 * @brief Busca componentes cuyo nombre, tipo o ubicación coincidan con una palabra clave.
 * @param keyword Palabra clave para buscar.
 * @return Lista de componentes coincidentes.
 */
QList<Component> DatabaseManager::searchComponents(const QString& keyword) {
    QList<Component> list;
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT id, nombre, tipo, cantidad, ubicacion, fechaAdquisicion FROM components "
        "WHERE nombre LIKE :kw OR tipo LIKE :kw OR ubicacion LIKE :kw"
        );

    QString pat = "%" + keyword + "%";
    query.bindValue(":kw", pat);

    if (!query.exec()) {
        qWarning() << "Error en búsqueda:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        Component c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt(),
            query.value(4).toString(),
            QDate::fromString(query.value(5).toString(), "yyyy-MM-dd")
            );
        list.append(c);
    }

    return list;
}

/**
 * @brief Actualiza un componente existente en la base de datos según su ID.
 * @param id Identificador del componente a actualizar.
 * @param comp Datos nuevos del componente.
 * @return true si la actualización fue exitosa.
 */
bool DatabaseManager::updateComponent(int id, const Component& comp) {
    QSqlQuery query(m_db);
    query.prepare(
        "UPDATE components SET nombre=:nombre, tipo=:tipo, cantidad=:cantidad, "
        "ubicacion=:ubicacion, fechaAdquisicion=:fecha WHERE id=:id"
        );

    query.bindValue(":nombre", comp.getNombre());
    query.bindValue(":tipo", comp.getTipo());
    query.bindValue(":cantidad", comp.getCantidad());
    query.bindValue(":ubicacion", comp.getUbicacion());
    query.bindValue(":fecha", comp.getFechaAdquisicion().toString("yyyy-MM-dd"));
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success)
        qWarning() << "Error al actualizar componente:" << query.lastError().text();
    return success;
}

/**
 * @brief Elimina un componente de la base de datos por su ID.
 * @param id ID del componente a eliminar.
 * @return true si se eliminó correctamente.
 */
bool DatabaseManager::deleteComponent(int id) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM components WHERE id=:id");
    query.bindValue(":id", id);

    bool success = query.exec();
    if (!success)
        qWarning() << "Error al eliminar componente:" << query.lastError().text();
    return success;
}

/**
 * @brief Devuelve una consulta SQL con todos los componentes (para reportes).
 * @return QSqlQuery listo para ser leído.
 */
QSqlQuery DatabaseManager::getAllComponentQuery()
{
    QSqlQuery query;
    query.exec("SELECT nombre, tipo, cantidad, ubicacion, fechaAdquisicion FROM components");
    return query;
}
