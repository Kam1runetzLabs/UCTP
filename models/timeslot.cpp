#include "timeslot.h"

#include <TreeFrogModel>

#include "sqlobjects/timeslotobject.h"

TimeSlot::TimeSlot() : TAbstractModel(), d(new TimeSlotObject()) {
  // set the initial parameters
}

TimeSlot::TimeSlot(const TimeSlot &other) : TAbstractModel(), d(other.d) {}

TimeSlot::TimeSlot(const TimeSlotObject &object)
    : TAbstractModel(), d(new TimeSlotObject(object)) {}

TimeSlot::~TimeSlot() {
  // If the reference count becomes 0,
  // the shared data object 'TimeSlotObject' is deleted.
}

int TimeSlot::id() const { return d->id; }

QString TimeSlot::timeSlotName() const { return d->timeSlotName; }

void TimeSlot::setTimeSlotName(const QString &timeSlotName) {
  d->timeSlotName = timeSlotName;
}

TimeSlot &TimeSlot::operator=(const TimeSlot &other) {
  d = other.d;  // increments the reference count of the data
  return *this;
}

TimeSlot TimeSlot::create(const QString &timeSlotName) {
  TimeSlotObject obj;
  obj.timeSlotName = timeSlotName;
  if (!obj.create()) {
    return TimeSlot();
  }
  return TimeSlot(obj);
}

TimeSlot TimeSlot::create(const QVariantMap &values) {
  TimeSlot model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

TimeSlot TimeSlot::get(int id) {
  TSqlORMapper<TimeSlotObject> mapper;
  return TimeSlot(mapper.findByPrimaryKey(id));
}

int TimeSlot::count() {
  TSqlORMapper<TimeSlotObject> mapper;
  return mapper.findCount();
}

QList<TimeSlot> TimeSlot::
    getAll() {
  return tfGetModelListByCriteria<TimeSlot, TimeSlotObject>(TCriteria());
}

QJsonArray TimeSlot::getAllJson() {
  QJsonArray array;
  TSqlORMapper<TimeSlotObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<TimeSlotObject> i(mapper); i.hasNext();) {
      array.append(QJsonValue(
          QJsonObject::fromVariantMap(TimeSlot(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *TimeSlot::modelData() { return d.data(); }

const TModelObject *TimeSlot::modelData() const { return d.data(); }

QDataStream &operator<<(QDataStream &ds, const TimeSlot &model) {
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, TimeSlot &model) {
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(TimeSlot)
