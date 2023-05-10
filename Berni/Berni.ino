/**
   Contrôle de deux moteurs cc avec un L298N
   http://electroniqueamateur.blogspot.com/2016/06/controle-dun-ou-deux-moteurs-cc-avec.html
 **/

// définition des pins de l'Arduino qui contrôlent le 1er moteur
#define pinIN1 2
#define pinIN2 3
#define pinENA 9  // doit être une pin PWM

// définition des pins de l'Arduino qui contrôlent le 2e moteur
#define pinIN3 4
#define pinIN4 5
#define pinENB 10  // doit être une pin PWM

// définition des pins de l'Arduino qui gèrent le capteur de couleur
#define s2 11
#define s3 12
#define out 13

//définition des variables de couleurs
byte red = 0;
byte green = 0;
byte blue = 0;

//définition de la variable qui permet de tester si le robot est sur une ligne paire ou impaire (tkt t'as pas besoin de savoir à quoi elle sert cte variable)
short int witchLine = 0;

//définition de la variable du temps pour le demi-tour
int u_turn = 2500;

void setup() {
  Serial.begin(9600);

  // toutes ces pins sont des sorties

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
}


void rightWheel(int direction, int speed) {
  // rightWheel(1) pour faire tourner la roue gauche vers l'avant
  // rightWheel(0) pour arrêter la roue gauche
  // rightWheel(-1) pour faire tourner la roue gauche vers l'arrière
  if (speed > 255) {
    speed = 255;
  }
  analogWrite(pinENA, speed);
  if (direction == 1) {
    digitalWrite(pinIN1, false);
    digitalWrite(pinIN2, true);
  }
  if (direction == 0) {
    digitalWrite(pinIN1, false);
    digitalWrite(pinIN2, false);
  }
  if (direction == -1) {
    digitalWrite(pinIN1, true);
    digitalWrite(pinIN2, false);
  }
}

void leftWheel(int direction, int speed) {
  // leftWheel(1) pour faire tourner la roue droite vers l'avant
  // leftWheel(0) pour arrêter la roue droite
  // leftWheel(-1) pour faire tourner la roue droite vers l'arrière
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
    leftWheel(-1, 255);
  }
  if (direction == -1) {
    leftWheel(1, 255);
    rightWheel(-1, 255);
  }
  delay(u_turn);
  stop();
}

int detectColor(int color) {
  // color = 1 -> Rouge
  // color = 2 -> Vert
  // color = 3 -> Bleu
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  int marge = 6;   // marge de 5 pour détecter une couleur
  String couleur;  // variable pour stocker la couleur détectée

  if (red < green - marge && red < blue - marge && color == 1) {
    return 1;
  } else if (blue < red - marge && blue < green - marge && color == 2) {
    return 1;
  } else if (green < red - marge && green < blue - marge && color == 3) {
    return 1;
  } else {
    return 0;
  }
}

void path(int direction, int color) {
  // direction = 1 pour commencer à gauche du circuit
  // direction = -1 pour commencer à droite du circuit
  // color = 1 pour detecter du rouge
  // color = 2 pour detecter du vert
  // color = 3 pour detecter du bleu

  int isColor = detectColor(color);
  forward();
  if (isColor == 1) {
    if (witchLine == 0) {
      UTurn(direction);
      witchLine = 1;
    } else {
      if (witchLine == 1) {
        UTurn(-1 * direction);
        witchLine = 0;
      }
    }
  }  
}

void loop() {
  path(1, 1);
}
