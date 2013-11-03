
   //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  void updateThingSpeak(String tsData)
  {
    if (client.connect(thingSpeakAddress, 80))
    {         
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(tsData.length());
      client.print("\n\n");
  
      client.print(tsData);
  
      lastConnectionTime = millis();
  
      if (client.connected())
      {
        Serial.println("Connecting to ThingSpeak...");
        Serial.println();
  
        failedCounter = 0;
      }
      else
      {
        failedCounter++;
  
        Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
        Serial.println();
      }
  
    }
    else
    {
      failedCounter++;
  
      Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
  
      lastConnectionTime = millis(); 
    }
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  
  void startEthernet()
  {
  
    client.stop();
  
    Serial.println("Connecting Arduino to network...");
    Serial.println();  
  
    delay(1000);
  
    // Connect to network amd obtain an IP address using DHCP
    if (Ethernet.begin(mac) == 0)
    {
      Serial.println("DHCP Failed, reset Arduino to try again");
      Serial.println();
    }
    else
    {
      Serial.println("Arduino connected to network using DHCP");
      Serial.println();
    }
  
    delay(1000);
  }
  

