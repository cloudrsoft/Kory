#ifndef WRITE_H
#define WRITE_H

#include <QtCore>
#include <openssl/aes.h>

class write
    {
    public:
        write();
        bool writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, QString Lang, QString Type);
};

#endif // WRITE_H
