#include <QDate>
#include <QDebug>
#include <QDirModel>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPrintDialog>
#include <QPrinter>
#include <QString>
#include <algorithm>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CustomSort.h"
#include "ErrorEditDialog.h"

#include "database/CSVReader.h"
#include "database/QSortListIO.h"
#include "database/RecordsManager.h"
#include "datamodel/TreeModel.h"
#include "datamodel/GrantFundingTreeModel.h"
#include "datamodel/PresentationTreeModel.h"
#include "datamodel/PublicationTreeModel.h"
#include "datamodel/TeachingTreeModel.h"

#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"

std::vector<std::string> MainWindow::GRANTS_MANFIELDS = {"Member Name", "Funding Type", "Status", "Peer Reviewed?", "Role", "Title", "Start Date", "Division"};
std::vector<std::string> MainWindow::PRES_MANFIELDS = {"Member Name", "Date", "Type", "Role", "Title", "Division"};
std::vector<std::string> MainWindow::PUBS_MANFIELDS = {"Member Name", "Type", "Status Date", "Role", "Title", "Division"};
std::vector<std::string> MainWindow::TEACH_MANFIELDS = {"Member Name", "Start Date", "Program", "Division"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    fundTree(NULL), presTree(NULL), pubTree(NULL), teachTree(NULL),
    funddb(NULL), presdb(NULL), pubdb(NULL), teachdb(NULL) {
    // draw GUI elements
    ui->setupUi(this);

    this->showMaximized();

    // set up the logo
    QPixmap logo(":/logo.png");
    ui->logo_label->setPixmap(logo);

    // set up application icon
    QIcon icon(":/icon32.ico");
    MainWindow::setWindowIcon(icon);

    // set the date format
    QString dFormat("yyyy");
    ui->FromDate->setDisplayFormat(dFormat);
    ui->ToDate->setDisplayFormat(dFormat);

    // set start year to be 1950
    QDate startDate(1950, 1, 1);

    // set ranges for spinbox
    ui->FromDate->setDateRange(startDate, QDate::currentDate());
    ui->ToDate->setDateRange(startDate, QDate::currentDate());

    // set default dates (1950->current)
    ui->FromDate->setDate(startDate);
    ui->ToDate->setDate(QDate::currentDate());

    // set some member variables to the current date values
    yearStart = 1950;
    yearEnd = QDate::currentDate().year();

    //default print is disabled
    ui->teachPrintButton->setEnabled(false);
    ui->fundPrintButton->setEnabled(false);
    ui->pubPrintButton->setEnabled(false);
    ui->presPrintButton->setEnabled(false);

    ui->teachExportButton->setEnabled(false);
    ui->fundExportButton->setEnabled(false);
    ui->pubExportButton->setEnabled(false);
    ui->presExportButton->setEnabled(false);

    //Setup printer
    printer = new QPrinter();

    dateChanged = {false, false, false, false};

    attemptToRestoreSession();
}

void MainWindow::attemptToRestoreSession() {
    //Load Session file and restore any GUI using it.
    int counter = 0;
    QString filename = "session.dat";
    QFile sessionFile(filename);
    if (sessionFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&sessionFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if (counter == 0) {
              if(!line.isEmpty()){
                  int year = line.toInt();
                  ui->FromDate->setDate(QDate(year, 1, 1));
              }
          }
          if (counter == 1) {
              if(!line.isEmpty()){
                  int year = line.toInt();
                  ui->ToDate->setDate(QDate(year, 1, 1));
              }
          }
          if (counter == 2) {
              if (!line.isEmpty()) {
                  load_teach(line);
              }
          }
          if (counter == 3) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->teachTreeView->setColumnWidth(0, columnWidth);
              }
          }
          if (counter == 4) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->teachTreeView->setColumnWidth(1, columnWidth);
              }
          }
          if (counter == 5) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->teachTreeView->setColumnWidth(2, columnWidth);
              }
          }
          if (counter == 6) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->teachTreeView->setColumnWidth(3, columnWidth);
              }
          }
          if (counter == 7) {
              if (!line.isEmpty()) {
                  int currentIndex = line.toInt();
                  ui->teach_sort->setCurrentIndex(currentIndex);
              }
          }
          if (counter == 8) {
              if (!line.isEmpty()) {
                  load_pub(line);
              }
          }
          if (counter == 9) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->pubTreeView->setColumnWidth(0, columnWidth);
              }
          }
          if (counter == 10) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->pubTreeView->setColumnWidth(1, columnWidth);
              }
          }
          if (counter == 11) {
              if (!line.isEmpty()) {
                  int currentIndex = line.toInt();
                  ui->pub_sort->setCurrentIndex(currentIndex);
              }
          }
          if (counter == 12) {
              if (!line.isEmpty()) {
                  load_pres(line);
              }
          }
          if (counter == 13) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->presTreeView->setColumnWidth(0, columnWidth);
              }
          }
          if (counter == 14) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->presTreeView->setColumnWidth(1, columnWidth);
              }
          }
          if (counter == 15) {
              if (!line.isEmpty()) {
                  int currentIndex = line.toInt();
                  ui->pres_sort->setCurrentIndex(currentIndex);
              }
          }
          if (counter == 16) {
              if (!line.isEmpty()) {
                  load_fund(line);
              }
          }
          if (counter == 17) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->fundTreeView->setColumnWidth(0, columnWidth);
              }
          }
          if (counter == 18) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->fundTreeView->setColumnWidth(1, columnWidth);
              }
          }
          if (counter == 19) {
              if(!line.isEmpty()){
                  int columnWidth = line.toInt();
                  ui->fundTreeView->setColumnWidth(3, columnWidth);
              }
          }
          if (counter == 20) {
              if (!line.isEmpty()) {
                  int currentIndex = line.toInt();
                  ui->fund_sort->setCurrentIndex(currentIndex);
              }
          }
          counter++;
       }
       sessionFile.close();
       sessionFile.remove();
    }
}

MainWindow::~MainWindow() {
    delete ui;

    delete fundTree;
    delete presTree;
    delete pubTree;
    delete teachTree;

    delete funddb;
    delete presdb;
    delete pubdb;
    delete teachdb;
    delete printer;
}

void MainWindow::on_actionLoad_file_triggered() {
    QStringList filePaths = QFileDialog::getOpenFileNames(this,
                                                          "Select one or more files to load",
                                                          QDir::currentPath(),
                                                          tr("CSV (*.csv);; All files (*.*)"));
    if (filePaths.size() > 0) {
        const int NUM_TABS = 4;
        bool all_loaded[NUM_TABS] = {false, false, false, false};
        int sum = std::accumulate(all_loaded, all_loaded + NUM_TABS, 0);
        QStringList::Iterator it = filePaths.begin();
        while (sum != NUM_TABS && it != filePaths.end()) {
            QString path = it[0];
            //note short-circuit eval
            if (!all_loaded[FUNDING] && load_fund(path, true)) {
                all_loaded[FUNDING] = true;
            } else if (!all_loaded[TEACH] && load_teach(path, true)) {
                all_loaded[TEACH] = true;
            } else if (!all_loaded[PUBLICATIONS] && load_pub(path, true)) {
                all_loaded[PUBLICATIONS] = true;
            } else if (!all_loaded[PRESENTATIONS] && load_pres(path, true)) {
                all_loaded[PRESENTATIONS] = true;
            }
            sum = std::accumulate(all_loaded, all_loaded + NUM_TABS, 0);
            ++it;
        }
    }
}


