#ifndef BUZZER_H
#define BUZZER_H

// buzzer pin gpio12
#define buzzer_pin 12


//define note needed for welcome sound
#define SOL_SHARP_L 415
#define RA_L        440
#define MI_L        659
#define RE_SHARP  622
#define FA_SHARP  740
#define DO_SHARP_H 1109
#define NOTHING 500000


//method

//buzzer initalize
void buzzer_init(void);

//buzz input note for duration
void beep(int note, int duration);

//buzz hyundai welcomesound
void welcomesound(void);



#endif