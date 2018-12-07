#include <DHT.h>

// ====PINES====
//Sensores
int sensorE = 10; //PIN DEL SENSOR DHT11 
int intensidad = A0; //fotoresistor
int yl69 = A1; //Humedad de tierra 


// ----VARIABLES---
//Sensores
DHT dhtE (sensorE,DHT11); //dht externo
float conversion=0;
float conversionH = 0; //esta variable almacena la conversion del foto resistor de ohms a lux
//lUX es una unidad de medida que representa la cantidad de luz recibida en cierta superficie, se maneja en porcentajes
float tempe,hume; //temperatura exterior y humedad exterior
float humedadtierra;

void setup() {
//Sensores
Serial.begin(9600);//se abre el monitor serial para recibir y enviar daros
dhtE.begin();//Se inicializa el sensor DHT22
pinMode(intensidad, INPUT); //El fotoresistor es de tipo INPUT
//pinMode(yl69, INPUT);
Serial.available(); //Si declaramos esto en el void setup las variables se almacenaran fuera del ciclo
// Con Serial.available() enviamos datos del arduino
}


void loop() {
  //El metodo sensores() maneja la captura de datos de los sensores 
hume = dhtE.readHumidity(); //metodo de la libreria del sensor DHT11 que captura la humedad 
tempe = dhtE.readTemperature(); //metodo de la libreria del sensor DHT11 que captura la humedad 

//Se imprimen todas los datos en una sola linea separada por una coma para que cuando c# reciva los datos estos se puedans separar por medio de la funcion .split()

Serial.print((float)tempe); 
Serial.print(",");
Serial.print((float)hume);
Serial.print(",");
intensidad = analogRead(A0); //Lee el pin analogo 0 (fotoresistor input) Unidad Ohms
yl69 = analogRead(A1);
//Serial.print((float)intensidad); //imprime los valores que arroja la fotoresistencia (Rango 0 - 1023)
//Serial.print(","); 
conversion = map(intensidad, 0, 1023, 0, 100); //La funcion map asigna los valores a un porcenjare (fuente, min, max , min, max) Entre mayor luz, mayores valores arroja
conversionH = map (yl69, 1023, 230 , 0 , 100);
Serial.print((float)conversion);//Unidad LUX
//Serial.print(",");
//Serial.print((float)yl69); voltaje del humedad
Serial.print(",");
Serial.print((float)conversionH);
//Serial.println(" ");
delay(500);

}
