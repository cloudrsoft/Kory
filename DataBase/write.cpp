#include "write.h"

    write::write()
    {

    }

    bool write::writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, QString Lang, QString Type, int Mind, QString Others)
    {
        QDir dir;
        QString dir_name;

        dir_name = source_dir + "/" + Lang + "/";

        if(!dir.exists(dir_name))
            dir.mkdir(dir_name);

        if(!dir.exists(dir_name + filetype)){
            dir.mkdir(dir_name + filetype); // make dir filetype
        }
        QFile file(dir_name + filetype + "/" + filename);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) // if can not open file
        {
            return false;
        }
        if(!file.readAll().isEmpty()){ // if file is not empty
            file.remove();
            if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) // if can not open file
            {
                return false;
            }
        }

        QString reply_string;
        for(int i = 0; i < Reply.size(); i++)
        {
            if(i == 0)
                reply_string.append(Reply.at(i));
            else
                reply_string.append("|" + Reply.at(i));
        }

        QTextStream tempStream(&file);

        tempStream << filetype + "\n" << filename + "\n" << reply_string + "\n" << Lang + "\n" << Type + "\n" << QString::number(Mind) + "\n" << Others;

        if(file.readAll().isEmpty()) // check file
        {
            return false;
        }
        file.close();
        return true;
    }
