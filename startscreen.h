#ifndef SCALEDPIXMAP_H
#define SCALEDPIXMAP_H

#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>

QT_FORWARD_DECLARE_CLASS(QPaintEvent)

class StartScreen : public QLabel
{
    Q_OBJECT
public:
    explicit StartScreen(QWidget*parent = Q_NULLPTR);
    void ScaledPixMapDelete();


public slots:
    void loadpicture (const QString& path); // Р В Р’В·Р В Р’В°Р В РЎвЂ“Р РЋР вЂљР РЋРЎвЂњР В Р’В·Р В РЎвЂќР В Р’В° Р В РЎвЂќР В Р’В°Р РЋР вЂљР РЋРІР‚С™Р В РЎвЂР В Р вЂ¦Р В РЎвЂќР В РЎвЂ
    void SetScaledPixMap(const QPixmap& pixmap);


protected:
    void paintEvent(QPaintEvent*);

private:
    QPixmap m_pixmap;
};

#endif // SCALEDPIXMAP_H

