#include "write.h"

    write::write()
    {

    }

    bool write::writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, int Lang, QString Type)
    {
        QDir dir;
        QString dir_name;
        QString lang_string;

        switch(Lang)
        {
            case LANGUAGE_DEFAULT:
                lang_string = language_string.at(Lang);
                break;

            case LANGUAGE_ENGLISH:
                lang_string = language_string.at(Lang);
                break;

            case LANGUAGE_KOREAN:
                lang_string = language_string.at(Lang);
                break;

            default:
                break;
        }

        dir_name = source_dir + "/" + lang_string + "/";

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

        tempStream << filetype + "\n" << filename + "\n" << reply_string + "\n" << QString::number(Lang) + "\n" << Type;

        /*QString tempString = tempStream.readAll();
        unsigned char in[] = (unsigned char)(tempString.toStdString().c_str());
        //strcpy( static_cast <char*>(in), tempString.toStdString().c_str());
        unsigned char out[10];

        AES_set_encrypt_key(key32, 32, &aes_ks3);

        AES_encrypt(in, out, &aes_ks3);

        file.write(out);*/

        if(file.readAll().isEmpty()) // check file
        {
            return false;
        }
        file.close();
        return true;
    }
