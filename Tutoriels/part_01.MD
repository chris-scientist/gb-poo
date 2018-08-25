
# SOKOBAN vs POO / Partie 1 : les bases

v0.0.2

Bonjour,

## SOKOBAN CONTRE POO ?

Non... POO n'est pas un ennemi !

Vous voici dans un tutoriel pour réaliser le jeu SOKOBAN en **Programmation Orientée Objet** c'est-à-dire POO. Dans ce tutoriel il paraît même que nous parlerons du modèle d'architecture **Modèle Vue Contrôleur** c'est-à-dire MVC. Le programme est ambitieux mais ne vous faites aucune crainte, nous avancerons pas à pas et je vais essayer d'être clair.  

Le tutoriel sera composé des 4 parties suivantes :
* La partie 1 (vous êtes ici ! en cours de rédaction) : vous permettra d'appréhender les bases de la POO et du MVC.
* La partie 2 (à rédiger !) : vous permettra de réaliser l'affichage du jeu et la gestion de la caméra (évidement à la sauce POO, comme le reste des parties).
* La partie 3 (à rédiger !) : vous permettra de gérer les déplacements du personnage.
* La partie 4 (à rédiger !) : vous permettra de gérer la physique du jeu et la fin de partie.

Voici pour la présentation du tutoriel.



Les **pré-requis** de ce tutoriel sont :
* Avoir une Gamebuino META.
* Avoir fait l'ensemble des ateliers.

## PRINCIPE DU JEU

Avant de faire une partie théorique, je vais vous présenter le jeu SOKOBAN. Il s'agit d'un jeu idéal pour appréhender les concepts de la programmation orienté objet. Et oui, sinon je n'aurai pas fait ce tutoriel.

Nous jouons un gardien dans un entrepôt.  Dans ce lieu se trouve des caisses que nous devons déplacer sur des zones de "chargement". C'est aussi simple que ça !

## THÉORIE

Nous allons, avant de passer à la pratique, nous écarter un peu du jeu SOKOBAN dans cette partie théorique. En effet, je vais vous présenter les concepts :
* de la Programmation Orientée Objet ;
* et du modèle d'architecture Modèle Vue Contrôleur.

### Version procédurale

Imaginons un petit jeu où l'on doit déplacer un personnage (ceci ressemble un peu à SOKOBAN...). Mais il se déplacera sur une petite carte (20 colonnes et 10 lignes) ainsi pas besoins de gérer de caméra puisqu'il s'agit de la taille de l'écran.

