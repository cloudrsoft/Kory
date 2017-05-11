#include "core.h"

core::core()
{

}

QString core::getAI(QString m_target, int lang, qreal lat, qreal lng)
{
    srand((unsigned int) time(NULL));

    read *db = new read();

    int random_num = rand();
    QString returnString;
    QStringList fileList = db->getAllFileName("db", lang);

    /* 문자열 처리 */

    QStringList stringList; // 단어별로 문장을 분리해서 처리할때 사용
    QList<QStringList> replyList; // Reply 를 가져오기
    QList<int> sentenceList; // SUBJECT 같은 ENUM 으로 선언된 문장의 Type을 담는데 사용

    /* 메인 코드 */

    for(int i = 0; i < fileList.size(); i++)
    {
            if(strstr(m_target.toStdString().c_str(), db->getFileName(fileList.at(i)).toStdString().c_str()) != NULL)
            {
                stringList.append(db->getFileName(fileList.at(i)).toStdString().c_str());
                if(strstr(QString(fileList.at(i)).toStdString().c_str(), "_BADS") != NULL)
                    sentenceList.append(write::BADS);
                else if(strstr(QString(fileList.at(i)).toStdString().c_str(), "_GOODS") != NULL)
                    sentenceList.append(write::GOODS);
                else
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
    bool is_retype = true;
    bool is_good_message = false;
    bool is_bad_message = false;
    int goodCount = set->getGoodPoint();
    int badCount = set->getBadPoint();

    int tmp_goodCount = goodCount;
    int tmp_badCount = badCount;

    for(int i = 0; i < stringList.size(); i++)
    {
        if(is_retype)
        {
            if(sentenceList.at(i) == write::MY)
            {
                if(is_good_message)
                {
                    if(goodCount < badCount)
                    {
                        if(random_num % 10 == rand() % 10)
                            goodCount++;
                        else{
                            returnString.clear();
                            returnString.append(db->randomBadReply("db", lang));
                            is_bad_message = true;
                            continue;
                        }

                    }else{
                        goodCount++;
                    }
                    returnString.clear();
                    returnString.append(replyList.at(i - 1).at(random_num % replyList.at(i).size()));
                    is_retype = false;
                    is_good_message = false;
                }else if(is_bad_message){
                    badCount++;
                    goodCount--;
                    returnString.clear();
                    returnString.append(replyList.at(i - 1).at(random_num % replyList.at(i).size()));
                    is_retype = false;
                    is_bad_message = false;
                }

                Target = write::MY;
            }else if(sentenceList.at(i) == write::TARGET)
                Target = write::TARGET;
            else if(sentenceList.at(i) == write::BADS)
            {
                if(Target == write::MY)
                {
                    badCount++;
                    goodCount--;
                }
                returnString.clear();
                returnString.append(replyList.at(i).at(random_num % replyList.at(i).size()));
                is_retype = false;
                is_bad_message = true;
            }else if(sentenceList.at(i) == write::WEATHER_AREA)
            {
                QString location = replyList.at(i).join(QString());
                Weather *weather = new Weather(0, WEATHER_API_KEY, (int)QString(location.split(",").first()).toDouble(), (int)QString(location.split(",").last()).toDouble());
                QString target_file = db->searchFile("db", "_WEATHER", lang);
                returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", stringList.at(i)).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 지역과 함께 날씨 가져오기
            }else if(sentenceList.at(i) == write::GET_WEATHER)
            {
                if(i == stringList.size()){
                    Weather *weather = new Weather(0, WEATHER_API_KEY, lat, lng);
                    QString target_file = db->searchFile("db", "_WEATHER", lang);
                    returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", m_target.replace(stringList.at(i), QString())).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 현재 위치의 날씨만 가져오기
                }else{
                    geocoding *geo = new geocoding(GOOGLE_API_GEOCODING_KEY, m_target.replace(stringList.at(i), QString()));
                    Weather *weather = new Weather(0, WEATHER_API_KEY, geo->getLocation().lat, geo->getLocation().lng);
                    QString target_file = db->searchFile("db", "_WEATHER", lang);
                    returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", m_target.replace(stringList.at(i), QString())).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 지역과 함께 날씨 가져오기

                }
            }else if(sentenceList.at(i) == write::GOODS){
                if(Target == write::MY)
                {
                    if(goodCount > badCount)
                    {
                        if(random_num % 2 == rand() % random_num)
                            goodCount++;
                        else{
                            returnString.clear();
                            returnString.append(db->randomBadReply("db", lang));
                            is_bad_message = true;
                            continue;
                        }

                    }else{
                        goodCount++;
                    }


                }

                returnString.clear();
                returnString.append(replyList.at(i).at(random_num % replyList.at(i).size()));
                is_retype = false;

                is_good_message = true;
            }else if(sentenceList.at(i) == write::SEARCH){
                    returnString.append(QString(replyList.at(i).at(random_num % replyList.at(i).size()).toStdString().c_str()));
                    CustomSearch *search = new CustomSearch(GOOGLE_API_CUSTOM_SEARCH_KEY, GOOGLE_CUSTOM_SEARCH_CX, m_target.split(db->searchFileFromType("db", write::SEARCH, lang)).last());

                    QString tmp_returnString;

                    QString title = search->getTitle();
                    QStringList items = search->getSearchData();

                    tmp_returnString.append(title + "\n");

                    for(int i = 0; i < items.size(); i++)
                    {
                        tmp_returnString.append(items.at(i) + "\n");
                    }

                    returnString.replace("%GOOGLESEARCH%", tmp_returnString);
            }else{
                QDateTime time = time.currentDateTime();
                returnString.clear();
                returnString.append(QString(replyList.at(i).at(random_num % replyList.at(i).size()).toStdString().c_str()).replace("%TIME%", time.time().toString()).replace("%BOTNAME%", BOTNAME));
                is_retype = false;
            }
        }
    }

    if(returnString.isEmpty())
    {
        QString searchFile = db->searchFile("db", "_UNKNOWN", lang);

        returnString.clear();
        returnString.append(db->getReply(searchFile, random_num % db->getReplySize(searchFile))); // 일치하는 문장이 없을때
    }

    set->goodPoint(goodCount - tmp_goodCount);
    set->badPoint(badCount - tmp_badCount);

    return returnString;
}

