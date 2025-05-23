#include "component.h"

/// @file component.cpp
/// @brief Implementación de la clase Component que representa un componente del inventario.


//=======================================================================
// Constructores
//=======================================================================

/**
 * @brief Constructor de la clase Component con ID explícito.
 * @param id Identificador único del componente.
 * @param nombre Nombre del componente.
 * @param tipo Tipo o categoría del componente.
 * @param cantidad Cantidad disponible del componente.
 * @param ubicacion Ubicación física del componente.
 * @param fechaAdquisicion Fecha en que el componente fue adquirido.
 */
Component::Component(int id,
                     const QString& nombre,
                     const QString& tipo,
                     int cantidad,
                     const QString& ubicacion,
                     const QDate& fechaAdquisicion)
    : id(id),
    nombre(nombre),
    tipo(tipo),
    cantidad(cantidad),
    ubicacion(ubicacion),
    fechaAdquisicion(fechaAdquisicion)
{}

/**
 * @brief Constructor de la clase Component sin ID (usado para inserciones nuevas).
 * @param nombre Nombre del componente.
 * @param tipo Tipo o categoría del componente.
 * @param cantidad Cantidad disponible del componente.
 * @param ubicacion Ubicación física del componente.
 * @param fechaAdquisicion Fecha en que el componente fue adquirido.
 */
Component::Component(const QString& nombre,
                     const QString& tipo,
                     int cantidad,
                     const QString& ubicacion,
                     const QDate& fechaAdquisicion)
    : id(-1),  // id aún no asignado
    nombre(nombre),
    tipo(tipo),
    cantidad(cantidad),
    ubicacion(ubicacion),
    fechaAdquisicion(fechaAdquisicion)
{}

//=======================================================================
// Métodos getter
//=======================================================================

/**
 * @brief Obtiene el ID del componente.
 * @return ID numérico.
 */
int Component::getId() const {
    return id;
}

/**
 * @brief Obtiene el nombre del componente.
 * @return Nombre como QString.
 */
QString Component::getNombre() const {
    return nombre;
}

/**
 * @brief Obtiene el tipo del componente.
 * @return Tipo como QString.
 */
QString Component::getTipo() const {
    return tipo;
}

/**
 * @brief Obtiene la cantidad disponible del componente.
 * @return Cantidad como entero.
 */
int Component::getCantidad() const {
    return cantidad;
}

/**
 * @brief Obtiene la ubicación del componente.
 * @return Ubicación como QString.
 */
QString Component::getUbicacion() const {
    return ubicacion;
}

/**
 * @brief Obtiene la fecha de adquisición del componente.
 * @return Fecha como QDate.
 */
QDate Component::getFechaAdquisicion() const {
    return fechaAdquisicion;
}

//=======================================================================
// Métodos setter
//=======================================================================

/**
 * @brief Establece el ID del componente.
 * @param id Nuevo ID.
 */
void Component::setId(int id) {
    this->id = id;
}

/**
 * @brief Establece el nombre del componente.
 * @param nombre Nuevo nombre.
 */
void Component::setNombre(const QString& nombre) {
    this->nombre = nombre;
}

/**
 * @brief Establece el tipo del componente.
 * @param tipo Nuevo tipo.
 */
void Component::setTipo(const QString& tipo) {
    this->tipo = tipo;
}

/**
 * @brief Establece la cantidad disponible del componente.
 * @param cantidad Nueva cantidad.
 */
void Component::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

/**
 * @brief Establece la ubicación del componente.
 * @param ubicacion Nueva ubicación.
 */
void Component::setUbicacion(const QString& ubicacion) {
    this->ubicacion = ubicacion;
}

/**
 * @brief Establece la fecha de adquisición del componente.
 * @param fechaAdquisicion Nueva fecha.
 */
void Component::setFechaAdquisicion(const QDate& fechaAdquisicion) {
    this->fechaAdquisicion = fechaAdquisicion;
}
