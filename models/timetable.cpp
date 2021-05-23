#include "timetable.h"

#include <TreeFrogModel>

#include "../src/algorithm/include/genetic_algorithm.hpp"
#include "sqlobjects/timetableobject.h"

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

Timetable::Status generateTimetable(const QList<Block> &blocks,
                                    const QList<Classroom> &classrooms,
                                    const QList<TimeSlot> &timeSlots,
                                    QList<TimetableObject> &result) {
  // todo generate timetable from genetic algorithm
  return Timetable::Status{};
}

Timetable::Status Timetable::calculate(const QList<Block> &blocks,
                                       const QList<Subject> &subjects,
                                       const QList<Classroom> &classrooms,
                                       const QList<TimeSlot> &timeSlots,
                                       QList<Timetable> &result) {
  std::vector<alg::Block> blocksIds;
  std::vector<int> classroomsType1Ids;
  std::vector<int> classroomsType2Ids;
  std::vector<int> timeSlotsIds;

  std::map<int, int> subjectTypeMap;
  for (const Subject& subject : subjects) {
    subjectTypeMap[subject.id()] = subject.subjectType();
  }

  for (const Block& block : blocks) {
    blocksIds.emplace_back(block.groupId(),
                           block.subjectId(),
                           subjectTypeMap[block.subjectId()],
                           block.teacherId());
  }
  for (const Classroom& classroom : classrooms) {
    if (classroom.classroomType() == 1)
      classroomsType1Ids.push_back(classroom.id());
    else if (classroom.classroomType() == 2)
      classroomsType2Ids.push_back(classroom.id());
  }
  for (const TimeSlot& timeSlot : timeSlots) {
    timeSlotsIds.push_back(timeSlot.id());
  }

  alg::Population myPopulation(blocksIds, classroomsType1Ids,
                               classroomsType2Ids, timeSlotsIds);
  std::shared_ptr<alg::Individual> bestInd = myPopulation.Iterations();

  QList<TimetableObject> objects;
  auto status = generateTimetable(blocks, classrooms, timeSlots, objects);
  for (TimetableObject obj : objects) {
    if (obj.create()) {
      result.append(Timetable(obj));
    }
  }
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
