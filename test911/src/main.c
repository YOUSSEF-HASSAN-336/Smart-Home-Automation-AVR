// #include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GI_interface.h"
// #include "EXTI_interface.h"
// #include "SSD_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "KPD_interface.h"
#include "TMR0_interface.h" 
#include "LED_interface.h"
#include "BUZZER_interface.h"
#include "PWM0_interface.h"
#include "PWM1_interface.h"
#include "UART_interface.h"
#include "SPI_interface.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

static int users=3;
int main(void) {
    u16 adcValue;
    f32 temperature;

    
    
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN4, DIO_PIN_OUTPUT);// GRN LED 

    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);//RED LED for alarm

    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN5, DIO_PIN_OUTPUT);//BLU LED 

    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT);//YEL LED 

    DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN6, DIO_PIN_OUTPUT);// Buzzer

    LED_voidOff(DIO_PORTA, DIO_PIN4, LED_FORWARD_CONNECTION);
    LED_voidOff(DIO_PORTB, DIO_PIN7, LED_FORWARD_CONNECTION);
    DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);

    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT); // OC0 output pin
    ADC_voidInit(ADC_REFERENCE_AVCC);
    
    PWM0_voidInit();


    LCD_voidInit();
    KPD_voidInit();
    EEPROM_voidInit();

    // Servo Motor (Door) Init
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT); // OC1A = PD5
    PWM1_voidInitChannel1A();

//<<<<<<<<<<<<<<<<<<<<<<<This code will only be executed the first time.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//

        //< adman sign in first once only >
    u8  key ;
    u8  NumOfUsernameDigtis=4 ,NumOfPassDigtis=4;  
    u8 valUsernameAdmin[NumOfUsernameDigtis];
    u8  valPasswordAdmin[NumOfPassDigtis];
    LCD_voidClear();
    LCD_voidDisplayString((u8*)" < Welcome Admin >");
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
    LCD_voidDisplayString((u8*)"sign in.");
    _delay_ms(2000);
    LCD_voidClear();

    LCD_voidDisplayString((u8*)"Enter username:"); //enter username for admin in EEPROM
    for (int i = 0; i < NumOfUsernameDigtis; i++)
    {
        do{
            KPD_voidGetValue(&key);
        }while(key==0xFF);
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO,i);
        LCD_voidDisplayChar('*');
        _delay_ms(300);
        valUsernameAdmin[i]=key;
    }
    // EEPROM_voidWritePage(0,valUsernameAdmin,16);//(PAG 1) username in EEPROM adrsing form 0 to 15
    LCD_voidClear();
    

    LCD_voidDisplayString((u8*)"Enter Password:");
    for (int i = 0; i < NumOfPassDigtis; i++)
    {
        do{
            KPD_voidGetValue(&key);
        }while(key==0xFF);
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO,i);
        LCD_voidDisplayChar('*');
        _delay_ms(300);
        valPasswordAdmin[i]=key;
    }
    // EEPROM_voidWritePage(15,valPasswordAdmin,16);//(PAG 2) password in EEPROM adrsing form 16 to 31
    LCD_voidClear();
//<<<<<<<<<<<<<<<<<<<<<<end code.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//


        //< created user by admin >

        u8 valUsernameUser1[NumOfUsernameDigtis];
        u8 valPasswordUser1[NumOfPassDigtis];

        u8 valUsernameUser2[NumOfUsernameDigtis];
        u8 valPasswordUser2[NumOfPassDigtis];

        u8 valUsernameUser3[NumOfUsernameDigtis];
        u8 valPasswordUser3[NumOfPassDigtis];

    LCD_voidDisplayString((u8*)"1)creat user"); //chose number for need 

    LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
    LCD_voidDisplayString((u8*)"2)end program.");
    do{
    KPD_voidGetValue(&key);}
    while(key==0xFF);
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO,15);
    LCD_voidDisplayChar(key);
    _delay_ms(700);
    LCD_voidClear();

    if(key=='1')
    { //created new user and sign in user
        users--;
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"< Welcome new user1 >");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
        LCD_voidDisplayString((u8*)"sign in.");
        _delay_ms(2000);
        LCD_voidClear();
