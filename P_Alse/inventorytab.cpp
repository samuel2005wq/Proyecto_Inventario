#include "inventorytab.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableWidgetItem>
#include <QMessageBox>

/**
 * @brief Constructor de InventoryTab.
 * @param manager Puntero al InventoryManager que gestiona la lógica del inventario.
 * @param parent QWidget padre (por defecto nullptr).
 */
InventoryTab::InventoryTab(InventoryManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Inicialización de la tabla
    table = new QTableWidget(this);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "Nombre" << "Tipo"
                                                   << "Cantidad" << "Ubicación"
                                                   << "Fecha");
    mainLayout->addWidget(table);

    connect(table, &QTableWidget::cellDoubleClicked, this, &InventoryTab::handleCellDoubleClicked);

    // Formulario de entrada
    QFormLayout* formLayout = new QFormLayout;
    nameEdit = new QLineEdit(this);
    typeEdit = new QLineEdit(this);
    quantitySpin = new QSpinBox(this);
    quantitySpin->setRange(0, 1000000);
    locationEdit = new QLineEdit(this);
    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");

    formLayout->addRow("Nombre:", nameEdit);
    formLayout->addRow("Tipo:", typeEdit);
    formLayout->addRow("Cantidad:", quantitySpin);
    formLayout->addRow("Ubicación:", locationEdit);
    formLayout->addRow("Fecha:", dateEdit);

    mainLayout->addLayout(formLayout);

    // Botón para agregar/editar
    addButton = new QPushButton("Agregar componente", this);
    mainLayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &InventoryTab::addOrUpdateComponent);

    // Botón para eliminar
    deleteButton = new QPushButton("Eliminar componente seleccionado", this);
    mainLayout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked, this, &InventoryTab::deleteSelectedComponent);

    // Mostrar los datos existentes
    refreshTable();
}

/**
 * @brief Agrega un nuevo componente o actualiza uno existente en función del estado de edición.
 */
void InventoryTab::addOrUpdateComponent()
{
    QString nombre = nameEdit->text();
    QString tipo = typeEdit->text();
    int cantidad = quantitySpin->value();
    QString ubicacion = locationEdit->text();
    QDate fecha = dateEdit->date();

    Component comp(nombre, tipo, cantidad, ubicacion, fecha);

    if (editingId == -1) {
        m_manager->addComponent(comp);
    } else {
        comp.setId(editingId);
        m_manager->updateComponent(editingId, comp);
        editingId = -1;
        addButton->setText("Agregar componente");
    }

    // Limpiar el formulario
    nameEdit->clear();
    typeEdit->clear();
    quantitySpin->setValue(0);
    locationEdit->clear();
    dateEdit->setDate(QDate::currentDate());

    refreshTable();
}

/**
 * @brief Recarga los datos de la tabla desde el inventario.
 */
void InventoryTab::refreshTable()
{
    table->clearContents();
    QList<Component> list = m_manager->getAllComponents();
    table->setRowCount(list.size());
    rowToIdMap.clear();

    for (int i = 0; i < list.size(); ++i) {
        const Component& comp = list.at(i);
        table->setItem(i, 0, new QTableWidgetItem(comp.getNombre()));
        table->setItem(i, 1, new QTableWidgetItem(comp.getTipo()));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(comp.getCantidad())));
        table->setItem(i, 3, new QTableWidgetItem(comp.getUbicacion()));
        table->setItem(i, 4, new QTableWidgetItem(comp.getFechaAdquisicion().toString("yyyy-MM-dd")));

        rowToIdMap[i] = comp.getId();
    }
}

/**
 * @brief Maneja el doble clic en una celda para editar un componente.
 * @param row Fila seleccionada.
 * @param column Columna seleccionada (no utilizada).
 */
void InventoryTab::handleCellDoubleClicked(int row, int)
{
    if (!rowToIdMap.contains(row)) return;

    int id = rowToIdMap[row];
    QList<Component> list = m_manager->getAllComponents();
    for (const Component& comp : list) {
        if (comp.getId() == id) {
            nameEdit->setText(comp.getNombre());
            typeEdit->setText(comp.getTipo());
            quantitySpin->setValue(comp.getCantidad());
            locationEdit->setText(comp.getUbicacion());
            dateEdit->setDate(comp.getFechaAdquisicion());

            editingId = id;
            addButton->setText("Guardar cambios");
            break;
        }
    }
}

/**
 * @brief Elimina el componente actualmente seleccionado en la tabla.
 */
void InventoryTab::deleteSelectedComponent()
{
    int row = table->currentRow();
    if (row < 0 || !rowToIdMap.contains(row)) return;

    int id = rowToIdMap[row];

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar eliminación",
                                  "¿Estás seguro de eliminar este componente?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_manager->deleteComponent(id);
        refreshTable();
    }
}
