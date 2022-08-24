```
World's easiest i2c Slave and Master

       Master                        Slave
   +--------------------+        +--------------------+
   |                    |        |                    |
   |3V3                 |        |3V3                 |
   |G22              G21+---+    |G22              G21+---+
   |G19              G25+-+ |    |G19              G25+-+ |
   |G23   G   G G     5V| | |    |G23   G   G G     5V| | |
   |G33   N 5 2 3    GND| | |    |G33   N 5 2 3    GND| | |
   |      D V 6 2       | | |    |      D V 6 2       | | |
   +--------------------+ | |    +--------------------+ | |
                          +-----------------------------+ |
                            |       SDA                   |
                            +-----------------------------+
                                    SCL
```
