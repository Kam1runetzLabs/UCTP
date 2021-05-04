#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT GroupObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString groupName;

    enum PropertyIndex {
        Id = 0,
        GroupName,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("group"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString groupName READ getgroupName WRITE setgroupName)
    T_DEFINE_PROPERTY(QString, groupName)
};

#endif // GROUPOBJECT_H
