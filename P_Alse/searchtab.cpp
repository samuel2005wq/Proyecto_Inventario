/**
 * @file searchtab.cpp
 * @brief Implementación de la clase SearchTab que proporciona una pestaña de búsqueda para componentes en el inventario.
 */

#include "searchtab.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QLabel>

/**
 * @brief Constructor de la clase SearchTab.
 *
 * Crea la interfaz de usuario para buscar componentes del inventario.
 *
 * @param manager Puntero al gestor de inventario.
 * @param parent Puntero al widget padre (por defecto es nullptr).
 */
SearchTab::SearchTab(InventoryManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* searchLayout = new QHBoxLayout;

    searchCriteriaCombo = new QComboBox(this);
    searchCriteriaCombo->addItems({"Nombre", "Tipo", "Cantidad", "Ubicación", "Fecha"});

    searchEdit = new QLineEdit(this);
    searchButton = new QPushButton("Buscar", this);

    searchLayout->addWidget(new QLabel("Buscar por:", this));
    searchLayout->addWidget(searchCriteriaCombo);
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);

    resultTable = new QTableWidget(this);
    resultTable->setColumnCount(5);
    resultTable->setHorizontalHeaderLabels(QStringList() << "Nombre" << "Tipo"
                                                         << "Cantidad" << "Ubicación"
                                                         << "Fecha");
    mainLayout->addWidget(resultTable);

    connect(searchButton, &QPushButton::clicked, this, &SearchTab::performSearch);
}

/**
 * @brief Realiza la búsqueda de componentes según el criterio y palabra clave ingresados.
 *
 * Llama al método searchComponents del InventoryManager y muestra los resultados en una tabla.
 */
void SearchTab::performSearch()
{
    QString keyword = searchEdit->text();
    QString criteria = searchCriteriaCombo->currentText();

    QList<Component> results = m_manager->searchComponents(keyword, criteria);
    resultTable->setRowCount(results.size());

    for (int i = 0; i < results.size(); ++i) {
        const Component& comp = results.at(i);
        resultTable->setItem(i, 0, new QTableWidgetItem(comp.getNombre()));
        resultTable->setItem(i, 1, new QTableWidgetItem(comp.getTipo()));
        resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(comp.getCantidad())));
        resultTable->setItem(i, 3, new QTableWidgetItem(comp.getUbicacion()));
        resultTable->setItem(i, 4, new QTableWidgetItem(comp.getFechaAdquisicion().toString("yyyy-MM-dd")));
    }
}