//----------------
        u8 valUsernameUser[NumOfUsernameDigtis];
        u8 valPasswordUser[NumOfPassDigtis];
        LCD_voidDisplayString((u8*)"Enter username:"); //enter username for user in EEPROM
        for (int i = 0; i < NumOfUsernameDigtis; i++)
        {
            do{
                KPD_voidGetValue(&key);
            }while(key==0xFF);
            LCD_voidGoToSpecificPosition(LCD_LINE_TWO,i);
            LCD_voidDisplayChar('*');
            _delay_ms(300);
            valUsernameUser[i]=key;
        }
        // EEPROM_voidWritePage(32,valUsernameUser,16);//(PAG 3) username in EEPROM adrsing form 32 to 47
        LCD_voidClear();
        

        LCD_voidDisplayString((u8*)"Enter Password:");
        for (int i = 0; i < NumOfPassDigtis; i++)
        {
            do{
                KPD_voidGetValue(&key);
            }while(key==0xFF);
            LCD_voidGoToSpecificPosition(LCD_LINE_TWO,i);
            LCD_voidDisplayChar('*');
            _delay_ms(300);
            valPasswordUser[i]=key;
        }
        // EEPROM_voidWritePage(48,valPasswordUser,16);//(PAG 4) password in EEPROM adrsing form 48 to 31
        LCD_voidClear();
    }

    //-------------------------------
    int trial = 0;
    while(1)
    {
    // ممكن نبقي نعملي لو انت يوزر ولا ادمن وبعد كده تدخل جوه
        LCD_voidDisplayString((u8*)"<Welcom, Adm or user");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
        LCD_voidDisplayString((u8*) "1)Admin");
        LCD_voidGoToSpecificPosition(LCD_LINE_THREE,0);
        LCD_voidDisplayString((u8*)"2)User");
        do{
            KPD_voidGetValue(&key);}
        while(key==0xFF);
        LCD_voidGoToSpecificPosition(LCD_LINE_FOUR,0);
        LCD_voidDisplayChar(key);
        _delay_ms(700);
        LCD_voidClear();
        u8 enterdUsername[NumOfUsernameDigtis];
        if(key=='1')//<<<<Admin>>>>>
        {
            LCD_voidDisplayString((u8*)"<<lgoin Admin>>");//login
            _delay_ms(2000);
            LCD_voidClear();

            int isCorrect;
            for(int i=0; i<3;i++)              //enter usernaem for Admin becouse check
            {
                isCorrect = 1;
                LCD_voidDisplayString((u8*)"enter your usernaem");
                for (int j = 0; j < NumOfUsernameDigtis; j++)
                {
                    do{
                        KPD_voidGetValue(&key);}
                    while(key==0xFF);
                    enterdUsername[j]=key;
                    LCD_voidGoToSpecificPosition(LCD_LINE_TWO,j);//<--
                    LCD_voidDisplayChar('*');
                    _delay_ms(300);//<--
                }
                LCD_voidClear();
                for (int j = 0; j < NumOfUsernameDigtis; j++)
                {
                    if (enterdUsername[j]!=valUsernameAdmin[j])
                    {
                        isCorrect=0;
                        break;
                    }
                }
                if (isCorrect) {
                    break;
                } else {
                    trial++;
                    LCD_voidDisplayString((u8*)"error, try again");
                    _delay_ms(1000);
                    LCD_voidClear();
                }
            }
            if(trial==3) //لو غلط يفتح البازار والليد الحمر وميقفش الا لما تضغط علي حرف ال D
            {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"ALARM!");
                LED_voidToggle(DIO_PORTB, DIO_PIN7 ); // Red LED blink
                DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH); // Buzzer on
                do{
                    KPD_voidGetValue(&key);}
                while(key==0xFF);//if enter D reseat for first loop else buzzer be on
                if(key=='D')
                {
                    DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW); // Buzzer off
                    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW); // Buzzer on
                    LCD_voidClear();
                    continue;    
                }
            }
