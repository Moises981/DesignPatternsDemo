#include <iostream>
#include <string>
#include <tuple>
#include <vector>

enum class RelationShip { parent, child, sibling };

struct Person {
  std::string name;
};

struct RelationShipBrowser {
  virtual std::vector<Person> find_all_children_of(const std::string &name) = 0;
};

struct RelationShips : RelationShipBrowser {
  std::vector<std::tuple<Person, RelationShip, Person>> relations;

  void add_parent_and_child(const Person &parent, const Person &child) {
    relations.push_back({parent, RelationShip::parent, child});
    relations.push_back({child, RelationShip::child, parent});
  }

  std::vector<Person> find_all_children_of(const std::string &name) {
    std::vector<Person> result;
    for (auto &item : relations) {
      auto &&first = std::get<0>(item);
      auto &&rel = std::get<1>(item);
      auto &&second = std::get<2>(item);
      if (first.name == name, rel == RelationShip::parent) {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research {
  Research(RelationShipBrowser &browser) {
    for (auto &child : browser.find_all_children_of("John")) {
      std::cout << "John has a child called " << child.name << std::endl;
    }
  }
};

int main() {
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};
  RelationShips relationShips;
  relationShips.add_parent_and_child(parent, child1);
  relationShips.add_parent_and_child(parent, child2);
  return 0;
}