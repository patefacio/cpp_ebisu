#ifndef __EBISU_GUI_ENVIRONMENT_ENVIRONMENT_HPP__
#define __EBISU_GUI_ENVIRONMENT_ENVIRONMENT_HPP__

#include "QHeaderView"
#include "QSplitter"
#include "QTableWidget"
#include "QTreeView"
#include <array>

namespace ebisu {
namespace gui {
namespace environment {
class Tree_path_model : public QAbstractItemModel {
  Q_OBJECT

 public:
  using Header_array_t = std::array<char *, 3>;

  // custom <ClsPublic Tree_path_model>
  // end <ClsPublic Tree_path_model>

  //! getter for column_headers_ (access is Ro)
  Header_array_t column_headers() const { return column_headers_; }

  //! getter for column_count_ (access is Ro)
  size_t column_count() const { return column_count_; }

 private:
  static Header_array_t column_headers_{};
  static size_t column_count_{};
};

class Q_environment : public QWidget {
  Q_OBJECT

 public:
  // custom <ClsPublic Q_environment>

  void populate_variable_list() {
    using namespace ebisu::environment;
    auto const &env = Environment::instance();
    variable_list_table_->setColumnCount(2);
    variable_list_table_->setRowCount(env.environment().size());
    variable_list_table_->setSortingEnabled(true);
    variable_list_table_->setSelectionMode(
        QAbstractItemView::ExtendedSelection);
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

  void populate_parsed_paths() {
    using namespace ebisu::environment;
    tree_path_view_->setModel(tree_path_model_);
    path_splitter_->addWidget(tree_path_view_);
    auto const &env = Environment::instance();
    using ebisu::utils::streamers::operator<<;
    std::cout << env << std::endl;
  }

  void populate_problem_table() {
    problem_table_->setColumnCount(column_count);
    problem_table_->setRowCount(5);
    problem_table_->setSortingEnabled(true);
    problem_table_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    problem_table_->setAutoFillBackground(true);
    problem_table_->verticalHeader()->hide();
    problem_table_->verticalHeader()->setDefaultSectionSize(15);

    for (size_t index = 0; index < column_count; ++index) {
      QTableWidgetItem *columnHeader(
          new QTableWidgetItem(QString(headers[index])));
      columnHeader->setTextAlignment(Qt::AlignLeft);
      problem_table_->setHorizontalHeaderItem(index, columnHeader);
    }

    QBoxLayout *problem_table_box_layout(
        new QBoxLayout(QBoxLayout::TopToBottom));
    problem_table_box_layout->addWidget(
        new QLabel("Potential Problem Files in XXX"));
    problem_table_box_layout->addWidget(problem_table_);
    path_splitter_->setLayout(problem_table_box_layout);
  }

  // end <ClsPublic Q_environment>

 private:
  QTableWidget *variable_list_table_{};
  QSplitter *slpitter_{};
  Tree_path_model *tree_path_model_{};
  QTreeView *tree_path_view_{};
  QSplitter *path_splitter_{};
  QTableWidget *problem_table_{};
};

}  // namespace environment
}  // namespace gui
}  // namespace ebisu

#endif  // __EBISU_GUI_ENVIRONMENT_ENVIRONMENT_HPP__
