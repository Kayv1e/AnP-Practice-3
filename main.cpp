#include <cstddef>
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

  struct HorizontalLine: IDraw
  {
    HorizontalLine(p_t s, p_t e);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t start, end;
  };

  struct Rectangle: IDraw
  {
    Rectangle(p_t s, p_t e);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t start, end;
  };

  // HOME TASK
  // add 2-3 more shapes (e.g. vertical line, horizontal line, diagonal line 45 degrees, or my own)

  // extend with points from a shape
  size_t points(const IDraw & d, p_t ** pts, size_t & s);

  // min and max on x and y from all points and create frame
  f_t frame(const p_t * pts, size_t s);

  // get rows and columns from frame
  char * canvas(f_t fr, char filler);

  // convert dot coordinates to 2d array coordinates
  void paint(char * cnv, f_t fr, p_t p, char filler);

  // display 2d array using rows and columns from frame
  void flush(std::ostream & os, const char * cnv, f_t fr);
}

int main()
{
  using topit::p_t;
  using topit::f_t;
  using topit::Dot;
  using topit::IDraw;
  using topit::frame;
  int err = 0;
  IDraw * shps[3] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    for (size_t i = 0; i < 3; ++i) {
      s += points(*(shps[i]), &pts, s);
    }
    f_t fr = frame(pts, s);
    char * cnv = canvas(fr, '.');
    for (size_t i = 0; i < s; ++i) {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete [] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }

  delete [] pts;
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

topit::Rectangle::Rectangle(p_t s, p_t e):
  start(s),
  end(e)
{}

topit::p_t topit::Rectangle::begin() const
{
  return start;
}

topit::p_t topit::Rectangle::next(p_t prev) const
{
  if (prev.y == start.y && start.x <= prev.x && prev.x < end.x) {
    return {prev.x + 1, prev.y};
  }
  if (prev.x == end.x && start.y >= prev.y && prev.y > end.y) {
    return {prev.x, prev.y - 1};
  }
  if (prev.y == end.y && start.x < prev.x && prev.x <= end.x) {
    return {prev.x - 1, prev.y};
  }
  if (prev.x == start.x && start.y > prev.y && prev.y >= end.y) {
    return {prev.x, prev.y + 1};
  }
  throw std::logic_error("Bad implementation");
}

topit::HorizontalLine::HorizontalLine(p_t s, p_t e):
  IDraw(),
  start(s),
  end(e)
{}

topit::p_t topit::HorizontalLine::begin() const
{
  return start;
}

topit::p_t topit::HorizontalLine::next(p_t prev) const
{
  if (prev == end) {
    return start;
  }
  if (prev.y == start.y && start.x <= prev.x && prev.x < end.x) {
    return {prev.x + 1, prev.y};
  }
  throw std::logic_error("Bad implementation");
}

bool topit::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return !(a == b);
}
