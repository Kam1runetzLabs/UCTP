#include "block.h"

#include <TreeFrogModel>

#include "sqlobjects/blockobject.h"

Block::Block() : TAbstractModel(), d(new BlockObject()) {
  // set the initial parameters
}

Block::Block(const Block &other) : TAbstractModel(), d(other.d) {}

Block::Block(const BlockObject &object)
    : TAbstractModel(), d(new BlockObject(object)) {}

Block::~Block() {
  // If the reference count becomes 0,
  // the shared data object 'BlockObject' is deleted.
}

int Block::id() const { return d->id; }

int Block::teacherId() const { return d->teacherId; }

void Block::setTeacherId(int teacherId) { d->teacherId = teacherId; }

int Block::subjectId() const { return d->subjectId; }

void Block::setSubjectId(int subjectId) { d->subjectId = subjectId; }

int Block::groupId() const { return d->groupId; }

void Block::setGroupId(int groupId) { d->groupId = groupId; }

Block &Block::operator=(const Block &other) {
  d = other.d;  // increments the reference count of the data
  return *this;
}

Block Block::create(int teacherId, int subjectId, int groupId) {
  BlockObject obj;
  obj.teacherId = teacherId;
  obj.subjectId = subjectId;
  obj.groupId = groupId;
  if (!obj.create()) {
    return Block();
  }
  return Block(obj);
}

Block Block::create(const QVariantMap &values) {
  Block model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

Block Block::get(int id) {
  TSqlORMapper<BlockObject> mapper;
  return Block(mapper.findByPrimaryKey(id));
}

int Block::count() {
  TSqlORMapper<BlockObject> mapper;
  return mapper.findCount();
}

QList<Block> Block::getAll() {
  return tfGetModelListByCriteria<Block, BlockObject>(TCriteria());
}

QJsonArray Block::getAllJson() {
  QJsonArray array;
  TSqlORMapper<BlockObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<BlockObject> i(mapper); i.hasNext();) {
      array.append(QJsonValue(
          QJsonObject::fromVariantMap(Block(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *Block::modelData() { return d.data(); }

const TModelObject *Block::modelData() const { return d.data(); }

QDataStream &operator<<(QDataStream &ds, const Block &model) {
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, Block &model) {
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Block)
