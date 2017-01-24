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

    set->setStyleSheetPath(":/test/Extra/stylesheet.txt");

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
        QString resultStyleSheet = style->getCoreStyleSheet(this);

        core_input = qobject_cast<QLineEdit*>(style->getWidget(0));
        connect(core_input, SIGNAL(returnPressed()), this, SLOT(getAI()));

        if(resultStyleSheet.isEmpty()) // if Style Sheet is Empty or Can not find file
            qDebug() << "[WARN] Could not find style sheet";
        else
            setStyleSheet(resultStyleSheet.toStdString().c_str());
    }

    Learn_Manager *learn_manager = new Learn_Manager;
    learn_manager->learnFromFile(":/test/Extra/text.txt", "db");
    learn_manager->makeFile("text.txt", "db", write::LANGUAGE_KOREAN);
}

ui_main::~ui_main()
{
    delete ui;
}

void ui_main::getAI()
{
    core *ai = new core;
    qDebug() << ai->getAI(core_input->text(), write::LANGUAGE_KOREAN, 0, 0);
}

void ui_main::closeEvent (QCloseEvent *event)
{
    event->accept();
}
