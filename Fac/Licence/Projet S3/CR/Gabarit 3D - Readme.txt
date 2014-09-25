A l'attention des futurs développeurs d'un sujet similaire :
------------------------------------------------------------

Je liste ici les bugs que j'ai rencontré, ainsi que les idées
de résolutions pour chacun d'entre eux.


 - Lors de la mise en place de seulement deux points, on remarque
que le déplacement d'un des deux entraîne un mauvais affichage de
l'objet 3D, en effet, la longueur est fixe lorque l'on réduit 
l'écart entre les deux points (d'ailleurs, cette longueur est plus
grande lorsque l'on déplace le second point...)

Ce bug peut être résolu de lui-même en changeant les structures
(voir à la fin dans les optimisations)


 - Lors de la suppression du troisième point quand il n'y en a que
trois, le bug d'avant entraîne un non-retour d'affichage et on 
observe un "chapeau triangulaire" au lieu d'une ligne...

Même résolution.


 - L'espace entre les deux derniers méridiens se retrouve en faces
triangulaires au lieu de rectangulaires, uniquement lorsque la 
vitesse de rotation est au maximum.

Même résolution.


 - La lumière ne s'affiche pas correctement à certains endroits.

Problème de calcul de normales, même résolution.


 - La lumière tourne avec l'objet au lieu de rester fixe.

A méditer.



---------------------------------------------------------------------
                      Optimisations nécessaires
---------------------------------------------------------------------

 - Definitions d'une structure "face" contenant 4 points et une normale.

 - Refonte du modèle en tableau de faces et non de points.

 - Calcul du modèle uniquement lors d'un changement et non à chaque tour
de boucle.

 - Régler la position de la lumière de façon à ce qu'elle ne tourne pas.


---------------------------------------------------------------------

Bon courage !