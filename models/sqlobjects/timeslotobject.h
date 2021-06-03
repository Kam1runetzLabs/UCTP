#ifndef TIMESLOTOBJECT_H
#define TIMESLOTOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT TimeSlotObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString timeSlotName;

    enum PropertyIndex {
        Id = 0,
        TimeSlotName,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("timeslot"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString timeSlotName READ gettimeSlotName WRITE settimeSlotName)
    T_DEFINE_PROPERTY(QString, timeSlotName)
};

#endif // TIMESLOTOBJECT_H