Ce personnage doit :
* connaître sa position ;
* savoir se déplacer (vers le haut, à droite, vers la bas et à gauche) ;
* savoir ses limites (il ne peut pas aller en dehors de l'écran).

Le personnage sera représenté par un "x".

Voici le code de la version procédurale de ce petit programme ([téléchargeable ici](https://github.com/chris-scientist/gb-sample/archive/v1.0.zip)).

    #include <Gamebuino-Meta.h>

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

        // effacer l'écran
        gb.display.clear();

        manageMove();
        paint();
    }

    // Gérer les déplacement
    void manageMove() {
        // Note :
        // * Le test : (yCharacter > 0) permet de ne pas sortir du haut de l'écran.
        // * Le test : (xCharacter < 19) permet de ne pas sortir de la droite de l'écran.
        // * Le test : (yCharacter < 9) permet de ne pas sortir du bas de l'écran.
        // * Le test : (xCharacter > 0) permet de ne pas sortir de la gauche de l'écran.
        // Ainsi on définit les limites du personnage.
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

    // Gérer l'affichage
    void paint() {
        for(int y=0 ; y<=yCharacter ; y++) {
            for(int x=0; x<20 || x<xCharacter ; x++) {
                if(x == xCharacter && y == yCharacter) {
                    gb.display.print("x"); // afficher le personnage
                } else {
                    gb.display.print(" "); // afficher une colonne vide
                }
            }
            gb.display.println(); // passage à la ligne suivante
        }
    }

### Version orientée objet en MVC

Le MVC est un modèle d'architecture, cela sert à décrire comment le code doit être découpé. Le MVC implique qu'il y ai 3 couches :
* le modèle : qui gère les données ;
* la vue : qui gère l'affichage ;
* et le contrôleur : qui fait l'interface entre la vue et le modèle.

Un concept important dans la POO est la classe. Une classe est une structure de donnée qui a :
* des attributs : les variables de la classe ;
* des méthodes : les fonctions de la classe.

******

Voici un exemple de classe C++ :

    // 1) Déclaration
    class Plan {
	    private:
		    int nbPieces;
	    public:
		    Plan(int unNbPieces);
		    void dessiner();
	};
	
	// 2) Définition
	Plan::Plan(int unNbPieces) : nbPieces(unNbPieces) {
	
	}
	
	void Plan::dessiner() {
	    for(int i=1 ; i<=nbPieces ; i++) {
			// dessiner la pièce...
		}
	}
	
	// 3) Instanciation et utilisation
	// Création d'un objet de type *Plan*
	Plan *maMaison = new Plan(2);
	// Utilisation de l'objet
	maMaison->dessiner();

On remarque plusieurs partit dans le code ci-dessus.

1. La déclaration

Elle définit notre classes : ses attribut et le prototype de ses méthodes. Le mot "class" est important c'est lui qui dit au compilateur que ce que l'on écrit est une classe.

Ici nous avons un attribut : *nbPieces* c'est un entier qui contient le nombre de pièces du plan (c'est pas une surprise, enfin j'espère !).

Ensuite, nous avons deux méthodes :
* *Plan* qui est une méthode particulière puisqu'il s'agit d'un constructeur (on en reparle un peu plus loin).
* *dessiner* qui nous permettra de dessiner le plan.

Remarque : Faites attention au point-virgule à la fin des classes, sans ce point-virgule l'IDE Arduino donnera l'erreur *new types may not be defined in a return type* à la compilation.

De plus, une chose très importante : les attributs doivent être privés. Il s'agit de l'encapsulation, un concept de la POO, qui veut que l'on interdit l'accès au attributs de classes depuis l'extérieur. Les méthodes sont en revanche publique ce qui permet de les utiliser dans le programme principale par exemple.

**Le constructeur**

Plusieurs choses doivent être dites à son sujet :
* Le/les constructeur(s), il peut en effet y en avoir plusieurs, ils doivent avoir le même nom que la classe (sans quoi ça ne serait qu'une méthode).
* On s'en sert pour initialiser la attributs de notre classe.

2. La définition

La définition du constructeur est particulière, en effet dans beaucoup de langage (ce qui reste possible en C++) il aurait fallut écrire ceci :

    Plan::Plan(int unNbPieces) {
	    nbPieces = unNbPieces;
	}

Le C++ a un petit sucre syntaxique qui permet de faire la même chose de la mannière suivante :

    Plan::Plan(int unNbPieces) : nbPieces(unNbPieces) {
	    
	}

Remarque : toutes méthodes dont le constructeur doivent préfixé par le nom de la classe, ici : *Plan::*.

La méthode *dessiner* est composée d'une boucle qui itére sur le nombre de pièces et le reste du code je le laisse pour votre imagination.

3. Instanciation et utilisation

Lorsque qu'on créé un objet à partir d'une classe on dit qu'on *instancie* un objet. Cet objet est une instance autrement dit c'est une maison alors que la classe est un plan. On créé ici un pointeur de Plan, en effet le type est *"Plan *"*. Ainsi pour instancier l'objet il faut faire appel au mot-clé C++ "new".

Enfin pour appeler une méthode (sur un pointeur) il faut utiliser le symbole suivant : "->" (ici : maMaison->dessiner()).

4. Bonus

Une représentation UML via un diagramme de classes est possible est le voici :

[Diagramme de classes de Plan](Images/diagramme_classes_plan.png)

Remarques : 
* Le *moins* avant l'attribut signifie qu'il est privé.
* Le *plus* avant les méthodes signifie qu'elle sont publiques.
* La modélisation n'est pas complète, il manque effectivement le paramètre du constructeur.


******

*Revenons à notre jeu.*

Maintenant que vous savez créé des classes voyons de quoi nous avons besoins pour que notre petit programme respecte le MVC. Il faut :
* CharacterModel : le modèle c'est-à-dire le personnage.
* CharacterView : la vue qui gère l'affichage du personnage.
* CharacterController : le contrôleur qui permet d'interagir avec le personnage.

Comme vous le voyez par convention :
* Le modèle est suffixé par *Model*.
* La vue est suffixé par *View*.
* Le contrôleur est suffixé par *Controller*.

Comme vous savez créé des classe, avant de passer à la réalisation du SOKOBAN, vous pouvez essayer de réaliser une version orienté objet qui respecte le MVC de notre exemple, ne réinventez pas tout vous pouvez en effet vous inspirez de la version procédurale.

Pour vous guider voici un diagramme de classes (fait en UML) qui représente notre petit programme avec toutes les classes et méthodes nécessaires :

[Astuce : diagramme de classes](Images/diagramme_classes_exemple.png)

Si vous n'y arrivez pas, n'ayez crainte vous pouvez télécharger la [version orientée objet](https://github.com/chris-scientist/gb-sample/archive/v2.0.zip) que j'ai fait.

Remarque : la vue n'a pas de constructeur du moins nous n'en n'avons pas déclaré. Nous utilisons le constructeur par défaut.

Enfin des améliorations sont possibles, effectivement il devrait être interdit d'instancier plusieurs personnages (imaginé le désordre que ça engendrerai !). *Ne lisez la suite que si vous voulez avoir mal de tête* ;). Pour faire cela nous pourrions utiliser le design pattern Singleton, mais ce n'est pas l'objectif de ce cours.

## PRATIQUE

La pratique vous permettra de créer l'ensemble des classes et méthodes utiles au jeu SOKOBAN. Pour les méthodes nous ferrons juste la description, en effet, nous verrons la définition (le contenu) de chacune d'elle au fur et à mesure des parties qui composent ce tutoriel.

Si vous ne vous sentez pas encore prêt à franchir le cap de la POO, il existe une version procédurale du jeu (cf.  partie 1 par jicehel).

*Ce chapitre est en cours de rédaction, merci de votre patience !*
