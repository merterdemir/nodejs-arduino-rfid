/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 *beyaz51 mavi53 kırmızı50 siyah52
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>

#define KAPI 4
#define KAYIT 2
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
byte regVal;
void(* resetFunc) (void) = 0;//declare reset function at address 0

typedef struct{
  char user_id[4];
  char user_name[10];
}USER;
USER Users[30];
//USER Users[20];
int i = 0;
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  
  pinMode(KAYIT, OUTPUT);
  pinMode(KAPI, OUTPUT);
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  delay(500);
  
  regVal = 0x88; //rx irq
  mfrc522.PCD_WriteRegister(mfrc522.ComIEnReg, regVal);
  
  Serial.println("Scan PICC to see UID and type...");
  char chars[50] = "hello";
  Serial.println(chars);
  char a = 'a';
  Serial.println(a, DEC);
  if('a' == (int)('a')){
    Serial.println("heyo");
  }
  {
    char new_user_id[4] = {46, 68, 111, 96};
    const char new_user_name = "bora";
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
    {
    char new_user_id[4] = {30, 95, -48, -26};
    const char new_user_name = "bora";//evren
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {30, -1, -37, 91};
    const char new_user_name = "bora";//onat
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {110, -55, -29, 98};
    const char new_user_name = "bora";//altuğ
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  
  {
    char new_user_id[4] = {-7, 67, 32, -44};
    char new_user_name = "alptug";//anil
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {-2, 67, -27, 91};
    char new_user_name = "alptug";//güven
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {-28, -90, 59, -60};
    char new_user_name = "alptug";//ayberk
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {17, 15, 111, -60};
    char new_user_name = "alptug";//elifcüce
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {110, -49, 112, 96};
    char new_user_name = "alptug";//sarp
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {-66, 5, -38, -26};
    char new_user_name = "alptug";//furkan
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {-74, -3, -83, -94};
    char new_user_name = "alptug";//alptuğ
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {119, -25, 12, -124};
    char new_user_name = "alptug";//hayri
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {115, -34, 64, 52};
    char new_user_name = "alptug";//öykü
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {126, 54, -36, -26};
    char new_user_name = "alptug";//sezer
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
    {
    char new_user_id[4] = {-80, 18, 32, -44};
    char new_user_name = "alptug";//enes
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
      {
    char new_user_id[4] = {-84, 101, 29, -44};
    char new_user_name = "alptug";//erencan
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
        {
    char new_user_id[4] = {-86, 39, -41, -39};
    char new_user_name = "alptug";//utku(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
          {
    char new_user_id[4] = {46, -65, -39, -26};
    char new_user_name = "alptug";//aybars
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
            {
    char new_user_id[4] = {-81, 93, 10, 98};
    char new_user_name = "alptug";//timur(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
              {
    char new_user_id[4] = {-106, 84, 32, -44};
    char new_user_name = "alptug";//eray(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
              {
    char new_user_id[4] = {-18, -122, -45, -26};
    char new_user_name = "alptug";//serhan
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
              {
    char new_user_id[4] = {-21, -15, 59, -60};
    char new_user_name = "alptug";//batu(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
                {
    char new_user_id[4] = {-70, 22, 33, -125};
    char new_user_name = "alptug";//melisa
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
                {
    char new_user_id[4] = {-66, 98, 18, -44};
    char new_user_name = "alptug";//muzo(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
                {
    char new_user_id[4] = {22, -112, -41, -39};
    char new_user_name = "alptug";//hasan(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {4, 48, 71, 26};
    char new_user_name = "alptug";//alptuğ_metro
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
    {
    char new_user_id[4] = {-103, -54, -74, -56};
    char new_user_name = "alptug";//Turanabi
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
      {
    char new_user_id[4] = {-98,-26, 120, 96};
    char new_user_name = "alptug";//Yusuf(f)
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  {
    char new_user_id[4] = {-82,-100, -38, 91};
    char new_user_name = "alptug";//Berfu
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
   {
    char new_user_id[4] = {-18, -59, -36, 91};
    char new_user_name = "alptug";//Şevval Ongun
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  
//   {
//    char new_user_id[4] = {-82, 27, -38, 91};
//    char new_user_name = "alptug";//Erdem
//    strcpy(Users[i].user_id, new_user_id);
//    //Users[i].user_id = new_user_id;
//    strcpy(Users[i].user_name, new_user_name);
//    i++;
//  }
//   {
//    char new_user_id[4] = {33, -55, -54, 106};
//    char new_user_name = "alptug";//Batuhan Aktaş
//    strcpy(Users[i].user_id, new_user_id);
//    //Users[i].user_id = new_user_id;
//    strcpy(Users[i].user_name, new_user_name);
//    i++;
//  }

//<< 
  /*
  {
    char new_user_id[4] = {"Insert User Id Here};
    const char new_user_name = "Insert Username here";
    strcpy(Users[i].user_id, new_user_id);
    //Users[i].user_id = new_user_id;
    strcpy(Users[i].user_name, new_user_name);
    i++;
  }
  */
  
}

void loop() {
  static int counter = 0;
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    digitalWrite(KAYIT, LOW);
    delay(500);
    digitalWrite(KAYIT, HIGH);
    Serial.println("check");
    counter++;
    if(counter > 8){
      resetFunc();
      mfrc522.PCD_Init();
      Serial.println("mfrc522 reinit");
      counter = 0;
    }
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Dump debug info about the card. PICC_HaltA() is automatically called.
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  char *string = mfrc522.uid.uidByte;
  //String string = String(mfrc522.uid.uidByte);
  for(int j = 0; j < 4; j++)
  {
    Serial.print(string[j], DEC);
    Serial.print(", ");
  }
 
  
  /*USER newuser;
  newuser.user_uid = string;*/
  for(int k = 0; k < i; k++){
    for(int l = 0; l < 4; l++){
      if(string[l] != (Users[k].user_id)[l]){
        break;
      }
      if(l == 3){
        Serial.println("Kapi aciliyor");
        Serial.println("Hos Geldin ");
        //Serial.println(Users[k].user_name);
        digitalWrite(KAPI, HIGH);
        delay(750);
        digitalWrite(KAPI, LOW);
        
        return;
      }
    }
    if(k == (i - 1)){
      /*if(state == HIGH){
        Serial.println("check");
        Serial.println(i);
        strcpy(Users[i].user_id, string);
        i++;
      }*/
      Serial.println("Kapi Acilamiyor");
      
      digitalWrite(KAYIT, HIGH);
      delay(500);
      digitalWrite(KAYIT, LOW);
    }
  }



  
  //Users[i] = newuser;
  /*Serial.println("   ");
  Serial.println(Users[i].user_id);*/
}
/*
 * .Do` -- Bora
 * 
 * 
 */
