/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

#ifndef UI_SCRIPT_H
#define UI_SCRIPT_H

#include <QString>
#include <QRegExp>
#include <QPoint>

class ui_script
{
public:
    ui_script(QString styleSheet);

    QString getCoreStyleSheet(); // ui 스타일 시트를 Qt 내장 스타일 시트로 되돌린다

    QString currentStyleSheet; // init 에서 설정된 스타일시트 (스크립트)
};

#endif // UI_SCRIPT_H
