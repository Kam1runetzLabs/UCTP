#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class TimeSlotObject;
class QJsonArray;


class T_MODEL_EXPORT TimeSlot : public TAbstractModel
{
public:
    TimeSlot();
    TimeSlot(const TimeSlot &other);
    TimeSlot(const TimeSlotObject &object);
    ~TimeSlot();

    int id() const;
    QString timeSlotName() const;
    void setTimeSlotName(const QString &timeSlotName);
    TimeSlot &operator=(const TimeSlot &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static TimeSlot create(const QString &timeSlotName);
    static TimeSlot create(const QVariantMap &values);
    static TimeSlot get(int id);
    static int count();
    static QList<TimeSlot> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<TimeSlotObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const TimeSlot &model);
    friend QDataStream &operator>>(QDataStream &ds, TimeSlot &model);
};

Q_DECLARE_METATYPE(TimeSlot)
Q_DECLARE_METATYPE(QList<TimeSlot>)

#endif // TIMESLOT_H
