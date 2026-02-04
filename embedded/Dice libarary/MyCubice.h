#ifndef MyCubice_h
#define MyCubice_h
#include "Arduino.h" 

#define SIDE_SENS_6  D0
#define SIDE_SENS_5  D5
#define SIDE_SENS_4  D7
#define SIDE_SENS_3  D8
#define SIDE_SENS_2  D3
#define SIDE_SENS_1  D4  // can not use D4 when Uploading code

class MyCubice{
	public: 
		MyCubice();
		void rolled();

		// if param is 5 every side gets shuffled but side 6  
		// if param is 6 every side gets shuffled 
 		// the lower the param the les sides that get shuffled
		void shuffleDices(int shuffled_sides);
		void calc_thrownDice();
		void rstShuffled();
		void rstRolled();
	
		int getDice();
		int get_secondDice();
		int get_thirdDice();
		int*get_diceArray();
		int*get_second_diceArray();
		int*get_third_diceArray();
		

		int gen_diceNR();
		int gen_2_diceNR ();
		int gen_3_diceNR ();
	private:
		
		int _thrownDice;
    		int _thrown_secondDice;
    		int _thrown_thirdDice;
    		int _dice [6]= {1,2,3,4,5,6};
    		int _second_dice [6]= {1,2,3,4,5,6};
    		int _third_dice [6]= {1,2,3,4,5,6};
};

	
#endif