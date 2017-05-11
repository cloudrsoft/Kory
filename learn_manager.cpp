#include "learn_manager.h"

Learn_Manager::Learn_Manager()
{

}

QStringList Learn_Manager::getList(QString file)
{
    QStringList returnList;

    QFile input(file);
    if(input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&input);
        while (!in.atEnd())
        {
            returnList.append(in.readLine());
        }
        input.close();
        return returnList;
    }

    return QStringList();
}

void Learn_Manager::learn(QString data, QString dir)
{
    QStringList learn = data.split("%NEXT%");

    write *db = new write;
    db->writeFile(dir, learn.at(0), learn.at(1), QString(learn.at(2)).split("|"), QString(learn.at(3)).toInt(), QString(learn.at(4)).toInt());
}

void Learn_Manager::learnFromFile(QString file, QString dir)
{
    QDir tmp_dir;

    if(!tmp_dir.exists(dir))
        tmp_dir.mkdir(dir);

    QStringList stringList = getList(file);

    for(int i = 0; i < stringList.size(); i++)
    {
        learn(stringList.at(i), dir);
    }
}

void Learn_Manager::makeFile(QString filePath, QString dir, int lang)
{
    read *db = new read;
    QStringList fileList = db->getAllFileName(dir, lang);

   QStringList stringList;

   for(int i = 0; i < fileList.size(); i++)
   {
       QStringList replyList;

       for(int a = 0; a < db->getReplySize(fileList.at(i)); a++)
       {
           replyList.append(db->getReply(fileList.at(i), a));
       }

       stringList.append(db->getFileType(fileList.at(i)) + "%NEXT%" + db->getFileName(fileList.at(i)) + "%NEXT%" + replyList.join("|") + "%NEXT%" + QString::number(db->getLang(fileList.at(i))) + "%NEXT%" + QString::number(db->getType(fileList.at(i))));
   }

   QFile file(filePath);

   if(file.open(QIODevice::ReadWrite | QIODevice::Text))
   {
       QTextStream in(&file);
       for(int i = 0; i < stringList.size(); i++)
       {
           in << stringList.at(i) << endl;
       }
       file.close();
       return;
   }

   return;
}
