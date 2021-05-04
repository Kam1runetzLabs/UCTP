#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class TimetableObject;
class QJsonArray;


class T_MODEL_EXPORT Timetable : public TAbstractModel
{
public:
    Timetable();
    Timetable(const Timetable &other);
    Timetable(const TimetableObject &object);
    ~Timetable();

    int id() const;
    int classroomId() const;
    void setClassroomId(int classroomId);
    int timeId() const;
    void setTimeId(int timeId);
    int blockId() const;
    void setBlockId(int blockId);
    Timetable &operator=(const Timetable &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Timetable create(int classroomId, int timeId, int blockId);
    static Timetable create(const QVariantMap &values);
    static Timetable get(int id);
    static int count();
    static QList<Timetable> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<TimetableObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Timetable &model);
    friend QDataStream &operator>>(QDataStream &ds, Timetable &model);
};

Q_DECLARE_METATYPE(Timetable)
Q_DECLARE_METATYPE(QList<Timetable>)

#endif // TIMETABLE_H
