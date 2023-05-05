# Smart Home
## Table of Contents

  1. [Introduction](#Introduction)
  2. [Components](#Components)
  3. [System Diagram](#System_Diagram)
  4. [Activity Diagram](#Activity_Diagram)
      1. [Normal system activity](#Normal_system_activity)
      2. [Alert check activity](#Alert_check_activity)


  
 ## Introduction <a name="Introduction"></a>
 
  Home automation is a growing trend in the 2010s that 
  allows owners to monitor their homes from afar. This project 
  is about designing a prototype for smart home submitted to IMT 
  School to get certification for completing the Embedded 
  Systems Diploma. 
  
  ## Components: <a name="Components"></a>
    1. ATmega32
    2. LCD
    3. Keypad
    4. LEDs
    5. DC motors(Fans)
    7. Temperature sensor
    8. EEPROM
    
    
 ## System Diagram <a name="System_Diagram"></a>

  ![image](https://user-images.githubusercontent.com/61395452/236462287-cd24844d-3b89-4c4b-b2a3-912ac073aa80.png)


 ## Activity Diagram <a name="Activity_Diagram"></a>
 
 #### 1. Normal system activity <a name="Normal_system_activity"></a>
 
   The system is divided into states each state has its own function. The 
  user can switch between states using keypad. Critical case has its own 
  handler and can interrupt the system in any case and when critical 
  case is done the system well send a message and go to main window.
  User can go to the previous window by clicking ‘B’ button, also can go 
  directly to the main window by clicking ‘S’ button.
  
  
  ![image](https://user-images.githubusercontent.com/61395452/236458785-68767c64-90e6-4ff2-a7b7-c111e3a769ed.png)
  
 #### 2. Alert check activity <a name="Alert_check_activity"></a>

  This check is done before managing keypad. If the temperature is more 
  than 45 the critical temperature an alert led will turn on as well as 
  a buzzer and the lcd will show alert message. The door will open to 
  facilitate the exit. When the temperature goes back to normal the 
  alert led and the buzzer will turn off and the door will go back to 
  the state before alert. Then welcome back message will be sent on lcd 
  and when the user presses any key the system will go to the main 
  window.
  
  
  ![image](https://user-images.githubusercontent.com/61395452/236459000-c0539254-075d-43fe-8a8b-3cea0dfda9ca.png)
