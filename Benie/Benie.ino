/**
   Contrôle de deux moteurs cc avec un L298N
   http://electroniqueamateur.blogspot.com/2016/06/controle-dun-ou-deux-moteurs-cc-avec.html
 **/

// définition des pins de l'Arduino qui contrôlent le 1er moteur
#define pinIN1 2
#define pinIN2 3
#define pinENA 9 // doit être une pin PWM 

// définition des pins de l'Arduino qui contrôlent le 2e moteur
#define pinIN3 4
#define pinIN4 5
#define pinENB 10 // doit être une pin PWM 


void setup() {

  // toutes ces pins sont des sorties

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

}


void rightWheel(int direction){ 
  // rightWheel(1) pour faire tourner la roue droite vers l'avant
  // rightWheel(0) pour arreter la roue droite
  // rightWheel(-1) pour faire tourner la roue droite vers l'arrière
  analogWrite(pinENA, 255);
  if (direction == 1){
    digitalWrite(pinIN1, true);
    digitalWrite(pinIN2, false);
  }
  if (direction == 0){
    digitalWrite(pinIN1, false);
    digitalWrite(pinIN2, false);
  }
  if (direction == -1){
    digitalWrite(pinIN1, false);
    digitalWrite(pinIN2, true);
  }
}

void leftWheel(int direction){
  // rightWheel(1) pour faire tourner la roue gauche vers l'avant
  // rightWheel(0) pour arreter la roue gauche
  // rightWheel(-1) pour faire tourner la roue gauche vers l'arrière
  analogWrite(pinENB, 255);
  if (direction == 1){
    digitalWrite(pinIN3, true);
    digitalWrite(pinIN4, false);
  }
  if (direction == 0){
    digitalWrite(pinIN3, false);
    digitalWrite(pinIN4, false);
  }
  if (direction == -1){
    digitalWrite(pinIN3, false);
    digitalWrite(pinIN4, true);
  }
}

void loop() {
}