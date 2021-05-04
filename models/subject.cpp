#include <TreeFrogModel>
#include "subject.h"
#include "sqlobjects/subjectobject.h"

Subject::Subject() :
    TAbstractModel(),
    d(new SubjectObject())
{
    // set the initial parameters
}

Subject::Subject(const Subject &other) :
    TAbstractModel(),
    d(other.d)
{ }

Subject::Subject(const SubjectObject &object) :
    TAbstractModel(),
    d(new SubjectObject(object))
{ }

Subject::~Subject()
{
    // If the reference count becomes 0,
    // the shared data object 'SubjectObject' is deleted.
}

int Subject::id() const
{
    return d->id;
}

QString Subject::subjectName() const
{
    return d->subjectName;
}

void Subject::setSubjectName(const QString &subjectName)
{
    d->subjectName = subjectName;
}

int Subject::subjectType() const
{
    return d->subjectType;
}

void Subject::setSubjectType(int subjectType)
{
    d->subjectType = subjectType;
}

Subject &Subject::operator=(const Subject &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Subject Subject::create(const QString &subjectName, int subjectType)
{
    SubjectObject obj;
    obj.subjectName = subjectName;
    obj.subjectType = subjectType;
    if (!obj.create()) {
        return Subject();
    }
    return Subject(obj);
}

Subject Subject::create(const QVariantMap &values)
{
    Subject model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Subject Subject::get(int id)
{
    TSqlORMapper<SubjectObject> mapper;
    return Subject(mapper.findByPrimaryKey(id));
}

int Subject::count()
{
    TSqlORMapper<SubjectObject> mapper;
    return mapper.findCount();
}

QList<Subject> Subject::getAll()
{
    return tfGetModelListByCriteria<Subject, SubjectObject>(TCriteria());
}

QJsonArray Subject::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<SubjectObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<SubjectObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Subject(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Subject::modelData()
{
    return d.data();
}

const TModelObject *Subject::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Subject &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Subject &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Subject)
