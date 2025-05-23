#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QDate>

/// @file component.h
/// @brief Declaración de la clase Component que representa un ítem del inventario.

/**
 * @class Component
 * @brief Representa un componente individual dentro del inventario, con atributos como nombre, tipo, cantidad, ubicación y fecha de adquisición.
 */
class Component {
public:
    /**
     * @brief Constructor con ID (usado para componentes ya almacenados en la base de datos).
     * @param id Identificador único del componente.
     * @param nombre Nombre del componente.
     * @param tipo Tipo o categoría del componente.
     * @param cantidad Cantidad disponible.
     * @param ubicacion Ubicación física en el inventario.
     * @param fechaAdquisicion Fecha de adquisición del componente.
     */
    Component(int id,
              const QString& nombre,
              const QString& tipo,
              int cantidad,
              const QString& ubicacion,
              const QDate& fechaAdquisicion);

    /**
     * @brief Constructor sin ID (usado para componentes nuevos que aún no han sido insertados en la base de datos).
     * @param nombre Nombre del componente.
     * @param tipo Tipo o categoría del componente.
     * @param cantidad Cantidad disponible.
     * @param ubicacion Ubicación física en el inventario.
     * @param fechaAdquisicion Fecha de adquisición del componente.
     */
    Component(const QString& nombre = "",
              const QString& tipo = "",
              int cantidad = 0,
              const QString& ubicacion = "",
              const QDate& fechaAdquisicion = QDate());

    // =======================
    // Métodos Getters
    // =======================

    /**
     * @brief Obtiene el ID del componente.
     * @return ID entero.
     */
    int getId() const;

    /**
     * @brief Obtiene el nombre del componente.
     * @return Nombre como QString.
     */
    QString getNombre() const;

    /**
     * @brief Obtiene el tipo del componente.
     * @return Tipo como QString.
     */
    QString getTipo() const;

    /**
     * @brief Obtiene la cantidad disponible.
     * @return Cantidad como entero.
     */
    int getCantidad() const;

    /**
     * @brief Obtiene la ubicación física del componente.
     * @return Ubicación como QString.
     */
    QString getUbicacion() const;

    /**
     * @brief Obtiene la fecha de adquisición.
     * @return Fecha como QDate.
     */
    QDate getFechaAdquisicion() const;

    // =======================
    // Métodos Setters
    // =======================

    /**
     * @brief Establece el ID del componente.
     * @param id Nuevo ID.
     */
    void setId(int id);

    /**
     * @brief Establece el nombre del componente.
     * @param nombre Nuevo nombre.
     */
    void setNombre(const QString& nombre);

    /**
     * @brief Establece el tipo del componente.
     * @param tipo Nuevo tipo.
     */
    void setTipo(const QString& tipo);

    /**
     * @brief Establece la cantidad disponible.
     * @param cantidad Nueva cantidad.
     */
    void setCantidad(int cantidad);

    /**
     * @brief Establece la ubicación física.
     * @param ubicacion Nueva ubicación.
     */
    void setUbicacion(const QString& ubicacion);

    /**
     * @brief Establece la fecha de adquisición.
     * @param fechaAdquisicion Nueva fecha.
     */
    void setFechaAdquisicion(const QDate& fechaAdquisicion);

private:
    int id;                  ///< Identificador único en la base de datos
    QString nombre;          ///< Nombre del componente
    QString tipo;            ///< Tipo o categoría del componente
    int cantidad;            ///< Cantidad disponible
    QString ubicacion;       ///< Ubicación en el inventario
    QDate fechaAdquisicion;  ///< Fecha de adquisición del componente
};

#endif // COMPONENT_H
