#include "QApplication"
#include "QPushButton"
#include "ebisu/environment/environment.hpp"
#include "ebisu/gui/environment/environment.hpp"
#include "ebisu/utils/block_indenter.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace ebisu {
namespace gui {
namespace {
char const *app_descr = R"(

AllowedOptions)";
}

struct Program_options {
  Program_options(int argc, char **argv) {
    using namespace boost::program_options;
    variables_map parsed_options;
    store(parse_command_line(argc, argv, description()), parsed_options);
    if (parsed_options.count("help") > 0) {
      help_ = true;
      return;
    }
  }

  static boost::program_options::options_description const &description() {
    using namespace boost::program_options;
    static options_description options{app_descr};

    if (options.options().empty()) {
      options.add_options()("help,h", "Display help information");
    }
    return options;
  }

  static void show_help(std::ostream &out) {
    out << description();
    out.flush();
  }

  friend inline std::ostream &operator<<(std::ostream &out,
                                         Program_options const &item) {
    out << "Program_options(" << &item << ") {";
    out << "\n  help:" << item.help_;
    out << "\n}\n";
    return out;
  }

  //! getter for help_ (access is Ro)
  bool help() const { return help_; }

 private:
  bool help_{};
};

// custom <FcbEndNamespace environment>

namespace environment {

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

void Q_environment::populate_variable_list() {
  using namespace ebisu::environment;
  auto const &env = Environment::instance();
  variable_list_table_->setColumnCount(2);
  variable_list_table_->setRowCount(env.environment().size());
  variable_list_table_->setSortingEnabled(true);
  variable_list_table_->setSelectionMode(QAbstractItemView::ExtendedSelection);
  variable_list_table_->setAutoFillBackground(true);
  QTableWidgetItem *variableColumnHeader(
      new QTableWidgetItem(QString("Variable")));
  variable_list_table_->setHorizontalHeaderItem(0, variableColumnHeader);
  variableColumnHeader->setTextAlignment(Qt::AlignLeft);
  QTableWidgetItem *valueColumnHeader(new QTableWidgetItem(QString("Value")));
  valueColumnHeader->setTextAlignment(Qt::AlignLeft);
  variable_list_table_->setHorizontalHeaderItem(1, valueColumnHeader);

  size_t index(0);
  for (auto const &vt : env.environment()) {
    variable_list_table_->setItem(
        index, 0, new QTableWidgetItem(QString(vt.first.c_str())));
    variable_list_table_->setItem(
        index, 1, new QTableWidgetItem(QString(vt.second.c_str())));
    ++index;
  }
  variable_list_table_->verticalHeader()->hide();
  variable_list_table_->verticalHeader()->setDefaultSectionSize(15);
  variable_list_table_->resizeColumnsToContents();
}
}

// end <FcbEndNamespace environment>

}  // namespace gui
}  // namespace ebisu

int main(int argc, char **argv) {
  using namespace ebisu::gui;
  try {
    //////////////////////////////////////////////////////////////////////
    // Read program options and display help if requested
    //////////////////////////////////////////////////////////////////////
    Program_options options = {argc, argv};
    if (options.help()) {
      Program_options::show_help(std::cout);
      return 0;
    }

    //////////////////////////////////////////////////////////////////////
    // User supplied environment protect block
    //////////////////////////////////////////////////////////////////////
    // custom <main>

    using namespace ebisu::gui::environment;

    QApplication app(argc, argv);
    //Q_environment env(nullptr);
    //env.show();

    return app.exec();

    // end <main>

  } catch (boost::program_options::error const &e) {
    std::cerr << "Caught boost program options exception: " << e.what()
              << std::endl;
    Program_options::show_help(std::cout);
    return -1;
  } catch (std::exception const &e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
    return -1;
  }
  return 0;
}
