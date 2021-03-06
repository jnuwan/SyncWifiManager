#ifndef SyncWifiManager_H
#define SyncWifiManager_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <Arduino.h>
#include <EEPROM.h>

class SyncWifiManager{
  private:

    String wifiEsid;
    String wifiEsPass;
    String content;
    ESP8266WebServer server;

    void readCredentials();
    bool connectWifi();
    void handleRoot();
    void handleScan();
    void handleSave();
    void setupAP();
    void createWebServer();

  public:

    SyncWifiManager();
    //~SyncWifiManager();
		void begin();
    void resetWiFiCredentials();

  const String HEADER="<!DOCTYPE html><html lang='en'><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>Synclones wifi Maneger</title><style>body{text-align:left;background-color:#000;color:#fff;}.ex{max-width:50%;min-width:400px;margin:auto;padding-top: 6px;}.d2{float:left;margin-left:8%;}.d3{margin-left:20%;}button{border:0;background-color:#ff6600;line-height:2.4rem;font-size:1.2rem;border-radius:.3rem;width:100%;}dt{font-weight:bold;}dd{margin:0;padding:0 0 0.5em 0;}.nw{width:100%;padding:0;}.nw li{list-style:none;border-bottom:1px solid #212328;padding:15px 20px;}a{color:#fff;font-weight:700;text-decoration:none;}a:hover{color:#ff6600;text-decoration:none;}.pullr{float:right;}.lock{background:#1fa3ec;border-radius:3px;width:14px;height:10px;margin-top:10px;position:relative;}.lock:before{content:'';display:block;position:absolute;border:3px solid #1fa3ec;top:-8px;left:2px;width:4px;height:11px;border-radius:35px 35px 0 0;}.w1{display:inline-block;position:absolute;margin-left:-36px;}.w2{display:inline-block;position:absolute;margin-top:0;margin-left:-35px;}.o1{margin:-10px 0 0 14px;width:20px;height:0;}.wave{display:inline-block;border:5px solid transparent;border-top-color:#1fa3ec;border-radius:50%;border-style:solid;margin:2px;}.ws-3 .wv4.wave,.ws-2 .wv4.wave,.ws-2 .wv3.wave,.ws-1 .wv4.wave,.ws-1 .wv3.wave,.ws-1 .wv2.wave{border-top-color:#eee;}input{width:99%;}.msg{padding:20px;margin:20px 0;border:1px solid #eee;border-left-width:5px;border-left-color:#1fa3ec;text-align:left;}.msg.P{border-left-color:#5cb85c;}.msg.D{border-left-color:#dc3630;}.foot{text-align:center;}</style><script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;p = l.nextElementSibling.classList.contains('l');if(p)document.getElementById('p').focus();};</script></head><body class='ex'><div class='d1'><div class='d2'><img src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABwAAAAzCAYAAACE92h3AAAC0UlEQVRYhb3XQWjTUBgH8E9liBMcKHjwIriLiicLIsKQOaXu0K4gi6xzUqOGdYjbzEEYjHmYwiwrcxZmQRyICk5PszDo6k4lZZB0jOwjjckUhrgdhPUgzKH4eYrMNbRJ+5YPvkteyO/9H++RBMCmdF0/bhgGSpK0z26cWc3MzKDP56Ptvby83MscSyQSBTvMatM088wwRDxZDrO62udTsr3hvwscxxWdgJIkoStITtaTAKUTdYL5fD7q6+srOMYEIBKA4vF46SSdgrFYrCJIsSbZwniet1+RwcFB3QmoKErZJbUgEoDC4TCqqnrC9kbTNEdq2TRbIRKAurq6MJ/Pny+7FOl02vYMWq2q6vMS6MGp79uxSCSChmEEymJWZbNZW1TTtEOVUlnJdF1vcoRtrdXV1TOFQuGZ3Rg9bipJRQJQsvO0hoi8a6xc2UFWz87OujqjNWEv73d6h5EAlMvl2IG/Hp3VK4HMMIDK6ZiCei790FOwePfIZycgRet+MwEdYSxTvuoNOEvICh0eHkY3ID1pXa8JTKVS7kABiJS3/VWDa2tr+zs6OlyjNaXMZDLYerHZfdIPyfqq0Xg8jq/bj37xNOnAwABq1w988hQVRRHXb9b99BSNRqO4eXv3piv03b1Y1SAR7eJ53tudaxhGD8dxrtDNFzdGakLn5+fxsv+SK7QmEABgYmLCWxAAgLvS5hhlAo6Pj3sLSpLkLbiysuII/NZ/rMgElGW5wQk4PT3N5lMyrygVE96JXGX33VoJex9uNGRZ9gYM+i9gKpXyBgsEAjg3N7fz2NNQo9nd3Y1LS0sMsZ69Je/EjVt7NoLBIE5NTTH+kxIP/9iO+f1+HB0dRU3TzjHF/iTaMluhlpYWHBoaQtM02aYCACiqHxv/QReaURRFXFhYYA9ZRQKQcu3gV57nMZvN7hxkYaFQCCcnJ3cWsmpsbAwXFxffeIKxrr/qfdB3NwRdsAAAAABJRU5ErkJggg==' alt='SC' width='28' height='51'/></div><div class='d3'>Configure WiFi credentials<br>";
  const String END="</div><hr><div class='foot'>Powered by <a href='http://www.synclones.com/'>Synclones</a></div></body></html>";
};

#endif
