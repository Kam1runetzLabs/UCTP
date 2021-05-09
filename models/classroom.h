#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class ClassroomObject;
class QJsonArray;

class T_MODEL_EXPORT Classroom : public TAbstractModel {
 public:
  Classroom();
  Classroom(const Classroom &other);
  Classroom(const ClassroomObject &object);
  ~Classroom();

  int id() const;
  QString classroomName() const;
  void setClassroomName(const QString &classroomName);
  int classroomType() const;
  void setClassroomType(int classroomType);
  Classroom &operator=(const Classroom &other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Classroom create(const QString &classroomName, int classroomType);
  static Classroom create(const QVariantMap &values);
  static Classroom get(int id);
  static int count();
  static QList<Classroom> getAll();
  static QJsonArray getAllJson();

 private:
  QSharedDataPointer<ClassroomObject> d;

  TModelObject *modelData() override;
  const TModelObject *modelData() const override;
  friend QDataStream &operator<<(QDataStream &ds, const Classroom &model);
  friend QDataStream &operator>>(QDataStream &ds, Classroom &model);
};

Q_DECLARE_METATYPE(Classroom)
Q_DECLARE_METATYPE(QList<Classroom>)

#endif  // CLASSROOM_H
