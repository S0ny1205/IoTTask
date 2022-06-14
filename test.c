#include <stdio.h>
#include <wiringPi.h>
#include <signal.h> //Signal 사용 헤더파일
#include <unistd.h>
#include <string.h> 
#include <errno.h>
#include <stdlib.h> //exit() 사용 헤더파일
#define trigPin 1       //gpio 21
#define echoPin 29 //gpio 18
#define DCMOTOR	23 // BCM_GPIO 13

int main(void)
{
        int distance=0;
        int pulse = 0;

        long startTime;
        long travelTime;
        if(wiringPiSetup () == -1)
        {
	        printf("Unable GPIO Setup"); 
                return 1;
        }

        pinMode (trigPin, OUTPUT);
        pinMode (echoPin, INPUT);
        pinMode (DCMOTOR, OUTPUT) ;

        volatile int eventCounter = 0;
unsigned char humandetect = 0;
int counter = 0;

void myInterrupt(void) {
   eventCounter++;
   humandetect = 1;

}
void Bpluspinmodeset(void);
void setRGB(int r, int g, int b);
void sig_handler(int signo); // SIGINT 핸들러 함수
void  Fade( int fromColor, int toColor, int offColor );

int main(void) {
  
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }

  
  if ( wiringPiISR (MOTION_IN, INT_EDGE_RISING, &myInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;

      if(wiringPicheck()) printf("Fail");
		    Bpluspinmodeset();
	      signal(SIGINT, (void *)sig_handler);
	      digitalWrite(RGBLEDPOWER, 1);
    
    int i = 0, j = 0, k=0;
	printf("RGB LED Various Color");
 
	softPwmCreate(RED, 0, 255);
	softPwmCreate(GREEN, 0, 255);
	softPwmCreate(BLUE, 0, 255);
  }
        while(1)
        {
                digitalWrite (trigPin, LOW);
     	        usleep(2);
                digitalWrite (trigPin, HIGH);
                usleep(20);
                digitalWrite (trigPin, LOW);

                while(digitalRead(echoPin) == LOW);

                startTime = micros();

                while(digitalRead(echoPin) == HIGH);
			travelTime = micros() - startTime;

                int distance = travelTime / 58;

                printf( "Distance: %dcm\n", distance);
				delay(200);
			if(distance < 3 )
				{
                //printf("here - FAN on\n");
                digitalWrite (DCMOTOR, 1) ; // On
				}
         while ( 1 ) {
    if(humandetect == 1)
	{
		printf("Detect %d\n", eventCounter );
		humandetect = 0;
		while(digitalRead(MOTION_IN))
        	{
            		printf("high %d \n", counter++);
            		delay(1000);
                Fade( RED, GREEN, BLUE );
                Fade( GREEN, BLUE, RED );
                Fade( BLUE, RED, GREEN );
        	}
		counter = 0;

	}
	else
	{
		printf(" No detect\n");
	}		
    
    delay( 500 ); 
  }

  return 0;
}

int wiringPicheck(void)
{
	if (wiringPiSetup () == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1 ;
	}
}

void Bpluspinmodeset(void)
{
	pinMode(RGBLEDPOWER, OUTPUT);
	pinMode (RED, OUTPUT);
	pinMode (GREEN, OUTPUT);
	pinMode (BLUE, OUTPUT);	
	
}

void  Fade( int fromColor, int toColor, int offColor )
{
  int  color; 
  
  softPwmWrite( offColor, 0 ); 
  
  for( color = 255; color >= 0; color-- )   
  {
    softPwmWrite( fromColor, color );     
    softPwmWrite( toColor, 255 - color );
    delay(30); 
  }
}

void sig_handler(int signo) 
{
    printf("process stop\n");
	digitalWrite(RED, 0);
	digitalWrite(GREEN, 0);
	digitalWrite(BLUE, 0);
	digitalWrite(RGBLEDPOWER, 0); //Off
	exit(0);
}

/**
void setRGB(int r, int g, int b){
  softPwmWrite(RED, 255-r);
  softPwmWrite(GREEN, 255-g);
  softPwmWrite(BLUE, 255-b);
}
*/
		else if(distance > 3)
				{
				digitalWrite (DCMOTOR, 0) ; // On
				}

		}
}

