#include "blockcontroller.h"

#include "block.h"

void BlockController::index() {
  auto blockList = Block::getAll();
  texport(blockList);
  render();
}

void BlockController::show(const QString &id) {
  auto block = Block::get(id.toInt());
  texport(block);
  render();
}

void BlockController::create() {
  switch (httpRequest().method()) {
    case Tf::Get:
      render();
      break;

    case Tf::Post: {
      auto block = httpRequest().formItems("block");
      auto model = Block::create(block);

      if (!model.isNull()) {
        QString notice = "Created successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        QString error = "Failed to create.";
        texport(error);
        texport(block);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void BlockController::save(const QString &id) {
  switch (httpRequest().method()) {
    case Tf::Get: {
      auto model = Block::get(id.toInt());
      if (!model.isNull()) {
        auto block = model.toVariantMap();
        texport(block);
        render();
      }
      break;
    }

    case Tf::Post: {
      QString error;
      auto model = Block::get(id.toInt());

      if (model.isNull()) {
        error =
            "Original data not found. It may have been updated/removed by "
            "another transaction.";
        tflash(error);
        redirect(urla("save", id));
        break;
      }

      auto block = httpRequest().formItems("block");
      model.setProperties(block);
      if (model.save()) {
        QString notice = "Updated successfully.";
        tflash(notice);
        redirect(urla("show", model.id()));
      } else {
        error = "Failed to update.";
        texport(error);
        texport(block);
        render();
      }
      break;
    }

    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void BlockController::remove(const QString &id) {
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto block = Block::get(id.toInt());
  block.remove();
  redirect(urla("index"));
}

// Don't remove below this line
T_DEFINE_CONTROLLER(BlockController)
