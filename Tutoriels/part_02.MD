
# SOKOBAN vs POO / Partie 2 : affichage et caméra

v0.0.2

## INTRODUCTION

Dans la [première partie](https://gamebuino.com/creations/sokoban-vs-poo-partie-1-les-bases) nous avons créé les bases de notre programme. Nous allons voir dans cette deuxième partie la gestion de l'affichage et la gestion de la caméra.

Les **pré-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.
* Avoir réaliser la [première partie](https://gamebuino.com/creations/sokoban-vs-poo-partie-1-les-bases) de ce tutoriel.

Je vous invite à télécharger [le code](https://github.com/chris-scientist/gb-poo/archive/v1.0.0.zip) qui est le résultat de la première partie, ceci pour partir sur des bases communes.

## PARAMÉTRAGE

Nous allons voir ici le paramétrage du programme c'est-à-dire la valorisation des constantes utiles au programme (du moins celle qui ne le sont pas déjà, en effet la carte du jeu est déjà initialisée comme d'autres paramètres du jeu).

Dans CameraModel nous avons deux constantes :
* W_CENTER_PLAYER : qui indique le nombre de sprites avant d'afficher le personnage sur l'axe X.
* H_CENTER_PLAYER : qui indique le nombre de sprites avant d'afficher le personnage sur l'axe Y.

Sur l'axe X on veut afficher 5 sprites avant le personnage et sur l'axe Y on veut afficher 4 sprites.

Nous allons initialisé ces valeurs dans le fichier de définition de la classe c'est-à-dire CameraModel.cpp. Pensez à inclure le fichier de déclaration de la classe, sans quoi vous aurez des problèmes.

Voici ce que devriez obtenir :

    #include "CameraModel.h"
	
	const int CameraModel::W_CENTER_PLAYER = 5;
	const int CameraModel::H_CENTER_PLAYER = 4;

## GESTION DE LA CAMÉRA

**Etape 1 : la position du joueur**

En effet, la caméra est centrée sur la position du joueur. Ainsi il nous faut connaître la position du joueur avant de développer la gestion de la caméra.

Nous allons écrire la définition de la méthode *initPlayerPositions* de la classe MapModel. Le pseudo code de cette méthode est le suivant :

    SI position non initialisé ALORS
	    PARCOURIR l'axe Y
		    PARCOURIR l'axe X
			    SI position actuelle = position du joueur ALORS
					Initialiser la position du joueur
				FIN SI
			FIN PARCOURIR
		FIN PARCOURIR
	FIN SI

Si vous ne savez pas comment faire ou si vous voulez vérifier votre code voici comment j'ai fait :

    void MapModel::initPlayerPositions() {
        if(playerPositions[0] == -1 && playerPositions[1] == -1) {
            // on initialise la position que si elle ne l'ai pas déjà
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

Il est nécessaire d'appeler cette méthode à l'initialisation du programme. Vous voyez où ? Oui c'est ça dans le constructeur de MapModel, comme ceci :

    MapModel::MapModel() {
        initPlayerPositions();
    }

Maintenant nous allons initialiser le joueur avec sa position (que nous venons de calculer) et nous allons développer un programme qui permet d'afficher cette position (ceci dans le but de débugguer notre programme).

Pour ce faire il faut écrire les accesseurs sur la position initial, on parle également de *getters*. Les quoi ? Les méthodes qui permettent d'accéder à un attribut. En effet, rappelez vous de l'encapsulation qui interdit au code extérieur d'avoir accès au attribut.

Il faut alors écrire :
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

Pour initialiser la position du joueur, il faut écrire les constructeur des classes suivantes :
* MainController
* MapController
* MapView
* CharacterController
* CharacterModel

Voici dans l'ordre les constructeurs, pensez à inclure les fichiers de déclaration :

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
	
	// Note : le rôle de l'attribut stopMove sera traité ultérieurement.
	
	// Dans CharacterModel.cpp :
	CharacterModel::CharacterModel(const int* initPlayerPos) : x(initPlayerPos[0]), y(initPlayerPos[1]), oldTypeOfSprites(TypeOfSprites::FLOOR_TYPE) {
        nextPos[0] = x;
        nextPos[1] = y;
    }

Nous allons maintenant initialisé nos objets dans le programme principale, voici ce que vous devez écrire (pensez à inclure les fichiers de déclaration) :

    // En dehors des fonctions setup et loop :
	MainController * mainController;
    MapModel * mapModel;
    MapController * mapController;
	
	// Voici à quoi doit ressembler la fonction setup
	void setup() {
        // initialiser la gamebuino
        gb.begin();
        // initialision de l'application
        mapModel = new MapModel();
        mapController = new MapController(mapModel, new MapView(mapModel));
        mainController = new MainController(mapController, new CameraModel(), new CharacterController(new CharacterModel(mapController->getPlayerPositions()), mapModel));
    }

Voilà pour l'initialisation de la position du joueur, à ce stade vous pouvez compiler votre code, ça ne fera rien mais vous ne devriez pas avoir d'erreur, maintenant affichons cette position.

Pour cela nous allons nous servir de la méthode run de MainController, qui va appeler la méthode paint de MapController, qui à son tour fait appel à paint de MapView.

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

Enfin avant de tester, il faut ajouter une ligne dans le programme principale, exactement à la fin de la fonction loop :

    mainController->run();

Compilez ce programme !

Votre gamebuino devrait afficher quelque chose comme :

    v2.0.0
	Init pos 11,8

La première étape pour la gestion de la caméra est achevée.

**Etape 2 : calculer coordonnées caméra**

Pour calculer les coordonnées de la caméra il nous faut accéder à la position actuelle du joueur, ainsi écrivons les getters des coordoonées.

Une petite aide rendez-vous dans CharacterModel et CharacterController.

Voici le code à écrire :

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

Une dernière étape avant de calculer les coordonnées de la caméra, il faut déterminer le nombres de sprites qu'on peut dessiner dans la largeur et la hauteur.

Pour ce faire rendez-vous dans SpritesManager où nous allons y définir la taille des sprites et c'est assez simple puisque les sprites font 8 pixels de large par 8 pixels de haut. Définissez les constantes WIDTH_SPRITES et HEIGHT_SPRITES.

Voici le code :

    // Dans SpritesManager.cpp :
	const uint16_t SpritesManager::WIDTH_SPRITES = 8;
	const uint16_t SpritesManager::HEIGHT_SPRITES = 8;

Calculer le nombre de sprites en largeur et en hauteur est plutôt facile, voici le pseudo code :

    // Nombre de sprites en largeur :
	Largeur d'écran / Largeur du sprites
	
	// Nombres de sprites en hauteur :
	Hauteur d'écran / Hauteur du sprites

Avant de regarder la solution, aller faire un tour dans Constantes.h, en effet on y définit la taille de l'écran. Enfin dernière piste : il faut écrire les méthodes getNbSpritesInWidth et getNbSpritesInHeight dans CameraModel.

Voici le résultat :

    const int CameraModel::getNbSpritesInWidth() {
        return (WIDTH_SCREEN / SpritesManager::WIDTH_SPRITES);
    }
    
    const int CameraModel::getNbSpritesInHeight() {
        return (HEIGHT_SCREEN / SpritesManager::HEIGHT_SPRITES);
    }

Pour vous guider dans l'écriture de la gestion de la caméra je vais vous fournir à nouveau le pseudo code, pour cela on suppose que *aX* représente la position x du joueur et *aY* sa position y. De plus, la caméra a deux couple de coordonnées (X0,Y0) et (X1,Y1), le premier couple se trouve en haut à gauche alors que le second se trouve en bas à droite.

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

Voici le code à écrire :

    const int* CameraModel::getCameraPositions(const int aX, const int aY) {
        // Par défaut, nous essayons de centrer la caméra sur le personnage soit :
        // - en largeur : 5 sprites + le personnage + 4 sprites
        // - en hauteur : 4 sprites + le personnage + 3 sprites
        cameraPositions[0] = aX - CameraModel::W_CENTER_PLAYER;
        cameraPositions[1] = aY - CameraModel::H_CENTER_PLAYER;
        cameraPositions[2] = cameraPositions[0] + getNbSpritesInWidth() + 1;
        cameraPositions[3] = cameraPositions[1] + getNbSpritesInHeight() + 1;

        // si la caméra est en-dehors de la carte
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

Remplacer la ligne suivante, par le calcul des coordonnées de la caméra c'est-à-dire faire appel à la méthode que l'on vient d'écrire :

    const int cameraPos[4] = {0, 0, 0, 0};

Voici comment faire :

    const int* cameraPos = cameraModel->getCameraPositions(characterController->getX(), characterController->getY());

Enfin pour tester votre code dans MainController::run ajouter les deux lignes suivantes :

    gb.display.printf("Cam %d,%d : %d,%d", cameraPos[0], cameraPos[1], cameraPos[2], cameraPos[3]);
    gb.display.println("");

Le résultat obtenu devrait ressembler à :

    v2.0.0
	Player pos 11,8
	Cam 6,3 : 17,11
	Init pos 11,8

La gestion de la caméra est désormais écrite, amusez vous à déplacer le joueur sur la carte (le caractère '@') et relancez le programme pour constater que les coordonnées de la caméra sont modifiées.

*Cette partie est en cours de rédaction, merci de votre patience !*
