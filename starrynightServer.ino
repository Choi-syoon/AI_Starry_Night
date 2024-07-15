#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

// WiFi 네트워크 정보
const char* ssid = "Infinite_thinker_2.4G";
const char* password = "infinitethinker_0117";

// 서버 포트 번호
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  // WiFi 네트워크에 연결
  WiFi.begin(ssid, password);

  // 연결 완료될 때까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // 서버 시작
  server.begin();
}

void loop() {
  // 클라이언트와 연결 시도
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println("Received: " + data);
        if(data.equals("0")){
            digitalWrite(13, HIGH);
        }
        else if(data.equals("1")){
            digitalWrite(13, LOW);
        }
        else;
        // 클라이언트에 응답 보내기
        //client.println("Received: " + data);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
