#include <QCoreApplication>

#include <iostream>
#include <QDebug>
#include <QTimer>
#include <core.h>
#include "learn_manager.h"
#include "qttelegrambot.h"

#define TOKEN "386834985:AAEQ0I49lZ3P1IyXY1jF8yxotxTwNQvc1pQ"

using namespace std;

Telegram::Bot *bot;
core *ai = new core;

void newMessage(Telegram::Message message)
{
    qDebug() << "[TELEGRAM] 새로운 메시지가 왔습니다 : " << message;

    if (bot && message.type == Telegram::Message::TextType) {
        if(strstr(message.string.toStdString().c_str(),"스탑타나") != NULL)
        {
            bot->sendMessage(QString::number(message.chat.id), ai->getAI(message.string, write::LANGUAGE_KOREAN, 0, 0));
        }
        if(strstr(message.string.toStdString().c_str(),"/stop") != NULL)
        {
            bot->sendMessage(QString::number(message.chat.id), "[SYSTEM] BOT 을 종료합니다..");
            bot->killTimer(0);
            QCoreApplication::exit();
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Learn_Manager *learn_manager = new Learn_Manager;
    learn_manager->learnFromFile(":/test/Extra/text.txt", "db");

    bot = new Telegram::Bot(TOKEN, true, 500, 4);
    QObject::connect(bot, &Telegram::Bot::message, &newMessage);
    qDebug() << "[TELEGRAM] Started Telegram Bot";

    return a.exec();
}
