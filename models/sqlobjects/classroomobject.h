#ifndef CLASSROOMOBJECT_H
#define CLASSROOMOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT ClassroomObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QString classroomName;
    int classroomType {0};

    enum PropertyIndex {
        Id = 0,
        ClassroomName,
        ClassroomType,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("classroom"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString classroomName READ getclassroomName WRITE setclassroomName)
    T_DEFINE_PROPERTY(QString, classroomName)
    Q_PROPERTY(int classroomType READ getclassroomType WRITE setclassroomType)
    T_DEFINE_PROPERTY(int, classroomType)
};

#endif // CLASSROOMOBJECT_H
