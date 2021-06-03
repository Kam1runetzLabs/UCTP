#ifndef BLOCK_H
#define BLOCK_H

#include <QDateTime>
#include <QSharedDataPointer>
#include <QStringList>
#include <QVariant>
#include <TAbstractModel>
#include <TGlobal>

class TModelObject;
class BlockObject;
class QJsonArray;

class T_MODEL_EXPORT Block : public TAbstractModel {
 public:
  Block();
  Block(const Block &other);
  Block(const BlockObject &object);
  ~Block();

  int id() const;
  int teacherId() const;
  void setTeacherId(int teacherId);
  int subjectId() const;
  void setSubjectId(int subjectId);
  int groupId() const;
  void setGroupId(int groupId);
  Block &operator=(const Block &other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save() override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static Block create(int teacherId, int subjectId,
                      int groupId);
  static Block create(const QVariantMap &values);
  static Block get(int id);
  static int count();
  static QList<Block> getAll();
  static QJsonArray getAllJson();

 private:
  QSharedDataPointer<BlockObject> d;

  TModelObject *modelData() override;
  const TModelObject *modelData() const override;
  friend QDataStream &operator<<(QDataStream &ds, const Block &model);
  friend QDataStream &operator>>(QDataStream &ds, Block &model);
};

Q_DECLARE_METATYPE(Block)
Q_DECLARE_METATYPE(QList<Block>)

#endif  // BLOCK_H
