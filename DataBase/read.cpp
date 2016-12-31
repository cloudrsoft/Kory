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

    int read::getLang(QString fileName)
    {
        return QString(readFile(fileName).at(3)).toInt();
    }

    int read::getType(QString fileName)
    {
        return QString(readFile(fileName).at(4)).toInt();
    }

    /* 서브 함수 */

    QStringList read::readFile(QString fileName)
    {
        QFile file(fileName);
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
    }

    QStringList read::getAllFileName(QString source_dir, int lang)
    {
        QStringList fileList;
        write *db = new write;
        QDirIterator dirIt(source_dir + "/" + db->language_string.at(lang),QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).fileName() != "_FILETYPE")
                fileList.append(dirIt.filePath());
        }
        return fileList;
    }
