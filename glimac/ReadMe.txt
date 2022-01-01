Information de Compilation :

Afin de préparer la compilation programme, il faut cd rendre dans le dossier "build"
puis executer la commande "cmake ..", ensuite pour compiler le programme on lance la commende "make".

Un executable sera alors créé dans le dossier Project appelé "Project_Bielle". Lancez la commande 
"./Project/Project_Bielle" afin de lancer le programme.

Lancer le programme avec un argument lance le programme dans une fenête 800x600 au lieu de plein écran
ce qui permet d'améliorer les performances.

La scene est composé d'une pièce de quatre murs en brique. Au milieu se trouve le système bielle-manivelle.
Quelques caisses et Bidons se trouvent sur le sol. Deux lumières sont allumés, une au dessus du système
bielle-manivelle et l'autre est une lampe torche dirigé dans la direction de la caméra.

L'utilisateur peux se déplacer dans la scène en utilisant les touches "Z,Q,S,D" du clavier qui permettent
respectivement d'avancer, d'aller a gauche, de reculer, d'aller a droite. L'utilisateur peux également
déplacer la caméra en effectuant un clique gauche puis en déplacant la souris. L'utilisateur se trouve à
une hauteur fixe et il lui est impossible de la quitter.

La touche "e" du clavier permet d'activer ou de desactiver la rotation système bielle-manivelle. 
Les touches "r" et "f" permettent respectivement d'accélérer et de ralentir la rotation du système 
bielle-manivelle.

Il est possible d'influer sur les dimensions du système bielle-manivelle :
    - Les touches "o" et "p" permettent d'augmenter ou de réduire la longueur de l'arbre du système. 
    - Les touches "l" et "m" permettent d'augmenter ou de réduire la taille du bras du système.
    - Les touches "u" et "i" permettent d'augmenter ou de réduire le diamètre de l'arbre du système.

Certaines contraintes sont imposées par le système :
    - La taille du bras ne peux pas dépasser la longueur de l'arbre.
    - Le double du diamètre de l'arbre ne peux dépasser la moitié de la taille du bras.

Il y a un total de 7 lumières dans la salles qui peuvent être éteintes ou allumer en utilisant les touches suivantes :

    > Lumières de type "Spot Light" :
        - "0" (pavé numérique) permet d'activer/de desactiver la lampe torche.
        - "1" (pavé numérique) permet d'activer/de desactiver la lampe du système bielle-manivelle.
        - "2" (pavé numérique) permet d'activer/de desactiver la lampe se trouvant dans un coin de la salle regardant le sytème.
    
    > Lumières de type "Point Light" :
        -"3" (pavé numérique) permet d'activer/de desactiver la lampe se trouvant au dessus du système vers la face.
        -"4" (pavé numérique) permet d'activer/de desactiver la lampe se trouvant au dessus du système vers le dos.
        -"5" (pavé numérique) permet d'activer/de desactiver la lampe tournant autour de la salle en haut.
        -"6" (pavé numérique) permet d'activer/de desactiver la lampe tournant autour de la salle en bas.
        -"7" (pavé numérique) permet d'activer/de desactiver la lampe se trouvant dans un coin de la salle.

Pour finir, la touche "ECHAP" du clavier permet de quitter l'application (cliquer sur la croix fonctionne également).