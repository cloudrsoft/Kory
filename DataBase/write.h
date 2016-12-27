#ifndef WRITE_H
#define WRITE_H

#include <QtCore>
#include <openssl/aes.h>

class write
    {
    public:
        write();
        bool writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, int Lang, int Type);

        enum{
            LANGUAGE_DEFAULT,
            LANGUAGE_ENGLISH,
            LANGUAGE_KOREAN,
        };

        enum{
            /* Default */
            SUBJECT,
            DIRECT_OBJECT,
            VERB,
            COMPLEMENT,
            OTHERS,
            /* Target */
            MY, // 인공지능을 대상으로
            TARGET, // 말하는 상대방을 대상으로
            /* Assistant */
            WEATHER_AREA,
            GET_WEATHER
        };

        QStringList language_string = QStringList() << "default" << "eng" << "kor";
};

#endif // WRITE_H
