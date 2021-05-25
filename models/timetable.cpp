#include "timetable.h"

#include <QThreadPool>
#include <TreeFrogModel>

#include "genetic_algorithm.hpp"
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

Timetable::Status Timetable::calculate(const QList<Block> &blocks,
                                       const QList<Subject> &subjects,
                                       const QList<Classroom> &classrooms,
                                       const QList<TimeSlot> &timeSlots,
                                       QList<Timetable> &result) {
  // todo args validation
  Status status;
  auto task = [&blocks, &subjects, &classrooms, &timeSlots, &result]() -> void {
    std::vector<alg::Block> blocksIds;
    std::vector<int> classroomsType1Ids;
    std::vector<int> classroomsType2Ids;
    std::vector<int> timeSlotsIds;

    std::map<int, int> subjectTypeMap;
    for (auto &subject : subjects) {
      subjectTypeMap[subject.id()] = subject.subjectType();
    }

    for (auto &block : blocks) {
      blocksIds.emplace_back(block.groupId(), block.subjectId(),
                             subjectTypeMap[block.subjectId()],
                             block.teacherId());
    }
    for (auto &classroom : classrooms) {
      if (classroom.classroomType() == 1)
        classroomsType1Ids.push_back(classroom.id());
      else if (classroom.classroomType() == 2)
        classroomsType2Ids.push_back(classroom.id());
    }
    for (auto &timeSlot : timeSlots) {
      timeSlotsIds.push_back(timeSlot.id());
    }

    alg::Population myPopulation(blocksIds, classroomsType1Ids,
                                 classroomsType2Ids, timeSlotsIds);
    std::shared_ptr<alg::Individual> bestInd = myPopulation.Iterations();
    std::shared_ptr<alg::ChromosomeAuditory> auditoriesChromosome =
        bestInd->GetAuditoryChromosome();
    std::shared_ptr<alg::ChromosomeTime> timesChromosome =
        bestInd->GetTimeChromosome();
    std::vector<alg::Gen> auditories = auditoriesChromosome->GetAuditoryGenes();
    std::vector<alg::Gen> times = timesChromosome->GetTimeGenes();

    for (int i = 0; i < blocks.length(); i++) {
      TimetableObject obj = TimetableObject();
      obj.classroomId = auditories[i].GetValue();
      obj.timeId = times[i].GetValue();
      obj.blockId = blocks[i].id();
      if (obj.create()) {
        result.append(Timetable(obj));
      }
    }
  };
  // todo temporary solution
  QThreadPool::globalInstance()->start(task);
  // todo handling status and email notification
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
