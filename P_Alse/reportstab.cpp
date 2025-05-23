#include "reportstab.h"
#include "inventorymanager.h"
#include "reportgenerator.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QPushButton>

/**
 * @brief Constructor de la pestaña de Reportes.
 *
 * Crea la interfaz de usuario y conecta los botones con sus funciones correspondientes.
 *
 * @param manager Puntero al InventoryManager para acceder a la base de datos.
 * @param parent Widget padre.
 */
ReportTab::ReportTab(InventoryManager* manager, QWidget *parent)
    : QWidget(parent)
    , m_manager(manager)
{
    // Creamos el ReportGenerator con el DatabaseManager interno de InventoryManager
    reportGenerator = new ReportGenerator(m_manager->getDatabaseManager(), this);

    // Botón para generar el reporte
    generateButton = new QPushButton("Generar reporte", this);

    // Layout vertical
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(generateButton);
    setLayout(layout);

    // Conexión de la señal clicked al slot
    connect(generateButton, &QPushButton::clicked,
            this, &ReportTab::onGenerateReport);
}

/**
 * @brief Slot que se ejecuta al presionar el botón "Generar reporte".
 *
 * Abre un diálogo para guardar un archivo y llama al generador correspondiente (CSV o PDF)
 * según el filtro seleccionado.
 */
void ReportTab::onGenerateReport()
{
    // Filtros de diálogo
    QString filter = "CSV (.csv);;PDF (.pdf)";
    QString selectedFilter;

    // Diálogo para elegir ruta y tipo
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Guardar reporte",
        QString(),
        filter,
        &selectedFilter
        );
    if (fileName.isEmpty())
        return;

    // Ajustar extensión y llamar al generador
    if (selectedFilter.startsWith("CSV")) {
        if (!fileName.endsWith(".csv", Qt::CaseInsensitive))
            fileName += ".csv";
        reportGenerator->generateCSV(fileName);
    }
    else {
        if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
            fileName += ".pdf";
        reportGenerator->generatePDF(fileName);
    }
}
