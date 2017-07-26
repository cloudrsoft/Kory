#ifndef WRITE_H
#define WRITE_H

#include <QtCore>

class write
    {
    public:
        write();
        bool writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, QString Lang, QString Type, int Mind, QString Others);
        //bool writeOthers(QString source_dir, QString filetype, QString filename)
};

#endif // WRITE_H
