#include "core.h"

core::core()
{

}

QString core::getAI(QString m_target, int lang)
{
    read *db = new read();

    QString returnString;
    QStringList fileList = db->getAllFileName("db", lang);

    /* 문자열 처리 */

    QStringList stringList; // 단어별로 문장을 분리해서 처리할때 사용
    QList<QStringList> replyList; // Reply 를 가져오기
    QList<int> sentenceList; // SUBJECT 같은 ENUM 으로 선언된 문장의 Type을 담는데 사용

    /* 메인 코드 */

    for(int i = 0; i < fileList.size(); i++)
    {
        if(strstr(m_target.toStdString().c_str(), db->getFileName(fileList.at(i)).toStdString().c_str()))
        {
            stringList.append(db->getFileName(fileList.at(i)).toStdString().c_str());
            sentenceList.append(db->getType(fileList.at(i)));
            QStringList tempList;
            for(int a = 0; a < db->getReplySize(fileList.at(i)); a++)
            {
                tempList.append(db->getReply(fileList.at(i), a));
            }
            replyList.append(tempList);
        }
    }

    /* 인공지능 처리에 필요한 변수 */
    int Target = 0;


    for(int i = 0; i < stringList.size(); i++)
    {
        if(sentenceList.at(i) == write::MY)
            Target = write::MY;
        else if(sentenceList.at(i) == write::TARGET)
            Target = write::TARGET;

        /* Weather 처리 */
        if(sentenceList.at(i) == write::WEATHER_AREA)
        {
            QString location = replyList.at(i).join(QString());
            Weather *weather = new Weather(0, WEATHER_API_KEY, (int)QString(location.split(",").first()).toDouble(), (int)QString(location.split(",").last()).toDouble());
            returnString.append(weather->dayOfWeek() + " " + stringList.at(i) + "지역의 현재 기온은" + weather->temperature() + "도 입니다."); // 지역과 함께 날씨 가져오기
        }else if(sentenceList.at(i) == write::GET_WEATHER)
        {
            if(i == stringList.size())
                returnString.append(QString()); // 현재 위치의 날씨만 가져오기
        }
    }

    return returnString;
}
