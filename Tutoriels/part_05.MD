
# SOKOBAN vs POO / Partie 5 : physique et partie

v0.0.1

## INTRODUCTION

Dans les parties précédentes nous avons vu les bases de notre programme, la gestion de la caméra, la gestion de l'affichage et la gestion du personnage. Nous allons voir dans cette cinquième et dernière partie la gestion de la physique et la gestion de la partie, ainsi à la fin de cette partie nous serons en mesure de faire déplacer une caisse par le personnage, de s'arrêter face à un mur et de déterminer si la partie est terminée.

Les **pré-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir réaliser la [partie 1](part_01.MD), la [partie 2](part_02.MD), la [partie 3](part_03.MD) et la [partie 4](part_04.MD) de ce tutoriel.

Je vous invite à télécharger [le code](https://github.com/chris-scientist/gb-poo/archive/v4.0.0.zip) qui est le résultat de la quatrième partie, ceci pour partir sur des bases communes.

## LA PHYSIQUE : COLLISION AVEC LES MURS

Il faut pouvoir rester bloqué si l'on cherche à franchir un mur, sachez qu'il s'agit de l'affaire de quelques lignes et que tout ce passe dans CharacterController.

D'abord, nous allons écrire la méthode pour détecter que le sprites (que nous nommerons aReplacedSprites) est un mur, il s'agit de la méthode isWall, voici le pseudo code :

    SI aReplacedSprites = mur ALORS
        Retourner vrai
    SINON
        Retourner faux
    FIN SI

Ceci dit ce pseudo code peut-être optimisé, en effet la condition renvoye vrai ou faux, le pseudo code est ainsi :

    Retourner (aReplacedSprites = mur)

Voici le code de la méthode :

    const bool CharacterController::isWall(const char aReplacedSprites) const {
        return (aReplacedSprites == TypeOfSprites::WALL_TYPE);
    }

Enfin nous avons plus qu'à interdire le déplacement si le sprite est un mur. Rappelez-vous du pseudo code du déplacement vers le haut par exemple, qui était le suivant :

    Calculer la position fictive relative à un déplacement vers le haut
    Récupérer le sprites relatif à la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ALORS
        Ecraser la position fictive avec la tuile correspondant au joueur
        Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
        Stocker le sprites relatif à la position fictive
        Mettre à jour la position du personnage
    SINON
        Réintialiser la position fictive
    FIN SI

Voici le pseudo code d'un déplacement vers le haut qui interdit de franchir un mur :

    Calculer la position fictive relative à un déplacement vers le haut
    Récupérer le sprites relatif à la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ET le sprites où nous voulons aller n'est pas un mur ALORS
        Ecraser la position fictive avec la tuile correspondant au joueur
        Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
        Stocker le sprites relatif à la position fictive
        Mettre à jour la position du personnage
    SINON
        Réintialiser la position fictive
    FIN SI

Voici le code du déplacement vers le haut avec la contrainte relative au franchissement de mur :

    void CharacterController::goUp() {
        // calcul de la nouvelle position
        character->goUp();
        // récupérer la tuile de la nouvelle position
        char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
        // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
        if(character->getNextPos()[1] >= 0 && !isWall(newTypeOfSprites)) {
            // écraser nouvelle position par la tuile du joueur
            mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
            // remplacer ancienne position par la tuile qui était à cette position précédement
            mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
            // stocker la tuile de la nouvelle position
            character->setOldTypeOfSprites(newTypeOfSprites);
            // mettre à jour la position
            character->updatePositions();
        } else {
            // remettre à zéro la position suivante
            character->resetNextPositions();
        }
    }

Ajouter la contrainte aux autres déplacements et le tour sera joué.

## LA PHYSIQUE : DÉPLACER UNE CAISSE

Nous allons maintenant voir le déplacement d'une caisse, sachez que c'est plus complexe que la contrainte précédente, mais je suis là pour vous guider. Et comme la contrainte précédente tout ce joue dans CharacterController.

Commençons par écrire le pseudo code de détection d'une caisse, pensez à la simplification utilisé lors de la détection de mur :

    Retourner (aReplacedSprites = caisse) || (aReplacedSprites = caisse sur zone de 'chargement')

Voici le code de la méthode isBox :

    const bool CharacterController::isBox(const char aReplacedSprites) const {
        return (aReplacedSprites == TypeOfSprites::BOX_TYPE) || 
            (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE);
    }

Ecrivons un gros morceau, soit le pseudo code pour déplacer une caisse, il s'agit de la méthode moveBox. Les paramètres de cette méthode sont le sprites à remplacer (aReplacedSprites), les coordonnées X1, Y1 ainsi que les coordonnées X2, Y2 ces dernières représentent le sprite après la caisse. Voici le pseudo code  :

    Récupérer le sprites ayant pour coordonnéées X2, Y2
    Affecter à stopMove la valeur du test suivant : est différent du sol ou différent d'une zone de chargement
    SI stopMove est faux ALORS
        SI le sprites de coordonnées X2, Y2 est une zone de chargement ALORS
            Affecter à replacedSprites2 un sprite de type caisse sur zone de chargement
        SINON
            Affecter à replacedSprites2 un sprite de type caisse
        FIN SI
        Ecraser la position X2, Y2 par replacedSprites2
		SI aReplacedSprites = caisse sur zone de chargement ALORS
            Retourner sprites de type zone de chargement
        SINON
            Retourner sprites de type sol
        FIN SI
	FIN SI
	Retourner aReplacedSprites

Nous pouvons simplifier le code à l'aide d'une condition particulière que l'on appelle condition ternaire. Voyons comment faire sur un exemple de pseudo code :

    SI nb > 0 ALORS
        Affecter à signe la valeur '+'
    SINON
        Affecter à signe la valeur '-'
    FIN SI

Voici le code relatif à cette exemple, utilisant une condition ternaire :

    char signe = (nb > 0) ? '+' : '-';

Je vous ai donner cette simplification car nous pouvons l'utiliser à deux reprises dans le code de moveBox que voici :

    const char CharacterController::moveBox(const char aReplacedSprites, const int aX1, const int aY1, const int aX2, const int aY2) {
        // on récupère le sprites en X2, Y2
        const char sprites = mapModel->getTypeOfSprites(aX2, aY2);
        // si c'est le sol ou une zone de chargement alors on déplace la caisse
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

Remarque : une optimisation est facultative mais possible, en effet nous n'avons pas besoin du couple de coordonnées X1, Y1, il peut donc être supprimer. Il s'agit d'une erreur de ma part, j'ai oublié de le supprimer dès la partie 1.

Il nous reste plus qu'à connecter les deux méthodes que l'on vient d'écrire au déplacement. Nous allons nous servir du déplacement vers le haut pour notre exemple, voici le pseudo code avec la contrainte de déplacement d'une caisse :

    Calculer la position fictive relative à un déplacement vers le haut
    Récupérer le sprites relatif à la position fictive
    SI nous sommes toujours sur la carte avec la position fictive ET le sprites où nous voulons aller n'est pas un mur ALORS
        SI le sprites relatif à la position fictive est une caisse ALORS
            Faire un appel à la méthode de déplacement d'une caisse et affecter la valeur de retour au sprites relatif à la positioon fictive
        SINON
            Affecter à stopMove la valeur false
        FIN SI
        
        SI stopMove est faux ALORS
            Ecraser la position fictive avec la tuile correspondant au joueur
            Remplacer l'ancienne position du joueur par le sprites qui s'y trouvait avant
            Stocker le sprites relatif à la position fictive
            Mettre à jour la position du personnage
        SINON
		    Réintialiser la position fictive
        FIN SI
    SINON
        Réintialiser la position fictive
    FIN SI

Voici le code de la méthode goUp modifier avec la contrainte de déplacement d'une caisse :

void CharacterController::goUp() {
  // calcul de la nouvelle position
  character->goUp();
  // récupérer la tuile de la nouvelle position
  char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
  // si la nouvelle position du personnage est sur la carte et que ce n'est pas un mur
  if(character->getNextPos()[1] >= 0 && !isWall(newTypeOfSprites)) {
    // déplacer une caisse
    if(isBox(newTypeOfSprites)) {
      newTypeOfSprites = moveBox(newTypeOfSprites, character->getNextPos()[0], character->getNextPos()[1], character->getNextPos()[0], character->getNextPos()[1] - 1);
    } else {
      stopMove = false;
    }

    if(!stopMove) {
      // écraser nouvelle position par la tuile du joueur
      mapModel->setTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1], getPlayerSprites(newTypeOfSprites));
      // remplacer ancienne position par la tuile qui était à cette position précédement
      mapModel->setTypeOfSprites(character->getX(), character->getY(), character->getOldTypeOfSprites());
      // stocker la tuile de la nouvelle position
      character->setOldTypeOfSprites(newTypeOfSprites);
      // mettre à jour la position
      character->updatePositions();
    } else {
      character->resetNextPositions();
    }
  } else {
    // remettre à zéro la position suivante
    character->resetNextPositions();
  }
}

