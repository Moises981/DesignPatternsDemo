#include <iostream>
#include <string>
#include <vector>

enum class Color { red, green, blue };

enum class Size { small, medium, large };

struct Product {
  std::string name;
  Color color;
  Size size;
};

template <typename T> struct Specification {
  virtual bool is_satisfied(T *item) const = 0;
};

template <typename T> struct Filter {
  virtual std::vector<T *> filter(std::vector<T *> items,
                                  Specification<T> &spec) const;
};

struct BetterFilter {
  virtual std::vector<Product *> filter(std::vector<Product *> items,
                                        Specification<Product> &spec) const {
    std::vector<Product *> result;
    for (auto &item : items) {
      if (spec.is_satisfied(item)) {
        result.push_back(item);
      }
    }
    return result;
  }
};

template <typename T> struct AndSpecification : Specification<T> {
  const Specification<T> &first;
  const Specification<T> &second;

  AndSpecification(const Specification<T> &first,
                   const Specification<T> &second)
      : first(first), second(second) {}

  bool is_satisfied(T *item) const override {
    bool d = first.is_satisfied(item) && second.is_satisfied(item);
    return d;
  }
};

template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first,
                               const Specification<T> &second) {
  return {first, second};
}

struct ColorSpecification : Specification<Product> {
  Color color;
  explicit ColorSpecification(Color color) : color(color) {}
  bool is_satisfied(Product *item) const override {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product> {
  Size size;
  explicit SizeSpecification(Size size) : size(size) {}
  bool is_satisfied(Product *item) const override { return item->size == size; }
};

int main() {
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const std::vector<Product *> all{&apple, &tree, &house};

  BetterFilter bf;
  ColorSpecification green(Color::green);
  auto green_things = bf.filter(all, green);

  for (auto &x : green_things)
    std::cout << x->name << " is green\n";

  SizeSpecification large(Size::large);

  auto spec = green && large;

  for (auto &x : bf.filter(all, spec)) {
    std::cout << x->name << " is green and large\n";
  }

  return 0;
}