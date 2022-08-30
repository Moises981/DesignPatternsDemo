#include <boost/lexical_cast.hpp>
#include <string>
#include <fstream>
#include <vector>

struct Journal {
  std::string title;
  std::vector<std::string> entries;

  Journal(const std::string &title) : title(title) {}

  void add_entry(const std::string &entry) {
    static int count = 1;
    entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
  }
};

struct PersistanceManager {
  static void save(const Journal &journal, const std::string &filename) {
    std::ofstream ofs(filename);
    for (auto &entry : journal.entries) {
      ofs << entry << std::endl;
    }
  }
};

int main() {
  Journal journal{"Dear diary"};
  journal.add_entry("I bought a course");
  journal.add_entry("I want to know more about C++");

  PersistanceManager pm;
  pm.save(journal, "./diary.txt");
  getchar();
  return 0;
}