
# SOKOBAN vs POO / Partie 3 : affichage

v0.1.1

## INTRODUCTION

Dans les parties précédentes nous avons vu les bases de notre programme ainsi que la gestion de la caméra. Nous allons voir dans cette troisième partie la gestion de l'affichage, ainsi à la fin de cette partie notre écran affichera de belles images.

Les **pré-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir réaliser la [partie 1](part_01.MD) ainsi que la [partie 2](part_02.MD) de ce tutoriel.

Je vous invite à télécharger [le code](https://github.com/chris-scientist/gb-poo/archive/v2.0.0.zip) qui est le résultat de la deuxième partie, ceci pour partir sur des bases communes.

## CRÉATION DES SPRITES

Nous allons voir dans un premier temps la gestion et l'affichage des différents sprites qui composent notre jeu. Le jeu compte 7 sprites différents qui sont :
* un mur ;
* une caisse (en dehors de la zone de 'chargement') ;
* une caisse sur la zone de 'chargement' ;
* une zone de 'chargement' ;
* le joueur (en dehors de la zone de 'chargement') ;
* le joueur sur la zone de chargement ;
* et le sol.

Pour chaque sprites le principe est le même, il faut créer une fois l'image et la stocker en mémoire afin de l'utiliser durant toute la vie de notre programme. Je vous montre avec l'image du mur et je vous laisserai faire avec les autres images. Rendez-vous dans SpritesManager.cpp, où nous allons y définir la méthode getWall.

Voici le code :

    bool SpritesManager::wallInitialized = false;
    Image SpritesManager::wall;
    
    Image& SpritesManager::getWall()  {
        if(! SpritesManager::wallInitialized) {
            static const uint16_t wallData[] = {
                8, 8, 1, 0, 0, 0, 
                0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,
                0xacd0,0xacd0,0xacd0,0x5268,0x5268,0xacd0,0xacd0,0xacd0,
                0xacd0,0xacd0,0xacd0,0x5268,0x5268,0xacd0,0xacd0,0xacd0,
                0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,
                0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,
                0x5268,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0x5268,
                0x5268,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0x5268,
                0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268,0x5268
            };
            SpritesManager::wall = Image(wallData);
            SpritesManager::wallInitialized = true;
        }
        return SpritesManager::wall;
    }

Voici les tableaux associés aux autres sprites :

    // Une caisse
    static const uint16_t boxData[] = {
        8, 8, 1, 0, 0, 0, 
        0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,
        0xacd0,0x0,0x0,0x0,0x0,0x0,0x0,0xacd0,
        0xacd0,0x0,0x0,0xfeb2,0xfeb2,0xfeb2,0x0,0xacd0,
        0xacd0,0x0,0xfeb2,0x0,0xfeb2,0xfeb2,0x0,0xacd0,
        0xacd0,0x0,0xfeb2,0xfeb2,0x0,0xfeb2,0x0,0xacd0,
        0xacd0,0x0,0xfeb2,0xfeb2,0xfeb2,0x0,0x0,0xacd0,
        0xacd0,0x0,0x0,0x0,0x0,0x0,0x0,0xacd0,
        0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0
    };
    
    // Une caisse sur la zone de 'chargement'
    static const uint16_t boxOnAreaData[] = {
        8, 8, 1, 0, 0, 0, 
        0x44a,0x44a,0x44a,0x44a,0x44a,0x44a,0x44a,0x44a,
        0x44a,0x0,0x0,0x0,0x0,0x0,0x0,0x44a,
        0x44a,0x0,0x0,0xfeb2,0xfeb2,0xfeb2,0x0,0x44a,
        0x44a,0x0,0xfeb2,0x0,0xfeb2,0xfeb2,0x0,0x44a,
        0x44a,0x0,0xfeb2,0xfeb2,0x0,0xfeb2,0x0,0x44a,
        0x44a,0x0,0xfeb2,0xfeb2,0xfeb2,0x0,0x0,0x44a,
        0x44a,0x0,0x0,0x0,0x0,0x0,0x0,0x44a,
        0x44a,0x44a,0x44a,0x44a,0x44a,0x44a,0x44a,0x44a
    };
    
    // Une zone de 'chargement'
    static const uint16_t areaData[] = {
        8, 8, 1, 0, 0, 0, 
        0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,
        0xd8e4,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xfd42,0xd8e4,
        0xd8e4,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xd8e4,
        0xd8e4,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xd8e4,
        0xd8e4,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xd8e4,
        0xd8e4,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xd8e4,
        0xd8e4,0xcc68,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xd8e4,
        0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4
    };
    
    // Le joueur (en dehors de la zone de 'chargement')
    static const uint16_t characterData[] = {
        8, 8, 1, 0, 0, 0, 
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,
        0xcc68,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xcc68,
        0xcc68,0xacd0,0x7ddf,0xfeb2,0xfeb2,0x7ddf,0xacd0,0xfd42,
        0xfd42,0xfd42,0xfd42,0xfeb2,0xfeb2,0xfd42,0xfd42,0xfd42,
        0xfd42,0x210,0x210,0x210,0x210,0x210,0x210,0xfd42,
        0xcc68,0xcc68,0x210,0x210,0x210,0x210,0xfd42,0xfd42,
        0xfd42,0xcc68,0xcc68,0x210,0x210,0xcc68,0xcc68,0xfd42,
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42
    };
    
    // Le joueur sur la zone de chargement
    static const uint16_t characterOnAreaData[] = {
        8, 8, 1, 0, 0, 0, 
        0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,
        0xd8e4,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xacd0,0xd8e4,
        0xd8e4,0xacd0,0x7ddf,0xfeb2,0xfeb2,0x7ddf,0xacd0,0xd8e4,
        0xd8e4,0xfd42,0xfd42,0xfeb2,0xfeb2,0xfd42,0xfd42,0xd8e4,
        0xd8e4,0x210,0x210,0x210,0x210,0x210,0x210,0xd8e4,
        0xd8e4,0xcc68,0x210,0x210,0x210,0x210,0xfd42,0xd8e4,
        0xd8e4,0xcc68,0xcc68,0x210,0x210,0xcc68,0xcc68,0xd8e4,
        0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4
    };
    
    // Le sol
    static const uint16_t floorData[] = {
        8, 8, 1, 0, 0, 0, 
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,
        0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xfd42,0xcc68,
        0xcc68,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xfd42,
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,
        0xcc68,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,0xfd42,
        0xfd42,0xcc68,0xcc68,0xfd42,0xfd42,0xcc68,0xcc68,0xfd42,
        0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42,0xfd42
    };

Je vous fournis des sprites mais libre à vous de personnaliser l'affichage comme vous le souhaitez. Pour ce faire rien de bien compliqué, créez votre image de 8 pixels par 8, passez cette dernière dans le [générateur](https://gamebuino.com/creations/png-to-code) puis modifier le tableau en conséquence.

Dans MapView.cpp nous allons écrire la méthode getSprites, dont voici un extrait du pseudo code :

    SELON type de sprites ALORS
        SI type de sprites = mur ALORS
            RETOURNER image du mur
        FIN SI
        SI type de sprites = caisse ALORS
            RETOURNER image de la caisse
        FIN SI
        // Faire de même pour l'ensemble des sprites
    FIN SELON

Voici le code complet de la méthode getSprites :

    Image& MapView::getSprites(const char typeOfSprites) const {
        switch(typeOfSprites) {
            case TypeOfSprites::WALL_TYPE:
                return SpritesManager::getWall();
            break;
            case TypeOfSprites::BOX_TYPE:
                return SpritesManager::getBox();
            break;
            case TypeOfSprites::DESTINATION_TYPE:
                return SpritesManager::getArea();
            break;
            case TypeOfSprites::BOX_ON_ZONE_TYPE:
                return SpritesManager::getBoxOnArea();
            break;
            case TypeOfSprites::PLAYER_TYPE:
                return SpritesManager::getCharacter();
            break;
            case TypeOfSprites::PLAYER_ON_ZONE_TYPE:
                return SpritesManager::getCharacterOnArea();
            break;
            case TypeOfSprites::FLOOR_TYPE:
                return SpritesManager::getFloorImg();
            break;
        }
    }

Nous allons tester l'affichage de nos sprites. Dans un premier temps vous pouvez commenter l'ensemble des lignes de debug créées jusqu'à maintenant, rappelez-vous il s'agit de ces lignes qui affichent du texte. Une fois fait, dans la méthode paint de MapView écrivez le code pour afficher les sprites.

Par exemple, pour afficher le mur en x, y voici ce que vous devez écrire :

    gb.display.drawImage(x, y, getSprites(TypeOfSprites::WALL_TYPE));

Essayez d'obtenir le résultat suivant :

[Affichage des différents sprites sur la Gamebuino](Images/affichage_sprites.BMP)

Voici le code que j'ai écris pour obtenir un tel résultat :

    void MapView::paint(const int* aCameraPos) const {
        //gb.display.printf("Init pos %d,%d", mapModel->getPlayerPositions()[0], mapModel->getPlayerPositions()[1]);
        gb.display.drawImage(0, 0, getSprites(TypeOfSprites::PLAYER_TYPE));
        gb.display.drawImage(16, 0, getSprites(TypeOfSprites::WALL_TYPE));
        gb.display.drawImage(32, 0, getSprites(TypeOfSprites::BOX_TYPE));
        gb.display.drawImage(48, 0, getSprites(TypeOfSprites::DESTINATION_TYPE));
        gb.display.drawImage(0, 16, getSprites(TypeOfSprites::PLAYER_ON_ZONE_TYPE));
        gb.display.drawImage(16, 16, getSprites(TypeOfSprites::FLOOR_TYPE));
        gb.display.drawImage(32, 16, getSprites(TypeOfSprites::BOX_ON_ZONE_TYPE));
    }

## AFFICHER LA ZONE VISIBLE DE LA CARTE

Dans un premier temps, nous allons afficher le caractère représentant le sprites, nous verrons ensuite comment afficher l'image correspondante.

Il faut écrire dans MapModel la méthode qui pour les coordonnées X, Y retourne le caractère, il s'agit de la méthode getTypeOfSprites que voici :

    const char MapModel::getTypeOfSprites(const int aXSprites, const int aYSprites) {
        return mapOfGame[aYSprites][aXSprites];
    }

Voici le pseudo code qui affiche la partie visible de la carte, à écrire dans la méthode paint de MapView :

    POUR y allant de Y0 à Y1 FAIRE
        POUR x allant de X0 à X1 FAIRE
            Afficher le caractère ayant pour coordonnées x, y
        FIN POUR
        Retourner à la ligne
    FIN POUR

Voici 2 astuces pour vous guider :

    // Afficher le caractère '@'
    gb.display.printf("%c", '@');
    
    // Retourner à la ligne
	gb.display.println("");

Voici le code à écrire :

    void MapView::paint(const int* aCameraPos) const {
        for(int y = aCameraPos[1] ; y < aCameraPos[3] ; y++) {
            for(int x = aCameraPos[0] ; x < aCameraPos[2] ; x++) {
                gb.display.printf("%c", mapModel->getTypeOfSprites(x, y));
            }
            gb.display.println("");
        }
    }

Dans un second temps, vous pouvez maintenant afficher les images des sprites, voici le code à écrire :

    void MapView::paint(const int* aCameraPos) const {
        int l = 0;
        for(int y = aCameraPos[1] ; y < aCameraPos[3] ; y++) {
            int c = 0;
            for(int x = aCameraPos[0] ; x < aCameraPos[2] ; x++) {
                gb.display.drawImage(c*SpritesManager::WIDTH_SPRITES, l*SpritesManager::HEIGHT_SPRITES, getSprites(mapModel->getTypeOfSprites(x, y)));
                c++;
            }
            l++;
        }
    }

La gestion de l'affichage est désormais écrite, amusez vous à déplacer le joueur sur la carte (le caractère '@') et relancez le programme pour constater que l'affichage est différent.

Si vous avez terminé ou si vous rencontrez des problèmes vous pouvez télécharger la solution [ici](https://github.com/chris-scientist/gb-poo/archive/v3.0.0.zip).

Dans la [prochaine partie](part_04.MD), c'est-à-dire la quatrième, nous réaliserons la gestion du personnage.

N'hésitez pas à me faire un retour : les améliorations que vous apporteriez (un regard extérieur est toujours bienvenu), les fautes, etc.
