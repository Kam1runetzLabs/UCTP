#ifndef TEACHER_H
#define TEACHER_H

#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class TeacherObject;
class QJsonArray;

class T_MODEL_EXPORT Teacher : public TAbstractModel {
 public:
  Teacher();
  Teacher(const Teacher &other);
  Teacher(const TeacherObject &object);
  ~Teacher();

  int id() const;
  QString teacherName() const;
  void setTeacherName(const QString &teacherName);
  Teacher &operator=(const Teacher &other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Teacher create(const QString &teacherName);
  static Teacher create(const QVariantMap &values);
  static Teacher get(int id);
  static int count();
  static QList<Teacher> getAll();
  static QJsonArray getAllJson();

 private:
  QSharedDataPointer<TeacherObject> d;

  TModelObject *modelData() override;
  const TModelObject *modelData() const override;
  friend QDataStream &operator<<(QDataStream &ds, const Teacher &model);
  friend QDataStream &operator>>(QDataStream &ds, Teacher &model);
};

Q_DECLARE_METATYPE(Teacher)
Q_DECLARE_METATYPE(QList<Teacher>)

#endif  // TEACHER_H
