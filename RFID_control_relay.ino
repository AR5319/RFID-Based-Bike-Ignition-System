#define Relay 3
int relay1 = LOW;

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup()
{
  pinMode(Relay, OUTPUT);
  Serial.begin(9600);  
  SPI.begin();     
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
 
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "F3 14 F4 0F") 
  {
    Serial.println("Authorized access");
    Serial.println();
   
      relay1 = ~ relay1;
            digitalWrite(Relay,relay1);
            delay(250);  
  }

  else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}
