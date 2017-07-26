#ifndef LEARN_MANAGER_H
#define LEARN_MANAGER_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>

#include <write.h>
#include <read.h>

class Learn_Manager
{
public:
    Learn_Manager();
    QStringList getList(QString file);
    void learn(QString data, QString dir);
    void learnFromFile(QString file, QString dir);

    void makeFile(QString filePath, QString dir, QString lang);
};

#endif // LEARN_MANAGER_H
