# Timex Datalink Notebook Adapter emulator for Arduino

This is an Arduino project that emulates the [Timex Datalink Notebook Adapter](https://user-images.githubusercontent.com/820984/187855124-5e84451c-f65b-4903-a9eb-f44ddde78eb1.png) using Arduino.  This allows the original [Timex Datalink software](https://assets.timex.com/html/data_link_software.html) to send data to [Timex Datalink watches](https://en.wikipedia.org/wiki/Timex_Datalink).

![image](https://user-images.githubusercontent.com/820984/187858116-41eeaa2b-e134-4b31-98ab-60f1f2b0d362.png)

This project uses no external libraries and is not dependent on any specific hardware, although it is designed with the [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) in mind.  The Teensy LC has USB serial and an onboard LED, so the board can be used as-is without any external components:

![image](https://user-images.githubusercontent.com/820984/187859185-94f02df7-64f5-4bb3-bf00-12621f5f3b38.png)
