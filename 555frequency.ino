/*
 * Created by 
 * Mauro Brum
 * Date: 27/12/2018
 * Function: scritp for the salinity sensor aparato
 */ 


/*
 * --------------------------- Libraries ---------------------------------------
 */
#include <LiquidCrystal.h>

/*
 * --------------------------- Global Variables --------------------------------
 */


// define some variable to account the pulse signel from 555 
int Htime = 0;              //integer for storing higher pulso in the frequency
int Ltime = 0;              //integer for storing lower pulse in the frequency
float Ttime = 0.0F;         //integer for storing total time of a cycle
float frequency = 0.0F;     //float for storing frequency
float freq_average = 0.0F;  //float for storing average frequency

#define NUMSAMPLES 10

int samples[NUMSAMPLES] = {0};
int current_sample = 0;


/*
 * --------------------------- Start objects -----------------------------------
 */
// select the pins used on the LCD panel
// LiquidCrystal (rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(8,  9,  4,  5,  6,  7);


/*
 * --------------------------- Setup -------------------------------------------
 */

void setup()
{
  // set the pin mode 1 to receive the signal from 555
  pinMode(2,INPUT);
  // start LCD the library
  lcd.begin(16, 2);
  // clear lcd
  lcd.clear();
}

/*
 * --------------------------- Loop --------------------------------------------
 */ 
void loop()
{
  // Read 555 pulse
  Htime = pulseIn(2, HIGH); // microseconds from high to low
  Ltime = pulseIn(2, LOW);  // microseconds from low to high
  Ttime = Htime + Ltime;  // total time
  frequency = 1000000.0F / Ttime;
  
  if(current_sample < NUMSAMPLES)
  {
    samples[current_sample] = frequency;  // save read frequency
    current_sample++;            // update index
  }
  else
  {
    current_sample = 0;      // update index
    
    // avarage of samples
    for(int i = 0; i < NUMSAMPLES; i++)
    {
      freq_average += samples[i];  
    }

    freq_average /= NUMSAMPLES;
  }
  
  lcd.setCursor(0,0);        // move cursor to position 0, line 0
  lcd.print("Frequency (Hz)");
  lcd.setCursor(0,1);        // move cursor to position 0, line 1
  lcd.print(freq_average);

}
