#include "timetablecontroller.h"
#include "timetable.h"


void TimetableController::index()
{
    auto timetableList = Timetable::getAll();
    texport(timetableList);
    render();
}

void TimetableController::show(const QString &id)
{
    auto timetable = Timetable::get(id.toInt());
    texport(timetable);
    render();
}

void TimetableController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

//    case Tf::Post: {
//        auto timetable = httpRequest().formItems("timetable");
//        auto model = Timetable::create(timetable);
//
//        if (!model.isNull()) {
//            QString notice = "Created successfully.";
//            tflash(notice);
//            redirect(urla("show", model.id()));
//        } else {
//            QString error = "Failed to create.";
//            texport(error);
//            texport(timetable);
//            render();
//        }
//        break; }

    case Tf::Post: {
        auto blockList = Block::getAll();
        auto classroomList = Classroom::getAll();
        auto timeSlotList = TimeSlot::getAll();

        auto timetableList = Timetable::calculate(blockList, classroomList, timeSlotList);
        redirect(urla("index"));
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

//void TimetableController::save(const QString &id)
//{
//    switch (httpRequest().method()) {
//    case Tf::Get: {
//        auto model = Timetable::get(id.toInt());
//        if (!model.isNull()) {
//            auto timetable = model.toVariantMap();
//            texport(timetable);
//            render();
//        }
//        break; }
//
//    case Tf::Post: {
//        QString error;
//        auto model = Timetable::get(id.toInt());
//
//        if (model.isNull()) {
//            error = "Original data not found. It may have been updated/removed by another transaction.";
//            tflash(error);
//            redirect(urla("save", id));
//            break;
//        }
//
//        auto timetable = httpRequest().formItems("timetable");
//        model.setProperties(timetable);
//        if (model.save()) {
//            QString notice = "Updated successfully.";
//            tflash(notice);
//            redirect(urla("show", model.id()));
//        } else {
//            error = "Failed to update.";
//            texport(error);
//            texport(timetable);
//            render();
//        }
//        break; }
//
//    default:
//        renderErrorResponse(Tf::NotFound);
//        break;
//    }
//}

//void TimetableController::remove(const QString &id)
//{
//    if (httpRequest().method() != Tf::Post) {
//        renderErrorResponse(Tf::NotFound);
//        return;
//    }
//
//    auto timetable = Timetable::get(id.toInt());
//    timetable.remove();
//    redirect(urla("index"));
//}

void TimetableController::removeAll()
{
    auto timetableList = Timetable::getAll();
    for (auto obj: timetableList) {
      obj.remove();
    }
    redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(TimetableController)
