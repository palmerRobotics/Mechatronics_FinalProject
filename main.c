#include "NU32.h"          // config bits, constants, funcs for startup and UART
// include other header files here

#define BUF_SIZE 200

int main() 
{
  char buffer[BUF_SIZE];
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;  // turn off the LEDs
  NU32_LED2 = 1;        
  __builtin_disable_interrupts();
  // in future, initialize modules or peripherals here
  __builtin_enable_interrupts();

  while(1)
  {
    NU32_ReadUART3(buffer,BUF_SIZE); // we expect the next character to be a menu command
    NU32_LED2 = 1;                   // clear the error LED
    switch (buffer[0]) {
      case 'a':
      {
        //read analog input pin and return value
        //function call to current sensing module: analog read
        int n = 1023;
        sprintf(buffer,"%d",n);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'b':
      {
        //read analog input pin and return value
        //function call to current sensing module: analog read
        //function call to current sensing module: convert counts to mA
        int n = 100;
        sprintf(buffer,"%d",n);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'c':
      {
        //read encoder counts and return value
        //function call to encoder module: read counts
        int n = 1023;
        sprintf(buffer,"%d",n);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'd':
      {
        //read encoder counts and return value
        //function call to encoder module: read counts
        //function call to encoder module: covert counts to deg
        int n = 360;
        sprintf(buffer,"%d",n);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'e':
        //set theta=0 to the encoder's current count
        //function call to encoder module: reset encoder
      {
        break;
      }
      case 'f':
      {
        //set PWM duty cycle
        //function call to current control module: set fixed PWM
        break;
      }
      case 'g':
      {
        //set current gains
        //function call to current control module: set current gains
        break;
      }
      case 'h':
      {
        //get current gains
        //function call to current control module: get current gains
        char gains[BUF_SIZE] = {'1 2'};
        sprintf(buffer,"%s", gains);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'i':
      {
        //set position gains
        //function call to position control module: set position gains
        break;
      }
      case 'j':
      {
        //get position gains
        //function call to position control module: get position gains
        char gains[BUF_SIZE] = {'1 2 3'};
        sprintf(buffer,"%s", gains);
        NU32_WriteUART3(buffer);
        break;
        break;
      }
      case 'k':
      {
        //test current controller
        //function call to current control module: test current controller
        break;
      }
      case 'l':
      {
        //go to angle
        //function call to position control module: go to angle
        break;
      }
      case 'm':
      {
        //load step trajectory
        //function call to position control module: follow trajectory
        int n = 1;
        sprintf(buffer,"%d",n);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'n':
      {
        break;
      }
      case 'o':
      {
        break;
      }
      case 'p':
      {
        break;
      }
      case 'q':
      {
        // handle q for quit. Later you may want to return to IDLE mode here. 
        break;
      }
      case 'r':
      {
        break;
      }
            case 'x': // dummy command for demonstration purposes
      {
        int a, b = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d %d", &a, &b);
        sprintf(buffer,"%d\r\n", a+b); // return the number1 * number2
        NU32_WriteUART3(buffer);
        break;
      }
      case 'z': // dummy command for demonstration purposes
      {
        int n = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n);
        sprintf(buffer,"%d\r\n", n + 1); // return the number + 1
        NU32_WriteUART3(buffer);
        break;
      }
      default:
      {
        NU32_LED2 = 0;  // turn on LED2 to indicate an error
        break;
      }
    }
  }
  return 0;
}
