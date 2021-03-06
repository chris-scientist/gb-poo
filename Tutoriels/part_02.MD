
# SOKOBAN vs POO / Partie 2 : cam�ra

v0.1.2

## INTRODUCTION

Dans la [premi�re partie](part_01.MD) nous avons cr�� les bases de notre programme. Nous allons voir dans cette deuxi�me partie la gestion de la cam�ra.

Les **pr�-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir r�aliser la [premi�re partie](part_01.MD) de ce tutoriel.

Je vous invite � t�l�charger [le code](https://github.com/chris-scientist/gb-poo/archive/v1.0.0.zip) qui est le r�sultat de la premi�re partie, ceci pour partir sur des bases communes.

## PARAM�TRAGE

Nous allons voir ici le param�trage du programme c'est-�-dire la valorisation des constantes utiles au programme (du moins celle qui ne le sont pas d�j�, en effet la carte du jeu est d�j� initialis�e comme d'autres param�tres du jeu).

Dans CameraModel nous avons deux constantes :
* W_CENTER_PLAYER : qui indique le nombre de sprites avant d'afficher le personnage sur l'axe X.
* H_CENTER_PLAYER : qui indique le nombre de sprites avant d'afficher le personnage sur l'axe Y.

Sur l'axe X on veut afficher 5 sprites avant le personnage et sur l'axe Y on veut afficher 4 sprites.

Nous allons initialis� ces valeurs dans le fichier de d�finition de la classe c'est-�-dire CameraModel.cpp. Pensez � inclure le fichier de d�claration de la classe, sans quoi vous aurez des probl�mes.

Voici ce que devriez obtenir :

    #include "CameraModel.h"
	
	const int CameraModel::W_CENTER_PLAYER = 5;
	const int CameraModel::H_CENTER_PLAYER = 4;

## GESTION DE LA CAM�RA

**Etape 1 : la position du joueur**

En effet, la cam�ra est centr�e sur la position du joueur. Ainsi il nous faut conna�tre la position du joueur avant de d�velopper la gestion de la cam�ra.

Nous allons �crire la d�finition de la m�thode *initPlayerPositions* de la classe MapModel. Le pseudo code de cette m�thode est le suivant :

    SI position non initialis� ALORS
	    PARCOURIR l'axe Y
		    PARCOURIR l'axe X
			    SI position actuelle = position du joueur ALORS
					Initialiser la position du joueur
				FIN SI
			FIN PARCOURIR
		FIN PARCOURIR
	FIN SI

Si vous ne savez pas comment faire ou si vous voulez v�rifier votre code voici comment j'ai fait :

    void MapModel::initPlayerPositions() {
        if(playerPositions[0] == -1 && playerPositions[1] == -1) {
            // on initialise la position que si elle ne l'ai pas d�j�
            for(int y=0 ; y < HEIGHT_MAP ; y++) {
                for(int x=0 ; x < WIDTH_MAP; x++) {
                    if(mapOfGame[y][x] == TypeOfSprites::PLAYER_TYPE) {
                        playerPositions[0] = x;
                        playerPositions[1] = y;
                    }
                }
            }
        }
    }

Remarque : cette m�thode n'est pas optimis�e, effectivement elle continue � parcourir le reste de la carte, et ceci m�me apr�s avoir trouv� le joueur.

Il est n�cessaire d'appeler cette m�thode � l'initialisation du programme. Vous voyez o� ? Oui c'est �a dans le constructeur de MapModel, comme ceci :

    MapModel::MapModel() {
        initPlayerPositions();
    }

Maintenant nous allons initialiser le joueur avec sa position (que nous venons de calculer) et nous allons d�velopper un programme qui permet d'afficher cette position (ceci dans le but de d�bugguer notre programme).

Pour ce faire il faut �crire les accesseurs sur la position initial, on parle �galement de *getters*. Les quoi ? Les m�thodes qui permettent d'acc�der � un attribut. En effet, rappelez vous de l'encapsulation qui interdit au code ext�rieur d'avoir acc�s au attribut.

Il faut alors �crire :
* *getPlayerPositions* de *MapModel*
* *getPlayerPositions* de *MapController*

Voici le code :

    // Dans MapModel.cpp
	const int* MapModel::getPlayerPositions() const {
        return playerPositions;
    }
	
	// Dans MapController.cpp
	const int* MapController::getPlayerPositions() const {
        return model->getPlayerPositions();
    }

Pour initialiser la position du joueur, il faut �crire les constructeur des classes suivantes :
* MainController
* MapController
* MapView
* CharacterController
* CharacterModel

