
# SOKOBAN vs POO / Partie 2 : affichage et caméra

v0.0.1

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
					Initilaiser la position du joueur
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

Pour ce faire il faut écrire les accesseurs sur la position initial. Les quoi ? Les méthodes qui permettent d'accéder à un attribut. En effet, rappelez vous de l'encapsulation qui interdit au code extérieur d'avoir accès au attribut.

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
	    const int* cameraPos[4] = {0, 0, 0, 0};
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

*Cette partie est en cours de rédaction, merci de votre patience !*
