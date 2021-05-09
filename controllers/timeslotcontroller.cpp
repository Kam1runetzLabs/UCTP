#include "timeslotcontroller.h"

#include "timeslot.h"

void TimeSlotController::index() {
  auto timeSlotList = TimeSlot::getAll();
  texport(timeSlotList);
  render();
}

void TimeSlotController::show(const QString &id) {
  auto timeSlot = TimeSlot::get(id.toInt());
  texport(timeSlot);
  render();
}

void TimeSlotController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto timeSlot = httpRequest().formItems("timeSlot");
      auto model = TimeSlot::create(timeSlot);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(timeSlot);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void TimeSlotController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = TimeSlot::get(id.toInt());
      if (!model.isNull()) {
        auto timeSlot = model.toVariantMap();
        texport(timeSlot);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = TimeSlot::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto timeSlot = httpRequest().formItems("timeSlot");
      model.setProperties(timeSlot);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(timeSlot);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void TimeSlotController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto timeSlot = TimeSlot::get(id.toInt());
  timeSlot.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(TimeSlotController)
