#include "timetablecontroller.h"

#include "block.h"
#include "classroom.h"
#include "group.h"
#include "subject.h"
#include "teacher.h"
#include "timeslot.h"
#include "timetable.h"

void TimetableController::index() {
  auto timetableList = Timetable::getAll();
  QList<TimeSlot> timeSlots;
  QList<Classroom> classrooms;
  Block block;
  QList<Group> groups;
  QList<Teacher> teachers;
  QList<Subject> subjects;
  for (auto const &timetable : timetableList) {
    timeSlots.append(TimeSlot::get(timetable.timeId()));
    classrooms.append(Classroom::get(timetable.timeId()));
    block = Block::get(timetable.blockId());
    groups.append(Group::get(block.groupId()));
    teachers.append(Teacher::get(block.teacherId()));
    subjects.append(Subject::get(block.subjectId()));
  }
  texport(timetableList);
  texport(timeSlots);
  texport(classrooms);
  texport(groups);
  texport(teachers);
  texport(subjects);
  render();
}

void TimetableController::show(const QString &id) {
  auto timetable = Timetable::get(id.toInt());
  texport(timetable);
  render();
}

void TimetableController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      //      auto timeSlots = TimeSlot::getAll();
      //      auto blocks = Block::getAll();
      //      auto classrooms = Classroom::getAll();
      //
      // create model from time, blocks and classrooms
      auto timetable = httpRequest().formItems("timetable");
      auto model = Timetable::create(timetable);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        // todo redirect to index
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(timetable);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void TimetableController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = Timetable::get(id.toInt());
      if (!model.isNull()) {
        auto timetable = model.toVariantMap();
        texport(timetable);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = Timetable::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto timetable = httpRequest().formItems("timetable");
      model.setProperties(timetable);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(timetable);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void TimetableController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto timetable = Timetable::get(id.toInt());
  timetable.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(TimetableController)
