#include "ui_main.h"
#include "ui_ui_main.h"
#include <weather.h>
#include <core.h>
#include <ui_script.h>

ui_main::ui_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ui_main)
{
    ui->setupUi(this);

    settings *set = new settings;

    set->setStyleSheetPath("files/stylesheet.txt");

    QFile file(set->getStyleSheetPath());

    QFileInfo filedir = QFileInfo(file.fileName());

    if(!filedir.dir().exists())
    {
        QDir dir;
        qDebug() << "[File] mkdir" << filedir.dir().path();
        dir.mkdir(filedir.dir().path());
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui_script *style = new ui_script(file.readAll());
        QString resultStyleSheet = style->getCoreStyleSheet(ui->centralWidget);

        if(resultStyleSheet.isEmpty()) // if Style Sheet is Empty or Can not find file
            qDebug() << "[WARN] Could not find style sheet";
        else
            setStyleSheet(resultStyleSheet.toStdString().c_str());
    }

    write *db = new write;
    db->writeFile("db", "인사", "안녕", QStringList(), write::LANGUAGE_DEFAULT, write::SUBJECT);
    db->writeFile("db", "대상", "나", QStringList(), write::LANGUAGE_DEFAULT, write::MY);
    db->writeFile("db", "날씨", "날씨", QStringList(), write::LANGUAGE_DEFAULT, write::GET_WEATHER);
    db->writeFile("db", "위치", "원주", QStringList() << "37.331024,127.926008", write::LANGUAGE_DEFAULT, write::WEATHER_AREA);

    core *ai = new core;
    qDebug() << ai->getAI("원주 날씨", write::LANGUAGE_DEFAULT);
}

ui_main::~ui_main()
{
    delete ui;
}
