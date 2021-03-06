
# SOKOBAN vs POO / Partie 5 : physique et partie

v0.2.2

## INTRODUCTION

Dans les parties pr�c�dentes nous avons vu les bases de notre programme, la gestion de la cam�ra, la gestion de l'affichage et la gestion du personnage. Nous allons voir dans cette cinqui�me et derni�re partie la gestion de la physique et la gestion de la partie, ainsi � la fin de cette partie nous serons en mesure de faire d�placer une caisse par le personnage, de s'arr�ter face � un mur et de d�terminer si la partie est termin�e.

Les **pr�-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir r�aliser la [partie 1](part_01.MD), la [partie 2](part_02.MD), la [partie 3](part_03.MD) et la [partie 4](part_04.MD) de ce tutoriel.

Je vous invite � t�l�charger [le code](https://github.com/chris-scientist/gb-poo/archive/v4.0.0.zip) qui est le r�sultat de la quatri�me partie, ceci pour partir sur des bases communes.

## LA PHYSIQUE : COLLISION AVEC LES MURS

Il faut pouvoir rester bloqu� si l'on cherche � franchir un mur, sachez qu'il s'agit de l'affaire de quelques lignes et que tout ce passe dans CharacterController.

D'abord, nous allons �crire la m�thode pour d�tecter que le sprites (que nous nommerons aReplacedSprites) est un mur, il s'agit de la m�thode isWall, voici le pseudo code :

    SI aReplacedSprites = mur ALORS
        Retourner vrai
    SINON
        Retourner faux
    FIN SI

Ceci dit ce pseudo code peut-�tre optimis�, en effet la condition renvoye vrai ou faux, le pseudo code est ainsi :

    Retourner (aReplacedSprites = mur)

Voici le code de la m�thode :

    const bool CharacterController::isWall(const char aReplacedSprites) const {
        return (aReplacedSprites == TypeOfSprites::WALL_TYPE);
    }

Enfin nous avons plus qu'� interdire le d�placement si le sprite est un mur. Rappelez-vous du pseudo code du d�placement vers le haut par exemple, qui �tait le suivant :

    Calculer la position fictive relative � un d�placement vers le haut
    R�cup�rer le sprites relatif � la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ALORS
        Ecraser la position fictive avec la tuile correspondant au joueur
        Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
        Stocker le sprites relatif � la position fictive
        Mettre � jour la position du personnage
    SINON
        R�intialiser la position fictive
    FIN SI

Voici le pseudo code d'un d�placement vers le haut qui interdit de franchir un mur :

    Calculer la position fictive relative � un d�placement vers le haut
    R�cup�rer le sprites relatif � la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ET le sprites o� nous voulons aller n'est pas un mur ALORS
        Ecraser la position fictive avec la tuile correspondant au joueur
        Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
        Stocker le sprites relatif � la position fictive
        Mettre � jour la position du personnage
    SINON
        R�intialiser la position fictive
    FIN SI

Voici le code du d�placement vers le haut avec la contrainte relative au franchissement de mur :

    void CharacterController::goUp() {
        // calcul de la nouvelle position
        character->goUp();
        // r�cup�rer la tuile de la nouvelle position
        char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
        // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
        if(character->getNextPos()[1] >= 0 && !isWall(newTypeOfSprites)) {
            // �craser nouvelle position par la tuile du joueur
            mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
            // remplacer ancienne position par la tuile qui �tait � cette position pr�c�dement
            mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
            // stocker la tuile de la nouvelle position
            character->setOldTypeOfSprites(newTypeOfSprites);
            // mettre � jour la position
            character->updatePositions();
        } else {
            // remettre � z�ro la position suivante
            character->resetNextPositions();
        }
    }

Ajouter la contrainte aux autres d�placements et le tour sera jou�.

## LA PHYSIQUE : D�PLACER UNE CAISSE

Nous allons maintenant voir le d�placement d'une caisse, sachez que c'est plus complexe que la contrainte pr�c�dente, mais je suis l� pour vous guider. Et comme la contrainte pr�c�dente tout ce joue dans CharacterController.

Commen�ons par �crire le pseudo code de d�tection d'une caisse, pensez � la simplification utilis� lors de la d�tection de mur :

    Retourner (aReplacedSprites = caisse) || (aReplacedSprites = caisse sur zone de 'chargement')

Voici le code de la m�thode isBox :

    const bool CharacterController::isBox(const char aReplacedSprites) const {
        return (aReplacedSprites == TypeOfSprites::BOX_TYPE) || 
            (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE);
    }

Ecrivons un gros morceau, soit le pseudo code pour d�placer une caisse, il s'agit de la m�thode moveBox. Les param�tres de cette m�thode sont le sprites � remplacer (aReplacedSprites), les coordonn�es X1, Y1 ainsi que les coordonn�es X2, Y2 ces derni�res repr�sentent le sprite apr�s la caisse. Voici le pseudo code  :

    R�cup�rer le sprites ayant pour coordonn��es X2, Y2
    Affecter � stopMove la valeur du test suivant : est diff�rent du sol ou diff�rent d'une zone de chargement
    SI stopMove est faux ALORS
        SI le sprites de coordonn�es X2, Y2 est une zone de chargement ALORS
            Affecter � replacedSprites2 un sprite de type caisse sur zone de chargement
        SINON
            Affecter � replacedSprites2 un sprite de type caisse
        FIN SI
        Ecraser la position X2, Y2 par replacedSprites2
		SI aReplacedSprites = caisse sur zone de chargement ALORS
            Retourner sprites de type zone de chargement
        SINON
            Retourner sprites de type sol
        FIN SI
	FIN SI
	Retourner aReplacedSprites

Nous pouvons simplifier le code � l'aide d'une condition particuli�re que l'on appelle condition ternaire. Voyons comment faire sur un exemple de pseudo code :

    SI nb > 0 ALORS
        Affecter � signe la valeur '+'
    SINON
        Affecter � signe la valeur '-'
    FIN SI

Voici le code relatif � cette exemple, utilisant une condition ternaire :

    char signe = (nb > 0) ? '+' : '-';

Je vous ai donner cette simplification car nous pouvons l'utiliser � deux reprises dans le code de moveBox que voici :

    const char CharacterController::moveBox(const char aReplacedSprites, const int aX1, const int aY1, const int aX2, const int aY2) {
        // on r�cup�re le sprites en X2, Y2
        const char sprites = mapModel->getTypeOfSprites(aX2, aY2);
        // si c'est le sol ou une zone de chargement alors on d�place la caisse
        stopMove = !((sprites == TypeOfSprites::FLOOR_TYPE) || (sprites == TypeOfSprites::DESTINATION_TYPE));
        if(!stopMove) {
            // on calcul le sprites X2, Y2
            const char replacedSprites2 = (sprites == TypeOfSprites::DESTINATION_TYPE) ? TypeOfSprites::BOX_ON_ZONE_TYPE : TypeOfSprites::BOX_TYPE ;
            // on affecte le sprites X2, Y2
            mapModel->setTypeOfSprites(aX2, aY2, replacedSprites2);
            return (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE) ? TypeOfSprites::DESTINATION_TYPE : TypeOfSprites::FLOOR_TYPE;
        }
        return aReplacedSprites;
    }

Remarque : une optimisation est facultative mais possible, en effet nous n'avons pas besoin du couple de coordonn�es X1, Y1, il peut donc �tre supprimer. Il s'agit d'une erreur de ma part, j'ai oubli� de le supprimer d�s la partie 1 de ce tutoriel.

Il nous reste plus qu'� connecter les deux m�thodes que l'on vient d'�crire au d�placement. Nous allons nous servir du d�placement vers le haut pour notre exemple, voici le pseudo code avec la contrainte de d�placement d'une caisse :

    Calculer la position fictive relative � un d�placement vers le haut
    R�cup�rer le sprites relatif � la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ET le sprites o� nous voulons aller n'est pas un mur ALORS
        SI le sprites relatif � la position fictive est une caisse ALORS
            Faire un appel � la m�thode de d�placement d'une caisse et affecter la valeur de retour au sprites relatif � la positioon fictive
        SINON
            Affecter � stopMove la valeur false
        FIN SI
        
        SI stopMove est faux ALORS
            Ecraser la position fictive avec la tuile correspondant au joueur
            Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
            Stocker le sprites relatif � la position fictive
            Mettre � jour la position du personnage
        SINON
		    R�intialiser la position fictive
        FIN SI
    SINON
        R�intialiser la position fictive
    FIN SI

Voici le code de la m�thode goUp modifier avec la contrainte de d�placement d'une caisse :

    void CharacterController::goUp() {
        // calcul de la nouvelle position
        character->goUp();
        // r�cup�rer la tuile de la nouvelle position
        char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
        // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
        if(character->getNextPos()[1] >= 0 && !isWall(newTypeOfSprites)) {
            // d�placer une caisse
            if(isBox(newTypeOfSprites)) {
                newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0], character->getNextPos()[1] - 1);
            } else {
                stopMove = false;
            }
    
            if(!stopMove) {
                // �craser nouvelle position par la tuile du joueur
                mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
                // remplacer ancienne position par la tuile qui �tait � cette position pr�c�dement
                mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
                // stocker la tuile de la nouvelle position
                character->setOldTypeOfSprites(newTypeOfSprites);
                // mettre � jour la position
                character->updatePositions();
            } else {
                 character->resetNextPositions();
            }
        } else {
            // remettre � z�ro la position suivante
            character->resetNextPositions();
        }
    }

