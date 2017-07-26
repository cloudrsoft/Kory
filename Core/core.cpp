#include "core.h"

core::core()
{

}

QString core::getAI(QString m_target, QString lang, qreal lat, qreal lng)
{
    srand((unsigned int) time(NULL));

    read *db = new read();

    int random_num = rand();
    QString returnString;
    QStringList fileList = db->getAllFileName("db", lang);

    /* 문자열 처리 */

    QStringList stringList; // 단어별로 문장을 분리해서 처리할때 사용
    QStringList sentenceList; // 선언된 문장의 Type을 담는데 사용
    QList<QStringList> replyList; // Reply 를 가져오기

    /* 메인 코드 */

    for(int i = 0; i < fileList.size(); i++)
    {
            if(stristr(m_target.toStdString().c_str(), db->getFileName(fileList.at(i)).toStdString().c_str()) != NULL)
            {
                stringList.append(db->getFileName(fileList.at(i)).toStdString().c_str());
                if(stristr(QString(fileList.at(i)).toStdString().c_str(), "_BADS") != NULL)
                    sentenceList.append("feel.bad");
                else if(stristr(QString(fileList.at(i)).toStdString().c_str(), "_GOODS") != NULL)
                    sentenceList.append("feel.good");
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
    QString Target = 0;
    QString WithTarget;
    bool is_retype = true;
    bool is_good_message = false;
    bool is_bad_message = false;
    int goodCount;
    int badCount;

    int tmp_goodCount = goodCount;
    int tmp_badCount = badCount;

    set->loadAPIKey();

    for(int i = 0; i < stringList.size(); i++)
    {
        if(is_retype)
        {
            if(sentenceList.at(i) == "target.my")
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

                Target = "target.my";
            }else if(sentenceList.at(i) == "target.target")
                Target = "target.target";
            else if(sentenceList.at(i) == "feel.bad")
            {
                if(Target == "target.my")
                {
                    badCount++;
                    goodCount--;
                }
                returnString.clear();
                returnString.append(replyList.at(i).at(random_num % replyList.at(i).size()));
                is_retype = false;
                is_bad_message = true;
            }else if(sentenceList.at(i) == "weather.area")
            {
                QString temp_weather_area = m_target.replace(stringList.at(i), QString());

                for(int a = 0; a < stringList.size(); a++)
                {
                    if(QString(sentenceList.at(0)) == "weather.area"){ } else { temp_weather_area.replace(stringList.at(i), QString()); }
                }

                geocoding *geo = new geocoding(set->getGeoCodingAPIKey(), temp_weather_area);
                QString location = replyList.at(i).join(QString());
                Weather *weather = new Weather(0, set->getWeatherAPIKey(), (int)QString(location.split(",").first()).toDouble(), (int)QString(location.split(",").last()).toDouble());
                QString target_file = db->searchFile("db", "_WEATHER", lang);
                returnString.clear();
                returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", geo->getAddress().short_name).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 지역과 함께 날씨 가져오기
                is_retype = false;
            }else if(sentenceList.at(i) == "weather.get")
            {
                if(i == stringList.size()){
                    Weather *weather = new Weather(0, set->getWeatherAPIKey(), lat, lng);
                    QString target_file = db->searchFile("db", "_WEATHER", lang);
                    returnString.clear();
                    returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", m_target.replace(stringList.at(i), QString())).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 현재 위치의 날씨만 가져오기
                    is_retype = false;
                }else{
                    QString temp_weather_area = m_target.replace(stringList.at(i), QString());

                    for(int a = 0; a < stringList.size(); a++)
                    {
                        if(a < stringList.size() - 1 && a != 0)
                        {

                            if(QString(sentenceList.at(a + 1)) == "weather.get")
                            {

                            }else if(!a == 0){
                                if(QString(sentenceList.at(a - 1)) == "weather.get"){ } else {
                                    if(QString(sentenceList.at(a)) == "weather.area"){ } else { temp_weather_area.replace(stringList.at(a), QString()); }
                                }
                            }else{
                                if(QString(sentenceList.at(a)) == "weather.area"){ } else { temp_weather_area.replace(stringList.at(a), QString()); }
                            }
                        }else{
                            if(QString(sentenceList.at(a)) == "weather.area"){ } else { temp_weather_area.replace(stringList.at(a), QString()); }
                        }
                    }

                    geocoding *geo = new geocoding(set->getGeoCodingAPIKey(), temp_weather_area);
                    if(!geo->getAddress().long_name.isEmpty())
                    {
                        Weather *weather = new Weather(0, set->getWeatherAPIKey(), geo->getLocation().lat, geo->getLocation().lng);
                        QString target_file = db->searchFile("db", "_WEATHER", lang);
                        returnString.clear();
                        returnString.append(db->getReply(target_file, rand() % db->getReplySize(target_file)).replace("%DATE%", weather->dayOfWeek()).replace("%AREA%", geo->getAddress().short_name).replace("%TEMP%", weather->temperature()).replace("%DES%", weather->weatherDescription())); // 지역과 함께 날씨 가져오기
                        is_retype = false;
                    }
                }
            }else if(sentenceList.at(i) == "feel.bad"){
                if(Target == "target.my")
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
            }else if(sentenceList.at(i) == "google.search"){
                    returnString.append(QString(replyList.at(i).at(random_num % replyList.at(i).size()).toStdString().c_str()));
                    CustomSearch *search = new CustomSearch(set->getCustomSearchAPIKey(), set->getCustomSearchCXKey(), m_target.split(db->searchFileFromType("db", "google.search", lang)).last());

                    QString tmp_returnString;

                    QString title = search->getTitle();
                    QStringList items = search->getSearchData();

                    tmp_returnString.append(title + "\n");

                    for(int i = 0; i < items.size(); i++)
                    {
                        tmp_returnString.append(items.at(i) + "\n");
                    }

                    returnString.replace("%GOOGLESEARCH%", tmp_returnString);
            }else if(sentenceList.at(i) == "target.with"){
                WithTarget = sentenceList.at(i - 1);
            }else if(sentenceList.at(i) == "text.noun"){

            }else{
                QDateTime time = time.currentDateTime();
                returnString.clear();
                returnString.append(QString(replyList.at(i).at(random_num % replyList.at(i).size()).toStdString().c_str()).replace("%TIME%", time.time().toString()).replace("%BOTNAME%", BOTNAME));
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

