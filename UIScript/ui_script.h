/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

#ifndef UI_SCRIPT_H
#define UI_SCRIPT_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QRegExp>
#include <QPoint>
#include <QSize>

class ui_script
{
public:
    ui_script(QString styleSheet);

    QString getCoreStyleSheet(QWidget *m_target); // ui 스타일 시트를 Qt 내장 스타일 시트로 되돌린다

    QString Parse(QString m_parsed, QString returnStyleSheet); // 스크립트 함수를 파싱

    QPoint ParsePoint(QString m_parsed); // 스크립트 함수에 지정된 위치 변수를 파싱

    QSize ParseSize(QString m_parsed); // 스크립트 함수에 지정된 크기 변수를 파싱

    QString currentStyleSheet; // init 에서 설정된 스타일시트 (스크립트)

private:
    QWidget *m_target_temp; // getCoreStyleSheet 함수 외에 QWidget 을 호출할때
};

#endif // UI_SCRIPT_H
