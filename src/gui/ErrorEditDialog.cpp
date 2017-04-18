#include "ui_ErrorEditDialog.h"
#include "ErrorEditDialog.h"

#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QAbstractButton>
#include <QMessageBox>
#include <iostream>

/*
 * Load data contained in the errors vector into a QWidgetTable
 * Fields will be marked red and editable if they are a mandatory field
 * and editable.  Otherwise all other fields will not be editable.
 * Clicking Save in the dialog will return the corrected entries to the main
 * program through the errors parameter.  If not all marked fields are edited
 * then a warning message will be displayed.  If cancel is clicked all errors
 * are discarded.
 */
ErrorEditDialog::ErrorEditDialog(QWidget *parent,
                                 std::vector<std::vector<std::string>*>& errors,
                                 std::vector<std::string>& headers,
                                 std::vector<std::string>& mandatory) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    errorList(errors),
    headerList(headers),
    mandatoryList(mandatory),
    ui(new Ui::ErrorEditDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount((int) errors.size());
    ui->tableWidget->setColumnCount((int) headers.size());

    QStringList listHeaders;
    for (int i = 0; i < (int) headers.size(); i++) {
        listHeaders << headers[i].c_str();
    }

    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);
    QTableWidgetItem* item;
    QBrush brush(QColor(255, 0, 0, 100));
    std::vector<std::vector<std::string>*>::iterator it;
    int row = 0;
    int errorCount = 0;
    for (it = errors.begin(); it != errors.end(); it++) {
        for (int col = 0; col < (int) headers.size() && col < (int) (*it)->size(); col++) {
            item = new QTableWidgetItem();
            Qt::ItemFlags flag = item->flags();
            item->setFlags(Qt::ItemIsSelectable);
            item->setText((*it)->at(col).c_str());
            for (int i = 0; i < (int) mandatory.size(); i++) {
                if (mandatory[i].compare(headers.at(col)) == 0
                        && (*it)->at(col).compare("") == 0) {
                    item->setBackground(brush);
                    item->setFlags(flag);
                    errorCount++;
                }
            }
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }
    QLabel* errorsLeftLabel = ui->errorsLeftLabel;
    errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
}

//Clean up allocated memory for the table items
ErrorEditDialog::~ErrorEditDialog()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
             //Must use deleteLater since tableWidget slot was added that involves fetching items that could have already been deallocated.
            ui->tableWidget->deleteLater();
        }
    }
    delete ui;
}

//Save the new data entered by the user via the error reference var
void ErrorEditDialog::saveData() {
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int col = 0; col < ui->tableWidget->columnCount() && col < (int) errorList[row]->size(); col++) {
            std::vector<std::string>::iterator it = errorList[row]->begin()+col;
            if (errorList[row]->at(col).compare("") == 0) {
                it = errorList[row]->erase(it);
                std::string insertStr = ui->tableWidget->item(row, col)->text().toStdString();
                insertStr[0] = toupper(insertStr[0]);
                errorList[row]->insert(it, insertStr);
            }
        }
    }
    accept();
}

void ErrorEditDialog::on_next_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    QTableWidgetItem* lastSelectedErrorItem;
    bool lastSelectedItemExists = false;
    if (selectedItems.count() > 0) {
        lastSelectedItemExists = true;
        lastSelectedErrorItem = selectedItems.last();

    }

    if (!lastSelectedItemExists) {
        bool firstItemFound = false;
        int errorCount = 0;
        QLabel* errorsLeftLabel = ui->errorsLeftLabel;
        QTableWidget* tableWidget = ui->tableWidget;
        for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
            for (int j = 0; j < (int) mandatoryList.size(); j++) {
                std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
                int col = it - headerList.begin();
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item->text().compare("") == 0) {
                    errorCount++;
                    if (firstItemFound == false) {
                        item->setSelected(true);
                        tableWidget->editItem(item);
                        tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                        lastSelectedErrorItem = item;
                        firstItemFound = true;
                    }
                }
            }
        }
        errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
    } else {
        bool itemChanged = false;
        int errorCount = 0;
        QLabel* errorsLeftLabel = ui->errorsLeftLabel;
        QTableWidget* tableWidget = ui->tableWidget;
        QTableWidgetItem* lastItem;
        for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
            for (int j = 0; j < (int) mandatoryList.size(); j++) {
                std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
                int col = it - headerList.begin();
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item->text().compare("") == 0) {
                    errorCount++;
                    if (!itemChanged) {
                        if (lastSelectedErrorItem->row() < item->row()) {
                            item->setSelected(true);
                            tableWidget->editItem(item);
                            tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                            itemChanged = true;
                        } else if (lastSelectedErrorItem->row() == item->row()) {
                            if (lastSelectedErrorItem->column() < item->column()) {
                                item->setSelected(true);
                                tableWidget->editItem(item);
                                tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                                itemChanged = true;
                            }
                        }
                    }
                }
            }
        }
        errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
        if (lastItem == ui->tableWidget->selectedItems().last()) {
            //Deselect all items when at the bottom.
            QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
            for (int i = 0; i < selectedItems.count(); i++) {
                selectedItems.at(i)->setSelected(false);
            }
        }
    }
}

