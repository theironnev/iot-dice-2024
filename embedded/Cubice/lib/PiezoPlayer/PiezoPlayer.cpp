/*
    Author : Theironne Velliam

    This is a class created for the  Piezzo Buzzer.
*/
#include "PiezoPlayer.h"



PiezoPlayer::PiezoPlayer(int pin , int channel): _tone32(pin, channel)  { //Constructor
  _buzzerPin = pin;
//   pinMode(_buzzerPin, OUTPUT);
    //  _tone32(pin, channel);
  
  _tempo = DEFAULT_TEMPO;
}
// Calculate the frequency that fits within the duty cycle constraints
uint32_t PiezoPlayer::_calculateFrequency(uint32_t targetFrequency) {
    // Constants , these are default settings of the LEDC PWM from Esspresif.
    const uint32_t clockFrequency = 80000000;  // 80 MHz
    const uint32_t resolution = 10;            // 10-bit resolution
    const float dutyCycle = 0.5;               // 50% duty cycle

    // Calculate the timer frequency
    uint32_t timerFrequency = clockFrequency / (1 << resolution);

    // Calculate the maximum frequency that fits within the duty cycle constraints
    uint32_t maxFrequency = timerFrequency / 2;

    // Check if the target frequency is within the constraints
    if (targetFrequency > maxFrequency) {
        // If not, return the maximum frequency
        return maxFrequency;
    }

    // Return the target frequency
    return targetFrequency;
}

