#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle{
  private:
    Point2D A;
    Point2D B;
    Point2D C;

  public:
    Triangle(const Point2D&,const Point2D&,const Point2D&);

    bool isoc() const;
    bool rect() const;
    bool equi() const;

    double peri() const;
};

#endif
