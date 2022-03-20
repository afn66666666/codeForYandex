#include "spaceshiphitbox.h"


SpaceShipHitbox::SpaceShipHitbox(QObject* parent):
    QObject(parent), QGraphicsItem()
{
     // Растягиваем содержимое по виджету
    angle = 0;     // Задаём угол поворота графического объекта
    setRotation(angle);     // Устанавилваем угол поворота графического объекта
    /* Также зададим минимальные размеры виджета
     * */
}
SpaceShipHitbox::~SpaceShipHitbox()
{

}

void SpaceShipHitbox::slotSpaceship()
{

}

void SpaceShipHitbox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;   /// Используем класс полигона, чтобы отрисовать треугольник
            /// Помещаем координаты точек в полигональную модель
            polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
            painter->setBrush(Qt::red);     /// Устанавливаем кисть, которой будем отрисовывать объект
            painter->drawPolygon(polygon);  /// Рисуем треугольник по полигональной модели
            Q_UNUSED(option);
            Q_UNUSED(widget);
}

