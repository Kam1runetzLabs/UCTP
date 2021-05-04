#ifndef BLOCKOBJECT_H
#define BLOCKOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT BlockObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    int blockCount {0};
    int teacherId {0};
    int subjectId {0};
    int groupId {0};

    enum PropertyIndex {
        Id = 0,
        BlockCount,
        TeacherId,
        SubjectId,
        GroupId,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("block"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(int blockCount READ getblockCount WRITE setblockCount)
    T_DEFINE_PROPERTY(int, blockCount)
    Q_PROPERTY(int teacherId READ getteacherId WRITE setteacherId)
    T_DEFINE_PROPERTY(int, teacherId)
    Q_PROPERTY(int subjectId READ getsubjectId WRITE setsubjectId)
    T_DEFINE_PROPERTY(int, subjectId)
    Q_PROPERTY(int groupId READ getgroupId WRITE setgroupId)
    T_DEFINE_PROPERTY(int, groupId)
};

#endif // BLOCKOBJECT_H
