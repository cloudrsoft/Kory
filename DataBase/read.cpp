#include "read.h"

    read::read()
    {

    }

    /* 메인 함수 */

    QString read::getFileType(QString fileName)
    {
        return readFile(fileName).at(0);
    }

    QString read::getFileName(QString fileName)
    {
        return readFile(fileName).at(1);
    }

    QString read::getReply(QString fileName, int at)
    {
        return QString(readFile(fileName).at(2)).split("|").at(at);
    }

    int read::getReplySize(QString fileName)
    {
        return QString(readFile(fileName).at(2)).split("|").size();
    }

    QString read::getLang(QString fileName)
    {
        return QString(readFile(fileName).at(3));
    }

    QString read::getType(QString fileName)
    {
        return QString(readFile(fileName).at(4));
    }

    int read::getMind(QString fileName)
    {
        return QString(readFile(fileName).at(5)).toInt();
    }

    QString read::getOthers(QString fileName)
    {
        return QString(readFile(fileName).at(6));
    }

    /* 서브 함수 */

    QStringList read::readFile(QString fileName)
    {
        QFile file(fileName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug() << fileName;
                file.close();
                return QStringList();
            }
            QTextStream textStream(&file);
            QStringList data;
            while(true)
            {
                QString line = textStream.readLine();
                if(line.isNull())
                    break;
                else
                    data.append(line);
            }
            file.close();
            return data;
    }

    QStringList read::getAllFileName(QString source_dir, QString lang)
    {
        QStringList fileList;
        QDirIterator dirIt(source_dir + "/" + lang,QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
                fileList.append(dirIt.filePath());
        }
        return fileList;
    }

    QString read::searchFile(QString source_dir, QString fileName, QString lang)
    {
        QDirIterator dirIt(source_dir + "/" + lang,QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
            if (QFileInfo(dirIt.filePath()).fileName() == fileName)
                return dirIt.filePath();
        }
        return QString();
    }

    QString read::randomBadReply(QString source_dir, QString lang)
    {
        QStringList fileList;
        QString targetFile;
        QDirIterator dirIt(source_dir + "/" + lang,QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
            if (strstr(dirIt.filePath().toStdString().c_str(), "_BADS") != NULL)
                fileList.append(dirIt.filePath());
        }

        targetFile = fileList.at(rand() % fileList.size());

        return getReply(targetFile, rand() % getReplySize(targetFile));
    }

    QString read::searchFileFromType(QString source_dir, QString type, QString lang)
    {
        QDirIterator dirIt(source_dir + "/" + lang,QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
            if (getType(dirIt.filePath()) == type)
                return QFileInfo(dirIt.filePath()).fileName();
        }
        return QString();
    }