//========================================================
//-----------------------------password check--------------------------------------
            isCorrect = 1;
            for(int i=0; i<3;i++)              //enter password for Admin becouse check
            {
                isCorrect = 1;
                LCD_voidDisplayString((u8*)"enter your password");
                for (int j = 0; j < NumOfPassDigtis; j++)
                {
                    do{
                        KPD_voidGetValue(&key);}
                    while(key==0xFF);
                    enterdUsername[j]=key;
                    LCD_voidGoToSpecificPosition(LCD_LINE_TWO,j);//<--
                    LCD_voidDisplayChar('*');
                    _delay_ms(300);//<--
                }
                LCD_voidClear();
                for (int j = 0; j < NumOfPassDigtis; j++)
                {
                    if (enterdUsername[j]!=valPasswordAdmin[j])
                    {
                        isCorrect=0;
                        break;
                    }
                }
                if (isCorrect) {
                    break;
                } else {
                    trial++;
                    LCD_voidDisplayString((u8*)"error, try again");
                    _delay_ms(1000);
                    LCD_voidClear();
                }
            }
            if(trial==3) //لو غلط يفتح البازار والليد الحمر وميقفش الا لما تضغط علي حرف ال D
            {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"ALARM!");
                LED_voidToggle(DIO_PORTB, DIO_PIN7 ); // Red LED blink
                DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH); // Buzzer on
                do{
                    KPD_voidGetValue(&key);}
                while(key==0xFF);//if enter D reseat for first loop else buzzer be on
                if(key=='D')
                {
                    DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW); // led off
                    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW); // Buzzer off
                    LCD_voidClear();
                    continue;    
                }
            }
            // After checking the password, if it is incorrect, continue the loop.
            if (!isCorrect) {
                continue;
            }
