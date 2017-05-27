#ifndef WRITE_H
#define WRITE_H

#include <QtCore>
#include <openssl/aes.h>

class write
    {
    public:
        write();
        bool writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, int Lang, QString Type);

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
            UNKNOWN,
            /* Target */
            MY, // 인공지능을 대상으로
            TARGET, // 말하는 상대방을 대상으로
            /* Feeling */
            GOODS,
            BADS,
            /* Assistant */
            WEATHER_AREA,
            GET_WEATHER,
            SEARCH,
            CALENDAR,
            WITH
        };

        const char *char_list[4096] = {"text.subject",
                                 "text.direct_object",
                                 "text.verb",
                                 "text.complement",
                                 "ai.others",
                                 "ai.unknown",
                                 "target.my",
                                 "target.target",
                                 "feel.good",
                                 "feel.bad",
                                 "weather.area",
                                 "weather.get",
                                 "google.search",
                                 "life.calendar",
                                 "target.with"};

        QStringList language_string = QStringList() << "default" << "eng" << "kor";
};

#endif // WRITE_H