Voici dans l'ordre les constructeurs, pensez � inclure les fichiers de d�claration :

    // Dans MainController.cpp :
	MainController::MainController(MapController *aMapController, CameraModel *aCameraModel, CharacterController * aCharacterController) : mapController(aMapController), cameraModel(aCameraModel), characterController(aCharacterController) {
    
    }
	
	// Dans MapController.cpp :
	MapController::MapController(MapModel *aMapModel, MapView *aMapView) : model(aMapModel), view(aMapView) {
    
    }
	
	// Dans MapView.cpp :
	MapView::MapView(MapModel *aMapModel) : mapModel(aMapModel) {
    
    }
	
	// Dans CharacterController.cpp :
	CharacterController::CharacterController(CharacterModel *aCharacter, MapModel *aMapModel) : character(aCharacter), mapModel(aMapModel), stopMove(false) {
    
    }
	
	// Note : le r�le de l'attribut stopMove sera trait� ult�rieurement.
	
	// Dans CharacterModel.cpp :
	CharacterModel::CharacterModel(const int* initPlayerPos) : x(initPlayerPos[0]), y(initPlayerPos[1]), oldTypeOfSprites(TypeOfSprites::FLOOR_TYPE) {
        nextPos[0] = x;
        nextPos[1] = y;
    }

Nous allons maintenant initialis� nos objets dans le programme principale, voici ce que vous devez �crire (pensez � inclure les fichiers de d�claration) :

    // En dehors des fonctions setup et loop :
	MainController * mainController;
    MapModel * mapModel;
    MapController * mapController;
	
	// Voici � quoi doit ressembler la fonction setup
	void setup() {
        // initialiser la gamebuino
        gb.begin();
        // initialision de l'application
        mapModel = new MapModel();
        mapController = new MapController(mapModel, new MapView(mapModel));
        mainController = new MainController(mapController, new CameraModel(), new CharacterController(new CharacterModel(mapController->getPlayerPositions()), mapModel));
    }

Voil� pour l'initialisation de la position du joueur, � ce stade vous pouvez compiler votre code, �a ne fera rien mais vous ne devriez pas avoir d'erreur, maintenant affichons cette position.

Pour cela nous allons nous servir de la m�thode run de MainController, qui va appeler la m�thode paint de MapController, qui � son tour fait appel � paint de MapView.

Voici le code :

    // Dans MainController.cpp :
	void MainController::run() {
	    gb.display.println("v2.0.0"); // A SUPPRIMER
	    const int cameraPos[4] = {0, 0, 0, 0};
	    mapController->paint(cameraPos);
	}
	
	// Dans MapController.cpp :
    void MapController::paint(const int* aCameraPos) const {
        view->paint(aCameraPos);
    }
	
	// Dans MapView.cpp
	void MapView::paint(const int* aCameraPos) const {
        gb.display.println("Init pos %d,%d", mapModel->getPlayerPositions()[0], mapModel->getPlayerPositions()[1]);
    }

Enfin avant de tester, il faut ajouter une ligne dans le programme principale, exactement � la fin de la fonction loop :

    mainController->run();

Compilez ce programme !

Votre gamebuino devrait afficher quelque chose comme :

    v2.0.0
	Init pos 11,8

La premi�re �tape pour la gestion de la cam�ra est achev�e.

**Etape 2 : calculer coordonn�es cam�ra**

Pour calculer les coordonn�es de la cam�ra il nous faut acc�der � la position actuelle du joueur, ainsi �crivons les getters des coordoon�es.

Une petite aide rendez-vous dans CharacterModel et CharacterController.

Voici le code � �crire :

    // ---------------------------------------
	// Dans CharacterModel.cpp :
	
	const int CharacterModel::getX() const {
	    return x;
	}
	
	const int CharacterModel::getY() const {
	    return y;
	}
	
	// ---------------------------------------
	// Dans CharacterController.cpp :
	
	const int CharacterController::getX() const {
		return character->getX();
	}
	
	const int CharacterController::getY() const {
	    return character->getY();
	}

Pour tester ces getters vous pouvez ajouter les deux lignes suivantes dans MainController::run :

    gb.display.printf("Player pos %d,%d", characterController->getX(), characterController->getY());
    gb.display.println("");

Ainsi votre programme devrait afficher quelque chose comme :

	v2.0.0
	Player pos 11,8
	Init pos 11,8

Une derni�re �tape avant de calculer les coordonn�es de la cam�ra, il faut d�terminer le nombres de sprites qu'on peut dessiner dans la largeur et la hauteur.

Pour ce faire rendez-vous dans SpritesManager o� nous allons y d�finir la taille des sprites et c'est assez simple puisque les sprites font 8 pixels de large par 8 pixels de haut. D�finissez les constantes WIDTH_SPRITES et HEIGHT_SPRITES.

Voici le code :

    // Dans SpritesManager.cpp :
	const uint16_t SpritesManager::WIDTH_SPRITES = 8;
	const uint16_t SpritesManager::HEIGHT_SPRITES = 8;

Calculer le nombre de sprites en largeur et en hauteur est plut�t facile, voici le pseudo code :

    // Nombre de sprites en largeur :
	Largeur d'�cran / Largeur du sprites
	
	// Nombres de sprites en hauteur :
	Hauteur d'�cran / Hauteur du sprites

Avant de regarder la solution, aller faire un tour dans Constantes.h, en effet on y d�finit la taille de l'�cran. Enfin derni�re piste : il faut �crire les m�thodes getNbSpritesInWidth et getNbSpritesInHeight dans CameraModel.