void ErrorEditDialog::on_prev_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    QTableWidgetItem* lastSelectedErrorItem;
    bool lastSelectedItemExists = false;
    if (selectedItems.count() > 0) {
        lastSelectedItemExists = true;
        lastSelectedErrorItem = selectedItems.last();
    }

    if (!lastSelectedItemExists) {
        bool firstItemFound = false;
        int errorCount = 0;
        QLabel* errorsLeftLabel = ui->errorsLeftLabel;
        QTableWidget* tableWidget = ui->tableWidget;
        for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
            for (int j = 0; j < (int) mandatoryList.size(); j++) {
                std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
                int col = it - headerList.begin();
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item->text().compare("") == 0) {
                    errorCount++;
                    if (firstItemFound == false) {
                        item->setSelected(true);
                        tableWidget->editItem(item);
                        tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                        lastSelectedErrorItem = item;
                        firstItemFound = true;
                    }
                }
            }
        }
        errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
    } else {
        std::vector<QTableWidgetItem*> mandatoryErrorItems;
        for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
            for (int j = 0; j < (int) mandatoryList.size(); j++) {
                std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
                int col = it - headerList.begin();
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item->text().compare("") == 0) {
                    mandatoryErrorItems.push_back(item);
                }
            }
        }
        bool itemChanged = false;
        int errorCount = 0;
        //std::reverse(mandatoryErrorItems.begin(), mandatoryErrorItems.end());
        for (int i = 0; i < mandatoryErrorItems.size(); i++) {
            QTableWidgetItem* item = mandatoryErrorItems.at(i);
            errorCount++;
            if (item == lastSelectedErrorItem && itemChanged == false) {
                i -= 1;
                errorCount -= 1;
                if (i >= 0) {
                   item = mandatoryErrorItems.at(i);
                   item->setSelected(true);
                   ui->tableWidget->editItem(item);
                   ui->tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                   itemChanged = true;
                }
                if (i == -1) {
                    i += 1;
                    //Deselect all items when back to top.
                    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
                    for (int i = 0; i < selectedItems.count(); i++) {
                        selectedItems.at(i)->setSelected(false);
                    }
                }
            }
        }
        ui->errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
    }
}

void ErrorEditDialog::on_save_clicked()
{
    bool search = true;
    //check if mandatory fields have been filled
    for (int row = 0; row < ui->tableWidget->rowCount() && search; row++) {
        for (int j = 0; j < (int) mandatoryList.size() && search; j++) {
            std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
            int col = it - headerList.begin();
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item->text().compare("") == 0) {
                QMessageBox::critical(this, "Error", "Mandatory fields are still empty.");
                search = false;
            }
        }
    }
    if (search) {
        saveData();
    }
}

void ErrorEditDialog::on_cancel_clicked()
{
    reject();
}

void ErrorEditDialog::on_tableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem* itemThatChanged = ui->tableWidget->item(row, column);
    //Ensure that the cell was selected by the user.
    if (!itemThatChanged->isSelected())
        return;
    itemThatChanged->setSelected(false);
    this->lastEditedItem = itemThatChanged;
    int errorCount = 0;
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int j = 0; j < (int) mandatoryList.size(); j++) {
            std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
            int col = it - headerList.begin();
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item == nullptr)
                return;
            if (item->text().compare("") == 0) {
                errorCount++;
                if (item->row() == itemThatChanged->row() && item->column() == itemThatChanged->column())
                    item->setBackgroundColor(QColor(255, 0, 0, 100));
            } else {
                if (item->row() == itemThatChanged->row() && item->column() == itemThatChanged->column())
                    item->setBackgroundColor(QColor(0,128,0, 100));
            }
        }
    }
    QLabel* errorsLeftLabel = ui->errorsLeftLabel;
    errorsLeftLabel->setText(QString::number(errorCount).append(" Errors Left."));
    if (errorCount == 0) {
        ui->next->setEnabled(false);
        ui->prev->setEnabled(false);
    }
}
