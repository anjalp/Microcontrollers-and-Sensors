//                                                      CONTROLLING A TV OVER THE AIR USING BLYNK-ESP8266-IR LED
//   This project as initiated due to the bad quality of the remote offered by the TV vendor, it was aimed to solve the problem of 
//   controlling a TV using a samrt phone with a blynk app, and a constant WiFi connection of the ESP8266 to connect over the Internet,
//   Initially simply task like turn on the TV, Turn off, Change the channel, increase or decrease the volume e.t.c.

// Open the app and create a text Widget and assign it to PIN Virtual V1 and also amke another button with digital pin to D0
// D0 is used for the verification thst the esp us turned on and connected to internet successfully.


// INITIALISING THE ESP8266 LIBRARY AND THE BLYNK LIBRARY.
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#else
#include <WiFi.h>
#endif  // ESP8266

// IR library
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR BLINK TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR SSID";
char pass[] = "YOUR PASSWORD";

String textIn = "Str";  // String send from the text widget  is stored in this vriable

// Before coding the below make sure that the IR codes of the device is Known to you, if not
// Find the IR codes for each key for the device usign the IRrecDumpV2 code in the folder 
// All the circuit diagram is given in the folder 'circuit'.

// Here the text entered by the user by the blynk app is stored by the textIn string which is analysed by the chk_input() function
// it first checks the first digit : is a string or a number: if number then it goes to the switch a case to enter the number and if string then it
// goes to the if statement to match the code to enter it. 

// ENTER YOUR CODE HERE TO CONTROL YOUR IR DEVICE

void chk_input(void) {
  // ASIANET CODES
  if (textIn=="aon" or textIn=="aof") {      // ON/OFF OF THE ASIANET SETUP BOX REMOTE.
    irsend.sendNEC(0x80BF3BC4);
  }
  else if (textIn=="c+") {     // channel ++ on asianet
    irsend.sendNEC(0x80BFA15E);
  }
  else if (textIn=="c-") {           // channel -- on  asianet
    irsend.sendNEC(0x80BF619E);
  }
  else if (textIn=="v+") {    //volume ++ on asianet
    irsend.sendNEC(0x80BF01FE);
  }
  else if (textIn=="v-") {       // volume -- on asianet
    irsend.sendNEC(0x80BF817E);
  }
  else if (textIn=="mut") {       // mute on asianet
    irsend.sendNEC(0x80BF39C6);
  }
  else if (textIn=="lst") {      // last channel on asianet
    irsend.sendNEC(0x80BF41BE);
  }
  else if (textIn=="inf") {       // info on asianet
    irsend.sendNEC(0x80BF11EE);
  }
  else if (textIn=="gid") {          // guide on asianet
    irsend.sendNEC(0x80BF5BA4);
  }
 // TV CODES
  else if (textIn=="ton" or textIn=="tof") {          // power on on tv
    irsend.sendNEC(0xFB38C7);
  }
  else if (textIn=="tv+") {          // volume ++ in tv
    irsend.sendNEC(0xFBD22D);
  }
  else if (textIn=="tv-") {          // volumr -- in tv
    irsend.sendNEC(0xFBF20D);
  }
  else if (textIn=="inp") {          // input mode to sleect in tv
    irsend.sendNEC(0xFB926D);
  }
  else if (textIn=="jup") {          // joystick up 
    irsend.sendNEC(0xFB58A7);
  }
  else if (textIn=="jdn") {          // joystick dowm
    irsend.sendNEC(0xFB12ED);
  }
  else if (textIn=="jet") {          // joystick east
    irsend.sendNEC(0xFBE01F);
  }
  else if (textIn=="jwt") {          // joystick west
    irsend.sendNEC(0xFBE21D);
  }
  else if (textIn=="tok") {          // ok in tv
    irsend.sendNEC(0xFB609F);
  }
  else if (textIn=="tmt") {          // mute in tv
    irsend.sendNEC(0xFB42BD);
  }
  // ASIANET NUMERICAL CODES
  else {                   // number for changing channel in tv: i.e. if 121 is passed then it split ot 1, 2, 1 and sends it seperatly.
    for(char x : textIn) {
      if (x==*"0") {
        irsend.sendNEC(0x80BFE11E);
      }
      else if (x==*"1") {
        irsend.sendNEC(0x80BF49B6);
      }
      else if (x==*"2") {
        irsend.sendNEC(0x80BFC936);
      }
      else if (x==*"3") {
        irsend.sendNEC(0x80BF33CC);
      }
      else if (x==*"4") {
        irsend.sendNEC(0x80BF718E);
      }
      else if (x==*"5") {
        irsend.sendNEC(0x80BFf10E);
      }
      else if (x==*"6") {
        irsend.sendNEC(0x80BF13EC);
      }
      else if (x==*"7") {
        irsend.sendNEC(0x80BF51AE);
      }
      else if (x==*"8") {
        irsend.sendNEC(0x80BFD12E);
      }
      else if (x==*"9") {
        irsend.sendNEC(0x80BF23DC);
      }
    }
  }
}

BLYNK_WRITE(V1) {   //Initilise the text widget to the virtual Pin V1 for sending the channel number. set it to max 3 digit.
   textIn = param.asStr();
   chk_input();
}

// ALSO SET THE GPIO 16 OR D0 TO A LED TO MAKE SUE THAT THE DEVICE IS CONNECTED TO INTERNET.
void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
