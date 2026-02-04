#include "Arduino.h"
#include "MyCubice.h"

MyCubice::MyCubice(){
	        //Tilt ball setup
        pinMode(SIDE_SENS_6, INPUT);
 	  pinMode(SIDE_SENS_5, INPUT);
  	pinMode(SIDE_SENS_4, INPUT);
  	pinMode(SIDE_SENS_3, INPUT);
  	pinMode(SIDE_SENS_2, INPUT);
  	pinMode(SIDE_SENS_1, INPUT);
}




   void MyCubice::rolled(){
         MyCubice::calc_thrownDice();
      }

	// if param is 5 lucky 6 is shuffled
    void MyCubice::shuffleDices(int shuffled_sides ){
        int n = 6;
          
          for (int i = 0; i < n - 1; i++)
          {
              int indexnr = random(0, shuffled_sides);
              int temp = MyCubice::_second_dice[i];
              MyCubice::_second_dice[i] = MyCubice::_second_dice[indexnr];
              MyCubice::_second_dice[indexnr] = temp;
          }
          for (int i = 0; i < n - 1; i++)
          {
              int indexnr = random(0, shuffled_sides);
              int temp = MyCubice::_third_dice[i];
              MyCubice::_third_dice[i] = MyCubice::_third_dice[indexnr];
              MyCubice::_third_dice[indexnr] = temp;
          }
        }


    void MyCubice::calc_thrownDice(){    
        if(digitalRead(SIDE_SENS_6) == HIGH){
            Serial.println("nummer 6 is gegooid");
             MyCubice::_thrownDice = _dice[6-1];
             MyCubice::_thrown_secondDice = _second_dice [6-1];
             MyCubice::_thrown_thirdDice = _third_dice [6-1];
          }
        else if(digitalRead(SIDE_SENS_5) == HIGH){
            Serial.println("nummer 5 is gegooid");
             MyCubice::_thrownDice = _dice[5-1];
             MyCubice::_thrown_secondDice = _second_dice [5-1];
             MyCubice::_thrown_thirdDice = _third_dice [5-1];
          }
        else if(digitalRead(SIDE_SENS_4) == HIGH){
          Serial.println("nummer 4 is gegooid");
             MyCubice::_thrownDice = _dice[4-1];
             MyCubice::_thrown_secondDice = _second_dice [4-1];
             MyCubice::_thrown_thirdDice = _third_dice [4-1];
          }
        else if(digitalRead(SIDE_SENS_3) == HIGH){
          Serial.println("nummer 3 is gegooid");
	     MyCubice::_thrownDice = _dice[3-1];
             MyCubice::_thrown_secondDice = _second_dice [3-1];
             MyCubice::_thrown_thirdDice = _third_dice [3-1];
          }
        else if(digitalRead(SIDE_SENS_2) == HIGH){
          Serial.println("nummer 2 is gegooid");
		MyCubice::_thrownDice = _dice[2-1];
             MyCubice::_thrown_secondDice = _second_dice [2-1];
             MyCubice::_thrown_thirdDice = _third_dice [2-1];
          }
        else if(digitalRead(SIDE_SENS_1) == HIGH){
          Serial.println("nummer 1 is gegooid");
		MyCubice::_thrownDice = _dice[1-1];
             MyCubice::_thrown_secondDice = _second_dice [1-1];
             MyCubice::_thrown_thirdDice = _third_dice [1-1];
          }
	else{
		Serial.println("sensor waarde niet berekent");
	}
      }

       int MyCubice::getDice(){
        return MyCubice::_thrownDice;
        }
       int MyCubice::get_secondDice(){
        return MyCubice::_thrown_secondDice;
        }
       int MyCubice::get_thirdDice(){
        return MyCubice::_thrown_thirdDice;
        }

	int*MyCubice::get_diceArray(){
	 return MyCubice::_dice;
	}
	int*MyCubice::get_second_diceArray(){
	 return MyCubice::_second_dice;
	}
	int*MyCubice::get_third_diceArray(){
	 return MyCubice::_third_dice;
	}



       void MyCubice::rstRolled(){
               MyCubice::_thrownDice = 0;
               MyCubice::_thrown_secondDice= 0;
               MyCubice::_thrown_thirdDice = 0;
          }

	void MyCubice::rstShuffled(){
		int _dice [6]= {1,2,3,4,5,6};
    		int _second_dice [6]= {1,2,3,4,5,6};
    		int _third_dice [6]= {1,2,3,4,5,6};
	}
      

      int MyCubice::gen_diceNR(){
        int num = rand()%6 +1; 
        return num;
       }

      int MyCubice::gen_2_diceNR (){
        int num = MyCubice::gen_diceNR()+MyCubice::gen_diceNR();
         return num;
      }
  
      int MyCubice::gen_3_diceNR (){
        int num = MyCubice::gen_diceNR()+ MyCubice::gen_diceNR()+ MyCubice::gen_diceNR(); 
        return num;
      }
    