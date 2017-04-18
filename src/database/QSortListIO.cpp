#include <QDataStream>
#include <QFile>
#include <QStringList>

#include "QSortListIO.h"

QSortListIO::QSortListIO(std::string _filename)
{
    filename = _filename;
}

void QSortListIO::saveList(QList<QStringList> sortFields)
{
    // open the file for writing
    QFile file(filename.c_str());
    file.open(QIODevice::WriteOnly);

    // we will serialize the data into the file
    QDataStream out(&file);

    // serialize the sort fields
    out << sortFields;

    // close the file, we're done
    file.close();
}

QList<QStringList> QSortListIO::readList()
{
    QList<QStringList> sortFields;
    // open the file for reading
    QFile file(filename.c_str());
    try {
        file.open(QIODevice::ReadOnly);

        // read the data serialized from the file
        QDataStream in(&file);

        // extract sort fields
        in >> sortFields;

        // close the file, we're done
        file.close();

        return sortFields;
    } catch (const std::bad_alloc &) {
        return sortFields;
    }
}
