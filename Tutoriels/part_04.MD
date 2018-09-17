
# SOKOBAN vs POO / Partie 4 : le personnage

v0.0.1

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

Nous venons d'écrire toutes les méthodes tranverses au déplacement. 

## SE DÉPLACER VERS LE HAUT

*A venir !*

## QUELQUES PISTES POUR LES AUTRES DÉPLACEMENTS

*A venir !*

## ASSOCIATION AVEC LA CROIX DIRECTIONNELLE

*A venir !*
