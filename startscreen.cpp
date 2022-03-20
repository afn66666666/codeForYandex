#include "startscreen.h"

#include <QtGui/QPainter>

StartScreen::StartScreen(QWidget*parent):
    QLabel(parent)
{

}

void StartScreen::loadpicture(const QString &path)
{
    QPixmap pixmap(path);
    SetScaledPixMap(pixmap);
}

void StartScreen::SetScaledPixMap(const QPixmap &pixmap) // установка ихображения для масштабирования
{
    m_pixmap = pixmap;
    update();
}

void StartScreen::paintEvent(QPaintEvent *  event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if(!m_pixmap.isNull()){ // если есть что рисовать
        QPoint CenterPoint(0,0); // точка центра
        QSize MenuScaledSize = size(); // текущий размер виджета
        QPixmap ScaledPicture = m_pixmap.scaled(MenuScaledSize, Qt::KeepAspectRatio); // замасштабированная картинка

        CenterPoint.setX((MenuScaledSize.width() - ScaledPicture.width())/2); // устанавливаем коо-ты центра вычитая из коо-ты виджета коо-ту сжатой
        CenterPoint.setY((MenuScaledSize.height() - ScaledPicture.height())/2); // картинки
        painter.drawPixmap(CenterPoint,ScaledPicture);
    }

}
