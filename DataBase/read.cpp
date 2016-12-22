#include "read.h"

namespace ProjectAIDB
{

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

    int read::getLang(QString fileName)
    {
        return QString(readFile(fileName).at(3));
    }

    /* 서브 함수 */

    QStringList read::readFile(QString fileName)
    {
        if(fileExists(fileName))
        {
            QFile file(getFileLocal(fileName));
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
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
        }else{
            return QStringList();
        }
    }

    bool read::fileExists(QString fileName)
    {
        QDirIterator dirIt("db",QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() == fileName)
            return true;
        }
        return false;
    }

    QString read::getFileLocal(QString fileName)
    {
        QDirIterator dirIt("db",QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() == fileName)
            return dirIt.filePath();
        }
        return QString();
    }

    QStringList read::getAllFileName()
    {
        QStringList fileList;
        QDirIterator dirIt("db",QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
            fileList.append(dirIt.fileName());
        }
        return fileList;
    }
}
