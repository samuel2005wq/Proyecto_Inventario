#ifndef REPORTSTAB_H
#define REPORTSTAB_H

#include <QWidget>
#include <QPushButton>

class InventoryManager;
class ReportGenerator;

/**
 * @brief Pestaña de la interfaz de usuario encargada de generar reportes de inventario.
 *
 * Permite al usuario exportar la información del inventario en formato PDF o CSV.
 */
class ReportTab : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de ReportTab.
     *
     * Inicializa los componentes de la interfaz y conecta los eventos necesarios.
     *
     * @param manager Puntero al InventoryManager para acceder a los datos del inventario.
     * @param parent Widget padre (opcional).
     */
    explicit ReportTab(InventoryManager* manager, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Slot que gestiona la generación de reportes.
     *
     * Abre un diálogo de archivo y llama a los métodos del ReportGenerator para exportar
     * los datos en el formato seleccionado.
     */
    void onGenerateReport();

private:
    InventoryManager* m_manager;        ///< Referencia al gestor de inventario.
    ReportGenerator* reportGenerator;  ///< Encargado de crear los reportes.
    QPushButton* generateButton;       ///< Botón para iniciar la generación del reporte.
};

#endif // REPORTSTAB_H
