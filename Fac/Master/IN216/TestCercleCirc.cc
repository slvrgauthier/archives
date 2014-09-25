int CentreCercleCirconscrit(int A[2], int B[2],int C[2], int O[3]){

  //Stocke dans O les coordonnees du centre du cercle circonscrit a A, B et C
    //Renvoie 1 si ces 3 points sont alignes, 0 sinon et fait le calcul dans ce cas

    if(det(A,B,A,C)==0){return 1;}
   int xa=A[0]; int ya=A[1];
   int xb=B[0]; int yb=B[1];
   int xc=C[0]; int yc=C[1];
   O[0]=(int)((float)((yc-yb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(yb-ya)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(A,B,B,C)));
   O[1]=(int)((float)((xc-xb)*(xb*xb+yb*yb-xa*xa-ya*ya)-(xb-xa)*(xc*xc+yc*yc-xb*xb-yb*yb))/(float)(2*det(B,C,A,B)));
   return 0;
}

---------------------------------------

void AffichageTestCercleCirconscrit(int sommet[4][2]){

  //Affiche les 4 points de sommet et le cercle circonscrit au trois premiers
    //Pour tester la fonction StrictementDansLeCercleCirconscrit

   ofstream output;
  output.open("Test.ps");//
  output << "%!PS-Adobe-3.0" << endl;
  output << endl;
  for(int i=0;i<4;i++){
    output << sommet[i][0] << " " << sommet[i][1] << " 2 0 360 arc"
           <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << sommet[i][0]+2 << " " << sommet[i][1] << " moveto"
           <<endl;
    output << "/Courier findfont 15 scalefont setfont" << endl;
    output << "("<< i+1 << ")" << " show" << endl;
    output << "stroke" << endl;
    output << endl;
  }
  output << endl;
  int O[2];  //Centre du cercle circonscrit
  if(CentreCercleCirconscrit(sommet[0],sommet[1],sommet[2],O)==1){cout
    << "Points alignes" << endl; exit(1);}
  output << O[0] << " " << O[1] << " 2 0 360 arc" <<endl;
  output << "0 setgray" <<endl;
  output << "fill" <<endl;
  output << O[0]+2 << " " << O[1] << " moveto" <<endl;
  output << "/Courier findfont 15 scalefont setfont" << endl;
  output << "(O)" << " show" << endl;
  output << "stroke" << endl;
  output << endl;
  int r; //Rayon du cercle circonscrit
     r=(int)sqrt((double)NormeAuCarre(sommet[0],O));
     output << O[0] << " " << O[1] << " " << r << " 0 360 arc" <<endl;
     output << "0 setgray" <<endl;
     output << "stroke" << endl;
     output << endl;
}




