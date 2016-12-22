#ifndef READ_H
#define READ_H

#include <QtCore>
#include <openssl/aes.h>

namespace ProjectAIDB
{

    class read
    {
    public:

        read();
        QString getFileType(QString fileName); // 파일 타입 가져오기
        QString getFileName(QString fileName); // 파일 이름 가져오기
        QString getReply(QString fileName, int at); // 대답 가져오기
        int getLang(QString fileName); // 언어 가져오기

        QStringList readFile(QString fileName);
        bool fileExists(QString fileName);
        QString getFileLocal(QString fileName);
        QStringList getAllFileName();
    };

}

#endif // READ_H
