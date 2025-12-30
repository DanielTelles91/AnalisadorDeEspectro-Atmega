//#include <SoftwareSerial.h>      // Biblioteca Comunicação Serial do Display VFD
#include <IRremote.h>             // Biblioteca IRemote
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // Núcleo da Biblioteca Gráfica TFT
#include <Adafruit_ST7789.h>   // Biblioteca da Controladora TFT ST7789


// Pino D9 - Ligado ao Sensor IR (Controle Remoto)
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;


// ST7789 TFT module connections
#define TFT_CS    10  // define chip select pin
#define TFT_DC    A4  // define data/command pin
#define TFT_RST   A5  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);



int transistorEfeitoDotBar_Spectrum = 2;
int transistorEfeitoDotBar_VU = 3;
int transistorLigaDesliga = 4;
int transistorAux = 5;
int transistorBacklight = 7;
boolean estadoEfeitoDotBar_Spectrum = false;
boolean estadoLigaDesliga = false;
boolean estadoAux1 = true;
boolean estadoAux2 = false;



void setup() {
  irrecv.enableIRIn(); // Ativa o sensor Infra Vermelho do Controle Remoto

  pinMode(transistorEfeitoDotBar_Spectrum , OUTPUT);
  digitalWrite(transistorEfeitoDotBar_Spectrum , HIGH);

  pinMode(transistorEfeitoDotBar_VU , OUTPUT);
  digitalWrite(transistorEfeitoDotBar_VU , LOW);

  pinMode(transistorLigaDesliga , OUTPUT);
  digitalWrite(transistorLigaDesliga , LOW); // Inicializa Desligado

  pinMode(transistorAux , OUTPUT);
  digitalWrite(transistorAux , LOW); // Inicializa Desligado

  pinMode(transistorBacklight , OUTPUT);
  digitalWrite(transistorBacklight , LOW); // Inicializa Desligado
  


  pinMode(A0 , OUTPUT);
  digitalWrite(A0 , LOW); // Inicializa Ligado (VERMELHO) STATUS Aparelho Desligado

  pinMode(A1 , OUTPUT);
  digitalWrite(A1 , HIGH); // Inicializa Desligado (VERDE) STATUS Aparelho Ligado

  pinMode(A2 , OUTPUT);
  digitalWrite(A2 , HIGH); // Inicializa Desligado (Azul) STATUS Sinal (Controle Remoto ...)


  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel
  tft.setRotation(2); // Rotação do Display TFT


  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);


  //tft.drawBitmap(0, 0,  monroe, 90, 90, ST77XX_WHITE);
  // telaColdBoot();




}



void telaBye() {


  tft.drawBitmap(0, 0, goodbye, 128, 128, ST77XX_WHITE);
  delay(4000);
  tft.fillScreen(ST77XX_BLACK);

  }





void telaChaveamentoBluetooth() {

  //                 X    Y


  tft.fillRoundRect(79, 119, 83, 110, 8, ST77XX_BLUE);
  tft.drawBitmap(66, 120,  bluetooth_img, 110, 110, ST77XX_WHITE);



}


void telaChaveamentoTapeDeck() {

  //                 X    Y
  tft.fillRoundRect(79, 119, 83, 110, 8, ST77XX_WHITE);
  tft.drawBitmap(66, 120,  tape_img, 110, 110, ST77XX_BLACK);


}




void sinalizacaoComando() { // Sinaliza piscando o LED AZUL quando recebe algum comando do Controle Remoto

  digitalWrite(A2 , LOW);
  delay(500);
  digitalWrite(A2 , HIGH);

}




void telaColdBoot() {



  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(4);
  tft.setTextWrap(true);
  tft.println("Analisador    de     Espectro");

  tft.setCursor(0, 225);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Versao 1.0   -  2023");

  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);

}


void fundoEscala() {

  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("+ 6");
  tft.setCursor(38, 0);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 25);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("+ 3");
  tft.setCursor(38, 25);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 50);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("  0");
  tft.setCursor(38, 50);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 75);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("- 3");
  tft.setCursor(38, 75);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 100);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("- 6");
  tft.setCursor(38, 100);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 125);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("- 9");
  tft.setCursor(38, 125);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 150);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-12");
  tft.setCursor(38, 150);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 175);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-15");
  tft.setCursor(38, 175);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 200);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-18");
  tft.setCursor(38, 200);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(0, 225);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.println("-21");
  tft.setCursor(38, 225);
  tft.setTextSize(2);
  tft.println("dB");


  tft.setCursor(76,84); //88
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("INPUT");


  //Direita

  tft.setCursor(180, 0);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("+ 6");
  tft.setCursor(218, 0);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 25);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("+ 3");
  tft.setCursor(218, 25);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 50);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("  0");
  tft.setCursor(218, 50);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 75);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("- 3");
  tft.setCursor(218, 75);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 100);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(2);
  tft.println("- 6");
  tft.setCursor(218, 100);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 125);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("- 9");
  tft.setCursor(218, 125);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 150);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-12");
  tft.setCursor(218, 150);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 175);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-15");
  tft.setCursor(218, 175);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 200);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("-18");
  tft.setCursor(218, 200);
  tft.setTextSize(2);
  tft.println("dB");

  tft.setCursor(180, 225);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.println("-21");
  tft.setCursor(218, 225);
  tft.setTextSize(2);
  tft.println("dB");




}