// play the melody that is picked out of melodyId 
void PiezoPlayer::melody(MelodyID MelodyID) {           // ?Can be optimized with a loop trough enum MelodyID¿

        // notes of the melody followed by the duration.
        // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
        // !!negative numbers are used to represent dotted notes,
        // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
     switch (MelodyID) {
         case START_DICE: {
            // int TUNE_1[] = {NOTE_D4,8, NOTE_E4,8, NOTE_F4,8, NOTE_G4,8, NOTE_E4,4, NOTE_C4,8, NOTE_D4,1};
            int TUNE_1[] = {ESP_NOTE_A,4, ESP_NOTE_E,4,ESP_NOTE_A,4, ESP_NOTE_E,4,
                            ESP_NOTE_A,6, ESP_NOTE_E,8,ESP_NOTE_D,8, ESP_NOTE_E,8,ESP_NOTE_C,2};
            _play(TUNE_1, sizeof(TUNE_1));
        break;
        }
        case COUNT_DOWN: {
            int TUNE_4[] = { ESP_NOTE_CS,1,REST,2, 
                    ESP_NOTE_CS,2,REST,4, ESP_NOTE_CS,2,REST,4, 
                    ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8,
                    ESP_NOTE_CS,8,REST,16, ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16, ESP_NOTE_CS,8,REST,16,
                    ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,
                    ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,
                    ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,
                    ESP_NOTE_CS,1
                    };
            _play(TUNE_4, sizeof(TUNE_4));
        break;
        }
        case HELLO_IOT: {
            int TUNE_3[] ={ESP_NOTE_D,8, ESP_NOTE_E,8, ESP_NOTE_F,8, ESP_NOTE_G,8, ESP_NOTE_E,4, ESP_NOTE_C,8, ESP_NOTE_D,1};
            _play(TUNE_3, sizeof(TUNE_3));
        break;
        }
        // Count down 
        case MELODY_4: {
            int TUNE_4[] = { ESP_NOTE_CS,1,REST,2, 
                             ESP_NOTE_CS,2,REST,4, ESP_NOTE_CS,2,REST,4, 
                             ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8, ESP_NOTE_CS,4,REST,8,
                             ESP_NOTE_CS,8,REST,16, ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16,ESP_NOTE_CS,8,REST,16, ESP_NOTE_CS,8,REST,16,
                             ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,ESP_NOTE_CS,16,REST,32,
                             ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,ESP_NOTE_CS,32,REST,64,
                             ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,ESP_NOTE_CS,64,REST,128,
                             ESP_NOTE_CS,1
                             };
            _play(TUNE_4, sizeof(TUNE_4));
        break;
        }
        case MELODY_5: {
            int TUNE_2[] = {  // Keyboard cat
        // Score available at https://musescore.com/user/142788/scores/147371

            // REST,1,
            // REST,1,
            NOTE_C4,4, NOTE_E4,4, NOTE_G4,4, NOTE_E4,4, 
            NOTE_C4,4, NOTE_E4,8, NOTE_G4,-4, NOTE_E4,4,
            NOTE_A3,4, NOTE_C4,4, NOTE_E4,4, NOTE_C4,4,
            NOTE_A3,4, NOTE_C4,8, NOTE_E4,-4, NOTE_C4,4,
            NOTE_G3,4, NOTE_B3,4, NOTE_D4,4, NOTE_B3,4,
            NOTE_G3,4, NOTE_B3,8, NOTE_D4,-4, NOTE_B3,4,

            };
            _play(TUNE_2, sizeof(TUNE_2));
        break;
        }
        case MELODY_6: {
            int TUNE_6[] = { ESP_NOTE_A,4, ESP_NOTE_E,4,ESP_NOTE_A,4, ESP_NOTE_E,4,
                            ESP_NOTE_A,6, ESP_NOTE_E,8,ESP_NOTE_D,8, ESP_NOTE_E,8,ESP_NOTE_C,2};
            _play(TUNE_6, sizeof(TUNE_6));
        break;
        }
        case MELODY_7: {
            int TUNE_7[] = {NOTE_D4,8, NOTE_E4,8, NOTE_F4,8, NOTE_G4,8, NOTE_E4,4, NOTE_C4,8, NOTE_D4,1};
            _play(TUNE_7, sizeof(TUNE_7));
        break;
        }
        case MELODY_8: {
            int TUNE_8[] = { ESP_NOTE_A,8, ESP_NOTE_E,8, NOTE_F4,8, NOTE_G4,8, NOTE_E4,4, NOTE_C4,8, NOTE_D4,1};
            _play(TUNE_8, sizeof(TUNE_8));
        break;
        }
        case MELODY_9: {
            int TUNE_9[] = {NOTE_D4,8, NOTE_E4,8, NOTE_F4,8, NOTE_G4,8, NOTE_E4,4, NOTE_C4,8, NOTE_D4,1};
            _play(TUNE_9,  sizeof(TUNE_9));
        break;
        }
     }
}
// this is a loop function that plays all the inividual notes of a melody array given to the function
void PiezoPlayer::_play(int melody[], int songLength) {
    // it does not matter that the sizeof is used, because ratio for calculation is same. 
    int notes = songLength / 2; // the melody array exoist out of notes and there duration, so half of them are notes.    // lenght / 2
    const int MILLISECONDS_PER_MINUTE = 60000;
    const int NOTES_PER_WHOLE_NOTE = 4;
    _wholenote = (MILLISECONDS_PER_MINUTE * NOTES_PER_WHOLE_NOTE) / _tempo;// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
    // iterate over the notes of the melody. 
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

         // calculates the duration of each note
        int divider = melody[thisNote + 1];
        int noteDuration;
        if (divider > 0) {
        // regular note, just proceed
        noteDuration = (_wholenote) / divider;
        } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (_wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    
    // calculate the achievable-freq from the target-freq
    uint32_t calculatedFrequency = _calculateFrequency(melody[thisNote]);
    // we only play the note for 90% of the duration, leaving 10% as a pause
    // tone(_buzzerPin, melody[thisNote], noteDuration*0.9);
    _tone32.playTone(calculatedFrequency  , noteDuration*0.9);
    // _tone32.playNote();
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    // stop the waveform generation before the next note.
    // noTone(_buzzerPin);
    _tone32.stopPlaying();
    // _tone32.update();
  }
}
// set adjusted tempo
void PiezoPlayer::setTempo(int tempo){
    _tempo = tempo;
}