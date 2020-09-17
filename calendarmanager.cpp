#include "calendarmanager.h"


CalendarManager::CalendarManager(QWidget *parent)
{

}

CalendarManager::~CalendarManager()
{

}

void CalendarManager::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if(!dates.isEmpty() && dates.contains(date)){
            QCalendarWidget::paintCell(painter, rect, date);
            painter->save();
            QFont font = painter->font();
            font.setPointSize(font.pointSize() * 4);
            painter->setFont(font);
            painter->setBrush(Qt::red);
            painter->drawEllipse(rect.center().x() + 10, rect.center().y() - 4, 8, 8);
            painter->restore();
    }
    else
        QCalendarWidget::paintCell(painter, rect, date);
}

void CalendarManager::setDates(QVector<QDate> m_dates)
{
    dates = m_dates;
}
