#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QList>
#include <QDate>


class Object
{
public:

    Object();
    Object(QString name, double x, double y, QString type, double time);
    Object(QString name, double x, double y, QString type, QDateTime time);
    Object(QString filename);


    QString getName() const;
    void setName(const QString &value);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    QString getType() const;
    void setType(const QString &value);

    QDateTime getTime() const;
    void setTime(qint64 value);
    QString ObjectToString();



private:
    QString Name;
    double X;
    double Y;
    QString Type;
    QDateTime Time;

};

#endif // OBJECT_H