Le code pour les autres directions est similaire, � l'exception des coordonn�es X2, Y2 pass� � moveBox qu'il faut adapter, voyons cela.

**Aller vers la droite**

    X2 = character->getNextPos()[0] + 1
    Y2 = character->getNextPos()[1]

**Aller vers le bas**

    X2 = character->getNextPos()[0]
    Y2 = character->getNextPos()[1] + 1

**Aller vers la gauche**

    X2 = character->getNextPos()[0] - 1
    Y2 = character->getNextPos()[1]

Une fois les m�thodes compl�t�es, amusez vous avec le jeu, en effet vous devriez �tre en mesure de d�placer les caisses sur les zones de chargement.

## GESTION DE LA PARTIE

Dans ce dernier chapitre du tutoriel nous allons aborder la gestion de la fin de partie. Effectivement il serait bien de f�liciter le joueur lorsque celui-ci � d�placer l'ensemble des caisses sur les zones de chargement.

Pour cela il faut parcourir la carte, la m�thode isFinish de MapModel nous indique si le jeu est termin�e ou non (via isEnd), voici le pseudo code :

    Affecter � isEnd la valeur true
    PARCOURIR la carte sur l'axe Y tant que le jeu est termin�
        PARCOURIR la carte sur l'axe X tant que le jeu est termin�
            Affecter � isEnd la valeur de isEnd ET (sprites X, Y diff�rent de zone de chargement ET sprites X, Y diff�rent de caisse)
        FIN PARCOURIR
    FIN PARCOURIR
    Retourner isEnd

