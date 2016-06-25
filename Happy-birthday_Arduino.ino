//ONG LIT YIT 2013-07-20
//This following code plays happy birthday melody on Arduino
//Put Piezo Buzzer on GDN and 9 (Positive and negative are reversible)
//this project requires a Piezo Buzzer and
// an Arduino board and
//jumper wires to connect Buzzer's (+) to ~9 and (-) to GND (any GND)
// Button: Push down=close, not push=open.

// Last Edite: 2016-6-25
// Co-Writer : Su Gao


#define led1       A0
#define led2       A1
#define led3       A4
#define led4       A5
#define speakerPin 9
#define button     6

int butState     = 0;
int butState_old = 0;
int stater       = 0;

int length = 28; // the number of notes

char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";

int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16 };

int tempo = 150;

void playTone(int tone, int duration) {

  for (long i = 0; i < duration * 1000L; i += tone * 2) {

    digitalWrite(speakerPin, HIGH);

    delayMicroseconds(tone);

    digitalWrite(speakerPin, LOW);

    delayMicroseconds(tone);

  }

}

void playNote(char note, int duration) {

  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',

                  'c', 'd', 'e', 'f', 'g', 'a', 'b',

                  'x', 'y'
                 };

  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                  956,  834,  765,  593,  468,  346,  224,

                  655 , 715
                };

  int SPEE = 5;

  // play the tone corresponding to the note name

  for (int i = 0; i < 17; i++) {

    if (names[i] == note) {
      int newduration = duration / SPEE;
      playTone(tones[i], newduration);

    }

  }

}


void playLED(){
  digitalWrite(led1, random(2));
  digitalWrite(led2, random(2));
  digitalWrite(led3, random(2));
  digitalWrite(led4, random(2));
}

void setup() {

  pinMode(speakerPin, OUTPUT);
  pinMode(button, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);

}

void loop() {

  for (int i = 0; i < length; i++) {

    butState = digitalRead(button);

    if (butState == 0 && butState_old == 1) { // When the button is pushed
      if (stater == 0) {
        // When the music stopped.start to play music.
        stater = 1;
        i = 0;
      } else {
        stater = 0;
      }
    }

    if (stater == 1) {
      playLED();
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
    }

    // pause between notes
    delay(tempo - 100);

    butState_old = butState; // update the old State of the button.

  }

  delay(tempo + 50);

}
