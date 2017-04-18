#include "Qtest.h"

void QTestSortList::QSORT_LIST_01() {
    QSortListIO sorter("NO FILE");
    QList<QStringList> list = sorter.readList();
    QVERIFY(list.size() == 0);
}

void QTestSortList::QSORT_LIST_02() {
    QSortListIO sorter("../Project Information/Sample Data/Grants_expanded.csv");
    QList<QStringList> list = sorter.readList();
    QVERIFY(list.size() == 0);
}

void QTestSortList::QSORT_LIST_03() {
    ofstream myfile;
      myfile.open ("testfile.txt");
      myfile << "testdata";
      myfile.close();
    QSortListIO sorter("testfile.txt");
    QList<QStringList> list = sorter.readList();
    QVERIFY(list.size() == 0);
}

void QTestCSVReader::QCSV_READER_TEST_01() {
    CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_02() {
    CSVReader reader("../Project Information/Sample Data/GrantsClinicalFunding_sample.csv");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_03() {
    CSVReader reader("../Project Information/Sample Data/Presentations_expanded.csv");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_04() {
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_05() {
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_06() {
    CSVReader reader("NO FILE");
    vector<string> header = reader.getHeaders();
    QVERIFY(header.size() == 0);
}

void QTestCSVReader::QCSV_READER_TEST_07() {
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
    vector< vector<string> > all_data = reader.getData();
    QVERIFY(all_data.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_08() {
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    vector< vector<string> > all_data = reader.getData();
    QVERIFY(all_data.size() != 0);
}

void QTestCSVReader::QCSV_READER_TEST_09() {
    CSVReader reader("../Project Information/STAR 2015 Acuity STAR Western CS intro V2.pptx");
    vector< vector<string> > all_data = reader.getData();
    QVERIFY(all_data.size() == 0);
}
