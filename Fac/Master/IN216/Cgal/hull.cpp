#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
//http://doc.cgal.org/latest/Convex_hull_2/group__PkgConvexHull2.html

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

void affichage(int n, Point_2* points, int m, Point_2* result){
   ofstream output;
   output.open("Hull.ps");//
   output << "%!PS-Adobe-3.0" << endl;
   output << endl;  
   for(int i=0;i<n;i++){
     output << points[i][0] << " " << points[i][1] << " 2 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "fill" <<endl;
     output << points[i][0]+2 << " " << points[i][1] << " moveto" <<endl;
     output << "/Courier findfont 15 scalefont setfont" << endl;
     output << "("<< i << ")" << " show" << endl;
     output << "stroke" << endl;
     output << endl;
   }
   output << endl;
   for(int i=0;i<m;i++){
      output << result[i][0] << " " << result[i][1] 
 	    << " moveto"  << endl;
      output << result[(i+1)%m][0] << " " << result[(i+1)%m][1] 
 	    << " lineto"  << endl;
      output << "stroke" << endl;
      output << endl;
   }
    output.close();
}

int main(){
  Point_2 points[5] = { Point_2(0,0), Point_2(500,0), Point_2(500,500),
			Point_2(300,250), Point_2(200,50) };
  Point_2 result[5];
  Point_2 *ptr = CGAL::convex_hull_2( points, points+5, result );
  affichage(5,points,ptr-result,result);
  std::cout << ptr - result << " points on the convex hull" <<
    std::endl;
  Point_2 * cpt=result;
  while(cpt != ptr){
    std::cout << *cpt++ << std::endl;
  }
  return 0;
}
