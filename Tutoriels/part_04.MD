
# SOKOBAN vs POO / Partie 4 : le personnage

v0.1.1

## INTRODUCTION

Dans les parties pr�c�dentes nous avons vu les bases de notre programme, la gestion de la cam�ra et la gestion de l'affichage. Nous allons voir dans cette quatri�me partie la gestion du personnage, ainsi � la fin de cette partie nous serons en mesure de d�placer le personnage (sans contrainte de physique : on pourra traverser les murs par exemple).

Les **pr�-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir r�aliser la [partie 1](part_01.MD), la [partie 2](part_02.MD) et la [partie 3](part_03.MD) de ce tutoriel.

Je vous invite � t�l�charger [le code](https://github.com/chris-scientist/gb-poo/archive/v3.0.0.zip) qui est le r�sultat de la troisi�me partie, ceci pour partir sur des bases communes.

## CR�ATION DES BASES

Nous allons dans un premier temps d�finir toutes les m�thodes transverses au d�placement, c'est-�-dire qu'on utilise quand on se d�place dans n'importe quelle direction.

Nous avons besoin d'un moyen d'agir sur la carte, en effet il va falloir d�placer le personnage mais aussi remplacer l'ancienne position du personnage par un sprite. Pour ce faire nous allons �crire un *setter*, il s'agit d'une m�thode qui modifie un attribut. Le setter en question est setTypeOfSprites de la classe MapModel, que voici :

    void MapModel::setTypeOfSprites(const int aXSprites, const int aYSprites, const char aTypeOfSprites) {
        mapOfGame[aYSprites][aXSprites] = aTypeOfSprites;
    }

Nous allons maintenant intervenir dans la classe CharacterModel.

D'abord, il faut cr�er le getter sur la nouvelle position soit la m�thode getNextPos :

    const int * CharacterModel::getNextPos() const {
        return nextPos;
    }

Ensuite, cr�ons le getter sur l'ancien sprites soit la m�thode getOldTypeOfSprites :

    const char CharacterModel::getOldTypeOfSprites() const {
        return oldTypeOfSprites;
    }

Cr�ons le setter sur l'ancien sprites soit la m�thode setOldTypeOfSprites :

    void CharacterModel::setOldTypeOfSprites(const char aOldTypeOfSprites) {
        oldTypeOfSprites = aOldTypeOfSprites;
    }

Cr�ons la m�thode updatePositions, cette m�thode affecte la position suivante (nextPos) � la position courante comme ceci :

    void CharacterModel::updatePositions() {
        x = nextPos[0];
        y = nextPos[1];
    }

Enfin cr�ons la m�thode resetNextPositions, cette m�thode r�initialise la position suivante avec la position courante comme ceci :

    void CharacterModel::resetNextPositions() {
        nextPos[0] = x;
        nextPos[1] = y;
    }

Il reste une derni�re m�thode transverse, en effet il faut calculer le sprites du joueur : s'agit-il du joueur ou du joueur sur une zone de 'chargement' ? Pour le d�terminer on s'appuie sur le sprites � remplacer. Voici le pseudo code de la m�thode getPlayerSprites de CharacterController, on pr�cise que le sprites � remplacer se nomme aReplacedSprites :

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

Nous venons d'�crire toutes les m�thodes tranverses au d�placement. 

## SE D�PLACER VERS LE HAUT

D�placer le personnage vers le haut n�cessite d'�crire deux m�thodes.

Dans un premier temps, il faut calculer les coordonn�es fictives qui correspondent au d�placement. Pourquoi des coordonn�es fictives ? Et bien c'est assez simple � comprendre : imaginez que le personnage est en haut de la carte et qu'il souhaite aller encore plus haut, et bien il faut interdire ce d�placement et ne pas modifier les coordonn�es du personnage.

Pour aller en haut il faut d�finir la m�thode goUp de CharacterModel, pour ce faire on cherche � modifier la coordonn�e y du personnage comme ceci :

    void CharacterModel::goUp() {
        nextPos[1] = y - 1;
    }

Dans un second temps, il faut �crire l'ensemble des actions n�cessaire au d�placement vers le haut, ceci sera r�alis� dans CharacterController et pr�cis�ment dans la m�thode goUp. goUp ? Mais on a d�j� une m�thode de ce nom dans CharacterModel ? C'est vrai, si le C++ n'autorise pas d'�crire deux fois une fonction avec le m�me nom (et la m�me signature), et bien vous pouvez en orient� objet �crire la m�thode x dans la classe A mais �galement �crire une m�thode x dans la classe B et avec la m�me signature. Voyons le pseudo code de CharacterController::goUp :

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

Avant de donner la solution le contr�le si nous sommes toujours sur la carte est relatif au d�placement effectu�, en effet ce ne sera pas le m�me lorsque nous allons en bas ou dans n'importe quelle autre direction. Le contr�le pour un d�placement vers le haut est le suivant :

    character->getNextPos()[1] >= 0

Voici le code de cettte m�thode :

    void CharacterController::goUp() {
        // calcul de la nouvelle position
        character->goUp();
        // r�cup�rer la tuile de la nouvelle position
        char newTypeOfSprites = mapModel->getTypeOfSprites(character->getNextPos()[0], character->getNextPos()[1]);
        // si la nouvelle position du personnage est sur la carte
        if(character->getNextPos()[1] >= 0) {
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

Vous pouvez compiler votre projet et tester... Rien ne se passe quand vous appuez sur la fl�che du haut !? C'est normal, nous verrons � la fin de cette partie comment animer notre personnage, soyez patient.

## QUELQUES PISTES POUR LES AUTRES D�PLACEMENTS

Pour les autres direction le principe est le m�me que pour le d�placement vers le haut, il faut simplement faire quelques adaptations. Je dresse ici une br�ve aide afin d'�crire les autres d�placements.

**Aller vers la droite**

Pour ce faire il faut �crire la m�thode CharacterModel::goRight comme ceci :

    void CharacterModel::goRight() {
        nextPos[0] = x + 1;
    }

Puis �crire la m�thode CharacterController::goRight � l'image de goUp, le contr�le est cette fois-ci le suivant :

    character->getNextPos()[0] < MapModel::WIDTH_MAP

**Aller vers le bas**

Pour ce faire il faut �crire la m�thode CharacterModel::goDown comme ceci :

    void CharacterModel::goDown() {
        nextPos[1] = y + 1;
    }

Puis �crire la m�thode CharacterController::goDown � l'image de goUp, le contr�le est cette fois-ci le suivant :

    character->getNextPos()[1] < MapModel::HEIGHT_MAP

**Aller vers la gauche**

Pour ce faire il faut �crire la m�thode CharacterModel::goLeft comme ceci :

    void CharacterModel::goLeft() {
        nextPos[0] = x - 1;
    }

Puis �crire la m�thode CharacterController::goLeft � l'image de goUp, le contr�le est cette fois-ci le suivant :

    character->getNextPos()[0] >= 0

## ASSOCIATION AVEC LA CROIX DIRECTIONNELLE

Une fois chaque d�placement d�velopp�, il nous reste � associer la croix directionnelle � chaque mouvement. Nous allons pour ce faire d�finir la m�thode CharacterController::run.

Il faut d�placer le personnage � chaque pression sur l'une des fl�ches ce qui ce traduit par l'utilisation de :

    gb.buttons.pressed(UN_BOUTON)

Le pseudo code est :

    SI le joueur appuie sur la fl�che du haut ALORS
        Aller vers le haut
    SINON SI le joueur appuie sur la fl�che de droite ALORS
        Aller vers la droite
    SINON SI le joueur appuie sur la fl�che du bas ALORS
        Aller vers le bas
    SINON SI le joueur appuie sur la fl�che de gauche ALORS
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

Enfin dans MainController::run il faut faire un appel � la m�thode que l'on vient d'�crire comme ceci :

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

Notre personnage est maintenant capable de se d�placer dans les limites de la carte � l'aide de la croix directionnelle.

Si vous avez termin� ou si vous rencontrez des probl�mes vous pouvez t�l�charger la solution [ici](https://github.com/chris-scientist/gb-poo/archive/v4.0.0.zip).

Dans la [prochaine partie](part_05.MD), c'est-�-dire la cinqui�me et derni�re, nous r�aliserons la gestion de la physique ainsi que la fin de partie.

N'h�sitez pas � me faire un retour : les am�liorations que vous apporteriez (un regard ext�rieur est toujours bienvenu), les fautes, etc.

