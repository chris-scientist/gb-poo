
# SOKOBAN vs POO / Partie 1 : les bases

v0.1.7

## SOKOBAN CONTRE POO ?

Non... POO n'est pas un ennemi !

Vous voici dans un tutoriel pour r�aliser le jeu SOKOBAN en **Programmation Orient�e Objet** c'est-�-dire POO. Dans ce tutoriel il para�t m�me que nous parlerons du mod�le d'architecture **Mod�le Vue Contr�leur** c'est-�-dire MVC. Le programme est ambitieux mais ne vous faites aucune crainte, nous avancerons pas � pas et je vais essayer d'�tre clair.  

Le tutoriel sera compos� des 5 parties suivantes :
* La partie 1 (vous �tes ici !) : vous permettra d'appr�hender les bases de la POO et du MVC.
* La [partie 2](part_02.MD) : vous permettra de r�aliser la gestion de la cam�ra (�videment � la sauce POO, comme le reste des parties).
* La [partie 3](part_03.MD) : vous permettra de g�rer l'affichage du jeu.
* La [partie 4](part_04.MD) : vous permettra de g�rer les d�placements du personnage.
* La [partie 5](part_05.MD) : vous permettra de g�rer la physique du jeu et la fin de partie.

Voici pour la pr�sentation du tutoriel.



Les **pr�-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.

## PRINCIPE DU JEU

Avant de faire une partie th�orique, je vais vous pr�senter le jeu SOKOBAN. Il s'agit d'un jeu id�al pour appr�hender les concepts de la programmation orient� objet. Et oui, sinon je n'aurai pas fait ce tutoriel.

Nous jouons un gardien dans un entrep�t.  Dans ce lieu se trouve des caisses que nous devons d�placer sur des zones de "chargement". C'est aussi simple que �a !

## TH�ORIE

Nous allons, avant de passer � la pratique, nous �carter un peu du jeu SOKOBAN dans cette partie th�orique. En effet, je vais vous pr�senter les concepts :
* de la Programmation Orient�e Objet ;
* et du mod�le d'architecture Mod�le Vue Contr�leur.

### Version proc�durale

Imaginons un petit jeu o� l'on doit d�placer un personnage (ceci ressemble un peu � SOKOBAN...). Mais il se d�placera sur une petite carte (20 colonnes et 10 lignes) ainsi pas besoins de g�rer de cam�ra puisqu'il s'agit de la taille de l'�cran.

