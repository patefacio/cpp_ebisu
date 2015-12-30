#ifndef __EBISU_GUI_ENVIRONMENT_Q_ENVIRONMENT_HPP__
#define __EBISU_GUI_ENVIRONMENT_Q_ENVIRONMENT_HPP__

#include "QBoxLayout"
#include "QHeaderView"
#include "QLabel"
#include "QSplitter"
#include "QTableWidget"
#include "QTreeView"
#include "ebisu/environment/environment.hpp"
#include "ebisu/timestamp/timestamp.hpp"
#include "ebisu/utils/block_indenter.hpp"
#include "ebisu/utils/streamers/vector.hpp"
#include <array>
#include <iosfwd>
#include <string>
#include <vector>

namespace ebisu {
namespace gui {
namespace environment {
class Tree_data_item {
 public:
  using Tree_data_item_ptr_t = Tree_data_item *;
  using Tree_data_item_sptr_t = std::shared_ptr<Tree_data_item>;
  using Tree_data_item_list_t = std::vector<Tree_data_item_sptr_t>;

  Tree_data_item(std::string const &data, int row,
                 Tree_data_item_ptr_t parent = nullptr,
                 std::string const &file_size = std::string(),
                 std::string const &last_modified = std::string())
      : data_(data),
        row_(row),
        parent_(parent),
        file_size_(file_size),
        last_modified_(last_modified) {}

  friend inline std::ostream &operator<<(std::ostream &out,
                                         Tree_data_item const &item) {
    using ebisu::utils::streamers::operator<<;
    out << "Tree_data_item(" << &item << ") {";
    out << "\n  data:" << item.data_;
    out << "\n  row:" << item.row_;
    out << "\n  parent:" << item.parent_;
    out << "\n  file_size:" << item.file_size_;
    out << "\n  last_modified:" << item.last_modified_;
    out << "\n  children:" << item.children_;
    out << "\n}\n";
    return out;
  }

  // custom <ClsPublic Tree_data_item>

  Tree_data_item_sptr_t child(int i) {
    if ((i >= 0) and (i < int(children_.size()))) {
      return children_[i];
    } else {
      return Tree_data_item_sptr_t();
    }
  }

  int row_count() const { return children_.size(); }

  void add_child(Tree_data_item_sptr_t const &child) {
    children_.push_back(child);
  }

  // end <ClsPublic Tree_data_item>

  //! getter for data_ (access is Ro)
  std::string const &data() const { return data_; }

  //! getter for row_ (access is Ro)
  int row() const { return row_; }

  //! getter for parent_ (access is Ro)
  Tree_data_item_ptr_t parent() const { return parent_; }

  //! getter for file_size_ (access is Ro)
  std::string const &file_size() const { return file_size_; }

  //! getter for last_modified_ (access is Ro)
  std::string const &last_modified() const { return last_modified_; }

  //! getter for children_ (access is Ro)
  Tree_data_item_list_t children() const { return children_; }

 private:
  std::string data_{};
  int row_{0};
  Tree_data_item_ptr_t parent_{};
  std::string file_size_{};
  std::string last_modified_{};
  Tree_data_item_list_t children_{};
};

class Tree_path_model : public QAbstractItemModel {
  Q_OBJECT

 public:
  using Header_array_t = std::array<char const *, 3>;
  using Tree_data_item_sptr_t = Tree_data_item::Tree_data_item_sptr_t;
  using Tree_data_item_ptr_t = Tree_data_item::Tree_data_item_ptr_t;

  // custom <ClsPublic Tree_path_model>

  Tree_path_model() {
    using namespace ebisu::environment;
    using namespace ebisu::utils::streamers;
    using namespace boost::filesystem;
    using Path_t = Environment::Path_t;

    auto const &path_variable_map = Environment::instance().path_variable_map();

    root_ = Tree_data_item_sptr_t(new Tree_data_item("Foo", 0, 0));
    size_t num_env_vars(0);
    for (Environment::Path_variable_map_t::value_type const &vt :
         path_variable_map) {
      Tree_data_item_sptr_t env_var_child(
          new Tree_data_item(vt.first, num_env_vars++, root_.get()));
      root_->add_child(env_var_child);
      size_t num_paths(0);
      for (Path_t const &path : vt.second) {
        Tree_data_item_sptr_t path_child(new Tree_data_item(
            path.string(), num_paths++, env_var_child.get()));
        env_var_child->add_child(path_child);

        if (is_directory(path)) {
          directory_iterator end_itr;
          size_t num_files(0);
          for (directory_iterator dir_iter(path); dir_iter != end_itr;
               ++dir_iter) {
            Path_t file_path(dir_iter->path());
            bool file_is_directory(is_directory(file_path));
            bool file_is_symlink(is_symlink(file_path));
            std::cout << file_path << " " << file_is_symlink << " & "
                      << file_is_directory << std::endl;
            bool read_file_size(!file_is_symlink and !file_is_directory);
            std::string last_write_time_string;
            if (read_file_size) {
              ebisu::timestamp::Timestamp_t last_write_timestamp(
                  boost::posix_time::from_time_t(last_write_time(file_path)));
              last_write_time_string = to_simple_string(last_write_timestamp);
            }
            Tree_data_item_sptr_t file_child(new Tree_data_item(
                boost::filesystem::basename(file_path), num_files++,
                path_child.get(),
                read_file_size ? stream_to_string(file_size(file_path))
                               : std::string(),
                last_write_time_string));
            path_child->add_child(file_child);
          }
        }
      }
    }
  }

  virtual ~Tree_path_model() override;

  QModelIndex index(int row, int column,
                    const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  static Header_array_t column_headers() {
    static Header_array_t result{"Variable/Path/File", "Size", "Last Modified"};
    return result;
  }

  // end <ClsPublic Tree_path_model>

 private:
  Tree_data_item_sptr_t root_{};
};

class Q_environment : public QWidget {
  Q_OBJECT

 public:
  // custom <ClsPublic Q_environment>

  explicit Q_environment(QWidget *parent)
      : QWidget(parent),
        variable_list_table_(new QTableWidget()),
        splitter_(new QSplitter(this)),
        tree_path_model_(new Tree_path_model()),
        tree_path_view_(new QTreeView()),
        path_splitter_(new QSplitter(Qt::Vertical)),
        problem_table_(new QTableWidget()) {

    populate_variable_list();
    populate_parsed_paths();
    populate_problem_table();

    setWindowTitle("Environment variables");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    splitter_->addWidget(variable_list_table_);
    splitter_->addWidget(path_splitter_);
    mainLayout->addWidget(splitter_);
    setLayout(mainLayout);
  }

  virtual ~Q_environment() override;
  void populate_variable_list();
  void populate_parsed_paths();
  void populate_problem_table();

  // end <ClsPublic Q_environment>

 private:
  QTableWidget *variable_list_table_{};
  QSplitter *splitter_{};
  Tree_path_model *tree_path_model_{};
  QTreeView *tree_path_view_{};
  QSplitter *path_splitter_{};
  QTableWidget *problem_table_{};
};

}  // namespace environment
}  // namespace gui
}  // namespace ebisu

#endif  // __EBISU_GUI_ENVIRONMENT_Q_ENVIRONMENT_HPP__
