#include "groupcontroller.h"

#include "group.h"

void GroupController::index() {
  auto groupList = Group::getAll();
  texport(groupList);
  render();
}

void GroupController::show(const QString &id) {
  auto group = Group::get(id.toInt());
  texport(group);
  render();
}

void GroupController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto group = httpRequest().formItems("group");
      auto model = Group::create(group);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(group);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void GroupController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = Group::get(id.toInt());
      if (!model.isNull()) {
        auto group = model.toVariantMap();
        texport(group);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = Group::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto group = httpRequest().formItems("group");
      model.setProperties(group);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(group);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void GroupController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto group = Group::get(id.toInt());
  group.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(GroupController)
