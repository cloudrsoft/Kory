#include "ui_main.h"
#include "ui_ui_main.h"
#include <weather.h>
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
        QString resultStyleSheet = style->getCoreStyleSheet();

        if(resultStyleSheet.isEmpty()) // if Style Sheet is Empty or Can not find file
            qDebug() << "[WARN] Could not find style sheet";
        else
            setStyleSheet(resultStyleSheet);
    }
}

ui_main::~ui_main()
{
    delete ui;
}