//----------------------------------------------------
            //if correct
            if (isCorrect) {
                LCD_voidDisplayString((u8*)"CORRECT, WELCOME");
                _delay_ms(1000);
                LCD_voidClear();
            
                LCD_voidDisplayString((u8*)"1)Air condtion");
            
                LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
                LCD_voidDisplayString((u8*)"2)Cnotrol Dore");

                LCD_voidGoToSpecificPosition(LCD_LINE_THREE,0);
                LCD_voidDisplayString((u8*)"3)Control led");

                LCD_voidGoToSpecificPosition(LCD_LINE_FOUR,0);
                LCD_voidDisplayString((u8*)"4)New user");

                LCD_voidGoToSpecificPosition(LCD_LINE_FOUR,6);
                LCD_voidDisplayString((u8*)"5)Delat user");              

                do{
                    KPD_voidGetValue(&key);}
                while(key==0xFF);
                enterdUsername[0]=key;
                LCD_voidGoToSpecificPosition(LCD_LINE_THREE,9);//<--
                LCD_voidDisplayChar(key);
                _delay_ms(300);

                if (key=='1')//Air condtion
                {
                    //....
                    ADC_voidGetDigitalValue(ADC_CHANNEL_0,&adcValue); 
                    temperature = (adcValue * 5.0 * 100) / 1024.0; 
                    temperature=temperature/10;
                    if(temperature < 20)
                    {
                        PWM0_voidGeneratePWM(0); 
                        LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                        LCD_voidDisplayString((u8*)"Temp: ");
                        LCD_voidDisplayNumber((u16)temperature); 
                        LCD_voidDisplayString((u8*)" C");

                    }
                    else if(temperature >= 20 && temperature < 25)
                    {
                        PWM0_voidGeneratePWM(25);
                        LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                        LCD_voidDisplayString((u8*)"Temp: ");
                        LCD_voidDisplayNumber((u16)temperature); 
                        LCD_voidDisplayString((u8*)" C");
                    }
                    else if(temperature >= 25 && temperature < 30)
                    { 
                        PWM0_voidGeneratePWM(50); 
                        LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                        LCD_voidDisplayString((u8*)"Temp: ");
                        LCD_voidDisplayNumber((u16)temperature); 
                        LCD_voidDisplayString((u8*)" C");
                    }
                    else if(temperature >= 30 && temperature < 35)
                    {
                        PWM0_voidGeneratePWM(75);
                        LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                        LCD_voidDisplayString((u8*)"Temp: ");
                        LCD_voidDisplayNumber((u16)temperature); 
                        LCD_voidDisplayString((u8*)" C");
                    }
                    else
                    {
                        PWM0_voidGeneratePWM(100); 
                        LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                        LCD_voidDisplayString((u8*)"Temp: ");
                        LCD_voidDisplayNumber((u16)temperature); 
                        LCD_voidDisplayString((u8*)" C");
                    }

                    _delay_ms(500); 
                    LCD_voidClear();
                    //...
                }
                else if (key=='2')// Door Control (Admin Only)
                {   
                    LCD_voidClear();
                    LCD_voidDisplayString((u8*)"Opening Door...");
                    
                    PWM1_voidGeneratePWM_channel1A(50, 7.5); // Rotate servo to open position (0 degrees → 7.5% duty cycle)
                    _delay_ms(3000); // Keep door open for 3 seconds
                    
                    LCD_voidClear();
                    LCD_voidDisplayString((u8*)"Closing Door...");
                    
                    PWM1_voidGeneratePWM_channel1A(50, 5); // Rotate servo to closed position (-90 degrees → 5% duty cycle)
                    _delay_ms(1000);// Wait for servo to complete motion
                    
                    LCD_voidClear();
                    
                }
                else if(key=='3')//control LED
                {
                    LCD_voidClear();
                    LCD_voidDisplayString((u8*)"1) GRN ON  2) OFF");
                    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
                    LCD_voidDisplayString((u8*)"3) RED ON  4) OFF");
                    LCD_voidGoToSpecificPosition(LCD_LINE_THREE, 0);
                    LCD_voidDisplayString((u8*)"5) BLU ON  6) OFF");
                    LCD_voidGoToSpecificPosition(LCD_LINE_FOUR, 0);
                    LCD_voidDisplayString((u8*)"7) YEL DIM");

                    do {
                    KPD_voidGetValue(&key);
                    } while (key == 0xFF);

                    switch (key)
                    {
                    case '1': // GRN ON
                    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_HIGH);
                    break;
                    case '2': // GRN OFF
                    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_LOW);
                    break;
                    case '3': // RED ON
                    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_HIGH);
                    break;
                    case '4': // RED OFF
                    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW);
                    break;
                    case '5': // BLU ON
                    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_HIGH);
                    break;
                    case '6': // BLU OFF
                    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_LOW);
                    break;
                    case '7': // YEL Dimming
                    LCD_voidClear();
                    LCD_voidDisplayString((u8*)"2)25%% 5)50%% 7)75%%");
                    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
                    LCD_voidDisplayString((u8*)"9)100%%");
                    do {
                        KPD_voidGetValue(&key);
                    } while (key == 0xFF);

                    if (key == '2') PWM0_voidGeneratePWM(25);
                    else if (key == '5') PWM0_voidGeneratePWM(50);
                    else if (key == '7') PWM0_voidGeneratePWM(75);
                    else if (key == '9') PWM0_voidGeneratePWM(100);
                    break;
                    }
                }
                else if(key=='4')//new user
                {
        if(users == 0){
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"Max users added");
            _delay_ms(1500);
            LCD_voidClear();
        }
        else {
            u8 newUserName[NumOfUsernameDigtis];
            u8 newUserPass[NumOfPassDigtis];
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"Add User");

            LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
            LCD_voidDisplayString((u8*)"Enter username:");
            for (int i = 0; i < NumOfUsernameDigtis; i++)
            {
                do{ KPD_voidGetValue(&key); }while(key==0xFF);
                LCD_voidGoToSpecificPosition(LCD_LINE_THREE,i);
                LCD_voidDisplayChar('*');
                _delay_ms(300);
                newUserName[i]=key;
            }
            LCD_voidClear();

            LCD_voidDisplayString((u8*)"Enter password:");
            for (int i = 0; i < NumOfPassDigtis; i++)
            {
                do{ KPD_voidGetValue(&key); }while(key==0xFF);
                LCD_voidGoToSpecificPosition(LCD_LINE_THREE,i);
                LCD_voidDisplayChar('*');
                _delay_ms(300);
                newUserPass[i]=key;
            }

            // Save to first empty user slot
            if(users == 3){
                for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser1[i] = newUserName[i];
                for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser1[i] = newUserPass[i];
            }
            else if(users == 2){
                for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser2[i] = newUserName[i];
                for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser2[i] = newUserPass[i];
            }
            else if(users == 1){
                for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser3[i] = newUserName[i];
                for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser3[i] = newUserPass[i];
            }

            users--;
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"User Added");
            _delay_ms(1500);
            LCD_voidClear();
        }
                }
                else if(key=='5')//Delet user
                {
                    LCD_voidClear();
                    LCD_voidDisplayString((u8*)"Del 1)U1 2)U2 3)U3");
                    do{ KPD_voidGetValue(&key); }while(key==0xFF);

                    if (key=='1' && users<3){
                        for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser1[i] = 0;
                        for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser1[i] = 0;
                        users++;
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"User1 Deleted");
                    }
                    else if (key=='2' && users<3){
                        for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser2[i] = 0;
                        for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser2[i] = 0;
                        users++;
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"User2 Deleted");
                    }
                    else if (key=='3' && users<3){
                        for(int i=0; i<NumOfUsernameDigtis; i++) valUsernameUser3[i] = 0;
                        for(int i=0; i<NumOfPassDigtis; i++) valPasswordUser3[i] = 0;
                        users++;
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"User3 Deleted");
                    }
                    else {
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"Invalid or Empty");
                    }

                    _delay_ms(1500);
                    LCD_voidClear();
                }
            }
       
        else if(key=='2') // <<<<< User >>>>>
        {
            u8 enteredUsername[NumOfUsernameDigtis];
            u8 enteredPassword[NumOfPassDigtis];
            u8 trial = 0;
            u8 found = 0;
            u8 i;

            // ======= Username check ========
            for(trial = 0; trial < 3; trial++)
            {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"Enter Username:");
                for(i = 0; i < NumOfUsernameDigtis; i++)
                {
                    do{ KPD_voidGetValue(&key); } while(key == 0xFF);
                    enteredUsername[i] = key;
                    LCD_voidDisplayChar('*');
                    _delay_ms(300);
                }

                {
                    u8 match1 = 1, match2 = 1, match3 = 1;
                    for(u8 j = 0; j < NumOfUsernameDigtis; j++) {
                        if(enteredUsername[j] != valUsernameUser1[j]) match1 = 0;
                        if(enteredUsername[j] != valUsernameUser2[j]) match2 = 0;
                        if(enteredUsername[j] != valUsernameUser3[j]) match3 = 0;
                    }
                    if(match1 || match2 || match3) {
                        found = 1;
                        break;
                    }
                    else
                    {
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"Wrong Username");
                        _delay_ms(1000);
                    }
                }
            }

            if(!found) {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"System Locked!");
                LED_voidOn(DIO_PORTB, DIO_PIN7, LED_FORWARD_CONNECTION); // Red LED ON
                DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);  // Buzzer ON
                _delay_ms(2000); 
                continue;
            }

            // ======= Password check ========
            trial = 0;
            found = 0;

            for(trial = 0; trial < 3; trial++)
            {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"Enter Password:");
                for(i = 0; i < NumOfPassDigtis; i++)
                {
                    do{ KPD_voidGetValue(&key); } while(key == 0xFF);
                    enteredPassword[i] = key;
                    LCD_voidDisplayChar('*');
                    _delay_ms(300);
                }

                {
                    u8 match1 = 1, match2 = 1, match3 = 1;
                    for(u8 j = 0; j < NumOfPassDigtis; j++) {
                        if(enteredPassword[j] != valPasswordUser1[j]) match1 = 0;
                        if(enteredPassword[j] != valPasswordUser2[j]) match2 = 0;
                        if(enteredPassword[j] != valPasswordUser3[j]) match3 = 0;
                    }
                    if(match1 || match2 || match3) {
                        found = 1;
                        break;
                    }
                    else
                    {
                        LCD_voidClear();
                        LCD_voidDisplayString((u8*)"Wrong Password");
                        _delay_ms(1000);
                    }
                }
            }

            if(!found) {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"System Locked!");
                LED_voidOn(DIO_PORTB, DIO_PIN7, LED_FORWARD_CONNECTION); // Red LED ON
                DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);  // Buzzer ON
                _delay_ms(2000); 
                continue;
            }

            // ======= User Menu ========
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"Welcome User");
            _delay_ms(1000);
            LCD_voidClear();

        while(1)
        {
            LCD_voidDisplayString((u8*)"1)Control Led");
            LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0);
            LCD_voidDisplayString((u8*)"2)Air condtion");
            do{ KPD_voidGetValue(&key); } while(key==0xFF);
            LCD_voidClear();

            if(key == '1')
            {
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"1) GRN ON  2) OFF");
                LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
                LCD_voidDisplayString((u8*)"3) RED ON  4) OFF");
                LCD_voidGoToSpecificPosition(LCD_LINE_THREE, 0);
                LCD_voidDisplayString((u8*)"5) BLU ON  6) OFF");
                LCD_voidGoToSpecificPosition(LCD_LINE_FOUR, 0);
                LCD_voidDisplayString((u8*)"7) YEL DIM");

                do {
                KPD_voidGetValue(&key);
                } while (key == 0xFF);

                switch (key)
                {
                case '1': // GRN ON
                DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_HIGH);
                break;
                case '2': // GRN OFF
                DIO_voidSetPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_LOW);
                break;
                case '3': // RED ON
                DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_HIGH);
                break;
                case '4': // RED OFF
                DIO_voidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW);
                break;
                case '5': // BLU ON
                DIO_voidSetPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_HIGH);
                break;
                case '6': // BLU OFF
                DIO_voidSetPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_LOW);
                break;
                case '7': // YEL Dimming
                LCD_voidClear();
                LCD_voidDisplayString((u8*)"2)25%% 5)50%% 7)75%%");
                LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
                LCD_voidDisplayString((u8*)"9)100%%");
                do {
                    KPD_voidGetValue(&key);
                } while (key == 0xFF);

                if (key == '2') PWM0_voidGeneratePWM(25);
                else if (key == '5') PWM0_voidGeneratePWM(50);
                else if (key == '7') PWM0_voidGeneratePWM(75);
                else if (key == '9') PWM0_voidGeneratePWM(100);
                break;
                }
            }
            else if(key == '2')
            {
                //....
                ADC_voidGetDigitalValue(ADC_CHANNEL_0,&adcValue); 
                temperature = (adcValue * 5.0 * 100) / 1024.0; 
                temperature=temperature/10;
                if(temperature < 20)
                {
                    PWM0_voidGeneratePWM(0); 
                    LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                    LCD_voidDisplayString((u8*)"Temp: ");
                    LCD_voidDisplayNumber((u16)temperature); 
                    LCD_voidDisplayString((u8*)" C");

                }
                else if(temperature >= 20 && temperature < 25)
                {
                    PWM0_voidGeneratePWM(25);
                    LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                    LCD_voidDisplayString((u8*)"Temp: ");
                    LCD_voidDisplayNumber((u16)temperature); 
                    LCD_voidDisplayString((u8*)" C");
                }
                else if(temperature >= 25 && temperature < 30)
                { 
                    PWM0_voidGeneratePWM(50); 
                    LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                    LCD_voidDisplayString((u8*)"Temp: ");
                    LCD_voidDisplayNumber((u16)temperature); 
                    LCD_voidDisplayString((u8*)" C");
                }
                else if(temperature >= 30 && temperature < 35)
                {
                    PWM0_voidGeneratePWM(75);
                    LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                    LCD_voidDisplayString((u8*)"Temp: ");
                    LCD_voidDisplayNumber((u16)temperature); 
                    LCD_voidDisplayString((u8*)" C");
                }
                else
                {
                    PWM0_voidGeneratePWM(100); 
                    LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
                    LCD_voidDisplayString((u8*)"Temp: ");
                    LCD_voidDisplayNumber((u16)temperature); 
                    LCD_voidDisplayString((u8*)" C");
                }

                _delay_ms(500); 
                LCD_voidClear();
                //...
            }
            else
            {
                LCD_voidDisplayString((u8*)"Invalid Option");
                _delay_ms(1000);
                LCD_voidClear();
            }
            }
        }
            
    } 
             
    }
}

        




    


