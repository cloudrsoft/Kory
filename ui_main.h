#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtWidgets>
#include <QTextBrowser>
#include <QPushButton>
#include <QTextToSpeech>

#include <customsearch.h>
#include <geocoding.h>

#include "config.h"
#include "settings.h"
#include "learn_manager.h"


namespace Ui {
class ui_main;
}

class ui_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit ui_main(QWidget *parent = 0);
    ~ui_main();

private slots:
    void closeEvent(QCloseEvent *event);
    void getAI();
    void addNewUserMessage();
    void addNewAIMessage(QString string);

private:
    Ui::ui_main *ui;
    QLineEdit *core_input;
    QWidget *frame_messages = new QWidget(this);
    QWidget *messages = new QWidget(frame_messages);
    QWidget *message_box = new QWidget(messages);
    QLabel *message_box_label = new QLabel(message_box);

    int message_number = 0;
    
    QStringList userMessages;
    QStringList aiMessages;
};

#endif // UI_MAIN_H
