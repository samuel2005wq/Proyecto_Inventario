#include "reportgenerator.h"
#include "databasemanager.h"
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPageSize>

/**
 * @brief Constructor de ReportGenerator.
 *
 * @param dbManager Puntero a la instancia de DatabaseManager usada para consultar datos.
 * @param parent Objeto padre (por defecto nullptr).
 */
ReportGenerator::ReportGenerator(DatabaseManager* dbManager, QObject* parent)
    : QObject(parent), m_dbManager(dbManager)
{
}

/**
 * @brief Genera un reporte PDF de todos los componentes del inventario.
 *
 * Consulta la base de datos y construye una tabla HTML con todos los datos,
 * que luego se imprime como archivo PDF.
 *
 * @param fileName Ruta del archivo PDF de salida.
 */
void ReportGenerator::generatePDF(const QString& fileName)
{
    if (!m_dbManager) {
        qWarning() << "DatabaseManager no está inicializado.";
        return;
    }

    QSqlQuery query = m_dbManager->getAllComponentQuery();
    if (!query.isActive()) {
        qWarning() << "No se pudo obtener los componentes desde la base de datos.";
        return;
    }

    int total = 0;
    QString tableRows;

    if (query.next()) {
        QSqlRecord rec = query.record();
        int idxNombre     = rec.indexOf("nombre");
        int idxTipo       = rec.indexOf("tipo");
        int idxCantidad   = rec.indexOf("cantidad");
        int idxUbicacion  = rec.indexOf("ubicacion");
        int idxFecha      = rec.indexOf("fechaAdquisicion");

        do {
            tableRows += "<tr>";
            tableRows += "<td>" + query.value(idxNombre).toString() + "</td>";
            tableRows += "<td>" + query.value(idxTipo).toString() + "</td>";
            tableRows += "<td>" + query.value(idxCantidad).toString() + "</td>";
            tableRows += "<td>" + query.value(idxUbicacion).toString() + "</td>";
            tableRows += "<td>" + query.value(idxFecha).toString() + "</td>";
            tableRows += "</tr>";
            total++;
        } while (query.next());
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);

    QString html;
    html += "<html><head><meta charset=\"UTF-8\"></head><body>";
    html += "<h1>Reporte de Inventario</h1>";
    html += "<p>Total de componentes: " + QString::number(total) + "</p>";
    html += "<table border=\"1\" cellspacing=\"0\" cellpadding=\"4\">";
    html += "<tr><th>Nombre</th><th>Tipo</th><th>Cantidad</th><th>Ubicación</th><th>Fecha</th></tr>";
    html += tableRows;
    html += "</table></body></html>";

    QTextDocument document;
    document.setHtml(html);
    document.setPageSize(printer.pageRect(QPrinter::Point).size());
    document.print(&printer);
}

/**
 * @brief Genera un archivo CSV con todos los componentes del inventario.
 *
 * Exporta los datos obtenidos de la base de datos a un archivo de texto
 * con formato CSV.
 *
 * @param fileName Ruta del archivo CSV de salida.
 */
void ReportGenerator::generateCSV(const QString& fileName)
{
    if (!m_dbManager) {
        qWarning() << "DatabaseManager no está inicializado.";
        return;
    }

    QSqlQuery query = m_dbManager->getAllComponentQuery();
    if (!query.isActive()) {
        qWarning() << "No se pudo obtener los componentes desde la base de datos.";
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "No se pudo abrir el archivo para escritura: " << fileName;
        return;
    }

    QTextStream out(&file);
    out << "Nombre,Tipo,Cantidad,Ubicación,Fecha\n";

    while (query.next()) {
        out << query.value("nombre").toString() << ","
            << query.value("tipo").toString() << ","
            << query.value("cantidad").toString() << ","
            << query.value("ubicacion").toString() << ","
            << query.value("fechaAdquisicion").toString() << "\n";
    }

    file.close();
}