void controleRemoto() {

  if (irrecv.decode(&results)) {


    // tft.fillScreen(ST77XX_BLACK);
    // tft.setCursor(83, 125);
    // tft.setTextColor(ST77XX_GREEN); //Exibe o código do controle remoto no TFT
    // tft.setTextSize(2);
    //  tft.println(results.value,HEX);



    switch (results.value) {

      //Botão Mudar o efeito
      case 0xFF6897:    //Controle Kit Arduino(*)
      case 0xB54A9966:  //Controle Pioneer(MENU)
        {

          if (estadoEfeitoDotBar_Spectrum == false && estadoLigaDesliga == true) {

            estadoEfeitoDotBar_Spectrum = true;
            digitalWrite(transistorEfeitoDotBar_Spectrum , LOW);//Define ledPin como HIGH, ligando o LED
            digitalWrite(transistorEfeitoDotBar_VU , HIGH);//Define ledPin como HIGH, ligando o LED
            sinalizacaoComando();    // Pisca o LED AZUL

            break;

          }

          else {

            estadoEfeitoDotBar_Spectrum = false;
            digitalWrite(transistorEfeitoDotBar_Spectrum , HIGH);//Define ledPin como HIGH, ligando o LED
            digitalWrite(transistorEfeitoDotBar_VU , LOW);//Define ledPin como HIGH, ligando o LED
            sinalizacaoComando();    // Pisca o LED AZUL




            break;

          }

          break;

        }

      //Chaveamento AUX 1 e AUX II
      case 0x9D62F00F:  //Controle Kenwood(OK)
      case 0xB54A9867:  //Controle Pioneer(MODE)
        {

          if (estadoAux1 == true && estadoLigaDesliga == true) {

            estadoAux1 = false;
            estadoAux2 = true;
            sinalizacaoComando();    // Pisca o LED AZUL
            digitalWrite(transistorAux , HIGH);// Liga o Aux II
            telaChaveamentoTapeDeck();
            break;
          }

          if (estadoAux2 == true && estadoLigaDesliga == true)  {

            estadoAux1 = true;
            estadoAux2 = false;
            sinalizacaoComando();    // Pisca o LED AZUL
            digitalWrite(transistorAux , LOW);// Liga o Aux I
            telaChaveamentoBluetooth();
            break;
          }


          break;
        }


      //Botão Liga/Desliga
      case 0xFFA25D:    // Controle Kit Arduino(1)
      case 0xB54A58A7:  // Controle Pioneer(SRC)
        {

          if (estadoLigaDesliga == false) { // Quando Pressionado o botão liga o aparelho

            estadoLigaDesliga = true;
            digitalWrite(transistorLigaDesliga , HIGH); // Liga o RELE da ENTRADA 9 Volts
            digitalWrite(A0 , HIGH); // Liga o LED VERDE
            digitalWrite(A1 , LOW);  // Desliga o LED VERMELHO
            sinalizacaoComando();    // Pisca o LED AZUL
            telaColdBoot();
            fundoEscala();
            if (estadoAux1 == true) {
              telaChaveamentoBluetooth();
            }
            if (estadoAux2 == true) {
              telaChaveamentoTapeDeck();
            }
            break;

          }

          if (estadoLigaDesliga == true) {

            estadoLigaDesliga = false;
            digitalWrite(transistorLigaDesliga , LOW); // Desliga o RELE da ENTRADA 9 Volts
            sinalizacaoComando();     // Pisca o LED AZUL
            digitalWrite(A0 , LOW);  // Desliga o LED VERDE
            digitalWrite(A1 , HIGH); // Liga o LED VERMELHO
            tft.fillScreen(ST77XX_BLACK);
            telaBye();
            break;
          }

          break;
        }

    }

    irrecv.resume();
  }
}



void loop() {
  controleRemoto();

}
