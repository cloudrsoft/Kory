/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

#include "ui_script.h"
#include <QDebug>

ui_script::ui_script(QString styleSheet)
{
    currentStyleSheet = styleSheet;
}

QString ui_script::getCoreStyleSheet(QWidget *m_target)
{
    m_target_temp = m_target;
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

    if(strstr(returnStyleSheet.toStdString().c_str(), "WidgetList") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "widgetlist") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "WIDGETLIST") != NULL)
    {

    }


    if(strstr(returnStyleSheet.toStdString().c_str(), "MicButton") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "micbutton") != NULL || strstr(returnStyleSheet.toStdString().c_str(), "MICBUTTON") != NULL)
    {
        QPushButton *micbutton = new QPushButton(m_target);
        micbutton->move(ParsePoint(Parse("MicButton", returnStyleSheet)));
        micbutton->resize(ParseSize(Parse("MicButton", returnStyleSheet)));
        micbutton->setText("Test MicButton");
        micbutton->show();
    }

    return returnStyleSheet;
}

QString ui_script::Parse(QString m_parsename, QString returnStyleSheet)
{
    QString m_parsed = returnStyleSheet.split(m_parsename).last();
    m_parsed = m_parsed.split("{").last();
    m_parsed = m_parsed.split("}").first();

    return m_parsed;
}

QPoint ui_script::ParsePoint(QString m_parsed)
{
    if(strstr(m_parsed.toStdString().c_str(), "pos") != NULL)
    {
        QString m_posparsed = QString(QString(m_parsed.split("pos:").last()).split(";").first());
        QPoint pos = QPoint(QString(m_posparsed.split(",").first()).toInt(), QString(m_posparsed.split(",").last()).toInt());
        return pos;
    }

    return QPoint();
}

QSize ui_script::ParseSize(QString m_parsed)
{
    if(strstr(m_parsed.toStdString().c_str(), "size") != NULL)
    {
        QString m_sizeparsed = QString(QString(m_parsed.split("size:").last()).split(";").first());
        QSize size;
        QString m_sizeparsed_temp1 = m_sizeparsed.split(",").first();
        QString m_sizeparsed_temp2 = m_sizeparsed.split(",").last();
        if(strstr(m_sizeparsed_temp1.toStdString().c_str(), "widget_width") != NULL)
        {
            size.setWidth(m_target_temp->width());
        }
        if(strstr(m_sizeparsed_temp2.toStdString().c_str(), "widget_height") != NULL)
        {
            size.setHeight(m_target_temp->height());
        }
        if(size.width() == -1)
        {
            size.setWidth(QString(m_sizeparsed.split(",").first()).toInt());
        }
        if(size.height() == -1)
        {
            size.setHeight(QString(m_sizeparsed.split(",").last()).toInt());
        }
        return size;
    }

    return QSize();
}
