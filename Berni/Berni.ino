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

// définition des pins de l'Arduino qui contrôlent les 2 potentiomètres
#define pinPot1 A0
#define pinPot2 A1

//définition des pins de l'Arduino qui contrôlent le start button
#define pinStartButton 6

void setup() {

    // toutes ces pins sont des sorties

    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
    pinMode(pinENA, OUTPUT);

    pinMode(pinIN3, OUTPUT);
    pinMode(pinIN4, OUTPUT);
    pinMode(pinENB, OUTPUT);

}


void rightWheel(int direction, int speed) {
    // rightWheel(1) pour faire tourner la roue droite vers l'avant
    // rightWheel(0) pour arrêter la roue droite
    // rightWheel(-1) pour faire tourner la roue droite vers l'arrière
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(pinENA, speed);
    if (direction == 1) {
        digitalWrite(pinIN1, true);
        digitalWrite(pinIN2, false);
    }
    if (direction == 0) {
        digitalWrite(pinIN1, false);
        digitalWrite(pinIN2, false);
    }
    if (direction == -1) {
        digitalWrite(pinIN1, false);
        digitalWrite(pinIN2, true);
    }
}

void leftWheel(int direction, int speed) {
    // rightWheel(1) pour faire tourner la roue gauche vers l'avant
    // rightWheel(0) pour arrêter la roue gauche
    // rightWheel(-1) pour faire tourner la roue gauche vers l'arrière
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(pinENB, speed);
    if (direction == 1) {
        digitalWrite(pinIN3, true);
        digitalWrite(pinIN4, false);
    }
    if (direction == 0) {
        digitalWrite(pinIN3, false);
        digitalWrite(pinIN4, false);
    }
    if (direction == -1) {
        digitalWrite(pinIN3, false);
        digitalWrite(pinIN4, true);
    }
}

void forward() {
    // fait avancer le robot
    rightWheel(1, 255);
    leftWheel(1, 255);
}

void backward() {
    // fait reculer le robot
    rightWheel(-1, 255);
    leftWheel(-1, 255);
}

void turnLeft() {
    // fait tourner le robot vers la gauche
    rightWheel(1, 255);
    leftWheel(-1, 255);
}

void turnRight() {
    // fait tourner le robot vers la droite
    rightWheel(-1, 255);
    leftWheel(1, 255);
}

void stop() {
    // arrête le robot
    rightWheel(0, 0);
    leftWheel(0, 0);
}

void UTurn(int direction) {
    // fait faire un demi-tour au robot
    // direction = 1 pour tourner à droite*
    // direction = -1 pour tourner à gauche*
    // *en regardant le robot de face
    if (direction == 1) {
        rightWheel(1, 255);
        leftWheel(1, 100);
    }
    if (direction == -1) {
        leftWheel(1, 255);
        rightWheel(1, 100);
    }
    delay(1000);
    stop();
}

int getPot1Value() {
    // retourne la valeur du potentiomètre 1
    return analogRead(pinPot1);
}

int getPot2Value() {
    // retourne la valeur du potentiomètre 2
    return analogRead(pinPot2);
}

void path(int direction) {
    // fait avancer le robot en fonction des valeurs des potentiomètres
    // direction = 1 pour commencer à gauche du circuit
    // direction = -1 pour commencer à droite du circuit

    int maxRange = 100; // valeur maximale du potentiomètre
    int pathLength = (getPot1Value() * maxRange) /
                     1023; // renvoie une valeur entre 0 et maxRange en fonction de la position du potentiomètre 1
    int pathWidth = (getPot2Value() * maxRange) /
                    1023; // renvoie une valeur entre 0 et maxRange en fonction de la position du potentiomètre 2
    int robotWidth = 20; // largeur du robot en cm
    int numberOfLines = pathWidth / robotWidth; // largeur du chemin en cm
    short int witchLine = 0; // variable qui permet de tester si le robot est sur une ligne paire ou impaire (tkt t'as pas besoin de savoir à quoi elle sert cte variable)
    for(int i = 0; i < pathLength; i++) {
        forward();
        delay(pathLength * 1000);
        if (witchLine < numberOfLines) {
            UTurn(direction);
            witchLine++;
        }
        else {
            UTurn(-direction);
            witchLine--;
        }
    }
}

void loop() {
    if (digitalRead(pinStartButton) == HIGH) { // démarre le circuit si le bouton est appuyé
        path(1);
    }
}