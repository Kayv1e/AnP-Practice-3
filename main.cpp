#include <iostream>

namespace topit
{
  struct p_t
  {
    int x, y;
  };

  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);

  struct f_t
  {
    p_t aa, bb;
  };

  struct IDraw
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  struct Dot: IDraw
  {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };
}

int main()
{
  using topit::Dot;
  using topit::IDraw;
  int err = 0;
  IDraw * shps[3] = {};
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    // TODO:
    // get all dots from shapes
    // count frame
    // make a canvas
    // - fill the canvas with '.'
    // draw all dots got from shapes
    // - draw '#'
    // display canvas
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }

  delete shps[0];
  delete shps[1];
  delete shps[2];
  return err;
}

topit::Dot::Dot(p_t dd):
  IDraw(),
  d{dd}
{}

topit::Dot::Dot(int x, int y):
  IDraw(),
  d{x, y}
{}

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const
{
  if (prev != begin()) {
    throw std::logic_error("Bad implementation");
  }
  return d;
}

bool topit::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return !(a == b);
}
