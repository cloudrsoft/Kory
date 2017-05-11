#include <QCoreApplication>
#include <iostream>
#include <core.h>

#include "learn_manager.h"
#include "config.h"

using namespace std;

core *ai = new core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Learn_Manager *learn_manager = new Learn_Manager;
    learn_manager->learnFromFile(":/test/Extra/text.txt", "db");

    cout << "[INFO] AI " << VERSION << " ( Test )" << endl;

    while(1)
    {
        cout << "[USER] ";
        string tmp;
        cin >> tmp;
        cout << "[BOT] " << ai->getAI(tmp.c_str(), write::LANGUAGE_KOREAN, 0, 0).toStdString().c_str() << endl;
    }

    return a.exec();
}
