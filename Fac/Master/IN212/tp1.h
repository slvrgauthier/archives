class Vector {
  private :
    double x;
    double y;
    double z;

  public :
    Vector() { x = y = z = (double)0; }
    Vector(const double x, const double y, const double z) { this->x = x; this->y = y; this->z = z; }
    Vector(const Vector& p) { x = p.getX(); y = p.getY(); z = p.getZ(); }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    void setX(const double x) { this->x = x; }
    void setY(const double y) { this->y = y; }
    void setZ(const double z) { this->z = z; }

    double Norme() const {
      return sqrt(x*x+y*y+z*z);
    }
    void Normalize() {
      double n = Norme();
      x /= n; y /= n; z /= n;
    }
    double Scalar(const Vector& vector2) const {
      return x*(vector2.getX())+y*(vector2.getY())+z*(vector2.getZ());
    }
    Vector Vectoriel(const Vector& vector2) const {
      return Vector(y*vector2.getZ()-z*vector2.getY(), z*vector2.getX()-x*vector2.getZ(), x*vector2.getY()-y*vector2.getX());
    }
    double Angle(const Vector& vector2) const {
      double cosA = (this->Scalar(vector2))/(Norme()*vector2.Norme());
      double sinA = (this->Vectoriel(vector2).Norme())/(Norme()*vector2.Norme());
      return (sinA < (double)0)?360-acos(cosA):acos(cosA);
    }

    void afficher(const double X, const double Y, const double Z) const {
	glBegin(GL_LINES);
		glVertex3f(X,Y,Z);
		glVertex3f(X+x,Y+y,Z+z);
	glEnd();
    }
};

class Point {
  public :
    double x;
    double y;
    double z;

  public :
    Point() { x = y = z = (double)0; }
    Point(const double x, const double y, const double z) { this->x = x; this->y = y; this->z = z; }
    Point(const Point& p) { x = p.getX(); y = p.getY(); z = p.getZ(); }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    void setX(const double x) { this->x = x; }
    void setY(const double y) { this->y = y; }
    void setZ(const double z) { this->z = z; }
    bool equals(const Point& p) { return (x==p.getX() && y==p.getY() && z==p.getZ()); }

    Point ProjectOnLine(const Point& Point1Line, const Point& Point2Line) const {
      Vector v2(x-Point2Line.getX(), y-Point2Line.getY(), z-Point2Line.getZ());
      return ProjectOnLine(Point1Line, v2);
    }

    Point ProjectOnLine(const Point& Point1, const Vector& vecteur) const {
      Vector v1(x-Point1.getX(), y-Point1.getY(), z-Point1.getZ());
      Vector v2 = vecteur;
      double distance = v1.Scalar(v2)/(v2.Norme());
      v2.Normalize();
      return Point(Point1.getX()+v2.getX()*distance, Point1.getY()+v2.getY()*distance, Point1.getZ()+v2.getZ()*distance);
    }

    Point ProjectOnPlan(const Point& PointOnPlane, const Vector& NormalOfPlane) const {
      Vector v1(x-PointOnPlane.getX(), y-PointOnPlane.getY(), z-PointOnPlane.getZ());
      double distance = v1.Scalar(NormalOfPlane)/(NormalOfPlane.Norme());
      return Point(PointOnPlane.getX()+NormalOfPlane.getX()*distance, PointOnPlane.getY()+NormalOfPlane.getY()*distance, PointOnPlane.getZ()+NormalOfPlane.getZ()*distance);
    }

    void afficher() {
	glBegin(GL_QUADS);
		glVertex3f(x-0.02,y-0.02,z);
		glVertex3f(x+0.02,y-0.02,z);
		glVertex3f(x+0.02,y+0.02,z);
		glVertex3f(x-0.02,y+0.02,z);
	glEnd();
    }
    
    void placer() {
		glVertex3f(x,y,z);
	}
};
