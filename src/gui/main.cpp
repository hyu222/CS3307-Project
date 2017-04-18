#include <iostream>
#include <stdio.h>
#include <QApplication>
#include <QTreeView>
#include "gui/mainwindow.h"
#include "database/TestCSVReader.h"
#include "tests/Qtest.h"
using namespace std;

int main(int argc, char *argv[]) {
    int test = 0;   /* test on */

    if (test) {
        // CSVReader Test Cases
        QTestCSVReader *csv_test = new QTestCSVReader();
        QTest::qExec(csv_test);
        // SortList Cases
        QTestSortList *sort_test = new QTestSortList();
        QTest::qExec(sort_test);
    }


    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