Le code pour les autres directions est similaire, à l'exception des coordonnées X2, Y2 passé à moveBox qu'il faut adapter, voyons cela.

**Aller vers la droite**

    X2 = character->getNextPos()[0] + 1
    Y2 = character->getNextPos()[1]

**Aller vers le bas**

    X2 = character->getNextPos()[0]
    Y2 = character->getNextPos()[1] + 1

**Aller vers la gauche**

    X2 = character->getNextPos()[0] - 1
    Y2 = character->getNextPos()[1]

Une fois les méthodes complétées, amusez vous avec le jeu, en effet vous devriez être en mesure de déplacer les caisses sur les zones de chargement.

## GESTION DE LA PARTIE

Dans ce dernier chapitre du tutoriel nous allons aborder la gestion de la fin de partie. Effectivement il serait bien de féliciter le joueur lorsque celui-ci à déplacer l'ensemble des caisses sur les zones de chargement.

Pour cela il faut parcourir la carte, la méthode isFinish de MapModel nous indique si le jeu est terminée ou non (via isEnd), voici le pseudo code :

    Affecter à isEnd la valeur true
    PARCOURIR la carte sur l'axe Y tant que le jeu est terminé
        PARCOURIR la carte sur l'axe X tant que le jeu est terminé
            Affecter à isEnd la valeur de isEnd ET (sprites X, Y différent de zone de chargement ET sprites X, Y différent de caisse)
        FIN PARCOURIR
    FIN PARCOURIR
    Retourner isEnd

