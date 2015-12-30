#include "ebisu/gui/environment/q_environment.hpp"

namespace ebisu {
namespace gui {
namespace environment {
// custom <FcbBeginNamespace tree_path_model>

Tree_path_model::~Tree_path_model() {}

QModelIndex Tree_path_model::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }
  Tree_data_item_ptr_t parent_item(
      parent.isValid()
          ? static_cast<Tree_data_item_ptr_t>(parent.internalPointer())
          : root_.get());
  Tree_data_item_ptr_t child_item(parent_item->child(row).get());
  return child_item ? createIndex(row, column, child_item) : QModelIndex();
}

QModelIndex Tree_path_model::parent(const QModelIndex &child) const {
  if (!child.isValid()) {
    return QModelIndex();
  } else {
    Tree_data_item_ptr_t child_item(
        static_cast<Tree_data_item_ptr_t>(child.internalPointer()));
    Tree_data_item_ptr_t parent(child_item->parent());
    if (parent and (parent != root_.get())) {
      return createIndex(parent->row(), 0, parent);
    } else {
      return QModelIndex();
    }
  }
}

int Tree_path_model::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) {
    return 0;
  } else {
    Tree_data_item_ptr_t result_item(
        parent.isValid()
            ? static_cast<Tree_data_item_ptr_t>(parent.internalPointer())
            : root_.get());
    return result_item->row_count();
  }
}

int Tree_path_model::columnCount(const QModelIndex &) const {
  column_headers().size();
}

QVariant Tree_path_model::data(const QModelIndex &index, int role) const {
  if (index.isValid()) {
    if (role == Qt::DisplayRole) {
      Tree_data_item_ptr_t item(
          static_cast<Tree_data_item_ptr_t>(index.internalPointer()));
      switch (index.column()) {
        case 0:
          return QVariant(item->data().c_str());
        case 1:
          return QVariant(item->file_size().c_str());
        case 2:
          return QVariant(item->last_modified().c_str());
        default:
          return QVariant("TODO");
      }
    } else if (role == Qt::TextAlignmentRole) {
      switch (index.column()) {
        case 1:
          return QVariant(Qt::AlignRight);
        default:
          return QVariant();
      }
    } else {
      return QVariant();
    }
  } else {
    return QVariant();
  }
}

QVariant Tree_path_model::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section < column_headers().size()) {
      return QVariant(column_headers()[section]);
    }
  }
  return QVariant();
}

// end <FcbBeginNamespace tree_path_model>

}  // namespace environment
}  // namespace gui
}  // namespace ebisu
