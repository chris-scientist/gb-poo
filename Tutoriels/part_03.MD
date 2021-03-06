
# SOKOBAN vs POO / Partie 3 : affichage

v0.1.1

## INTRODUCTION

Dans les parties pr�c�dentes nous avons vu les bases de notre programme ainsi que la gestion de la cam�ra. Nous allons voir dans cette troisi�me partie la gestion de l'affichage, ainsi � la fin de cette partie notre �cran affichera de belles images.

Les **pr�-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir r�aliser la [partie 1](part_01.MD) ainsi que la [partie 2](part_02.MD) de ce tutoriel.

Je vous invite � t�l�charger [le code](https://github.com/chris-scientist/gb-poo/archive/v2.0.0.zip) qui est le r�sultat de la deuxi�me partie, ceci pour partir sur des bases communes.

## CR�ATION DES SPRITES

Nous allons voir dans un premier temps la gestion et l'affichage des diff�rents sprites qui composent notre jeu. Le jeu compte 7 sprites diff�rents qui sont :
* un mur ;
* une caisse (en dehors de la zone de 'chargement') ;
* une caisse sur la zone de 'chargement' ;
* une zone de 'chargement' ;
* le joueur (en dehors de la zone de 'chargement') ;
* le joueur sur la zone de chargement ;
* et le sol.

Pour chaque sprites le principe est le m�me, il faut cr�er une fois l'image et la stocker en m�moire afin de l'utiliser durant toute la vie de notre programme. Je vous montre avec l'image du mur et je vous laisserai faire avec les autres images. Rendez-vous dans SpritesManager.cpp, o� nous allons y d�finir la m�thode getWall.

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

Voici les tableaux associ�s aux autres sprites :

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

Je vous fournis des sprites mais libre � vous de personnaliser l'affichage comme vous le souhaitez. Pour ce faire rien de bien compliqu�, cr�ez votre image de 8 pixels par 8, passez cette derni�re dans le [g�n�rateur](https://gamebuino.com/creations/png-to-code) puis modifier le tableau en cons�quence.

Dans MapView.cpp nous allons �crire la m�thode getSprites, dont voici un extrait du pseudo code :

    SELON type de sprites ALORS
        SI type de sprites = mur ALORS
            RETOURNER image du mur
        FIN SI
        SI type de sprites = caisse ALORS
            RETOURNER image de la caisse
        FIN SI
        // Faire de m�me pour l'ensemble des sprites
    FIN SELON

Voici le code complet de la m�thode getSprites :

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

Nous allons tester l'affichage de nos sprites. Dans un premier temps vous pouvez commenter l'ensemble des lignes de debug cr��es jusqu'� maintenant, rappelez-vous il s'agit de ces lignes qui affichent du texte. Une fois fait, dans la m�thode paint de MapView �crivez le code pour afficher les sprites.

Par exemple, pour afficher le mur en x, y voici ce que vous devez �crire :

    gb.display.drawImage(x, y, getSprites(TypeOfSprites::WALL_TYPE));

Essayez d'obtenir le r�sultat suivant :

[Affichage des diff�rents sprites sur la Gamebuino](Images/affichage_sprites.BMP)

Voici le code que j'ai �cris pour obtenir un tel r�sultat :

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

Dans un premier temps, nous allons afficher le caract�re repr�sentant le sprites, nous verrons ensuite comment afficher l'image correspondante.

Il faut �crire dans MapModel la m�thode qui pour les coordonn�es X, Y retourne le caract�re, il s'agit de la m�thode getTypeOfSprites que voici :

    const char MapModel::getTypeOfSprites(const int aXSprites, const int aYSprites) {
        return mapOfGame[aYSprites][aXSprites];
    }

Voici le pseudo code qui affiche la partie visible de la carte, � �crire dans la m�thode paint de MapView :

    POUR y allant de Y0 � Y1 FAIRE
        POUR x allant de X0 � X1 FAIRE
            Afficher le caract�re ayant pour coordonn�es x, y
        FIN POUR
        Retourner � la ligne
    FIN POUR

Voici 2 astuces pour vous guider :

    // Afficher le caract�re '@'
    gb.display.printf("%c", '@');
    
    // Retourner � la ligne
	gb.display.println("");

Voici le code � �crire :

    void MapView::paint(const int* aCameraPos) const {
        for(int y = aCameraPos[1] ; y < aCameraPos[3] ; y++) {
            for(int x = aCameraPos[0] ; x < aCameraPos[2] ; x++) {
                gb.display.printf("%c", mapModel->getTypeOfSprites(x, y));
            }
            gb.display.println("");
        }
    }

Dans un second temps, vous pouvez maintenant afficher les images des sprites, voici le code � �crire :

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

La gestion de l'affichage est d�sormais �crite, amusez vous � d�placer le joueur sur la carte (le caract�re '@') et relancez le programme pour constater que l'affichage est diff�rent.

Si vous avez termin� ou si vous rencontrez des probl�mes vous pouvez t�l�charger la solution [ici](https://github.com/chris-scientist/gb-poo/archive/v3.0.0.zip).

Dans la [prochaine partie](part_04.MD), c'est-�-dire la quatri�me, nous r�aliserons la gestion du personnage.

N'h�sitez pas � me faire un retour : les am�liorations que vous apporteriez (un regard ext�rieur est toujours bienvenu), les fautes, etc.