Voici le code de la m�thode :

    bool MapModel::isFinish() const {
        bool isEnd = true;
        for(int y=0 ; y < HEIGHT_MAP && isEnd ; y++) {
            for(int x=0 ; x < WIDTH_MAP && isEnd ; x++) {
                isEnd = isEnd && !(mapOfGame[y][x] == TypeOfSprites::DESTINATION_TYPE || mapOfGame[y][x] == TypeOfSprites::BOX_TYPE);
            }
        }
        return isEnd;
    }

Il faut maintenant que le contr�leur ai acc�s � isFinish, on rend cela possible via la m�thode isEndOfGame de MapController que voici:

    bool MapController::isEndOfGame() const {
        return model->isFinish();
    }

Modifions la m�thode run de MainController pour que lorsque la partie est finie on affiche un �cran "Gagn�", soit le code suivant :

    void MainController::run() {
        if(! mapController->isEndOfGame()) {
            characterController->run();
            const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());
            mapController->paint(cameraPos);
        } else {
            gb.display.setFontSize(2);
            gb.display.setColor(BROWN);
            gb.display.println("");
            gb.display.println("");
            gb.display.println("  Gagne");
        }
    }

Votre jeu est maintenant compl�tement jouable, amusez vous bien !

## CONCLUSION

Cette partie �tait la derni�re du tutoriel. Vous pouvez t�l�charger le [code source final](https://github.com/chris-scientist/gb-poo/archive/v5.0.0.zip). Le jeu est jouable mais �galement am�liorable. En effet il pourrait �tre int�ressant de pouvoir recommencer la partie (sans avoir � quitter le jeu), ou bien avoir plusieurs cartes, etc. Mais le but de ce tutoriel �tait de proposer une initiation � la programmation orient� objet et au mod�le d'architecture Mod�le Vue Contr�leur (MVC), j'esp�re que ce tutoriel vous servira dans vos prochaine cr�ations. Le d�coupage de ce tutoriel n'est pas anodin, effectivement nous avons d�velopper chacune des briques de notre jeu pas � pas, bloc de fonctionnalit�s apr�s bloc, et c'est comme cela que vous devez concevoir vos jeux. Enfin comme les autres parties n'h�sitez pas � me donner votre avis.

### Aller plus loin

Avant de partir, et si vous voulez voir une autre approche du MVC, je vous conseille fortement de lire l'excellent tutoriel de [steph](https://gamebuino.com/@steph) sur le jeu de la vie disponible [ici](https://gamebuino.com/creations/game-of-life). Le tutoriel pr�sente le jeu selon diff�rentes approches : une approche fonctionnelle jusqu'au MVC en passant par une version purement objet. De plus, il a ajout�, toujours dans ce tutoriel, des interactions avec les LEDs ainsi que des effets sonores.
