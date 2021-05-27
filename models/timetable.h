#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

#include "block.h"
#include "classroom.h"
#include "subject.h"
#include "timeslot.h"

class TModelObject;

class TimetableObject;

class QJsonArray;

class T_MODEL_EXPORT Timetable : public TAbstractModel {
 public:
  Timetable();

  Timetable(const Timetable &other);

  explicit Timetable(const TimetableObject &object);

  ~Timetable();

  int id() const;

  int classroomId() const;

  void setClassroomId(int classroomId);

  int timeId() const;

  void setTimeId(int timeId);

  int blockId() const;

  void setBlockId(int blockId);

  Timetable &operator=(const Timetable &other);

  bool create() override { return TAbstractModel::create(); }

  bool update() override { return TAbstractModel::update(); }

  bool save() override { return TAbstractModel::save(); }

  bool remove() override { return TAbstractModel::remove(); }

  static Timetable create(int classroomId, int timeId, int blockId);

  static Timetable create(const QVariantMap &values);

  // todo temporary solution
  struct Status {
   public:
    Status() : m_ErrorMessage(nullptr){};

    bool ok() const { return true; };

    const char *error() const { return ""; };

   private:
    char *m_ErrorMessage;
  };

  static Status calculate(const QList<Block> &blocks,
                          const QList<Subject> &subjects,
                          const QList<Classroom> &classrooms,
                          const QList<TimeSlot> &timeSlots,
                          QList<Timetable> &result,
                          int population, int iterations);

  static Timetable get(int id);

  static int count();

  static QList<Timetable> getAll();

  static QJsonArray getAllJson();

 private:
  QSharedDataPointer<TimetableObject> d;

  TModelObject *modelData() override;

  const TModelObject *modelData() const override;

  friend QDataStream &operator<<(QDataStream &ds, const Timetable &model);

  friend QDataStream &operator>>(QDataStream &ds, Timetable &model);
};

Q_DECLARE_METATYPE(Timetable)

Q_DECLARE_METATYPE(QList<Timetable>)

#endif  // TIMETABLE_H
