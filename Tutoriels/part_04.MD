
# SOKOBAN vs POO / Partie 4 : le personnage

v0.0.2

## INTRODUCTION

Dans les parties précédentes nous avons vu les bases de notre programme, la gestion de la caméra et la gestion de l'affichage. Nous allons voir dans cette quatrième partie la gestion du personnage, ainsi à la fin de cette partie nous serons en mesure de déplacer le personnage (sans contrainte de physique : on pourra traverser les murs par exemple).

Les **pré-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir réaliser la [partie 1](part_01.MD), la [partie 2](part_02.MD) et la [partie 3](part_03.MD) de ce tutoriel.

Je vous invite à télécharger [le code](https://github.com/chris-scientist/gb-poo/archive/v3.0.0.zip) qui est le résultat de la troisième partie, ceci pour partir sur des bases communes.

## CRÉATION DES BASES

Nous allons dans un premier temps définir toutes les méthodes transverses au déplacement, c'est-à-dire qu'on utilise quand on se déplace dans n'importe quelle direction.

Nous avons besoin d'un moyen d'agir sur la carte, en effet il va falloir déplacer le personnage mais aussi remplacer l'ancienne position du personnage par un sprite. Pour ce faire nous allons écrire un *setter*, il s'agit d'une méthode qui modifie un attribut. Le setter en question est setTypeOfSprites de la classe MapModel, que voici :

    void MapModel::setTypeOfSprites(const int aXSprites, const int aYSprites, const char aTypeOfSprites) {
        mapOfGame[aYSprites][aXSprites] = aTypeOfSprites;
    }

Nous allons maintenant intervenir dans la classe CharacterModel.

D'abord, il faut créer le getter sur la nouvelle position soit la méthode getNextPos :

    const int * CharacterModel::getNextPos() const {
        return nextPos;
    }

Ensuite, créons le getter sur l'ancien sprites soit la méthode getOldTypeOfSprites :

    const char CharacterModel::getOldTypeOfSprites() const {
        return oldTypeOfSprites;
    }

Créons le setter sur l'ancien sprites soit la méthode setOldTypeOfSprites :

    void CharacterModel::setOldTypeOfSprites(const char aOldTypeOfSprites) {
        oldTypeOfSprites = aOldTypeOfSprites;
    }

Créons la méthode updatePositions, cette méthode affecte la position suivante (nextPos) à la position courante comme ceci :

    void CharacterModel::updatePositions() {
        x = nextPos[0];
        y = nextPos[1];
    }

Enfin créons la méthode resetNextPositions, cette méthode réinitialise la position suivante avec la position courante comme ceci :

    void CharacterModel::resetNextPositions() {
        nextPos[0] = x;
        nextPos[1] = y;
    }

Il reste une dernière méthode transverse, en effet il faut calculer le sprites du joueur : s'agit-il du joueur ou du joueur sur une zone de 'chargement' ? Pour le déterminer on s'appuie sur le sprites à remplacer. Voici le pseudo code de la méthode getPlayerSprites de CharacterController, on précise que le sprites à remplacer se nomme aReplacedSprites :

    SI aReplacedSprites = zone de chargement OU aReplacedSprites = caisse sur zone de chargement ALORS
        Retourner sprites joueur sur zone de chargement
    SINON
        Retourner sprites du joueur
    FIN SI

Voici le code correspondant :

    char CharacterController::getPlayerSprites(const char aReplacedSprites) const {
        if((aReplacedSprites == TypeOfSprites::DESTINATION_TYPE) || (aReplacedSprites == TypeOfSprites::BOX_ON_ZONE_TYPE)) {
            return TypeOfSprites::PLAYER_ON_ZONE_TYPE;
        }
        return TypeOfSprites::PLAYER_TYPE;
    }

Nous venons d'écrire toutes les méthodes tranverses au déplacement. 

## SE DÉPLACER VERS LE HAUT

Déplacer le personnage vers le haut nécessite d'écrire deux méthodes.

Dans un premier temps, il faut calculer les coordonnées fictives qui correspondent au déplacement. Pourquoi des coordonnées fictives ? Et bien c'est assez simple à comprendre : imaginez que le personnage est en haut de la carte et qu'il souhaite aller encore plus haut, et bien il faut interdire ce déplacement et ne pas modifier les coordonnées du personnage.

Pour aller en haut il faut définir la méthode goUp de CharacterModel, pour ce faire on cherche à modifier la coordonnée y du personnage comme ceci :

    void CharacterModel::goUp() {
        nextPos[1] = y - 1;
    }

Dans un second temps, il faut écrire l'ensemble des actions nécessaire au déplacement vers le haut, ceci sera réalisé dans CharacterController et précisément dans la méthode goUp. goUp ? Mais on a déjà une méthode de ce nom dans CharacterModel ? C'est vrai, si le C++ n'autorise pas d'écrire deux fois une fonction avec le même nom (et la même signature), et bien vous pouvez en orienté objet écrire la méthode x dans la classe A mais également écrire une méthode x dans la classe B et avec la même signature. Voyons le pseudo code de CharacterController::goUp :

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

Avant de donner la solution le contrôle si nous sommes toujours sur la carte est relatif au déplacement effectué, en effet ce ne sera pas le même lorsque nous allons en bas ou dans n'importe quelle autre direction. Le contrôle pour un déplacement vers le haut est le suivant :

    character->getNextPos()[1] >= 0

Voici le code de cettte méthode :

    void CharacterController::goUp() {
        // calcul de la nouvelle position
        character->goUp();
        // récupérer la tuile de la nouvelle position
        char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
        // si la nouvelle position du personnage est sur la carte
        if(character->getNextPos()[1] >= 0) {
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

Vous pouvez compiler votre projet et tester... Rien ne se passe quand vous appuez sur la flèche du haut !? C'est normal, nous verrons à la fin de cette partie comment animer notre personnage, soyez patient.

## QUELQUES PISTES POUR LES AUTRES DÉPLACEMENTS

Pour les autres direction le principe est le même que pour le déplacement vers le haut, il faut simplement faire quelques adaptations. Je dresse ici une brève aide afin d'écrire les autres déplacements.

**Aller vers la droite**

Pour ce faire il faut écrire la méthode CharacterModel::goRight comme ceci :

    void CharacterModel::goRight() {
        nextPos[0] = x + 1;
    }

Puis écrire la méthode CharacterController::goRight à l'image de goUp, le contrôle est cette fois-ci le suivant :

    character->getNextPos()[0] < MapModel::WIDTH_MAP

**Aller vers le bas**

Pour ce faire il faut écrire la méthode CharacterModel::goDown comme ceci :

    void CharacterModel::goDown() {
        nextPos[1] = y + 1;
    }

Puis écrire la méthode CharacterController::goDown à l'image de goUp, le contrôle est cette fois-ci le suivant :

    character->getNextPos()[1] < MapModel::HEIGHT_MAP

**Aller vers la gauche**

Pour ce faire il faut écrire la méthode CharacterModel::goLeft comme ceci :

    void CharacterModel::goLeft() {
        nextPos[0] = x - 1;
    }

Puis écrire la méthode CharacterController::goLeft à l'image de goUp, le contrôle est cette fois-ci le suivant :

    character->getNextPos()[0] >= 0

## ASSOCIATION AVEC LA CROIX DIRECTIONNELLE

Une fois chaque déplacement développé, il nous reste à associer la croix directionnelle à chaque mouvement. Nous allons pour ce faire définir la méthode CharacterController::run.

Il faut déplacer le personnage à chaque pression sur l'une des flèches ce qui ce traduit par l'utilisation de :

    gb.buttons.pressed(UN_BOUTON)

Le pseudo code est :

    SI le joueur appuie sur la flèche du haut ALORS
        Aller vers le haut
    SINON SI le joueur appuie sur la flèche de droite ALORS
        Aller vers la droite
    SINON SI le joueur appuie sur la flèche du bas ALORS
        Aller vers le bas
    SINON SI le joueur appuie sur la flèche de gauche ALORS
        Aller vers la gauche
    FIN SI

Voici le code :

    void CharacterController::run() {
        if(gb.buttons.pressed(BUTTON_UP)) {
            goUp();
        } else if(gb.buttons.pressed(BUTTON_RIGHT)) {
            goRight();
        }  else if(gb.buttons.pressed(BUTTON_DOWN)) {
            goDown();
        } else if(gb.buttons.pressed(BUTTON_LEFT)) {
            goLeft();
        }
    }

Enfin dans MainController::run il faut faire un appel à la méthode que l'on vient d'écrire comme ceci :

    void MainController::run() {
        //gb.display.println("v2.0.0"); // A SUPPRIMER
        //gb.display.printf("Player pos %d,%d", characterController->getX(), characterController->getY());
        //gb.display.println("");
        characterController->run();
        const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());
        //gb.display.printf("Cam %d,%d : %d,%d", cameraPos[0], cameraPos[1], cameraPos[2], cameraPos[3]);
        //gb.display.println("");
        mapController->paint(cameraPos);
    }

Notre personnage est maintenant capable de se déplacer dans les limites de la carte à l'aide de la croix directionnelle.

Si vous avez terminé ou si vous rencontrez des problèmes vous pouvez télécharger la solution ici.

Dans la prochaine partie, c'est-à-dire la cinquième et dernière, nous réaliserons la gestion de la physique ainsi que la fin de partie.

N'hésitez pas à me faire un retour : les améliorations que vous apporteriez (un regard extérieur est toujours bienvenu), les fautes, etc.

