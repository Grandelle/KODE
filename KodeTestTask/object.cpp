#include "object.h"

Object::Object()
{

}

Object::Object(QString name, double x, double y, QString type, double time)
{
    this->Name = name;
    this->X = x;
    this->Y = y;
    this->Type = type;
    this->setTime(time);
}

Object::Object(QString name, double x, double y, QString type, QDateTime time)
{
    this->Name = name;
    this->X = x;
    this->Y = y;
    this->Type = type;
    this->Time = time;
}

Object::Object(QString filestr)
{
    QStringList list = filestr.split(" ");
    this->setName(list[0]);
    this->setX(list[1].toDouble());
    this->setY(list[2].toDouble());
    this->setType(list[3]);
    this->setTime(list[4].toDouble());

}

QString Object::getName() const
{
    return Name;
}

void Object::setName(const QString &value)
{
    Name = value;
}

double Object::getX() const
{
    return X;
}

void Object::setX(double value)
{
    X = value;
}

double Object::getY() const
{
    return Y;
}

void Object::setY(double value)
{
    Y = value;
}

QString Object::getType() const
{
    return Type;
}

void Object::setType(const QString &value)
{
    Type = value;
}

QDateTime Object::getTime() const
{
    return Time;
}

void Object::setTime(qint64 value)
{
    this->Time.setSecsSinceEpoch(value);


}

QString Object::ObjectToString()
{
 return this->getName() + ' ' + QString::number(this->getX()) + ' ' + QString::number(this->getY()) + ' ' + this->getType() + ' ' + this->getTime().toString();
}
