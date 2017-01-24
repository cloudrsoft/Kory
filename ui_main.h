#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMessageBox>
#include <QWidget>
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

private:
    Ui::ui_main *ui;
    QLineEdit *core_input;
};

#endif // UI_MAIN_H
