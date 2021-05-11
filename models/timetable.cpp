#include "timetable.h"

#include <TreeFrogModel>

#include "sqlobjects/timetableobject.h"
#include "utility/ThreadPool.hpp"

Timetable::Timetable() : TAbstractModel(), d(new TimetableObject()) {
  // set the initial parameters
}

Timetable::Timetable(const Timetable &other) : TAbstractModel(), d(other.d) {}

Timetable::Timetable(const TimetableObject &object)
    : TAbstractModel(), d(new TimetableObject(object)) {}

Timetable::~Timetable() {
  // If the reference count becomes 0,
  // the shared data object 'TimetableObject' is deleted.
}

int Timetable::id() const { return d->id; }

int Timetable::classroomId() const { return d->classroomId; }

void Timetable::setClassroomId(int classroomId) {
  d->classroomId = classroomId;
}

int Timetable::timeId() const { return d->timeId; }

void Timetable::setTimeId(int timeId) { d->timeId = timeId; }

int Timetable::blockId() const { return d->blockId; }

void Timetable::setBlockId(int blockId) { d->blockId = blockId; }

Timetable &Timetable::operator=(const Timetable &other) {
  d = other.d;  // increments the reference count of the data
  return *this;
}

Timetable Timetable::create(int classroomId, int timeId, int blockId) {
  TimetableObject obj;
  obj.classroomId = classroomId;
  obj.timeId = timeId;
  obj.blockId = blockId;
  if (!obj.create()) {
    return Timetable();
  }
  return Timetable(obj);
}

Timetable Timetable::create(const QVariantMap &values) {
  Timetable model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

QList<TimetableObject> generateTimetable(const QList<Block> &blocks,
                                         const QList<Classroom> &classrooms,
                                         const QList<TimeSlot> &timeSlots) {
  // todo generate timetable from genetic algorithm
  return QList<TimetableObject>();
}

Timetable::Status Timetable::calculate(const QList<Block> &blocks,
                                       const QList<Classroom> &classrooms,
                                       const QList<TimeSlot> &timeSlots,
                                       QList<Timetable> &result) {
  // todo arguments validation
  Status status;
  /*
   * if (args invalid) status = error;*/

  static ThreadPool threadPool(ThreadPool::HardwareConcurrency());

  auto generateTask = [&blocks, &classrooms, &timeSlots] {
    return generateTimetable(blocks, classrooms, timeSlots);
  };

  auto callback = [&result](QList<TimetableObject> &objects) {
    for (auto &obj : objects) {
      if (obj.create()) {
        result.append(Timetable(obj));
      }
    }
  };

  threadPool.Execute(
      ThreadPool::Task(generateTask, blocks, classrooms, timeSlots),
      ThreadPool::Callback(callback));
  return status;
}

Timetable Timetable::get(int id) {
  TSqlORMapper<TimetableObject> mapper;
  return Timetable(mapper.findByPrimaryKey(id));
}

int Timetable::count() {
  TSqlORMapper<TimetableObject> mapper;
  return mapper.findCount();
}

QList<Timetable> Timetable::getAll() {
  return tfGetModelListByCriteria<Timetable, TimetableObject>(TCriteria());
}

QJsonArray Timetable::getAllJson() {
  QJsonArray array;
  TSqlORMapper<TimetableObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<TimetableObject> i(mapper); i.hasNext();) {
      array.append(QJsonValue(
          QJsonObject::fromVariantMap(Timetable(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *Timetable::modelData() { return d.data(); }

const TModelObject *Timetable::modelData() const { return d.data(); }

QDataStream &operator<<(QDataStream &ds, const Timetable &model) {
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, Timetable &model) {
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Timetable)
