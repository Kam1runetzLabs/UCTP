#ifndef SUBJECT_H
#define SUBJECT_H

#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class SubjectObject;
class QJsonArray;

class T_MODEL_EXPORT Subject : public TAbstractModel {
 public:
  Subject();
  Subject(const Subject &other);
  Subject(const SubjectObject &object);
  ~Subject();

  int id() const;
  QString subjectName() const;
  void setSubjectName(const QString &subjectName);
  int subjectType() const;
  void setSubjectType(int subjectType);
  Subject &operator=(const Subject &other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Subject create(const QString &subjectName, int subjectType);
  static Subject create(const QVariantMap &values);
  static Subject get(int id);
  static int count();
  static QList<Subject> getAll();
  static QJsonArray getAllJson();

 private:
  QSharedDataPointer<SubjectObject> d;

  TModelObject *modelData() override;
  const TModelObject *modelData() const override;
  friend QDataStream &operator<<(QDataStream &ds, const Subject &model);
  friend QDataStream &operator>>(QDataStream &ds, Subject &model);
};

Q_DECLARE_METATYPE(Subject)
Q_DECLARE_METATYPE(QList<Subject>)

#endif  // SUBJECT_H
