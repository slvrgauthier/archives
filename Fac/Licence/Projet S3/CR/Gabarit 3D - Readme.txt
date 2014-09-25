A l'attention des futurs d�veloppeurs d'un sujet similaire :
------------------------------------------------------------

Je liste ici les bugs que j'ai rencontr�, ainsi que les id�es
de r�solutions pour chacun d'entre eux.


 - Lors de la mise en place de seulement deux points, on remarque
que le d�placement d'un des deux entra�ne un mauvais affichage de
l'objet 3D, en effet, la longueur est fixe lorque l'on r�duit 
l'�cart entre les deux points (d'ailleurs, cette longueur est plus
grande lorsque l'on d�place le second point...)

Ce bug peut �tre r�solu de lui-m�me en changeant les structures
(voir � la fin dans les optimisations)


 - Lors de la suppression du troisi�me point quand il n'y en a que
trois, le bug d'avant entra�ne un non-retour d'affichage et on 
observe un "chapeau triangulaire" au lieu d'une ligne...

M�me r�solution.


 - L'espace entre les deux derniers m�ridiens se retrouve en faces
triangulaires au lieu de rectangulaires, uniquement lorsque la 
vitesse de rotation est au maximum.

M�me r�solution.


 - La lumi�re ne s'affiche pas correctement � certains endroits.

Probl�me de calcul de normales, m�me r�solution.


 - La lumi�re tourne avec l'objet au lieu de rester fixe.

A m�diter.



---------------------------------------------------------------------
                      Optimisations n�cessaires
---------------------------------------------------------------------

 - Definitions d'une structure "face" contenant 4 points et une normale.

 - Refonte du mod�le en tableau de faces et non de points.

 - Calcul du mod�le uniquement lors d'un changement et non � chaque tour
de boucle.

 - R�gler la position de la lumi�re de fa�on � ce qu'elle ne tourne pas.


---------------------------------------------------------------------

Bon courage !