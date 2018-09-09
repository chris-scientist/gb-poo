// author: chris-scientist
// created at: 08/08/2018
// updated at: 26/08/2018

#include <Gamebuino-Meta.h>

void setup() {
  // initialiser la gamebuino
  gb.begin();
}

void loop() {
  // boucle d'attente
  while(!gb.update());

  // effacer l'écran
  gb.display.clear();

  gb.display.println("Hello world");
}
