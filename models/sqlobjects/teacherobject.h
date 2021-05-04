#ifndef TEACHEROBJECT_H
#define TEACHEROBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT TeacherObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString teacherName;

    enum PropertyIndex {
        Id = 0,
        TeacherName,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("teacher"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString teacherName READ getteacherName WRITE setteacherName)
    T_DEFINE_PROPERTY(QString, teacherName)
};

#endif // TEACHEROBJECT_H
