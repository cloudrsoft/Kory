/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

#include "ui_script.h"
#include <QDebug>

ui_script::ui_script(QString styleSheet)
{
    currentStyleSheet = styleSheet;
}

QString ui_script::getCoreStyleSheet()
{
    QString returnStyleSheet = currentStyleSheet;

    QRegExp main("(\\Main|\\main|\\MAIN)"); // Main Split List
    QRegExp button("(\\QButton|\\qbutton|\\QBUTTON)"); // Button Split List
    QRegExp button_pressed("(\\QPushButton_Pressed)"); // Button Split List
    QRegExp lineedit("(\\QInput|\\qinput|\\QINPUT)"); // LineEdit Split List

    returnStyleSheet.replace(main,"QWidget#centralWidget"); // Parsing Main Window
    returnStyleSheet.replace(button,"QPushButton"); // Parsing Button
    returnStyleSheet.replace(button_pressed,"QPushButton::pressed"); // Parsing Button
    returnStyleSheet.replace(lineedit,"QLineEdit"); // Parsing Input

    if(strstr(returnStyleSheet.toStdString().c_str(), "QWidget") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "qwidget") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "QWIDGET") != NULL)
        qDebug() << "[UI Script] QWidget Script is Available";

    if(strstr(returnStyleSheet.toStdString().c_str(), "MicButton") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "micbutton") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "MICBUTTON") != NULL)
    {
        QString m_parsed = returnStyleSheet.split("MicButton").last();
        m_parsed = m_parsed.split("{").last();
        m_parsed = m_parsed.split("}").first();

        if(strstr(m_parsed.toStdString().c_str(), "pos") != NULL)
        {
            QString m_posparsed = QString(QString(m_parsed.split("pos:").last()).split(";").first());
            QPoint pos = QPoint(QString(m_posparsed.split(",").first()).toInt(), QString(m_posparsed.split(",").last()).toInt());
            qDebug() << pos;
        }
    }

    return returnStyleSheet;
}

