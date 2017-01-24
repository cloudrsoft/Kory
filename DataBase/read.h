#ifndef READ_H
#define READ_H

#include <QtCore>
#include <openssl/aes.h>
#include <write.h>

class read
    {
    public:

        read();
        QString getFileType(QString fileName); // 파일 타입 가져오기
        QString getFileName(QString fileName); // 파일 이름 가져오기
        QString getReply(QString fileName, int at); // 대답 가져오기
        int getReplySize(QString fileName); // 대답을 List 로 가져올때 Size
        int getLang(QString fileName); // 언어 가져오기
        int getType(QString fileName); // 타입 가져오기

        QStringList readFile(QString fileName);
        QStringList getAllFileName(QString source_dir,int lang = write::LANGUAGE_DEFAULT);
        QString searchFile(QString source_dir, QString fileName, int lang);
        QString randomBadReply(QString source_dir, int lang); // 안좋은말을 랜덤으로 골라내기
        QString searchFileFromType(QString source_dir, int type, int lang);
};

#endif // READ_H