Ce personnage doit :
* conna�tre sa position ;
* savoir se d�placer (vers le haut, � droite, vers la bas et � gauche) ;
* savoir ses limites (il ne peut pas aller en dehors de l'�cran).

Le personnage sera repr�sent� par un "x".

Voici le code de la version proc�durale de ce petit programme ([t�l�chargeable ici](https://github.com/chris-scientist/gb-sample/archive/v1.0.zip)).

    // TODO inclure la biblioth�que Gamebuino META

    // position du personnage
    int xCharacter;
    int yCharacter;

    void setup() {
        // initialiser la gambuino
        gb.begin();

        // initialisation de la position du personnage
        xCharacter = 10;
        yCharacter = 5;
    }

    void loop() {
        // boucle d'attente
        while(!gb.update());

        // effacer l'�cran
        gb.display.clear();

        manageMove();
        paint();
    }

    // G�rer les d�placement
    void manageMove() {
        // Note :
        // * Le test : (yCharacter > 0) permet de ne pas sortir du haut de l'�cran.
        // * Le test : (xCharacter < 19) permet de ne pas sortir de la droite de l'�cran.
        // * Le test : (yCharacter < 9) permet de ne pas sortir du bas de l'�cran.
        // * Le test : (xCharacter > 0) permet de ne pas sortir de la gauche de l'�cran.
        // Ainsi on d�finit les limites du personnage.
        if(gb.buttons.pressed(BUTTON_UP)) {
            if(yCharacter > 0) {
                yCharacter--;
            }
        } else if(gb.buttons.pressed(BUTTON_RIGHT)) {
            if(xCharacter < 19) {
                xCharacter++;
            }
        } else if(gb.buttons.pressed(BUTTON_DOWN)) {
            if(yCharacter < 9) {
                yCharacter++;
            }
        } else if(gb.buttons.pressed(BUTTON_LEFT)) {
            if(xCharacter > 0) {
                xCharacter--;
            }
        }
    }

    // G�rer l'affichage
    void paint() {
        for(int y=0 ; y<=yCharacter ; y++) {
            for(int x=0; x<20 || x<xCharacter ; x++) {
                if(x == xCharacter && y == yCharacter) {
                    gb.display.print("x"); // afficher le personnage
                } else {
                    gb.display.print(" "); // afficher une colonne vide
                }
            }
            gb.display.println(); // passage � la ligne suivante
        }
    }

### Version orient�e objet en MVC

Le MVC est un mod�le d'architecture, cela sert � d�crire comment le code doit �tre d�coup�. Le MVC implique qu'il y ai 3 couches :
* le mod�le : qui g�re les donn�es ;
* la vue : qui g�re l'affichage ;
* et le contr�leur : qui fait l'interface entre la vue et le mod�le.

Dans votre programme principale vous devez avoir uniquement des interactions avec le/les contr�leur(s).

De plus, imaginez que vous souhaitez faire un portage de votre programme vers un autre terminal (sur ordinateur, par exemple) et bien dans ce cas vous n'avez que la couche vue � modifier, voil� un int�r�t du MVC.

Encore un avantage du MVC, la r�solution de bugs :
* si vous rencontrez un bug de comportement de vos donn�es alors inspectez la couche mod�le.
* si vous rencontrez un bug d'affichage alors inspectez la couche vue.
* si vous rencontrez un bug d'interactions alors inspectez la couche contr�leur.

Pour un petit programme le d�coupage peut-�tre lourd mais voyez les avantages que cela apporte.

Un concept important dans la POO est la classe. Une classe est une structure de donn�e qui a :
* des attributs : les variables de la classe ;
* des m�thodes : les fonctions de la classe.

******

*Faisons un point sur les classes.*

Voici un exemple de classe C++ :

    // 1) D�claration
    class Plan {
	    private:
		    int nbPieces;
	    public:
		    Plan(int unNbPieces);
		    void dessiner();
	};
	
	// 2) D�finition
	Plan::Plan(int unNbPieces) : nbPieces(unNbPieces) {
	
	}
	
	void Plan::dessiner() {
	    for(int i=1 ; i<=nbPieces ; i++) {
			// dessiner la pi�ce...
		}
	}
	
	// 3) Instanciation et utilisation
	// Cr�ation d'un objet de type *Plan*
	Plan *maMaison = new Plan(2);
	// Utilisation de l'objet
	maMaison->dessiner();

On remarque plusieurs parties dans le code ci-dessus.

1. La d�claration

Elle d�finit notre classes : ses attribut et le prototype de ses m�thodes. Le mot "class" est important c'est lui qui dit au compilateur que ce que l'on �crit est une classe.

Ici nous avons un attribut : *nbPieces* c'est un entier qui contient le nombre de pi�ces du plan (c'est pas une surprise, enfin j'esp�re !).

Ensuite, nous avons deux m�thodes :
* *Plan* qui est une m�thode particuli�re puisqu'il s'agit d'un constructeur (on en reparle un peu plus loin).
* *dessiner* qui nous permettra de dessiner le plan.

Remarque : Faites attention au point-virgule � la fin des classes, sans ce point-virgule l'IDE Arduino donnera l'erreur *new types may not be defined in a return type* � la compilation.

De plus, une chose tr�s importante : les attributs doivent �tre priv�s. Il s'agit de l'encapsulation, un concept de la POO, qui veut que l'on interdit l'acc�s au attributs de classes depuis l'ext�rieur. Les m�thodes sont en revanche publique ce qui permet de les utiliser dans le programme principale par exemple.

Enfin, la d�claration se place dans un fichier *.h* (pour header, Plan.h).

**Le constructeur**

Plusieurs choses doivent �tre dites � son sujet :
* Le/les constructeur(s), il peut en effet y en avoir plusieurs, ils doivent avoir le m�me nom que la classe (sans quoi �a ne serait qu'une m�thode).
* On s'en sert pour initialiser les attributs de notre classe.

2. La d�finition

La d�finition du constructeur est particuli�re, en effet dans beaucoup de langage (ce qui reste possible en C++) il aurait fallut �crire ceci :

    Plan::Plan(int unNbPieces) {
	    nbPieces = unNbPieces;
	}

Le C++ a un petit sucre syntaxique qui permet de faire la m�me chose de la mani�re suivante :

    Plan::Plan(int unNbPieces) : nbPieces(unNbPieces) {
	    
	}

Remarque : toutes m�thodes dont le constructeur doivent �tre pr�fix�es par le nom de la classe, ici : *Plan::*.

La m�thode *dessiner* est compos�e d'une boucle qui it�re sur le nombre de pi�ces et le reste du code je le laisse pour votre imagination.

La d�finition se place dans un fichier *.cpp* (Plan.cpp pour notre exemple).

3. Instanciation et utilisation

Lorsque qu'on cr�� un objet � partir d'une classe on dit qu'on *instancie* un objet. Cet objet est une instance autrement dit c'est une maison alors que la classe est un plan. On cr�� ici un pointeur de Plan, en effet le type est "Plan *". Ainsi pour instancier l'objet il faut faire appel au mot-cl� C++ "new". Le "2" pass� au constructeur c'est le nombre de pi�ces de notre maison.

Enfin pour appeler une m�thode (sur un pointeur) il faut utiliser le symbole suivant : "->" (ici : maMaison->dessiner()).

4. Bonus

Une repr�sentation UML via un diagramme de classes est possible est le voici :

[Diagramme de classes de Plan](Images/diagramme_classes_plan.png)

Remarques : 
* Le *moins* avant l'attribut signifie qu'il est priv�.
* Le *plus* avant les m�thodes signifie qu'elles sont publiques.
* La mod�lisation n'est pas compl�te, il manque effectivement le param�tre du constructeur.


******

*Revenons � notre jeu.*

Maintenant que vous savez cr�er des classes voyons de quoi nous avons besoins pour que notre petit programme respecte le MVC. Il faut :
* CharacterModel : le mod�le c'est-�-dire le personnage.
* CharacterView : la vue qui g�re l'affichage du personnage.
* CharacterController : le contr�leur qui permet d'interagir avec le personnage.

Comme vous le voyez par convention :
* Le mod�le est suffix� par *Model*.
* La vue est suffix�e par *View*.
* Le contr�leur est suffix� par *Controller*.

Comme vous savez cr�er des classes, avant de passer � la r�alisation du SOKOBAN, vous pouvez essayer de r�aliser une version orient� objet qui respecte le MVC de notre exemple, ne r�inventez pas tout vous pouvez en effet vous inspirer de la version proc�durale.

Pour vous guider voici un diagramme de classes (fait en UML) qui repr�sente notre petit programme avec toutes les classes et m�thodes n�cessaires :

[Astuce : diagramme de classes](Images/diagramme_classes_exemple_v0.0.2.png)

Si vous n'y arrivez pas, n'ayez crainte vous pouvez t�l�charger la [version orient�e objet](https://github.com/chris-scientist/gb-sample/archive/v2.0.zip) que j'ai fait.

Remarques :
* La vue n'a pas de constructeur du moins nous n'en n'avons pas d�clar�. Nous utilisons le constructeur par d�faut.
* Il s'agit ici d'un petit exemple avec peu de classes, imaginez que vous ayez un [Rubik's cube](https://gamebuino.com/creations/jeu-rubik-s-cube) � d�velopper : l'int�r�t du MVC est alors non n�gligeable.

Enfin des am�liorations sont possibles, effectivement il devrait �tre interdit d'instancier plusieurs personnages (imaginez le d�sordre que �a engendrerai !). *Ne lisez la suite que si vous voulez avoir mal de t�te* ;). Pour faire cela nous pourrions utiliser le design pattern Singleton, mais ce n'est pas l'objectif de ce cours.

## PRATIQUE

La pratique vous permettra de cr�er l'ensemble des classes et m�thodes utiles au jeu SOKOBAN. Pour les m�thodes nous ferrons juste la description, en effet, nous verrons la d�finition (le contenu) de chacune d'elle au fur et � mesure des parties qui composent ce tutoriel.

Si vous ne vous sentez pas encore pr�t � franchir le cap de la POO, il existe une version proc�durale du jeu SOKOBAN (cf.  [partie 1 par jicehel](https://gamebuino.com/creations/sokoban-partie-1-preparons-notre-jeu)).

Je vous invite � t�l�charger le code source qui vous servira de base au programme, vous le trouverez [ici](https://github.com/chris-scientist/gb-poo/archive/v0.0.1.zip).

Voici le  diagramme de classes du code que vous devez �crire :
[Diagramme de classes Sokoban](Images/diagramme_classes_sokoban_v0.0.1.png)

Remarques :
* Les membres (attributs et m�thodes), qui sont soulign�s, repr�sentent des membres de classe, autrement dit statique (on en reparle plus loin).
* Je donne par la suite la description (type de retour et param�tres) des m�thodes (je ne l'ai pas mis sur le diagramme afin de ne pas le surcharger).
* Comme le montre le diagramme ci-dessus, vous pouvez adapter le MVC, par exemple pour une classe vous n'avez pas l'obligation d'�crire les 3 couches (c'est pourquoi il n'y a que le mod�le de cam�ra).

**Membre statique (ou membre de classe)**

On d�finit par membre statique un membre appartenant � la classe. Par exemple, un attribut statique aura la m�me valeur pour chacune des instances de la classes. Si pour une classe donn�e vous avez du code commun � toutes les instances vous pouvez alors l'�crire dans une m�thode statique.

### D�finition des m�thodes

Remarques :
* Si le type de retour n'est pas pr�cis� c'est que la m�thode ne retourne rien.
* S'il on ne pr�cise aucun attribut c'est que la m�thode n'en a pas.
* Pour les param�tres je fournis les noms.

1. CameraModel
* getNbSpritesInWidth : retourne un entier qu'on ne doit pas modifier.
* getNbSpritesInHeight : retourne un entier qu'on ne doit pas modifier.
* getCameraPositions : retourne un tableau d'entier, et prend deux entier qu'on ne doit pas modifier (aX et aY).

2. CharacterController
* moveBox : retourne un caract�re qu'on ne doit pas modifier, et prend un caract�re qu'on ne doit pas modifier (aReplacedSprites), ainsi que 4 entiers qu'on ne doit pas modifier (aX1, aY1, aX2 et aY2).
* getPlayerSprites : retourne un caract�re, et prend un caract�re qu'on ne doit pas modifier (aReplacedSprites), de plus cette m�thode ne doit pas modifier l'objet.
* isWall : retourne un bool�en qu'on ne doit pas modifier, et prend un caract�re qu'on ne doit pas modifier (aReplacedSprites), de plus cette m�thode ne doit pas modifier l'objet.
* isBox : retourne un bool�en qu'on ne doit pas modifier, et prend un caract�re qu'on ne doit pas modifier (aReplacedSprites), de plus cette m�thode ne doit pas modifier l'objet.
* CharacterController : prend deux param�tre un CharacterModel et un MapModel.
* getX : retourne un entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* getY : retourne un entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.

3. CharacterModel
* CharacterModel : prend un tableau d'entier qu'on ne doit pas modifier (initPlayerPos).
* getX : retourne un entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* getY : retourne un entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* getNextPos : retourne un tableau d'entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* getOldTypeOfSprites : retourne un caract�re qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* setOldTypeOfSprites : prend un caract�re qu'on ne doit pas modifier.

4. MainController
* MainController : prend un pointeur de MapController, un pointeur de CameraModel et un pointeur de CharacterController en param�tre (respectivement aMapController, aCameraModel et aCharacterController).

5. MapController
* MapController : prend un pointeur de MapModel et un pointeur de MapView en param�tre (respectivement aMapModel et aMapView).
* getPlayerPositions : retourne un tableau d'entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* paint : prend un tableau d'entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* isEndOfGame : retourne un bool�en, et cette m�thode ne doit pas modifier l'objet.

6. MapModel
* getPlayerPositions : retourne un tableau d'entier qu'on ne doit pas modifier, et cette m�thode ne doit pas modifier l'objet.
* getTypeOfSprites : retourne un caract�re qu'on ne doit pas modifier, et prend 2 entiers qu'on ne doit pas modifier (aXSprites et aYSprites).
* setTypeOfSprites : prend 2 entiers qu'on ne doit pas modifier (aXSprites et aYSprites), et un caract�re qu'on ne doit pas modifier (aTypeOfSprites).
* isFinish : retourne un bool�en, et cette m�thode ne doit pas modifier l'objet.

7. MapView
* getSprites : retourne une r�f�rence d'Image, prend un caract�re qu'on ne doit pas modifier (typeOfSprites), de plus cette m�thodes ne doit pas modifier l'objet.
* MapView : prend un pointeur de MapModel en param�tre (aMapModel).
* paint : prend un tableau d'entier, et cette m�thode ne doit pas modifier l'objet.

8. SpritesManager
* getArea : retourne une r�f�rence d'Image.
* getBox : retourne une r�f�rence d'Image.
* getBoxOnArea : retourne une r�f�rence d'Image.
* getCharacter : retourne une r�f�rence d'Image.
* getCharacterOnArea : retourne une r�f�rence d'Image.
* getFloorImg : retourne une r�f�rence d'Image.
* getWall : retourne une r�f�rence d'Image.

******

**Astuces**

1. M�thode ne devant pas modifier l'objet

On telle m�thode s'�crit suivi par le mot-cl� "const", comme dans l'exemple suivant :

    class Voiture {
	    public:
		    void reviser() const;
	};
	
	void Voiture::reviser() const {
	
	}

Effectivement, il para�t absurde de modifier la voiture lorsqu'on la r�vise, en effet on n'a pas � modifier l'�tat de la voiture.

2. Pointeur

Voici un exemple d'une fonction qui prend en param�tre un pointeur de notre classe Voiture :

    void detruire(Voiture * unPointeur) {
	
	}

On dit que notre type est un pointeur gr�ce au mot-cl� "*". Ainsi unPointeur est un pointeur de Voiture.

3. R�f�rence

Voici un exemple de fonction qui retourne une r�f�rence de Voiture :

    Voiture& construire() {
	
	}

Le "&" signifie qu'on a une r�f�rence.

4. Membres statiques

Voici un exemple d'attribut statique et de m�thode statique :

    class Voiture {
	    private:
		    static int nbInstances;
		public:
		    static int getNbInstances();
	};
	
	int Voiture::getNbInstances() {
	    return Voiture::nbInstances;
	}

Plusieurs remarques :
* Le mot-cl� "static" permet de d�finir un membre statique (attribut ou m�thode).
* Lors de la d�finition d'une m�thode de classe on ne repr�cise pas qu'il s'agit d'un membre statique, vous l'avez en effet remarqu� le mot-cl� "static" n'est pas �crit (et ce n'est pas une faute).
* Pour acc�der � un attribut statique de MaClasse, il faut le pr�fix� par "MaClasse::".

******

Vous avez d�sormais toutes les cartes en main pour �crire les bases du Sokoban en orient� objet.

Si vous avez termin� ou si vous rencontrez des probl�mes vous pouvez t�l�charger la solution [ici](https://github.com/chris-scientist/gb-poo/archive/v1.0.0.zip).

Dans la [prochaine partie](part_02.MD), c'est-�-dire la deuxi�me, nous r�aliserons la gestion de la cam�ra.

N'h�sitez pas � me faire un retour : les am�liorations que vous apporteriez (un regard ext�rieur est toujours bienvenu), les fautes, etc.
