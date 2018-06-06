#include <avr/io.h>
#include<util/delay.h>

int count=1;
volatile uint8_t history = 0xFF;

#define Switch1 2 //PCINT18
#define Switch2 3 //PCINT18    
#define Switch3 4 //PCINT20

struct ind {
    int i,j;
};
int X[5],O[5];


const int l[3][3]= {{5,6,7},{0,1,2,},{3,4,5}};
int d[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int i=0,j=0,r=0,k=0,g=0,h=0;

int mov(int i,int j,int r) {
    if(r==1) {
        if(j==2) {
            if(i==0) {
                PORTD &= ~(1<<l[i][j]);
                j=0;
                PORTD = (1<<l[i][j]);
                _delay_ms(200);
            }
            else {
                PORTB &= ~(1<<l[i][j]);
                j=0;
                PORTB = (1<<l[i][j]);
                _delay_ms(200);
            }
        }
        else
        {



            if(i==0) {

                PORTD &= ~(1<<l[i][j]);
                j=j+1;
                PORTD = (1<<l[i][j]);
                _delay_ms(200);

            }
            else {

                PORTB &= ~(1<<l[i][j]);
                j=j+1;
                PORTB = (1<<l[i][j]);
                _delay_ms(200);
            }
        }
        return (j);
    }
    if(r==2) {

        if(i==2) {

            PORTB &= ~(1<<l[i][j]);
            i=0;
            PORTD = (1<<l[i][j]);
            _delay_ms(200);

        }
        else if(i==0) {

            PORTD &= ~(1<<l[i][j]);
            i=i+1;
            PORTB = (1<<l[i][j]);
            _delay_ms(200);

        }
        else if(i==1) {

            PORTB &= ~(1<<l[i][j]);
            i=i+1;
            PORTB = (1<<l[i][j]);
            _delay_ms(200);
        }
        return (i);
    }

}

void TIMER()
{
    OCR1A = 15000;
    TCCR1B |= (1<<WGM12);
    TIMSK1 |= (1<<OCIE1A);
    TCCR1B |= (1<<CS12)|(1<<CS10);
    sei();
}
/*void check()
  {
   Serial.print('q');
   if(((d[0][0]==9) && (d[0][1]==9)&& (d[0][2]==9) )||((d[1][0]==9) && (d[1][1]==9)&& (d[1][2]==9) )||((d[2][0]==9) && (d[2][1]==9)&& (d[2][2]==9) )||((d[0][0]==9) && (d[1][0]==9)&& (d[2][0]==9) )||((d[0][1]==9) && (d[1][1]==9)&& (d[2][1]==9) )||((d[0][2]==9) && (d[1][2]==9)&& (d[2][2]==9) )||((d[0][0]==9) && (d[1][1]==9)&& (d[2][2]==9) )||((d[2][0]==9) && (d[1][1]==9)&& (d[0][2]==9) ))
  {
   PORTB = (1<<5)|(1<<3)|(1<<1);
   PORTD = (1<<5)|(1<<7);
  }
   if(((d[0][0]==10) && (d[0][1]==10)&& (d[0][2]==10) )||((d[1][0]==10) && (d[1][1]==10)&& (d[1][2]==10) )||((d[2][0]==10) && (d[2][1]==10)&& (d[2][2]==10) )||((d[0][0]==10) && (d[1][0]==10)&& (d[2][0]==10) )||((d[0][1]==10) && (d[1][1]==10)&& (d[2][1]==10) )||((d[0][2]==10) && (d[1][2]==10)&& (d[2][2]==10) )||((d[0][0]==10) && (d[1][1]==10)&& (d[2][2]==10) )||((d[2][0]==10) && (d[1][1]==10)&& (d[0][2]==10) ))
  {
   PORTB = (1<<4)|(1<<0)|(1<<2);
   PORTD = (1<<6);
  }
  }*/
void pinchange() {
    PCICR |= (1<<PCIE2);
    PCMSK2 |= (1<<PCINT20);
    PCMSK2 |= (1<<PCINT19);
    PCMSK2 |= (1<<PCINT18);
}


int main(void) {
    DDRD =(1<<5)|(1<<6)|(1<<7);
    DDRB =(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
    _delay_ms(100);
    sei();
    Serial.begin(9600);
    Serial.print('X');
    while(1) {

    }
}
ISR (PCINT2_vect) {
    uint8_t change;
    change = PIND ^ history;
    history = PIND;
    count=count+1;
    if( count%2 ==0) {
        if(change & (1 << 3)) {
            Serial.print('b');
            i=mov(i,j,2);

            Serial.print(k);

            if(k%2==0) {

            }
            else {

            }


        }

        else if(change & (1 << 4)) {
            Serial.print('c');

            j=mov(i,j,1);
            Serial.print(k);

            if(k%2==0) {

            }
            else {

            }



        }

        else if( (change & (1 << 2))) {
            Serial.print('a');
            k=k+1;
            Serial.print(k);
            if(k%2==0) {

                d[i][j]= 9;

            }
            else {

                d[i][j]= 10;

            }

        }
        /* check();*/
    }
}

ISR (TIMER1_COMPA_vect) {

    if(i==0) {

        PORTD = (1<<l[i][j]);
    }
    else {

        PORTB = (1<<l[i][j]);
    }
}




