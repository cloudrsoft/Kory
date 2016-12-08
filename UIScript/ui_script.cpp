/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

#include "ui_script.h"

ui_script::ui_script(QString styleSheet)
{
    currentStyleSheet = styleSheet;
}

QString ui_script::getCoreStyleSheet()
{
    QString returnStyleSheet = currentStyleSheet;

    QRegExp button("(\\Button|\\button|\\BUTTON)"); // Button Split List
    QRegExp main("(\\Main|\\main|\\MAIN"); // Button Split List

    returnStyleSheet.replace(button,"QPushButton"); // Parsing Button
    returnStyleSheet.replace(main,"QMainWindow#ui_main"); // Parsing Main Window

    return returnStyleSheet;
}