//     while (trial < 3) {


//         for (i = 0; i < 4; i++) {
//             do {
//                 KPD_voidGetValue(&key);
//             } while (key == 0xFF);
            
//             enteredPass[i] = key;
//             LCD_voidDisplayChar('*');
//             _delay_ms(300);
//         }
//         enteredPass[4] = '\0';

//         if (enteredPass[0] == '5' && enteredPass[1] == '5' && enteredPass[2] == '5' && enteredPass[3] == '5') {
//             LED_voidOn(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION); // Green LED on
//             LCD_voidClear();
//             LCD_voidDisplayString((u8*)"Welcome");
//             _delay_ms(5000);
//             LED_voidOff(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION);
//             break;
//         } else {
//             trial++;
//             LCD_voidClear();
//             LCD_voidDisplayString((u8*)"Wrong Password");
//             _delay_ms(1000);
//         }
//     }

//     if (trial == 3) {
//         LCD_voidClear();
//         LCD_voidDisplayString((u8*)"ALARM!");
//         while (1) {
//             LED_voidToggle(DIO_PORTB, DIO_PIN7 ); // Red LED blink
//             DIO_voidSetPinValue(DIO_PORTA, DIO_PIN2, DIO_PIN_HIGH); // Buzzer on
//             _delay_ms(300);
//             DIO_voidSetPinValue(DIO_PORTA, DIO_PIN2, DIO_PIN_LOW); // Buzzer off
//             _delay_ms(300);
//         }
//     }

