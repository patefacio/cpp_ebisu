#include "ebisu/gui/environment/q_environment.hpp"

namespace ebisu {
namespace gui {
namespace environment {
// custom <FcbBeginNamespace q_environment>

Q_environment::~Q_environment() {}

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

void Q_environment::populate_parsed_paths() {
  using namespace ebisu::environment;
  tree_path_view_->setModel(tree_path_model_);
  path_splitter_->addWidget(tree_path_view_);
  auto const &env = Environment::instance();
  using ebisu::utils::streamers::operator<<;
  std::cout << env << std::endl;
}

void Q_environment::populate_problem_table() {
  const size_t column_count = Tree_path_model::column_headers().size();
  problem_table_->setColumnCount(column_count);
  problem_table_->setRowCount(5);
  problem_table_->setSortingEnabled(true);
  problem_table_->setSelectionMode(QAbstractItemView::ExtendedSelection);
  problem_table_->setAutoFillBackground(true);
  problem_table_->verticalHeader()->hide();
  problem_table_->verticalHeader()->setDefaultSectionSize(15);

  {
    int index{0};
    for (auto header : Tree_path_model::column_headers()) {
      QTableWidgetItem *columnHeader(new QTableWidgetItem(QString(header)));
      columnHeader->setTextAlignment(Qt::AlignLeft);
      problem_table_->setHorizontalHeaderItem(index++, columnHeader);
    }
  }

  QBoxLayout *problem_table_box_layout(new QBoxLayout(QBoxLayout::TopToBottom));
  problem_table_box_layout->addWidget(
      new QLabel("Potential Problem Files in XXX"));
  problem_table_box_layout->addWidget(problem_table_);
  path_splitter_->setLayout(problem_table_box_layout);
}

// end <FcbBeginNamespace q_environment>

}  // namespace environment
}  // namespace gui
}  // namespace ebisu
