#include "SyncWifiManager.h"

SyncWifiManager::SyncWifiManager(){

}

void SyncWifiManager::begin(){
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  readCredentials();
  if (!connectWifi()){
    setupAP();
		unsigned long timeBegin = micros();
    while ((WiFi.status() != WL_CONNECTED)){
      delay(100);
      server.handleClient();
			if(wifiEsid.length() > 0 && wifiEsPass.length() > 0){
				if(connectWifi()){
					return;
				}
			}
    }
  }
}

void SyncWifiManager::readCredentials(){
  for (int i = 0; i < 32; ++i){
    wifiEsid += char(EEPROM.read(i));
  }
  for (int i = 32; i < 96; ++i){
    wifiEsPass += char(EEPROM.read(i));
  }
}

bool SyncWifiManager::connectWifi(){
  WiFi.begin(wifiEsid.c_str(), wifiEsPass.c_str());
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED){
      return true;
    }
    delay(200);
    c++;
  }
  return false;
}

void SyncWifiManager::setupAP(){
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP("sDevice", "password");
  createWebServer();
  // Start the server
  server.begin();
}

void SyncWifiManager::createWebServer(){
  {
    server.on("/", std::bind(&SyncWifiManager::handleRoot, this));
    server.on("/scan", std::bind(&SyncWifiManager::handleScan, this));
    server.on("/wifisave", std::bind(&SyncWifiManager::handleSave, this));
  }
}

void SyncWifiManager::handleRoot() {
  IPAddress ip = WiFi.softAPIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

  content = HEADER + "sHome device<br>IP: "+ ipStr +"</div></div><h3>&nbsp;</h3><div class='d1'>";
  content += "<form action='/scan' method='get'><button>Configure WiFi</button></form><br/>";
  content += "<h2>Chipset information</h3><hr><dl><dt>Chip ID</dt><dd>";
  content += String(ESP.getChipId(),HEX);
  content += "</dd><dt>Flash Chip ID</dt><dd>";
  content += (String)ESP.getFlashChipId();
  content += "</dd><dt>SDK version</dt><dd>";
  content += (String)system_get_sdk_version();
  content += "</dd><dt>Core version</dt><dd>";
  content += (String)ESP.getCoreVersion();
  content += "</dd><dt>Boot version</dt><dd>";
  content += (String)system_get_boot_version();
  content += "</dd><dt>Station MAC</dt><dd>";
  content += WiFi.macAddress();
  content += "</dd><dt>SSID</dt><dd>";
  content += (String)WiFi.SSID();
  content += "</dd><dt>Access Point IP</dt><dd>";
  content += WiFi.softAPIP().toString();
  content += "</dd><dt>BSSID</dt><dd>";
  content += (String)WiFi.BSSIDstr();
  content += "</dd><dt>Access Point MAC</dt><dd>";
  content += (String)WiFi.softAPmacAddress();
  content += "</dd></dl>";
  content += END;
  server.send(200, "text/html", content);
}

void SyncWifiManager::handleScan() {
  IPAddress ip = WiFi.softAPIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

  content = HEADER + "sHome device<br>IP: "+ ipStr +"</div></div><h3>&nbsp;</h3><div class='d1'>";
  content += "<div class='d1'><ul class='nw'>";

  int n = WiFi.scanNetworks();
  if (n == 0){
    content += "<li><a href='#'>No networks found!</a></li>";
  }
  else{
    for (int i = 0; i < n; ++i){
      // Print SSID and RSSI for each network found
      content += "<li><a href='#p' onclick='c(this)'>";
      content += WiFi.SSID(i);
      content += "</a><div class='pullr'>";
      if(!(WiFi.encryptionType(i) == ENC_TYPE_NONE))
        content += "<div class='w1'><div class='lock'></div></div>";
      int strenght = WiFi.RSSI(i);
      if(strenght > -55)
        strenght = 4;
      else if(strenght > -70)
        strenght = 3;
      else if(strenght > -90)
        strenght = 2;
      else
        strenght = 1;
      content += "<div class='w2'><div class='ws-";
      content += strenght;
      content += "' o1'><div class='wv4 wave'><div class='wv3 wave'><div class='wv2 wave'>";
      content += "</div></div></div></div></div></div>";
      delay(10);
    }
  }
  content += "</ul></div><hr><div class='d1'><form method='POST' action='wifisave'><div class='d1'><label for='s'>SSID</label>";
  content += "<input id='s' name='s' maxlength='32' type='text' placeholder='SSID'></div><br><div class='d1'><label for='p'>Password</label>";
  content += "<input id='p' name='p' maxlength='64' type='password' placeholder='password'></div><br><button type='submit'>Save</button></form>";
  content += "<form style='margin-top: 10px;' action='/scan' method='get'><button>Refresh</button></form>";
  content += END;
  server.send(200, "text/html", content);
}

void SyncWifiManager::handleSave() {
  IPAddress ip = WiFi.softAPIP();
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  content = HEADER + "sHome device<br>IP: "+ ipStr +"</div></div><h3>&nbsp;</h3><div class='d1'>";
  if (server.method() == HTTP_POST){
    wifiEsid = server.arg("s");
    wifiEsPass = server.arg("p");
    if (wifiEsid.length() > 0 && wifiEsPass.length() > 0 && wifiEsid.length() < 33 && wifiEsPass.length() < 65){
      WiFi.mode(WIFI_AP);
      delay(100);
      if(connectWifi()){
        for (int i = 0; i < 96; ++i){
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < wifiEsid.length(); ++i){
          EEPROM.write(i, wifiEsid[i]);
        }
        for (int i = 0; i < wifiEsPass.length(); ++i){
          EEPROM.write(32 + i, wifiEsPass[i]);
        }
        EEPROM.commit();
        content += "<div class='msg P'><h3>WiFi Connected</h3><br><small>WiFi connection is established with ";
        content += wifiEsid;
        content += ".</small></div>";
      }
      else{
        content += "<div class='msg'><h3>Connection Fail</h3><br><small>Trying to connect ";
        content += wifiEsid;
        content += " WiFi network. But it failed. Please try again.</small></div>";
        content += "<form action='/scan' method='get'><button>Re-Search</button></form>";
      }
    }
    content += END;
    server.send(200, "text/html", content);
    delay(1500);
    ESP.reset();
  }
}

//public method for reset password
void SyncWifiManager::resetWiFiCredentials(){
  for (int i = 0; i < 10; ++i) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  ESP.reset();
}
