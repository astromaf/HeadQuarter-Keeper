 // Application to monitor, collect real-time data and interfacing with social networks 
 // from our "Robotics Club headquarter". http://www.aerobot.org.es/
 // This code reads the light and temperature values ​​from two sensors and sends them, 
 // through an ethernet module, to two servers to be plotted (ThingSpeak) and issue 
 // a warning via Twitter and email (PushingBox).
 
 // Twitter account for warnings issued:
 // Web page with dynamic graphs of light and temperature:
 // More info:
 
 // Based on previous work from ThingSpeak & PushingBox.
 // By MAF: http://madebyfrutos.wordpress.com/ . Madrid Octubre'13
 
  #include <SPI.h>
  #include <Ethernet.h>
  
  #define LDR_Pin  A2   //analog LDR pin Analog 2
  #define Temp_Pin A3   //analog Temp pin Analog 3
  #define Led_Pin  13   //Donde hay un led, hay alegria
  
  boolean estado=0;     // Logic state
  int LDR=0;            //ADC readings
  int Temp= 0;          // Temp readins
  
  /////////////////
  // MODIFY HERE //
  /////////////////
  byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x19 }; // Be sure this address is unique in your network
  
  //Your secret API key from servers
  char DEVID1[] = "vB3315C23E888FFE";        //Scenario : "LightON"
  char DEVID2[] = "v390B3DB2BA59796";        //Scenario : "LightOFF"
  String writeAPIKey = "LASEOTZVGU6DHM88";   // Api key to ThingsSpeak
 
  const int updateThingSpeakInterval = 10 * 1000; // Time interval to update ThingSpeak  
  boolean DEBUG = false;   // Debug mode
  //////////////
  //   End    //
  //////////////
  
  char thingSpeakAddress[] = "api.thingspeak.com"; // ThingSpeak Settings
  char serverName[] = "api.pushingbox.com";
  long lastConnectionTime = 0; 
  boolean lastConnected = false;
  int failedCounter = 0;
  
  // Initialize the Ethernet client library
  // with the IP address and port of the server 
  // that you want to connect to (port 80 is default for HTTP):
  EthernetClient client;
  
   ///////////////////////////SETUP//////////////////////////
  ///////////////////////////////////////////////////////////
  void setup() {
    Serial.begin(9600);
    pinMode(Led_Pin, OUTPUT);
    LDR= luz(); 
  
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // no point in carrying on, so do nothing forevermore:
      while(true);
    }
    else{
      Serial.println("Ethernet ready");
      // print the Ethernet board/shield's IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
  }
  
  ///////////////////////////LOOP////////////////////////////
  ///////////////////////////////////////////////////////////
  void loop()
  {   
    //Sensor feed
    Temp=temp();
    LDR= luz(); 
    
      //If light ON or OFF send a Twitter and email update
      if(LDR>850 && estado==0){    // Light ON
        estado=1;                  //Update state to "Light ON"
        if(DEBUG){Serial.println("ENCENDIDO");}
        sendToPushingBox(DEVID1); 
      } 
      if(LDR<500 && estado==1){   //Light OFF
        estado=0;                 //Update state to "Light OFF"
        if(DEBUG){Serial.println("APAGADO");}
        sendToPushingBox(DEVID2);
      }
      
     if(estado==1){digitalWrite(Led_Pin, HIGH);} // Check status   
     else{digitalWrite(Led_Pin, LOW);}
    
    //DEBUG part
    // this write the respons from Server.
    // You should see a "200 OK"
    if (client.available()) {
      char c = client.read();
      if(DEBUG){
        Serial.print(c);
      }
    }
  
    // if there's no net connection, but there was one last time
    // through the loop, then stop the client:
    if (!client.connected() && lastConnected) {
      if(DEBUG){
        Serial.println();
      }
      if(DEBUG){
        Serial.println("disconnecting.");
      }
      client.stop();
    }
    
    //Now send sensor readings to ThingSpeak sever for dynamic graphs
    if(!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
    {
      updateThingSpeak("field1="+String(Temp, DEC)+"&field2="+String(LDR, DEC));
    }
  
    // Check if Arduino Ethernet needs to be restarted
    if (failedCounter > 3 ) {
      startEthernet();
    }
    lastConnected = client.connected();
  }
  ///////////////////////////END LOOP////////////////////////
  ///////////////////////////////////////////////////////////
  
  
  
