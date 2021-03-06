#pragma config(Sensor, S2,     sengirp,        sensorEV3_Gyro)
#pragma config(Sensor, S3,     sencolor,       sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorB,          motb,          tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          motc,          tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motorA,          motd,          tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
task main(){
	int giro_fin=0,cont = 0, state = 0, deg = 0 ; //Definimos variables que nos ayudar� para realizar el juego
	while (true){
		int color = SensorValue[sencolor];

		if(color == 0) { //Si el sensor no detecta colores, el robot permacer� quieto y luego se reinicia hasta que detecte un color
			cont = 0;
			state = 0;
			motor[motb] = 0; //as� funciona por ahora xd (antes = motor(motorB)
			motor(motc) = 0;
			wait1Msec(10);
			continue;
		}

		if ((color == 1)&&(cont < 4)){ // Cuando el sensor detecta el color negro, a la variable cont se le suma 1
			if(cont < 4) { // Si cont es menor a 2 el robot sigue avanzando
				motor(motb) = 10;
				motor(motc) = 10;
				cont++;
				wait1Msec(500);
			}
		}
		else { // Si el sensor no detect� ning�n color negro sigue avanzando
			motor(motb) = 10;
			motor(motc) = 10;
		}

		if (cont == 4){ //Si el cont es igual a 2 el sensor giroscopio har� que �ste gire
			wait1Msec(500);
			resetGyro(sengirp);
			if(state == 0) { // Giro de DERECHA
				motor(motb) = 10;
				motor(motc) = 10;
				wait1Msec(1500);
				motor(motb) = 5;
				motor(motc) = -5;

				while(SensorValue[sengirp] < (90)) { //Giro con �NGULO
					wait1Msec(5);
					continue;
				}
				motor(motb) = -10; //Para reacomodar el robot dentro del sector, ponemos los valores de los motores en negativo para que el robot retroceda
				motor(motc) = -10;
				wait1Msec(1000);
				resetGyro(sengirp);
				while(giro_fin!=1){
					color = SensorValue[sencolor];
					if (color==1){
						motor(motb) = 10;
						motor(motc) = 10;
						wait1Msec(2000);
						motor(motb) = 5;
						motor(motc) = -5;
						while(SensorValue[sengirp] < (90)) {
							wait1Msec(5);
							continue;
						}
						giro_fin=1;
						motor(motb) = -10;
						motor(motc) = -10;
						wait1Msec(700);
					}
					else{
						motor(motb)= 10;
						motor(motc)= 10;

					}
				}//while giro_fin
			}
			if(state==1){//Ultimo giro
				motor(motb) = 10;
				motor(motc) = 10;
				wait1Msec(2500);
				motor(motb) = -5;
				motor(motc) = 5;
				}//giro izquierda
			state++;
			cont=0;
				}
		}//if cont
	}//while True
}
