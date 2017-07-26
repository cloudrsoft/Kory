#include <QCoreApplication>
#include <iostream>
#include <core.h>

#include "learn_manager.h"
#include "config.h"
#include "settings.h"

using namespace std;

settings *set = new settings;
core *ai = new core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Learn_Manager *learn_manager = new Learn_Manager;
    learn_manager->learnFromFile(":/test/Extra/kr_text.txt", "db");
    learn_manager->learnFromFile(":/test/Extra/en_text.txt", "db");

    cout << "[INFO] " << BOTNAME << " " << VERSION << " ( " << CODENAME << " )" << endl;

    for(;;){
        cout << "[USER] ";
        string tmp;
        std::getline(std::cin, tmp);

        if(strstr(tmp.c_str(), "/") != NULL)
        {
            if(strstr(tmp.c_str(),"/setlang") != NULL)
            {
                QString tmp_arg = QString(tmp.c_str()).split(" ").last();
                if(tmp_arg.isEmpty() || tmp_arg == "/setlang")
                {
                    cout << "HOW TO USE? : /setlang LANG" << endl;
                }else{
                    set->setLang(tmp_arg);
                }
            }else if(strstr(tmp.c_str(),"/lang") != NULL){
                cout << "Current Lang is : " << set->getLang().toStdString().c_str() << endl;
            }else{
                cout << "Unknown Command";
            }
        }else{
            cout << "[BOT] " << ai->getAI(tmp.c_str(), set->getLang(), 0, 0).toStdString().c_str() << endl;
        }
    }

    return a.exec();
}

