#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include <QCalendarWidget>

#include <QStringList>
#include <QBrush>
#include <QColor>
#include <QFile>
#include <QList>
#include <QDate>
#include <QPen>
#include <QDebug>
#include <QPainter>

class CalendarManager : public QCalendarWidget
{
    Q_OBJECT

public:
    CalendarManager(QWidget *parent = 0);
    ~CalendarManager();

    void setDates(QVector<QDate> m_dates);

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date)
const;

private:
    QVector<QDate> dates;

};

#endif // CALENDARMANAGER_H
