#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QObject>
#include <QString>

class DatabaseManager;

/**
 * @brief Clase encargada de generar reportes en formato PDF y CSV
 *        a partir de los datos de inventario almacenados en la base de datos.
 */
class ReportGenerator : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de ReportGenerator.
     *
     * @param dbManager Puntero a una instancia de DatabaseManager para acceder a los datos.
     * @param parent Objeto padre (opcional).
     */
    explicit ReportGenerator(DatabaseManager* dbManager, QObject* parent = nullptr);

    /**
     * @brief Genera un archivo PDF con todos los componentes del inventario.
     *
     * El archivo contiene una tabla HTML con la información estructurada.
     *
     * @param fileName Ruta completa del archivo PDF a generar.
     */
    void generatePDF(const QString& fileName);

    /**
     * @brief Genera un archivo CSV con todos los componentes del inventario.
     *
     * El archivo contiene los datos en formato separado por comas.
     *
     * @param fileName Ruta completa del archivo CSV a generar.
     */
    void generateCSV(const QString& fileName);

private:
    DatabaseManager* m_dbManager; ///< Referencia al administrador de base de datos.
};

#endif // REPORTGENERATOR_H