/*
 * When the load file button is clicked a file open dialog box
 * is opened.  If a file name is successfully returned, makeTree()
 * is called.
 */
QString MainWindow::load_file() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(),
                                                    tr("CSV (*.csv);; All files (*.*)"));

    if (!filePath.isEmpty()) {
        return filePath;
    } else {
        return "";
    }
}

void MainWindow::refresh(int tabIndex) {
    // if we've loaded in a file, update that data
    switch (tabIndex) {
    case FUNDING:
        if (!fundPath.isEmpty()) {
            makeTree(FUNDING);
            ui->fund_graph_stackedWidget->hide();
            ui->fundGraphTitle->clear();
        }
        break;

    case PRESENTATIONS:
        if (!presPath.isEmpty()) {
            makeTree(PRESENTATIONS);
            ui->pres_graph_stackedWidget->hide();
            ui->presGraphTitle->clear();
        }
        break;
    case PUBLICATIONS:
        if (!pubPath.isEmpty()) {
            makeTree(PUBLICATIONS);
            ui->pub_graph_stackedWidget->hide();
            ui->pubGraphTitle->clear();
        }
        break;

    case TEACH:
        if (!teachPath.isEmpty()) {
            makeTree(TEACH);
            ui->teach_graph_stackedWidget->hide();
            ui->teachGraphTitle->clear();
        }
        break;
    }
}

