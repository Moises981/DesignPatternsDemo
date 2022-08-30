#include <iostream>
#include <string>
#include <vector>

class Rectangle {
protected:
  int width, height;

public:
  Rectangle(int width, int height) : width(width), height(height) {}

  int getWidth() const { return width; }
  virtual void setWidth(int width) { Rectangle::width = width; }
  int getHeight() const { return width; }
  virtual void setHeight(int height) { Rectangle::height = height; }

  int area() const { return width * height; }
};

class Square : public Rectangle {
public:
  Square(int size) : Rectangle(size, size) {}

  virtual void setWidth(int width) override {
    Rectangle::width = Rectangle::height = width;
  }

  virtual void setHeight(int height) override {
    Rectangle::width = Rectangle::height = height;
  }
};

void process(Rectangle &rect) {
  int w = rect.getWidth();
  rect.setHeight(10);
  std::cout << "Expected area = " << (w * 10) << ", got " << rect.area()
            << std::endl;
}

struct RectangleFactory {
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};

int main() {
  Rectangle rect{4, 3};
  process(rect);

  Square sqr{4};
  process(sqr);
  return 0;
}