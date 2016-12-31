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
};

#endif // READ_H