int MainWindow::checkFile(int index, QString filePath) {
    CSVReader reader;
    std::vector<std::string> header;
    std::string searchstring;

    int sortHeaderIndex = 2;

    switch (index) {

    case TEACH:
        // read if first or if a new file is loaded
        if (teachPath.isEmpty() || (!teachPath.isEmpty() && filePath.compare(teachPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete teachdb;
            teachdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Program";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = teachdb->getHeaderIndex("Start Date");
                teachData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) teachData.size(); i++) {
                    for (j = 0; j < TEACH_MANFIELDS.size(); j++) {
                        int index = teachdb->getHeaderIndex(TEACH_MANFIELDS[j]);
                        if (teachData[i][index].compare("") == 0) {
                            f_errs.push_back(&teachData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == TEACH_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = teachdb->getHeaderIndex("Start Date");
                        int year;
                        sscanf(teachData[i][yrIndex].c_str(), "%4d", &year);
                        teachData[i][yrIndex] = std::to_string(year);

                        teachdb->addRecord(reader.parseDateString(teachData[i][sortHeaderIndex]), &teachData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, TEACH_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            teachdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->teachPrintButton->setEnabled(true);
        ui->teachExportButton->setEnabled(true);
        break;

    case PUBLICATIONS:
        // read if first or if a new file is loaded
        if (presPath.isEmpty() || (!presPath.isEmpty() && filePath.compare(presPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete pubdb;
            pubdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Publication Status";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = pubdb->getHeaderIndex("Status Date");
                pubData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) pubData.size(); i++) {
                    for (j = 0; j < PUBS_MANFIELDS.size(); j++) {
                        int index = pubdb->getHeaderIndex(PUBS_MANFIELDS[j]);
                        if (pubData[i][index].compare("") == 0) {
                            f_errs.push_back(&pubData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == PUBS_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = pubdb->getHeaderIndex("Status Date");
                        int year;
                        sscanf(pubData[i][yrIndex].c_str(), "%4d", &year);
                        pubData[i][yrIndex] = std::to_string(year);

                        pubdb->addRecord(reader.parseDateString(pubData[i][sortHeaderIndex]), &pubData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, PUBS_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            pubdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->pubPrintButton->setEnabled(true);
        ui->pubExportButton->setEnabled(true);
        break;

    case PRESENTATIONS:
        // read if first or if a new file is loaded
        if (presPath.isEmpty() || (!presPath.isEmpty() && filePath.compare(presPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete presdb;
            presdb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Activity Type";
            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = presdb->getHeaderIndex("Date");
                presData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j = 0;
                for (int i = 0; i < (int) presData.size(); i++) {
                    //check through mandatory fields for empty fields
                    for (j = 0; j < PRES_MANFIELDS.size(); j++) {
                        int index = presdb->getHeaderIndex(PRES_MANFIELDS[j]);
                        if (presData[i][index].compare("") == 0) {
                            f_errs.push_back(&presData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == PRES_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = presdb->getHeaderIndex("Date");
                        int year;
                        sscanf(presData[i][yrIndex].c_str(), "%4d", &year);
                        presData[i][yrIndex] = std::to_string(year);

                        presdb->addRecord(reader.parseDateString(presData[i][sortHeaderIndex]), &presData[i]);
                    }
                }

                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, PRES_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            presdb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->presPrintButton->setEnabled(true);
        ui->presExportButton->setEnabled(true);
        break;

    case FUNDING:
        // read if first or if a new file is loaded
        if (fundPath.isEmpty() || (!fundPath.isEmpty() && filePath.compare(fundPath))) {
            // create a new reader to read in the file
            reader = CSVReader(filePath.toStdString());
            header = reader.getHeaders();

            // create a new manager for the data
            delete funddb;
            funddb = new RecordsManager(&header);

            // check for right file type by searching for unique header
            searchstring = "Funding Type";

            if (std::find(header.begin(), header.end(), searchstring) != header.end()) {
                // load in data into the manager, with the date as the key
                sortHeaderIndex = funddb->getHeaderIndex("Start Date");
                fundData = reader.getData();
                std::vector<std::vector<std::string>*> f_errs;
                unsigned int j;
                for (int i = 0; i < (int) fundData.size(); i++) {
                    for (j = 0; j < GRANTS_MANFIELDS.size(); j++) {
                        int index = funddb->getHeaderIndex(GRANTS_MANFIELDS[j]);
                        if (fundData[i][index].compare("") == 0) {
                            f_errs.push_back(&fundData[i]);
                            break;
                        }
                    }

                    // if all mandatory fields are okay
                    if (j == GRANTS_MANFIELDS.size()) {
                        // date interpretation
                        int yrIndex = funddb->getHeaderIndex("Start Date");
                        int year;
                        sscanf(fundData[i][yrIndex].c_str(), "%4d", &year);
                        fundData[i][yrIndex] = std::to_string(year);

                        // boolean interpretation
                        int prIndex = funddb->getHeaderIndex("Peer Reviewed?");
                        if (fundData[i][prIndex].compare("True") == 0) {
                            fundData[i][prIndex] = "Peer Reviewed";
                        } else {
                            fundData[i][prIndex] = "Not Peer Reviewed";
                        }
                        funddb->addRecord(reader.parseDateString(fundData[i][sortHeaderIndex]), &fundData[i]);
                    }
                }
                if (f_errs.size() > 0) {
                    if(handle_field_errors(f_errs, header, GRANTS_MANFIELDS)) {
                        for (unsigned int i = 0; i < f_errs.size(); i++) {
                            funddb->addRecord(reader.parseDateString((*(f_errs[i]))[sortHeaderIndex]), f_errs[i]);
                        }
                    }
                }
            } else {
                return EXIT_FAILURE;
            }
        } else {
            return EXIT_SUCCESS;
        }
        ui->fundPrintButton->setEnabled(true);
        ui->fundExportButton->setEnabled(true);
        break;
    }
    return EXIT_SUCCESS;
}

void MainWindow::createDefaultSortOrder(int tabIndex) {
    QStringList defaultOrder;
    defaultOrder << "Default";

    switch (tabIndex) {
    case FUNDING:
        // specify default sort order
        defaultOrder << "Member Name" << "Funding Type" << "Peer Reviewed?" << "Status" << "Role" << "Title";

        // add default list to member variable
        allFundOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO saveFundSort(FUNDORDER_SAVE);
        saveFundSort.saveList(allFundOrders);
    }

        break;
    case PRESENTATIONS:
        // specify default sort order
        defaultOrder << "Member Name" << "Type" << "Role" << "Title";

        // add default list to member variable
        allPresOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO savePresSort(PRESORDER_SAVE);
        savePresSort.saveList(allPresOrders);
    }

        break;
    case PUBLICATIONS:
        // specify default sort order
        defaultOrder << "Member Name" << "Type" << "Role" << "Title";

        // add default list to member variable
        allPubOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO savePubSort(PUBORDER_SAVE);
        savePubSort.saveList(allPubOrders);
    }

        break;
    case TEACH:
        // specify default sort order
        defaultOrder << "Member Name" << "Program";

        // add default list to member variable
        allTeachOrders << defaultOrder;

    {
        // save the default for the user
        QSortListIO saveTeachSort(FUNDORDER_SAVE);
        saveTeachSort.saveList(allFundOrders);
    }

        break;
    }
}

/*
 * err: vector of pointers to record entries.
 * headers: vector of strings containing the db headers
 * mandatory: vector of strings containing the mandatory fields in the db
 *
 * Returns true when the passed err vector contains edited fields.
 * Returns false when no fields have been edited.
 */
bool MainWindow::handle_field_errors(std::vector<std::vector<std::string>*>& err,
                                     std::vector<std::string>& headers,
                                     std::vector<std::string>& mandatory) {
    //Since CSVReader alldata contains completely empty records
    //remove them first.
    std::vector<std::vector<std::string>*>::iterator it;
    for (it = err.begin(); it != err.end(); it++) {
        bool allEmpty = true;
        for (int col = 0; col < (int) (*it)->size(); col++) {
            if ((*it)->at(col).compare("") != 0) {
                allEmpty = false;
            }
        }
        if (allEmpty) {
            it = err.erase(it);
            it--;
        }
    }
    //Return false; there are no errors to correct
    if (err.size() == 0) {
        return false;
    }
    QMessageBox prompt;
    QString mainText = "File contains ";
    mainText.append(QString::number(err.size()));
    mainText.append(" records with missing mandatory fields.");
    prompt.setText(mainText);
    prompt.setInformativeText("Do you want to edit these entries or discard?");
    prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    prompt.setDefaultButton(QMessageBox::Yes);
    prompt.setButtonText(QMessageBox::Yes, "Edit");
    prompt.setButtonText(QMessageBox::No, "Discard");
    prompt.setWindowIcon(QIcon(":/icon32.ico"));
    int ret = prompt.exec();

    switch (ret) {
    case QMessageBox::Yes: {
        ErrorEditDialog diag(this, err, headers, mandatory);
        if(diag.exec()) {
            return true;
        }
        return false;
    }

    case QMessageBox::No:
    default:
        return false;
    }
}

/*
 * Builds a TreeModel for the ui's embedded treeview.
 */
void MainWindow::makeTree(int tabIndex) {
    switch (tabIndex) {
    case TEACH:
        // set up some member variables to point to the current data in use
        currentdb = teachdb;
        delete teachTree;
        teachTree = new TeachingTreeModel(currentdb);
        proxyModel = new QSortFilterProxyModel(teachTree);
        currentTree = teachTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->teachTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, teachSortOrder, getFilterStartChar(TEACH), getFilterEndChar(TEACH));
        proxyModel->setSourceModel(currentTree);
       // proxyModel->setFilterRegExp(QRegExp("",Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterRegExp(QRegExp());
        proxyModel->setFilterKeyColumn(1);
        currentView->setModel(proxyModel);
        currentView ->setSortingEnabled(true);
        currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);

        ui->teach_pie_button->toggle();

        break;

    case PUBLICATIONS:
        // set up some member variables to point to the current data in use
        currentdb = pubdb;
        delete pubTree;
        pubTree = new PublicationTreeModel(currentdb);
        proxyModel = new QSortFilterProxyModel(pubTree);
        currentTree = pubTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->pubTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, pubSortOrder, getFilterStartChar(PUBLICATIONS), getFilterEndChar(PUBLICATIONS));
        proxyModel->setSourceModel(currentTree);
        currentView->setModel(proxyModel);
        proxyModel->setFilterRegExp(QRegExp("",Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterKeyColumn(1);
        currentView->setSortingEnabled(true);
        currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->pub_pie_button->toggle();

        break;
    case PRESENTATIONS:
        // set up some member variables to point to the current data in use
        currentdb = presdb;
        delete presTree;

        presTree = new PresentationTreeModel(currentdb);
        proxyModel = new QSortFilterProxyModel(presTree);
        currentTree = presTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->presTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, presSortOrder, getFilterStartChar(PRESENTATIONS), getFilterEndChar(PRESENTATIONS));
        proxyModel->setSourceModel(currentTree);
        currentView->setModel(proxyModel);
        proxyModel->setFilterRegExp(QRegExp("",Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterKeyColumn(1);
        currentView->setSortingEnabled(true);
        currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->pres_pie_button->toggle();

        break;

    case FUNDING:
        // set up some member variables to point to the current data in use
        currentdb = funddb;
        delete fundTree;
        fundTree = new GrantFundingTreeModel(currentdb);
        proxyModel = new QSortFilterProxyModel(fundTree);
        currentTree = fundTree;

        // get some UI elements so we can put the tree and graphs into them
        currentView = ui->fundTreeView;

        // analyze the data into a tree
        currentTree->setupModel(yearStart, yearEnd, fundSortOrder, getFilterStartChar(FUNDING), getFilterEndChar(FUNDING));
        proxyModel->setSourceModel(currentTree);
        currentView->setModel(proxyModel);
        proxyModel->setFilterRegExp(QRegExp("",Qt::CaseInsensitive, QRegExp::FixedString));
        proxyModel->setFilterKeyColumn(1);
        currentView->setSortingEnabled(true);
        currentView->setSelectionMode(QAbstractItemView::ExtendedSelection);

        ui->fund_pie_button->toggle();

        break;
    }

    // set up the tree in our UI
    //currentView->setModel(currentTree);

    // set resize property to stretch
    currentView->header()->resizeSections(QHeaderView::Stretch);
    currentView->setSortingEnabled(true);
}

void MainWindow::setupPieChart(PieChartWidget* pieChart, QListWidget *pieListWidget, std::vector<std::pair <std::string, double>> pieChartList) {
    // draws the pie graph by sending piechartwidget a vector of name, presentation count
    int pieSize = (int) pieChartList.size();
    QVector<QColor> colorList(pieSize);
    pieListWidget->clear();
    for (int i = 0; i < pieSize; i++) {
        colorList[i] = (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        pieListWidget->addItem(QString::fromStdString(pieChartList[i].first));

        // set legend colors
        QPixmap pixmap(100, 100);
        pixmap.fill(QColor(colorList[i]));
        QIcon tempIcon(pixmap);
        pieListWidget->item(i)->setIcon(tempIcon);
    }

    pieChart->setData(pieChartList, colorList); //passes vector list to piechartwidget
}

void MainWindow::setupBarChart(QCustomPlot *barChart, std::vector<std::pair <std::string, double>> barChartList) {
    // create empty bar chart objects:
    QCPBars *yLabels = new QCPBars(barChart->yAxis, barChart->xAxis);
    barChart->addPlottable(yLabels);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    yLabels->setName("Type");
    pen.setColor(QColor(255, 131, 0));
    yLabels->setPen(pen);
    yLabels->setBrush(QColor(255, 131, 0, 50));

    //get label list
    int barSize = (int) barChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<QString> ylabels;
    QVector<double> count;

    //add label list to y axis labels
    for (int i = 0; i < barSize; i++){
        ticks << (i+1);
        ylabels << QString::fromStdString(barChartList[i].first);
        if (barChartList[i].second>1000000){
            scaledCount = barChartList[i].second/1000000;
        } else if (barChartList[i].second>1000){
            scaledCount = barChartList[i].second/1000;
        } else{
            scaledCount = barChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < barChartList[i].second)
            maxCount = barChartList[i].second;
    }

    //setup Y Axis
    barChart->yAxis->setAutoTicks(false);
    barChart->yAxis->setAutoTickLabels(false);
    barChart->yAxis->setTickVector(ticks);
    barChart->yAxis->setTickVectorLabels(ylabels);
    barChart->yAxis->setTickLabelPadding(1);
    barChart->yAxis->setSubTickCount(0);
    barChart->yAxis->setTickLength(0, 1);
    barChart->yAxis->grid()->setVisible(true);
    barChart->yAxis->setRange(0, barSize+1);

    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        barChart->xAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        barChart->xAxis->setLabel("Total (in Thousands)");
    }else{
        barChart->xAxis->setLabel("Total");
    }

    // setup X Axis
    barChart->xAxis->setAutoTicks(true);
    barChart->xAxis->setRange(0,maxCount+(maxCount*.05));
    barChart->xAxis->setAutoTickLabels(true);
    barChart->xAxis->setAutoTickStep(true);
    barChart->xAxis->grid()->setSubGridVisible(true);

    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    barChart->xAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    barChart->xAxis->grid()->setSubGridPen(gridPen);

    yLabels->setData(ticks, count);
}

//add team lynx add the line chart
void MainWindow::setupLineChart(QCustomPlot *lineChart, std::vector<std::pair <std::string, double>> lineChartList) {
    QCPGraph *xLabels = new QCPGraph(lineChart->xAxis, lineChart->yAxis);
    lineChart->addPlottable(xLabels);

    //set the style of the line point
    xLabels->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 5));

    //get label list
    int lineSize = (int) lineChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<double> count;
    QVector<QString> xlabels;

    //add label list to x axis labels
    for (int i = 0; i < lineSize; i++){
        ticks << (i+1);
        xlabels << QString::fromStdString(lineChartList[i].first);
        if (lineChartList[i].second>1000000){
            scaledCount = lineChartList[i].second/1000000;
        } else if (lineChartList[i].second>1000){
            scaledCount = lineChartList[i].second/1000;
        } else{
            scaledCount = lineChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < lineChartList[i].second)
            maxCount = lineChartList[i].second;
    }

    //setup X Axis
    lineChart->xAxis->setAutoTicks(false);
    lineChart->xAxis->setAutoTickLabels(false);
    lineChart->xAxis->setTickVector(ticks);
    lineChart->xAxis->setTickVectorLabels(xlabels);
    lineChart->xAxis->setTickLabelPadding(1);
    lineChart->xAxis->setSubTickCount(0);
    lineChart->xAxis->setTickLength(0, 1);
    lineChart->xAxis->grid()->setVisible(true);
    lineChart->xAxis->setRange(0, lineSize+1);
    lineChart->xAxis->setTickLabelRotation(15);

    //set the xAxis label's font to avoid overlapping
    QFont xFont;
    xFont.setPointSize(10);
    lineChart->xAxis->setTickLabelFont(xFont);

    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        lineChart->yAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        lineChart->yAxis->setLabel("Total (in Thousands)");
    }else{
        lineChart->yAxis->setLabel("Total");
    }

    // setup Y Axis
    lineChart->yAxis->setAutoTicks(true);
    lineChart->yAxis->setRange(0,maxCount+(maxCount*.05));
    lineChart->yAxis->setAutoTickLabels(true);
    lineChart->yAxis->setAutoTickStep(true);
    lineChart->yAxis->grid()->setSubGridVisible(true);

    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    lineChart->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    lineChart->yAxis->grid()->setSubGridPen(gridPen);

    xLabels->setData(ticks, count);
}

//add team lynx add the scatter chart
void MainWindow::setupScatterChart(QCustomPlot *scatterChart, std::vector<std::pair <std::string, double>> scatterChartList) {
    //QCPGraph *xLabels = new QCPGraph(scatterChart->xAxis, scatterChart->yAxis);
    scatterChart->addGraph();

    //set the style of the point
    scatterChart->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    scatterChart->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::darkCyan, 8));

    //get label list
    int scatterSize = (int) scatterChartList.size();
    double maxCount = 0;
    double scaledCount;
    QVector<double> ticks;
    QVector<double> count;
    QVector<QString> xlabels;

    //add label list to x axis labels
    for (int i = 0; i < scatterSize; i++){
        ticks << (i+1);
        xlabels << QString::fromStdString(scatterChartList[i].first);
        if (scatterChartList[i].second>1000000){
            scaledCount = scatterChartList[i].second/1000000;
        } else if (scatterChartList[i].second>1000){
            scaledCount = scatterChartList[i].second/1000;
        } else{
            scaledCount = scatterChartList[i].second;
        }
        count <<scaledCount;

        if (maxCount < scatterChartList[i].second)
            maxCount = scatterChartList[i].second;
    }

    //setup X Axis
    scatterChart->xAxis->setAutoTicks(false);
    scatterChart->xAxis->setAutoTickLabels(false);
    scatterChart->xAxis->setTickVector(ticks);
    scatterChart->xAxis->setTickVectorLabels(xlabels);
    scatterChart->xAxis->setTickLabelPadding(1);
    scatterChart->xAxis->setSubTickCount(0);
    scatterChart->xAxis->setTickLength(0, 1);
    scatterChart->xAxis->grid()->setVisible(true);
    scatterChart->xAxis->setRange(0, scatterSize+1);
    scatterChart->xAxis->setTickLabelRotation(15);

    //set the xAxis label's font to avoid overlapping
    QFont xFont;
    xFont.setPointSize(10);
    scatterChart->xAxis->setTickLabelFont(xFont);

    if(maxCount>1000000){
        maxCount = maxCount/1000000;
        scatterChart->yAxis->setLabel("Total (in Millions)");
    }else if (maxCount>1000){
        maxCount = maxCount/1000;
        scatterChart->yAxis->setLabel("Total (in Thousands)");
    }else{
        scatterChart->yAxis->setLabel("Total");
    }

    // setup Y Axis
    scatterChart->yAxis->setAutoTicks(true);
    scatterChart->yAxis->setRange(0,maxCount+(maxCount*.05));
    scatterChart->yAxis->setAutoTickLabels(true);
    scatterChart->yAxis->setAutoTickStep(true);
    scatterChart->yAxis->grid()->setSubGridVisible(true);

    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    scatterChart->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    scatterChart->yAxis->grid()->setSubGridPen(gridPen);

    scatterChart->graph()->setData(ticks, count);
}


void MainWindow::on_teach_new_sort_clicked() {
    if (teachdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(TEACH_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allTeachOrders << newSortOrder;
            ui->teach_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO saveTeachSort(TEACHORDER_SAVE);
            saveTeachSort.saveList(allTeachOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_pub_new_sort_clicked() {
    if (pubdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(PUBS_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allPubOrders << newSortOrder;
            ui->pub_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO savePubSort(PUBORDER_SAVE);
            savePubSort.saveList(allPubOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_pres_new_sort_clicked() {
    if (presdb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(PRES_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allPresOrders << newSortOrder;
            ui->pres_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO savePresSort(PRESORDER_SAVE);
            savePresSort.saveList(allPresOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_fund_new_sort_clicked() {
    if (funddb != NULL) {
        CustomSort* sortdialog = new CustomSort();
        sortdialog->setFields(GRANTS_MANFIELDS);
        int ret = sortdialog->exec();
        if (ret) {
            QStringList newSortOrder = sortdialog->getSortFields();
            allFundOrders << newSortOrder;
            ui->fund_sort->addItem(newSortOrder.at(0));

            // save the sort fields to file
            QSortListIO saveFundSort(FUNDORDER_SAVE);
            saveFundSort.saveList(allFundOrders);
        }
        delete sortdialog;
    } else {
        QMessageBox::critical(this, "Missing File", "Please load a file first.");
    }
}

void MainWindow::on_teach_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allTeachOrders[index];
        teachSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            teachSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->teach_filter->setText(QString::fromStdString(teachSortOrder[0]));
        refresh(TEACH);
    }
}

void MainWindow::on_pub_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allPubOrders[index];
        pubSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            pubSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->pub_filter->setText(QString::fromStdString(pubSortOrder[0]));
        refresh(PUBLICATIONS);
    }
}

void MainWindow::on_pres_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allPresOrders[index];
        presSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            presSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->pres_filter->setText(QString::fromStdString(presSortOrder[0]));
        refresh(PRESENTATIONS);
    }
}

void MainWindow::on_fund_sort_currentIndexChanged(int index) {
    if(index != -1) {
        QStringList sortOrder = allFundOrders[index];
        fundSortOrder.clear();
        for (int i = 1; i < sortOrder.size(); i++) {
            fundSortOrder.emplace_back(sortOrder[i].toStdString());
        }
        ui->fund_filter->setText(QString::fromStdString(fundSortOrder[0]));
        refresh(FUNDING);
    }
}

void MainWindow::on_teach_delete_sort_clicked() {
    if (ui->teach_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->teach_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allTeachOrders.removeAt(ui->teach_sort->currentIndex());
            ui->teach_sort->removeItem(ui->teach_sort->currentIndex());

            QSortListIO saveTeachSort(TEACHORDER_SAVE);
            saveTeachSort.saveList(allTeachOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_pub_delete_sort_clicked() {
    if (ui->pub_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->pub_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allPubOrders.removeAt(ui->pub_sort->currentIndex());
            ui->pub_sort->removeItem(ui->pub_sort->currentIndex());

            QSortListIO savePubSort(PUBORDER_SAVE);
            savePubSort.saveList(allPubOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_pres_delete_sort_clicked() {
    if (ui->pres_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->pres_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allPresOrders.removeAt(ui->pres_sort->currentIndex());
            ui->pres_sort->removeItem(ui->pres_sort->currentIndex());

            QSortListIO savePresSort(PRESORDER_SAVE);
            savePresSort.saveList(allPresOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

void MainWindow::on_fund_delete_sort_clicked() {
    if (ui->fund_sort->currentIndex()!=0) {
        QMessageBox prompt;
        prompt.setText("Are you sure you want to delete " + ui->fund_sort->currentText() + "?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        if (prompt.exec()==QMessageBox::Yes) {
            allFundOrders.removeAt(ui->fund_sort->currentIndex());
            ui->fund_sort->removeItem(ui->fund_sort->currentIndex());

            QSortListIO saveFundSort(FUNDORDER_SAVE);
            saveFundSort.saveList(allFundOrders);
        }
    } else {
        QMessageBox::critical(this, "", "Cannot delete Default");
    }
}

//add team lynx
void MainWindow::on_teach_pie_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_teach_bar_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_teach_line_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_teach_scatter_button_toggled() { ui->teach_graph_stackedWidget->setCurrentIndex(3);}

void MainWindow::on_pub_pie_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_pub_bar_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_pub_line_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_pub_scatter_button_toggled() { ui->pub_graph_stackedWidget->setCurrentIndex(3);}

void MainWindow::on_pres_pie_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_pres_bar_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_pres_line_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_pres_scatter_button_toggled() { ui->pres_graph_stackedWidget->setCurrentIndex(3);}

void MainWindow::on_fund_pie_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(0);}
void MainWindow::on_fund_bar_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(1);}
void MainWindow::on_fund_line_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(2);}
void MainWindow::on_fund_scatter_button_toggled() { ui->fund_graph_stackedWidget->setCurrentIndex(3);}

void MainWindow::on_teach_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_teach(path);
    }
}

bool MainWindow::load_teach(QString path, bool multi_file) {
    if (!checkFile(TEACH, path)) {
        //add team lynx
        // enable gui elements
        ui->teach_sort->setEnabled(true);
        ui->teach_delete_sort->setEnabled(true);
        ui->teach_new_sort->setEnabled(true);
        ui->teach_filter_from->setEnabled(true);
        ui->teach_filter_to->setEnabled(true);
        ui->teach_pie_button->setEnabled(true);
        ui->teach_bar_button->setEnabled(true);
        ui->teach_line_button->setEnabled(true);
        ui->teach_scatter_button->setEnabled(true);
        ui->teach_to_label->setEnabled(true);
        ui->teach_sort_label->setEnabled(true);
        ui->teach_filter->setEnabled(true);
        ui->teach_filter_label->setEnabled(true);

        // load save order
        QSortListIO teachSaveOrder(TEACHORDER_SAVE);
        allTeachOrders = teachSaveOrder.readList();
        ui->teach_sort->clear();
        for (int i = 0; i < allTeachOrders.size(); i++) {
            ui->teach_sort->addItem(allTeachOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->teach_sort->currentIndex() < 0) {
            createDefaultSortOrder(TEACH);
            ui->teach_sort->addItem(allTeachOrders[0][0]);
        }

        // create the tree
        teachPath = path;
        makeTree(TEACH);
        ui->teach_file_label->setText(teachPath);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid teaching file.");
            on_teach_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_pub_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_pub(path);
    }
}

bool MainWindow::load_pub(QString path, bool multi_file) {
    if (!checkFile(PUBLICATIONS, path)) {
        //add team lynx
        // enable gui elements
        ui->pub_sort->setEnabled(true);
        ui->pub_delete_sort->setEnabled(true);
        ui->pub_new_sort->setEnabled(true);
        ui->pub_filter_from->setEnabled(true);
        ui->pub_filter_to->setEnabled(true);
        ui->pub_pie_button->setEnabled(true);
        ui->pub_bar_button->setEnabled(true);
        ui->pub_line_button->setEnabled(true);
        ui->pub_scatter_button->setEnabled(true);
        ui->pub_to_label->setEnabled(true);
        ui->pub_sort_label->setEnabled(true);
        ui->pub_filter->setEnabled(true);
        ui->pub_filter_label->setEnabled(true);

        // load save order
        QSortListIO pubSaveOrder(PUBORDER_SAVE);
        allPubOrders = pubSaveOrder.readList();
        ui->pub_sort->clear();
        for (int i = 0; i < allPubOrders.size(); i++) {
            ui->pub_sort->addItem(allPubOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->pub_sort->currentIndex() < 0) {
            createDefaultSortOrder(PUBLICATIONS);
            ui->pub_sort->addItem(allPubOrders[0][0]);
        }

        // create the tree
        pubPath = path;
        makeTree(PUBLICATIONS);
        ui->pub_file_label->setText(pubPath);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid publications file.");
            on_pub_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_pres_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_pres(path);
    }
}

bool MainWindow::load_pres(QString path, bool multi_file) {
    if (!checkFile(PRESENTATIONS, path)) {
        //add team lynx
        // enable gui elements
        ui->pres_sort->setEnabled(true);
        ui->pres_delete_sort->setEnabled(true);
        ui->pres_new_sort->setEnabled(true);
        ui->pres_filter_from->setEnabled(true);
        ui->pres_filter_to->setEnabled(true);
        ui->pres_pie_button->setEnabled(true);
        ui->pres_bar_button->setEnabled(true);
        ui->pres_line_button->setEnabled(true);
        ui->pres_scatter_button->setEnabled(true);
        ui->pres_to_label->setEnabled(true);
        ui->pres_sort_label->setEnabled(true);
        ui->pres_filter->setEnabled(true);
        ui->pres_filter_label->setEnabled(true);

        // load save order
        QSortListIO presSaveOrder(PRESORDER_SAVE);
        allPresOrders = presSaveOrder.readList();
        ui->pres_sort->clear();
        for (int i = 0; i < allPresOrders.size(); i++) {
            ui->pres_sort->addItem(allPresOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->pres_sort->currentIndex() < 0) {
            createDefaultSortOrder(PRESENTATIONS);
            ui->pres_sort->addItem(allPresOrders[0][0]);
        }

        // create the tree
        presPath = path;
        makeTree(PRESENTATIONS);
        ui->pres_file_label->setText(presPath);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid presentations file.");
            on_pres_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_fund_load_file_clicked() {
    QString path = load_file();
    if (!path.isEmpty()) {
        load_fund(path);
    }
}

bool MainWindow::load_fund(QString path, bool multi_file) {
    if (!checkFile(FUNDING, path)) {
        //add team lynx
        // enable gui elements
        ui->fund_sort->setEnabled(true);
        ui->fund_delete_sort->setEnabled(true);
        ui->fund_new_sort->setEnabled(true);
        ui->fund_filter_from->setEnabled(true);
        ui->fund_filter_to->setEnabled(true);
        ui->fund_pie_button->setEnabled(true);
        ui->fund_bar_button->setEnabled(true);
        ui->fund_line_button->setEnabled(true);
        ui->fund_scatter_button->setEnabled(true);
        ui->fund_to_label->setEnabled(true);
        ui->fund_sort_label->setEnabled(true);
        ui->fund_filter->setEnabled(true);
        ui->fund_filter_label->setEnabled(true);

        // load save order
        QSortListIO fundSaveOrder(FUNDORDER_SAVE);
        allFundOrders = fundSaveOrder.readList();
        ui->fund_sort->clear();
        for (int i = 0; i < allFundOrders.size(); i++) {
            ui->fund_sort->addItem(allFundOrders.at(i).at(0));
        }

        // create default sort order if none are loaded
        if (ui->fund_sort->currentIndex() < 0) {
            createDefaultSortOrder(FUNDING);
            ui->fund_sort->addItem(allFundOrders[0][0]);
        }

        // create the tree
        fundPath = path;
        makeTree(FUNDING);
        ui->fund_file_label->setText(fundPath);

        return true;
    } else {
        if (!multi_file) {
            QMessageBox::critical(this, "Invalid File", "Not a valid grants and funding file.");
            on_fund_load_file_clicked();
        }
    }
    return false;
}

void MainWindow::on_FromDate_dateChanged(const QDate &date) {
    // set the member variable to the new date
    yearStart = date.year();

    // update end date spinbox to not fall below that year
    ui->ToDate->setMinimumDate(date);

    dateChanged = {true, true, true, true};

    // refresh the GUI
    refresh(ui->categoryTab->currentIndex());
}

void MainWindow::on_ToDate_dateChanged(const QDate &date) {
    // set the member variable to the new date
    yearEnd = date.year();

    // update end date spinbox to not fall below that year
    ui->ToDate->setMinimumDate(ui->FromDate->date());

    dateChanged = {true, true, true, true};

    // refresh the GUI
    refresh(ui->categoryTab->currentIndex());
}

void MainWindow::on_categoryTab_currentChanged() {
    if (dateChanged[ui->categoryTab->currentIndex()] == true) {
        refresh(ui->categoryTab->currentIndex());
        dateChanged[ui->categoryTab->currentIndex()] = false;
    }
}

void MainWindow::on_teachTreeView_clicked() {
    QItemSelectionModel *selection = ui->teachTreeView->selectionModel();
    QModelIndexList indexes = selection->selectedRows(0);
    QString graphName, names;
    std::vector<std::string> parents;
    std::vector<std::vector<std::string>> parentsList;

    foreach(QModelIndex current, indexes) {
        graphName.append(current.data(Qt::DisplayRole).toString()).append("\n");
        while (true) {
            names = current.data(Qt::DisplayRole).toString();
            if(names!="") {
                auto it = parents.begin();
                it = parents.insert(it, names.toStdString());
            } else {
                break;
            }
            current = current.parent();
        }
        auto it = parentsList.begin();
        it = parentsList.insert(it, parents);
        parents.clear();
    }

    std::vector<std::pair <std::string, int>> list;
    std::vector<std::pair <std::string, double>> chartList;
    std::pair<std::string, double> pair;

    foreach(std::vector<std::string> par, parentsList) {
        std::vector<std::string> sortOrder(teachSortOrder.begin(), teachSortOrder.begin()+par.size()+1);
        list = teachdb->getCountTuple(yearStart, yearEnd, sortOrder, par, getFilterStartChar(TEACH), getFilterEndChar(TEACH));
        int size;
        for (int i = 0; i < (int) list.size(); i++) {
            pair = std::make_pair (list[i].first, static_cast<double>(list[i].second));
            if (chartList.empty()) {
              chartList.emplace_back(pair);
            }
            else {
                size = chartList.size();
                for (int j = 0; j < size; j++) {
                        if (chartList[j].first == list[i].first){
                            chartList[j].second += list[i].second;
                            break;
                        }
                        else{
                            if(j==size-1)
                               chartList.emplace_back(pair);
                        }
                }
            }
        }
    }

    if (!chartList.empty()) {
       ui->teachBarChart->clearPlottables();
       setupBarChart(ui->teachBarChart, chartList);
       ui->teachBarChart->replot();
       //add team lynx
       ui->teachLineChart->clearPlottables();
       setupLineChart(ui->teachLineChart, chartList);
       ui->teachLineChart->replot();
       //add team lynx
       ui->teachScatterChart->clearPlottables();
       setupScatterChart(ui->teachScatterChart, chartList);
       ui->teachScatterChart->replot();
       setupPieChart(ui->teachPieChart, ui->teachPieList, chartList);
       ui->teachGraphTitle->setText("Total for: " + graphName + "Teaching by " + QString::fromStdString(teachSortOrder[parentsList[0].size()]));
       ui->teach_graph_stackedWidget->show();
    }
}

void MainWindow::on_pubTreeView_clicked() {
    QItemSelectionModel *selection = ui->pubTreeView->selectionModel();
    QModelIndexList indexes = selection->selectedRows(0);
    QString graphName, names;
    std::vector<std::string> parents;
    std::vector<std::vector<std::string>> parentsList;

    foreach(QModelIndex current, indexes) {
        graphName.append(current.data(Qt::DisplayRole).toString()).append("\n");
        while (true) {
            names = current.data(Qt::DisplayRole).toString();
            if(names!="") {
                auto it = parents.begin();
                it = parents.insert(it, names.toStdString());
            } else {
                break;
            }
            current = current.parent();
        }
        auto it = parentsList.begin();
        it = parentsList.insert(it, parents);
        parents.clear();
    }

    std::vector<std::pair <std::string, int>> list;
    std::vector<std::pair <std::string, double>> chartList;
    std::pair<std::string, double> pair;

    foreach(std::vector<std::string> par, parentsList) {
        std::vector<std::string> sortOrder(pubSortOrder.begin(), pubSortOrder.begin()+par.size()+1);
        list = pubdb->getCountTuple(yearStart, yearEnd, sortOrder, par, getFilterStartChar(PUBLICATIONS), getFilterEndChar(PUBLICATIONS));
        int size;
        for (int i = 0; i < (int) list.size(); i++) {
            pair = std::make_pair (list[i].first, static_cast<double>(list[i].second));
            if (chartList.empty()) {
              chartList.emplace_back(pair);
            }
            else {
                size = chartList.size();
                for (int j = 0; j < size; j++) {
                        if (chartList[j].first == list[i].first){
                            chartList[j].second += list[i].second;
                            break;
                        }
                        else{
                            if(j==size-1)
                               chartList.emplace_back(pair);
                        }
                }
            }
        }
    }

    if (!chartList.empty()) {
       ui->pubBarChart->clearPlottables();
       setupBarChart(ui->pubBarChart, chartList);
       ui->pubBarChart->replot();
       //add team lynx
       ui->pubLineChart->clearPlottables();
       setupLineChart(ui->pubLineChart, chartList);
       ui->pubLineChart->replot();
       //add team lynx
       ui->pubScatterChart->clearPlottables();
       setupScatterChart(ui->pubScatterChart, chartList);
       ui->pubScatterChart->replot();
       setupPieChart(ui->pubPieChart, ui->pubPieList, chartList);
       ui->pubGraphTitle->setText("Total for: " + graphName + "Publications by " + QString::fromStdString(pubSortOrder[parentsList[0].size()]));
       ui->pub_graph_stackedWidget->show();
    }
}

void MainWindow::on_presTreeView_clicked() {
    QItemSelectionModel *selection = ui->presTreeView->selectionModel();
    QModelIndexList indexes = selection->selectedRows(0);
    QString graphName, names;
    std::vector<std::string> parents;
    std::vector<std::vector<std::string>> parentsList;

    foreach(QModelIndex current, indexes) {
        graphName.append(current.data(Qt::DisplayRole).toString()).append("\n");
        while (true) {
            names = current.data(Qt::DisplayRole).toString();
            if(names!="") {
                auto it = parents.begin();
                it = parents.insert(it, names.toStdString());
            } else {
                break;
            }
            current = current.parent();
        }
        auto it = parentsList.begin();
        it = parentsList.insert(it, parents);
        parents.clear();
    }

    std::vector<std::pair <std::string, int>> list;
    std::vector<std::pair <std::string, double>> chartList;
    std::pair<std::string, double> pair;

    foreach(std::vector<std::string> par, parentsList) {
        std::vector<std::string> sortOrder(presSortOrder.begin(), presSortOrder.begin()+par.size()+1);
        list = presdb->getCountTuple(yearStart, yearEnd, sortOrder, par, getFilterStartChar(PRESENTATIONS), getFilterEndChar(PRESENTATIONS));
        int size;
        for (int i = 0; i < (int) list.size(); i++) {
            pair = std::make_pair (list[i].first, static_cast<double>(list[i].second));
            if (chartList.empty()) {
              chartList.emplace_back(pair);
            }
            else {
                size = chartList.size();
                for (int j = 0; j < size; j++) {
                        if (chartList[j].first == list[i].first){
                            chartList[j].second += list[i].second;
                            break;
                        }
                        else{
                            if(j==size-1)
                               chartList.emplace_back(pair);
                        }
                }
            }
        }
    }

    if (!chartList.empty()) {
       ui->presBarChart->clearPlottables();
       setupBarChart(ui->presBarChart, chartList);
       ui->presBarChart->replot();
       //add team lynx
       ui->presLineChart->clearPlottables();
       setupLineChart(ui->presLineChart, chartList);
       ui->presLineChart->replot();
       //add team lynx
       ui->presScatterChart->clearPlottables();
       setupScatterChart(ui->presScatterChart, chartList);
       ui->presScatterChart->replot();
       setupPieChart(ui->presPieChart, ui->presPieList, chartList);
       ui->presGraphTitle->setText("Total for: " + graphName + "Presentations by " + QString::fromStdString(presSortOrder[parentsList[0].size()]));
       ui->pres_graph_stackedWidget->show();
    }
}

void MainWindow::on_fundTreeView_clicked() {
    QItemSelectionModel *selection = ui->fundTreeView->selectionModel();
    QModelIndexList indexes = selection->selectedRows(0);
    QString graphName, names;
    std::vector<std::string> parents;
    std::vector<std::vector<std::string>> parentsList;

    foreach(QModelIndex current, indexes) {
        graphName.append(current.data(Qt::DisplayRole).toString()).append("\n");
        while (true) {
            names = current.data(Qt::DisplayRole).toString();
            if(names!="") {
                auto it = parents.begin();
                it = parents.insert(it, names.toStdString());
            } else {
                break;
            }
            current = current.parent();
        }
        auto it = parentsList.begin();
        it = parentsList.insert(it, parents);
        parents.clear();
    }

    std::vector<std::pair <std::string, int>> list;
    std::vector<std::pair <std::string, double>> chartList;
    std::pair<std::string, double> pair;

    foreach(std::vector<std::string> par, parentsList) {
        std::vector<std::string> sortOrder(fundSortOrder.begin(), fundSortOrder.begin()+par.size()+1);
        list = funddb->getCountTuple(yearStart, yearEnd, sortOrder, par, getFilterStartChar(FUNDING), getFilterEndChar(FUNDING));
        int size;
        for (int i = 0; i < (int) list.size(); i++) {
            pair = std::make_pair (list[i].first, static_cast<double>(list[i].second));
            if (chartList.empty()) {
              chartList.emplace_back(pair);
            }
            else {
                size = chartList.size();
                for (int j = 0; j < size; j++) {
                        if (chartList[j].first == list[i].first){
                            chartList[j].second += list[i].second;
                            break;
                        }
                        else{
                            if(j==size-1)
                               chartList.emplace_back(pair);
                        }
                }
            }
        }
    }

    if (!chartList.empty()) {
       ui->fundBarChart->clearPlottables();
       setupBarChart(ui->fundBarChart, chartList);
       ui->fundBarChart->replot();
       //add team lynx
       ui->fundLineChart->clearPlottables();
       setupLineChart(ui->fundLineChart, chartList);
       ui->fundLineChart->replot();
       //add team lynx
       ui->fundScatterChart->clearPlottables();
       setupScatterChart(ui->fundScatterChart, chartList);
       ui->fundScatterChart->replot();
       setupPieChart(ui->fundPieChart, ui->fundPieList, chartList);
       ui->fundGraphTitle->setText("Total for: " + graphName + "Funding by " + QString::fromStdString(fundSortOrder[parentsList[0].size()]));
       ui->fund_graph_stackedWidget->show();
    }
}

void MainWindow::on_teachPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->teachChartFrame->render(&painter);
    }
}

void MainWindow::on_fundPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->fundChartFrame->render(&painter);
    }
}

void MainWindow::on_presPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->presChartFrame->render(&painter);
    }
}

void MainWindow::on_pubPrintButton_clicked()
{
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QCPPainter painter;
        painter.begin(printer);
        ui->pubChartFrame->render(&painter);
    }
}

void MainWindow::on_teachExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->teachChartFrame->render(&painter);
        /* Another option for bar chart since it is QCustom plot
        if (ui->teach_bar_button->isChecked()) {
            ui->teachBarChart->savePdf(fileName);
        } */
    }

}

void MainWindow::on_fundExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->fundChartFrame->render(&painter);
    }
}

void MainWindow::on_presExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->presChartFrame->render(&painter);
    }
}

void MainWindow::on_pubExportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                    QDir::homePath(),
                                                    tr("PDF (*.pdf)"));
    if (fileName.contains("") != 0) {
        QPdfWriter writer(fileName);
        writer.setPageOrientation(QPageLayout::Landscape);
        QPainter painter;
        painter.begin(&writer);
        painter.scale(10.0, 10.0);
        ui->pubChartFrame->render(&painter);
    }
}


char MainWindow::getFilterStartChar(int type) {
    char charInField;

    // get char from the text field
    switch (type) {
    case FUNDING:
        charInField = ui->fund_filter_from->text().toStdString()[0];
        break;
    case PRESENTATIONS:
        charInField = ui->pres_filter_from->text().toStdString()[0];
        break;
    case PUBLICATIONS:
        charInField = ui->pub_filter_from->text().toStdString()[0];
        break;
    case TEACH:
        charInField = ui->teach_filter_from->text().toStdString()[0];
        break;
    }

    // convert the char to uppercase
    char uppercase = charInField & ~0x20;

    // if alphabetical, return that letter
    if ('A' <= uppercase && uppercase <= 'Z') {
        return uppercase;
    } else {
        // otherwise, default is '*'
        return '*';
    }
}

char MainWindow::getFilterEndChar(int type) {
    char charInField;

    // get char from the text field
    switch (type) {
    case FUNDING:
        charInField = ui->fund_filter_to->text().toStdString()[0];
        break;
    case PRESENTATIONS:
        charInField = ui->pres_filter_to->text().toStdString()[0];
        break;
    case PUBLICATIONS:
        charInField = ui->pub_filter_to->text().toStdString()[0];
        break;
    case TEACH:
        charInField = ui->teach_filter_to->text().toStdString()[0];
        break;
    }

    // convert the char to uppercase
    char uppercase = charInField & ~0x20;

    // if alphabetical, return that letter
    if ('A' <= uppercase && uppercase <= 'Z') {
        return uppercase;
    } else if (charInField == '*') {
        // otherwise, is it '*'?
        return charInField;
    } else {
        // otherwise, default is 'Z'
        return 'Z';
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*if (this->teachPath.isEmpty() && this->pubPath.isEmpty() && this->presPath.isEmpty() && this->fundPath.isEmpty()) {
        event->accept();
        return;
    }*/
    QMessageBox prompt;
    prompt.setText("Would you like to save the current session?");
    prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    prompt.setDefaultButton(QMessageBox::Yes);
    prompt.setWindowIcon(QIcon(":/icon32.ico"));
    int execValue = prompt.exec();
    if (execValue == QMessageBox::Yes) {
        //Save file paths of each of the four tabs to a QFile before closing application.
        QString filename = "session.dat";
        QFile sessionFile(filename);
        sessionFile.remove();
        if (sessionFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream stream(&sessionFile);
            stream << ui->FromDate->date().year() << endl << ui->ToDate->date().year() << endl;
            stream << this->teachPath << endl;
            //column width
            stream << ui->teachTreeView->columnWidth(0) << endl;
            stream << ui->teachTreeView->columnWidth(1) << endl;
            stream << ui->teachTreeView->columnWidth(2) << endl;
            stream << ui->teachTreeView->columnWidth(3) << endl;
            stream << ui->teach_sort->currentIndex() << endl;

            stream << this->pubPath << endl;
            stream << ui->pubTreeView->columnWidth(0) << endl;
            stream << ui->pubTreeView->columnWidth(1) << endl;
            stream << ui->pub_sort->currentIndex() << endl;

            stream << this->presPath << endl;
            stream << ui->presTreeView->columnWidth(0) << endl;
            stream << ui->presTreeView->columnWidth(1) << endl;
            stream << ui->pres_sort->currentIndex() << endl;

            stream << this->fundPath << endl;
            stream << ui->fundTreeView->columnWidth(0) << endl;
            stream << ui->fundTreeView->columnWidth(1) << endl;
            stream << ui->fundTreeView->columnWidth(2) << endl;
            stream << ui->fund_sort->currentIndex() << endl;

        }
        sessionFile.close();
        event->accept();
    }
    if (execValue == QMessageBox::No) {
        QString filename = "session.dat";
        QFile sessionFile(filename);
        sessionFile.remove();
        event->accept();
    }
}

void MainWindow::on_teach_filter_from_textChanged() { refresh(TEACH);}
void MainWindow::on_teach_filter_to_textChanged() { refresh(TEACH);}
void MainWindow::on_pub_filter_from_textChanged() { refresh(PUBLICATIONS);}
void MainWindow::on_pub_filter_to_textChanged() { refresh(PUBLICATIONS);}
void MainWindow::on_pres_filter_from_textChanged() { refresh(PRESENTATIONS);}
void MainWindow::on_pres_filter_to_textChanged() { refresh(PRESENTATIONS);}
void MainWindow::on_fund_filter_from_textChanged() { refresh(FUNDING);}
void MainWindow::on_fund_filter_to_textChanged() { refresh(FUNDING);}



