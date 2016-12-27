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
    QList<int> sentenceList; // SUBJECT 같은 ENUM 으로 선언된 문장의 Type을 담는데 사용

    /* 메인 코드 */

    for(int i = 0; i < fileList.size(); i++)
    {
        if(strstr(m_target.toStdString().c_str(), db->getFileName(fileList.at(i)).toStdString().c_str()))
        {
            stringList.append(db->getFileName(fileList.at(i)).toStdString().c_str());
            sentenceList.append(db->getType(fileList.at(i)));
        }
    }

    /* 인공지능 처리에 필요한 변수 */
    int Target = 0;


    for(int i = 0; i < stringList.size(); i++)
    {
        /* Target */
        if(sentenceList.at(i) == write::MY)
            Target = write::MY;
        else if(sentenceList.at(i) == write::TARGET)
            Target = write::TARGET;
        /* End Target */



        /* Weather 처리 */
        if(sentenceList.at(i) == write::WEATHER_AREA)
        {
            returnString.append(QString()); // 지역과 함께 날씨 가져오기
        }else if(sentenceList.at(i) == write::GET_WEATHER)
        {
            if(i == stringList.size())
                returnString.append(QString()); // 현재 위치의 날씨만 가져오기
        }
    }

    return QString();
}
