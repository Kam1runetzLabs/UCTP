#include <TreeFrogModel>
#include "classroom.h"
#include "sqlobjects/classroomobject.h"

Classroom::Classroom() :
    TAbstractModel(),
    d(new ClassroomObject())
{
    // set the initial parameters
}

Classroom::Classroom(const Classroom &other) :
    TAbstractModel(),
    d(other.d)
{ }

Classroom::Classroom(const ClassroomObject &object) :
    TAbstractModel(),
    d(new ClassroomObject(object))
{ }

Classroom::~Classroom()
{
    // If the reference count becomes 0,
    // the shared data object 'ClassroomObject' is deleted.
}

int Classroom::id() const
{
    return d->id;
}

QString Classroom::classroomName() const
{
    return d->classroomName;
}

void Classroom::setClassroomName(const QString &classroomName)
{
    d->classroomName = classroomName;
}

int Classroom::classroomType() const
{
    return d->classroomType;
}

void Classroom::setClassroomType(int classroomType)
{
    d->classroomType = classroomType;
}

Classroom &Classroom::operator=(const Classroom &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Classroom Classroom::create(const QString &classroomName, int classroomType)
{
    ClassroomObject obj;
    obj.classroomName = classroomName;
    obj.classroomType = classroomType;
    if (!obj.create()) {
        return Classroom();
    }
    return Classroom(obj);
}

Classroom Classroom::create(const QVariantMap &values)
{
    Classroom model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Classroom Classroom::get(int id)
{
    TSqlORMapper<ClassroomObject> mapper;
    return Classroom(mapper.findByPrimaryKey(id));
}

int Classroom::count()
{
    TSqlORMapper<ClassroomObject> mapper;
    return mapper.findCount();
}

QList<Classroom> Classroom::getAll()
{
    return tfGetModelListByCriteria<Classroom, ClassroomObject>(TCriteria());
}

QJsonArray Classroom::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<ClassroomObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<ClassroomObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Classroom(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Classroom::modelData()
{
    return d.data();
}

const TModelObject *Classroom::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Classroom &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Classroom &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Classroom)
