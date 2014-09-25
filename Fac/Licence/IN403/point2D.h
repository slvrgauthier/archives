#ifndef POINT2D_H
#define POINT2D_H
class Point2D{
  private:
    float x;
    float y;

  public:
    Point2D();
    Point2D(float,float);

    void affiche() const;
    double distance(const Point2D&) const;

    float getX() const;
    void setX(float);
    float getY() const;
    void setY(float);
};
#endif