//     while (1);
// }









/*
    // u8 val[]={'Y','H','G'};
    u8 val[] ="Youssef Hassan";
    EEPROM_voidInit();
    EEPROM_voidWritePage(0,16,val);
    EEPROM_voidReadPage(0,16,val);
    LCD_voidInit();
    for (int i = 0; i < 14; i++)
    {
        LCD_voidGoToSpecificPosition(2,LCD_LINE_TWO);
        LCD_voidDisplayChar(val[i]);
        
    }
    



=====================
<<< code PWM  >>>
int main(void)
{
    DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT) ; // oc0
    DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN6,DIO_PIN_INPUT);
    LED_voidInit(DIO_PORTA,DIO_PIN4);
    LED_voidOn(DIO_PORTA,DIO_PIN4,LED_FORWARD_CONNECTION);
    PWM0_voidInit();
    PWM0_voidGeneratePWM(100);                          


    while (1)
    {

      
    }
    return 0;
}






task
هتكتب dc motor ب :
pwm
dion b8bh








    DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT) ; //OC0
    DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT) ; 
    DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT) ; 

    // DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
    PWM0_voidInit();
    PWM0_voidGeneratePWM(5);
    DIO_voidSetPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_HIGH);
    DIO_voidSetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);



-------------------------------------

<<<<<code fan and temretcher>>>>>


// #include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GI_interface.h"
// #include "EXTI_interface.h"
// #include "SSD_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
// #include "KPD_interface.h"
#include "TMR0_interface.h"
#include "LED_interface.h"
#include "PWM0_interface.h"
#include "PWM1_interface.h"

#include <util/delay.h>
int main(void)
{
    u16 adcValue;
    f32 temperature;


    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT); 
    ADC_voidInit(ADC_REFERENCE_AVCC);
    PWM0_voidInit();
    LCD_voidInit();

    while(1)
    {
        ADC_voidGetDigitalValue(ADC_CHANNEL_0,&adcValue); 
        temperature = (adcValue * 5.0 * 100) / 1024.0; 
        temperature=temperature/10;
        if(temperature < 20)
        {
            PWM0_voidGeneratePWM(0); 
            LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
            LCD_voidDisplayString("Temp: ");
            LCD_voidDisplayNumber((u16)temperature); 
            LCD_voidDisplayString(" C");

        }
        else if(temperature >= 20 && temperature < 25)
        {
            PWM0_voidGeneratePWM(25);
            LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
            LCD_voidDisplayString("Temp: ");
            LCD_voidDisplayNumber((u16)temperature); 
            LCD_voidDisplayString(" C");
        }
        else if(temperature >= 25 && temperature < 30)
        {
            PWM0_voidGeneratePWM(50); 
            LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
            LCD_voidDisplayString("Temp: ");
            LCD_voidDisplayNumber((u16)temperature); 
            LCD_voidDisplayString(" C");
        }
        else if(temperature >= 30 && temperature < 35)
        {
            PWM0_voidGeneratePWM(75);
            LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
            LCD_voidDisplayString("Temp: ");
            LCD_voidDisplayNumber((u16)temperature); 
            LCD_voidDisplayString(" C");
        }
        else
        {
            PWM0_voidGeneratePWM(100); 
            LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
            LCD_voidDisplayString("Temp: ");
            LCD_voidDisplayNumber((u16)temperature); 
            LCD_voidDisplayString(" C");
        }

        _delay_ms(500); 
        LCD_voidClear();

    }
}








---------------------------------------_

    <<<<<<assinment 1 (lcd)>>>>>>> doun
// #include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GI_interface.h"
// #include "EXTI_interface.h"
// #include "SSD_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "KPD_interface.h"
#include "TMR0_interface.h" 
#include "LED_interface.h"
#include "PWM0_interface.h"
#include "PWM1_interface.h"
#include "UART_interface.h"
#include "SPI_interface.h"
#include "TWI_interface.h"

#include <util/delay.h>

int main(void) {
    u8 i, key, trial = 0;
    u8 enteredPass[5];
    
    // Green LED for door open
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN4, DIO_PIN_OUTPUT);
    // Red LED for alarm
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);
    // Buzzer
    DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN6, DIO_PIN_OUTPUT);

    LED_voidOff(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION);
    LED_voidOff(DIO_PORTA, DIO_PIN1, LED_FORWARD_CONNECTION);
    DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);

    LCD_voidInit();
    KPD_voidInit();

    while (trial < 3) {
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"Enter Password:");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);

        for (i = 0; i < 4; i++) {
            do {
                KPD_voidGetValue(&key);
            } while (key == 0xFF);
            
            enteredPass[i] = key;
            LCD_voidDisplayChar('*');
            _delay_ms(300);
        }
        enteredPass[4] = '\0';

        if (enteredPass[0] == '1' && enteredPass[1] == '0' && enteredPass[2] == '7' && enteredPass[3] == '5') {
            LED_voidOn(DIO_PORTA, DIO_PIN4, LED_FORWARD_CONNECTION); // Green LED on
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"Welcome");
            _delay_ms(5000);
            LED_voidOff(DIO_PORTA, DIO_PIN4, LED_FORWARD_CONNECTION);
            break;
        } else {
            trial++;
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"Wrong Password");
            _delay_ms(1000);
        }
    }

    if (trial == 3) {
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"ALARM!");
        while (1) {
            LED_voidToggle(DIO_PORTB, DIO_PIN7 ); // Red LED blink
            DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH); // Buzzer on
            _delay_ms(300);
            DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW); // Buzzer off
            _delay_ms(300);
        }
    }

    while (1);
}



--------------------------------_-----



<<<<code master>>>>

int main(void) {
    //CODE MASTER
    u8 LOCALU8DATA;
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT);//MOSI
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT);//MISO
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);//SCLK
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT);//ss

    LED_voidInit(DIO_PORTA,DIO_PIN4);
    SPI_voidInit();
    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_PIN_LOW);//SS=0
    
 while(1){
    SPI_voidTransceive(25,&LOCALU8DATA);
    if(7==LOCALU8DATA){
        LED_voidToggle(DIO_PORTA,DIO_PIN4);
    }
    _delay_ms(250);
 }


}










<<<<<?????? lcd محاولة للاسيمنت
// #include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GI_interface.h"
// #include "EXTI_interface.h"
// #include "SSD_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "KPD_interface.h"
#include "TMR0_interface.h"
#include "LED_interface.h"
#include "PWM0_interface.h"
#include "PWM1_interface.h"
#include "UART_interface.h"
#include "SPI_interface.h"

#include <util/delay.h>

int main(void) {
    u8 i, key, trial = 0;
    u8 password[]={'1','2','3', '4'};

    u8 enteredPass[5];
    
    // Green LED for door open
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_OUTPUT);
    // Red LED for alarm
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN1, DIO_PIN_OUTPUT);
    // Buzzer
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT);

    LED_voidOff(DIO_PORTA, DIO_PIN0, LED_FORWARD_CONNECTION);
    LED_voidOff(DIO_PORTA, DIO_PIN1, LED_FORWARD_CONNECTION);
    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN2, DIO_PIN_LOW);

    LCD_voidInit();
    KPD_voidInit();
    u8 count;
    while (trial < 3) {
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"Enter Password:");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
        for (int i = 0; i < 4; i++)
        {
            KPD_voidGetValue(&key);
            if (key !=password[i])
            {
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"worng password");
            LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
            _delay_ms(1000);
            count++;
            break;
            }
        }
        if (count==3)
        {
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"error");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);

        DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT)  ;//led red 
        DIO_voidSetPinValue (DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH) ;

        DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT)  ;//buzer
        DIO_voidSetPinValue (DIO_PORTC,DIO_PIN6,DIO_PIN_HIGH) ;
        }
        else{
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"correct password");
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);

        DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT)  ;//led grean 
        DIO_voidSetPinValue (DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH) ;
        }
        
    }

    while (1);
}

*/


