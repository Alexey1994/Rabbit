#ifndef PC_SPEAKER_H_INCLUDED
#define PC_SPEAKER_H_INCLUDED

 //Play sound using built in speaker
 static void play_sound(unsigned int nFrequence) {
 	unsigned int Div;
 	Byte tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	out(0x43, 0xb6);
 	out(0x42, (Byte) (Div) );
 	out(0x42, (Byte) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = in(0x61);
  	if (tmp != (tmp | 3)) {
 		out(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 static void nosound() {
 	Byte tmp = in(0x61) & 0xFC;
 
 	out(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 //timer_wait(10);
 	 //nosound();
          //set_PIT_2(old_frequency);
 }

#endif //PC_SPEAKER_H_INCLUDED