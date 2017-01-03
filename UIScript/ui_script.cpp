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

    if(strstr(returnStyleSheet.toStdString().c_str(), "Functions") != NULL)
    {
        QString m_parsed = Parse("Functions", returnStyleSheet);
        QStringList functions = QString(m_parsed.split(";").first()).split(",");

        for(int i = 0; i < functions.size(); i++)
        {
            if(strstr(returnStyleSheet.toStdString().c_str(), QString(functions.at(i)).toStdString().c_str()) != NULL)
            {
                QString m_parse_function = Parse(functions.at(i), returnStyleSheet);

                if(strstr(ParseString(m_parse_function, "type").toStdString().c_str(), "LineEdit") != NULL)
                {
                    QLineEdit *input_line = new QLineEdit(m_target);
                    input_line->move(ParsePoint(m_parse_function));
                    input_line->resize(ParseSize(m_parse_function));
                    input_line->setText(ParseString(m_parse_function, "text"));
                    input_line->setPlaceholderText(ParseString(m_parse_function, "placeHolderText"));

                    if(strstr(ParseString(m_parse_function, "frame").toStdString().c_str(), "false") != NULL)
                        input_line->setFrame(false);

                    if(strstr(ParseString(m_parse_function, "alignment").toStdString().c_str(), "center") != NULL)
                        input_line->setAlignment(Qt::AlignHCenter);

                    if(strstr(ParseString(m_parse_function, "readonly").toStdString().c_str(), "true") != NULL)
                        input_line->setReadOnly(true);

                    input_line->show();

                    widgetList->append(input_line);
                }else if(strstr(ParseString(m_parse_function, "type").toStdString().c_str(), "Button") != NULL)
                {

                }
            }else{
                qDebug() << "[UI Script] Can't Found";
            }
        }
    }

    return returnStyleSheet;
}

QString ui_script::Parse(QString m_parsename, QString returnStyleSheet)
{
    QString m_parsed = returnStyleSheet.split(m_parsename).last();
    m_parsed = m_parsed.split("{").at(1);
    m_parsed = m_parsed.split("}").at(0);

    return m_parsed;
}

QPoint ui_script::ParsePoint(QString m_parsed)
{
    if(strstr(m_parsed.toStdString().c_str(), "pos") != NULL)
    {
        QString m_posparsed = QString(QString(m_parsed.split("pos:").last()).split(";").first());
        QPoint pos;
        if(strstr(m_posparsed.toStdString().c_str(), "bottom") != NULL)
            pos = QPoint(0, m_target_temp->rect().bottom() - ParseSize(m_parsed).height());
        else
            pos = QPoint(QString(m_posparsed.split(",").first()).toInt(), QString(m_posparsed.split(",").last()).toInt());
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

        if(strstr(m_sizeparsed_temp1.toStdString().c_str(), "max") != NULL)
            size.setWidth(m_target_temp->width());
        if(strstr(m_sizeparsed_temp2.toStdString().c_str(), "max") != NULL)
            size.setHeight(m_target_temp->height());

        if(size.isEmpty())
        {
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
        }
        return size;
    }

    return QSize();
}

QString ui_script::ParseString(QString m_parsed, QString m_parse_target)
{
    if(strstr(m_parsed.toStdString().c_str(), m_parse_target.toStdString().c_str()) != NULL)
    {
        return QString(QString(m_parsed.split(m_parse_target + ":").last()).split(";").first());
    }

    return QString();
}

QObject *ui_script::getWidget(int num)
{
    return widgetList->at(num);
}
