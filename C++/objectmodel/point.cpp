#include <iostream>
using namespace std;
struct stPoint {
  double _x, _y, _z;
  stPoint(double x = 0, double y = 0, double z = 0) : _x(x), _y(y), _z(z){};
  friend ostream &operator<<(ostream &os, const stPoint &pt);
};
ostream &operator<<(ostream &os, const stPoint &pt) {
  os << "(" << pt._x << "," << pt._y << "," << pt._z << ")";
  return os;
}
class Point {
public:
  Point(double x) : _x(x) {}
  friend ostream &operator<<(ostream &os, const Point &pt);

protected:
  double _x;
};
inline ostream &operator<<(ostream &os, const Point &pt) {
  os << pt._x;
  return os;
}
class Point2D : public Point {
public:
  Point2D(double x = 0, double y = 0) : Point(x), _y(y) {}
  friend ostream &operator<<(ostream &os, const Point2D &pt);

protected:
  double _y;
};
inline ostream &operator<<(ostream &os, const Point2D &pt) {
  os << pt._x << "," << pt._y;
  return os;
}

class Point3D : public Point2D {
public:
  Point3D(double x = 0, double y = 0, double z = 0) : Point2D(x, y), _z(z) {}
  friend ostream &operator<<(ostream &os, const Point3D &pt);

protected:
  double _z;
};
inline ostream &operator<<(ostream &os, const Point3D &pt) {
  os << "(" << pt._x << "," << pt._y << "," << pt._z << ")";
  return os;
}

template <class T> class PointT {
public:
  PointT(T x = 0, T y = 0, T z = 0) : _x(x), _y(y), _z(z) {}
  template <class V>
  friend ostream &operator<<(ostream &os, const PointT<V> &pt);

protected:
  T _x, _y, _z;
};

template <class V> ostream &operator<<(ostream &os, const PointT<V> &pt) {
  os << "(" << pt._x << "," << pt._y << "," << pt._z << ")";
  return os;
};

int main(int argc, char *argv[]) {
  stPoint pt1;
  cout << "stPoint's size:" << sizeof(pt1) << endl;
  Point3D pt2;
  cout << "Point3D's size:" << sizeof(pt2) << endl;
  PointT<double> pt3;
  cout << "PointT<double>'s size:" << sizeof(pt3) << endl;
}
