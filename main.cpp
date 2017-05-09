#include <QApplication>
#include <iostream>

#include <core.h>
#include "learn_manager.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Learn_Manager *learn_manager = new Learn_Manager;
    learn_manager->learnFromFile(":/test/Extra/text.txt", "db");

    core *ai = new core;

    while(1)
    {
        string tmp_string;
        cout << "[USER] ";
        cin >> tmp_string;
        cout << "[BOT] " << ai->getAI(QString(tmp_string.c_str()), write::LANGUAGE_KOREAN, 0, 0).toStdString() << endl;
    }

    return a.exec();
}
