#ifndef TIMETABLEOBJECT_H
#define TIMETABLEOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT TimetableObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    int classroomId {0};
    int timeId {0};
    int blockId {0};

    enum PropertyIndex {
        Id = 0,
        ClassroomId,
        TimeId,
        BlockId,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("timetable"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(int classroomId READ getclassroomId WRITE setclassroomId)
    T_DEFINE_PROPERTY(int, classroomId)
    Q_PROPERTY(int timeId READ gettimeId WRITE settimeId)
    T_DEFINE_PROPERTY(int, timeId)
    Q_PROPERTY(int blockId READ getblockId WRITE setblockId)
    T_DEFINE_PROPERTY(int, blockId)
};

#endif // TIMETABLEOBJECT_H