Voici le code de la méthode :

    bool MapModel::isFinish() const {
        bool isEnd = true;
        for(int y=0 ; y < HEIGHT_MAP && isEnd ; y++) {
            for(int x=0 ; x < WIDTH_MAP && isEnd ; x++) {
                isEnd = isEnd && !(mapOfGame[y][x] == TypeOfSprites::DESTINATION_TYPE || mapOfGame[y][x] == TypeOfSprites::BOX_TYPE);
            }
        }
        return isEnd;
    }

Il faut maintenant que le contrôleur ai accès à isFinish, on rend cela possible via la méthode isEndOfGame de MapController que voici:

    bool MapController::isEndOfGame() const {
        return model->isFinish();
    }

Modifions la méthode run de MainController pour que lorsque la partie est finie on affiche un écran "Gagné", soit le code suivant :

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

Votre jeu est maintenant complétement jouable, amusez vous bien !

## CONCLUSION

Cette partie était la dernière du tutoriel. Vous pouvez télécharger le code source final. Le jeu est jouable mais également améliorable. En effet il pourrait être intéressant de pouvoir recommencer la partie (sans avoir à quitter le jeu), ou bien avoir plusieurs cartes, etc. Mais le but de ce tutoriel était de proposer une initiation à la programmation orienté objet et au modèle d'architecture Modèle Vue Contrôleur, j'espère que ce tutoriel vous servira dans vos prochaine créations. Le découpage de ce tutoriel n'est pas anodin, effectivement nous avons développer chacune des briques de notre jeu pas à pas, bloc de fonctionnalités après bloc, et c'est comme cela que vous devez concevoir vos jeux. Enfin comme les autres parties n'hésitez pas à me donner votre avis.
