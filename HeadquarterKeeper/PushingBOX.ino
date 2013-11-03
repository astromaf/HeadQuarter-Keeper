
  //////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////// 
  //Function for sending the request to PushingBox
  void sendToPushingBox(char devid[]){
    client.stop();
    if(DEBUG){
      Serial.println("connecting...");
    }
  
    if (client.connect(serverName, 80)) {
      if(DEBUG){
        Serial.println("connected");
      }
  
      if(DEBUG){
        Serial.println("sendind request");
      }
      client.print("GET /pushingbox?devid=");
      client.print(devid);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(serverName);
      client.println("User-Agent: Arduino");
      client.println();
    } 
    else {
      if(DEBUG){
        Serial.println("connection failed");
      }
    }
  }
  
  
  
