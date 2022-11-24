# Timex Datalink Notebook Adapter emulator for Arduino

This project emulates the [Timex Datalink Notebook Adapter](https://user-images.githubusercontent.com/820984/187855124-5e84451c-f65b-4903-a9eb-f44ddde78eb1.png) for early [Timex Datalink watches](https://en.wikipedia.org/wiki/Timex_Datalink) in Arduino!  It is 100% compatible with the original Notebook Adapter, and works with vintage and modern computer hardware.

This project is not dependent on any specific Arduino board, although it is designed with the [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) in mind.  The Teensy LC has USB serial and an onboard LED, so the board can be used as-is without any external components:

![image](https://user-images.githubusercontent.com/820984/187859185-94f02df7-64f5-4bb3-bf00-12621f5f3b38.png)

## How does it work?

The early Datalink watches receives data over light, and the original intent was to take advantage of [a flashing electron beam on a CRT](https://www.youtube.com/watch?v=GCHHzw4s5W4&t=1168s).  Timex also offered a Notebook Adapter accessory intended for mobile users at the time, which replicates the data sent from a CRT using a single LED:

![image](https://user-images.githubusercontent.com/820984/203725872-8dc8ec66-57bd-444a-9c36-4138955c83e5.png)

The Notebook Adapter is a serial device with a proprietary protocol that was reverse-engineered for this project.  With the Arduino device present, the original [Timex Datalink software](https://assets.timex.com/html/data_link_software.html) can be configured to use the Notebook Adapter and send data to your watch:

![image](https://user-images.githubusercontent.com/820984/203725992-728c8586-0787-4d99-8226-c45812ee6a1b.png)