Voici le r�sultat :

    const int CameraModel::getNbSpritesInWidth() {
        return (WIDTH_SCREEN / SpritesManager::WIDTH_SPRITES);
    }
    
    const int CameraModel::getNbSpritesInHeight() {
        return (HEIGHT_SCREEN / SpritesManager::HEIGHT_SPRITES);
    }

Pour vous guider dans l'�criture de la gestion de la cam�ra je vais vous fournir � nouveau le pseudo code, pour cela on suppose que *aX* repr�sente la position x du joueur et *aY* sa position y. De plus, la cam�ra a deux couple de coordonn�es (X0,Y0) et (X1,Y1), le premier couple se trouve en haut � gauche alors que le second se trouve en bas � droite.

    X0 = aX - Nombre de sprites en largeur avant le joueur
	Y0 = aY - Nombre de sprites en hauteur avant le joueur
	X1 = X0 + Nombre de sprites en largeur + 1
	Y1 = Y0 + Nombre de sprites en hauteur + 1
	
	SI X0 en dehors de la carte ALORS
	    X0 = 0
        X1 = X0 + Nombre de sprites en largeur + 1
	FIN SI
	
	SI Y0 en dehors de la carte ALORS
	    Y0 = 0
        Y1 = Y0 + Nombre de sprites en hauteur + 1
	FIN SI
    
	SI X1 en dehors de la carte ALORS
	    X1 = Largeur de la carte
        X0 = X1 - Nombre de sprites en largeur
	FIN SI
    
	SI Y1 en dehors de la carte ALORS
	    Y1 = Hauteur de la carte
        Y0 = Y1 - Nombre de sprites en hauteur
	FIN SI

Voici le code � �crire :

    const int* CameraModel::getCameraPositions(const int aX, const int aY) {
        // Par d�faut, nous essayons de centrer la cam�ra sur le personnage soit :
        // - en largeur : 5 sprites + le personnage + 4 sprites
        // - en hauteur : 4 sprites + le personnage + 3 sprites
        cameraPositions[0] = aX - CameraModel::W_CENTER_PLAYER;
        cameraPositions[1] = aY - CameraModel::H_CENTER_PLAYER;
        cameraPositions[2] = cameraPositions[0] + getNbSpritesInWidth() + 1;
        cameraPositions[3] = cameraPositions[1] + getNbSpritesInHeight() + 1;

        // si la cam�ra est en-dehors de la carte
        bool cameraX0Out = (cameraPositions[0] < 0);
        bool cameraY0Out = (cameraPositions[1] < 0);
        bool cameraX1Out = (cameraPositions[2] >= MapModel::WIDTH_MAP);
        bool cameraY1Out = (cameraPositions[3] >= MapModel::HEIGHT_MAP);
        if(cameraX0Out || cameraY0Out || cameraX1Out || cameraY1Out) {
            if(cameraX0Out) {
                cameraPositions[0] = 0;
                cameraPositions[2] = cameraPositions[0] + getNbSpritesInWidth() + 1;
            }
            if(cameraY0Out) {
                cameraPositions[1] = 0;
                cameraPositions[3] = cameraPositions[1] + getNbSpritesInHeight() + 1;
            }
            if(cameraX1Out) {
                cameraPositions[2] = MapModel::WIDTH_MAP;
                cameraPositions[0] = cameraPositions[2] - getNbSpritesInWidth();
            }
            if(cameraY1Out) {
                cameraPositions[3] = MapModel::HEIGHT_MAP;
                cameraPositions[1] = cameraPositions[3] - getNbSpritesInHeight();
            }
        }

        return cameraPositions;
    }

Remplacer la ligne suivante, par le calcul des coordonn�es de la cam�ra c'est-�-dire faire appel � la m�thode que l'on vient d'�crire :

    const int cameraPos[4] = {0, 0, 0, 0};

Voici comment faire :

    const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());

Enfin pour tester votre code dans MainController::run ajouter les deux lignes suivantes :

    gb.display.printf("Cam %d,%d : %d,%d", cameraPos[0], cameraPos[1], cameraPos[2], cameraPos[3]);
    gb.display.println("");

Compilez, le r�sultat obtenu devrait ressembler � :

    v2.0.0
	Player pos 11,8
	Cam 6,3 : 17,11
	Init pos 11,8

La gestion de la cam�ra est d�sormais �crite, amusez vous � d�placer le joueur sur la carte (le caract�re '@') et relancez le programme pour constater que les coordonn�es de la cam�ra sont modifi�es.

Si vous avez termin� ou si vous rencontrez des probl�mes vous pouvez t�l�charger la solution [ici](https://github.com/chris-scientist/gb-poo/archive/v2.0.0.zip).

Dans la [prochaine partie](part_03.MD), c'est-�-dire la troisi�me, nous r�aliserons l'affichage du jeu.

N'h�sitez pas � me faire un retour : les am�liorations que vous apporteriez (un regard ext�rieur est toujours bienvenu), les fautes, etc.
