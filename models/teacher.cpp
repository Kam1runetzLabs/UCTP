#include "teacher.h"

#include <TreeFrogModel>

#include "sqlobjects/teacherobject.h"

Teacher::Teacher() : TAbstractModel(), d(new TeacherObject()) {
  // set the initial parameters
}

Teacher::Teacher(const Teacher &other) : TAbstractModel(), d(other.d) {}

Teacher::Teacher(const TeacherObject &object)
    : TAbstractModel(), d(new TeacherObject(object)) {}

Teacher::~Teacher() {
  // If the reference count becomes 0,
  // the shared data object 'TeacherObject' is deleted.
}

int Teacher::id() const { return d->id; }

QString Teacher::teacherName() const { return d->teacherName; }

void Teacher::setTeacherName(const QString &teacherName) {
  d->teacherName = teacherName;
}

Teacher &Teacher::operator=(const Teacher &other) {
  d = other.d;  // increments the reference count of the data
  return *this;
}

Teacher Teacher::create(const QString &teacherName) {
  TeacherObject obj;
  obj.teacherName = teacherName;
  if (!obj.create()) {
    return Teacher();
  }
  return Teacher(obj);
}

Teacher Teacher::create(const QVariantMap &values) {
  Teacher model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

Teacher Teacher::get(int id) {
  TSqlORMapper<TeacherObject> mapper;
  return Teacher(mapper.findByPrimaryKey(id));
}

int Teacher::count() {
  TSqlORMapper<TeacherObject> mapper;
  return mapper.findCount();
}

QList<Teacher> Teacher::getAll() {
  return tfGetModelListByCriteria<Teacher, TeacherObject>(TCriteria());
}

QJsonArray Teacher::getAllJson() {
  QJsonArray array;
  TSqlORMapper<TeacherObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<TeacherObject> i(mapper); i.hasNext();) {
      array.append(QJsonValue(
          QJsonObject::fromVariantMap(Teacher(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *Teacher::modelData() { return d.data(); }

const TModelObject *Teacher::modelData() const { return d.data(); }

QDataStream &operator<<(QDataStream &ds, const Teacher &model) {
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, Teacher &model) {
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Teacher)
