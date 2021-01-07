#include <Servo.h>
const int Trig = 2;
const int Echo= 3;
int Distancia_Calculo();

int x,y,r,c,j=0,k=0,i,busqueda,ifinal, interpuesto=0;
double iprim,angx,angy,ipromedio,iaux;
long distancia,distanciaPrueba,distanciaAux;

Servo Motor; 
double Entorno[50][4], Entorno_Fijo[15][3];

void setup() {
  pinMode(Trig, OUTPUT); 
  pinMode(Echo, INPUT); 
  Serial.begin(9600);
  Motor.attach(7); 
}

  
void loop() {
for(i=195;i>14;i--){
      Motor.write(i);
      delay(15);
  }
  Serial.println("Vuelta");
  Serial.println("--------------------------");
  Serial.println("--------------------------");
  for(i=15;i<=195;i++){ 
  Motor.write(i);
  delay(50);
  distancia = Distancia_Calculo();
  if(distancia>0&&(i!=0))
  {  
    interpuesto=0;
    ifinal=i+1;
    distanciaPrueba=1;
    iaux=0;
    while(distanciaPrueba>0)
    {
      Motor.write(ifinal);
      delay(200);
      distanciaPrueba = Distancia_Calculo();
      if(distanciaPrueba>(distancia+15)||distanciaPrueba<(distancia-15))
      {
        interpuesto=-1;
        break;
      }
      else
      { 
        if (ifinal>=195)
        {
          break;
        }
        else
        {
           ifinal++;
        }
       
      }
    }
    busqueda=0;
    for(r=0;r<j;r++)
    {
      if((i<(Entorno[r][0]+5))&&(i>(Entorno[r][0]-5)))
      {
        if((distancia<(Entorno[r][1]+5))&&(distancia>(Entorno[r][1]-5)))
        {
          if((ifinal<(Entorno[r][2]+5))&&(ifinal>(Entorno[r][2]-5)))
          {
            Entorno[r][3]=Entorno[r][3]+1;
            busqueda=-1;
          }
        }
      }
    }
    if (busqueda==0)
    {
      Entorno[j][0]=i;
      Entorno[j][1]=distancia;
      Entorno[j][2]=ifinal;
      Entorno[j][3]=0;
      j++;
    }
    for(r=0;r<j;r++)
    {
      if(Entorno[r][3]==3)
      {
        Entorno_Fijo[k][0]=Entorno[r][0];
        Entorno_Fijo[k][1]=Entorno[r][1];
        Entorno_Fijo[k][2]=Entorno[r][2];
        k++;
      }
    }
    busqueda=0;
    for(r=0;r<k;r++)
    {
      if(((Entorno_Fijo[r][0]<(i+5)))&&(Entorno_Fijo[r][0]>(i-5)))
      {
        if((distancia<(Entorno_Fijo[r][1]+5))&&(distancia>(Entorno_Fijo[r][1]-5)))
        {
          if((ifinal<(Entorno_Fijo[r][2]+5))&&(ifinal>(Entorno_Fijo[r][2]-5)))
          {
            busqueda=-1;
          }

        }
      }
    }
    if(busqueda==0)
    {      
      ipromedio = ((ifinal-15)+(i-15))/2;
      iprim = ipromedio*3.14159/180;
      angx= cos(iprim);
      angy= sin(iprim);
      x= angx*distancia;
      y=angy*distancia;
     
      Serial.print("Se encontró un objeto en: ");
      Serial.print("(");
      Serial.print(x); 
      Serial.print(", "); 
      Serial.print(y);
      Serial.println(")"); 
      Serial.println("--------------------------");
      Serial.println("--------------------------");
    }
    i=ifinal;
    if(interpuesto==0)
    {
       for(r=0;r<5;r++)
       {
         i++;
         Motor.write(i);
         delay(50);
       }
      
    }
  }
 }
}
int Distancia_Calculo()
{ 
  long distancia1;
  long duracion;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duracion = pulseIn(Echo, HIGH); 
  distancia1= duracion*0.01715;
  if(distancia1>85||distancia1<1)
  {
    distancia1=-1;
  }
  return distancia1;
}
