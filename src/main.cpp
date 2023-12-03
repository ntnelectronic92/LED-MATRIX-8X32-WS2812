#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
const char *ssid = "YourNameWifi";
const char *password = "YourPasswordWifi";

#define PIN_DATA D4
#define COLUMNS 32
#define ROWS    8
#define WIDTH_FONT 6


void init_Matrix_Ws2812(void);
void init_UserData(void);
void init_WebServer(void);

void WebServer_Update(void);
void WebServer_CallHTML(void);
void WebServer_Handle(void);

String stringView = "Xin chao den voi kenh NTN.ELECTRONIC";
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN_DATA,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS,
  NEO_GRB            + NEO_KHZ800);
Preferences preferences;
int startView = matrix.width();
int indexColor = 0;
char charArray[100];
int16_t lengthTextForViewScroll;
const uint16_t colorsText[] =
{
  matrix.Color(204, 0, 204),
  matrix.Color(204, 204, 0),
  matrix.Color(0, 255, 255),
  matrix.Color(255, 10, 127),
  matrix.Color(127, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255, 99, 255)
};

ESP8266WebServer server(80);

// Init area
void init_Matrix_Ws2812(void)
{
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50);
  matrix.setTextColor(colorsText[0]);
  lengthTextForViewScroll = - (stringView.length() * WIDTH_FONT);
}
void init_UserData(void)
{
   preferences.begin("UserData", false);
   if(preferences.getString("stringView") != stringView)
   {
     stringView = preferences.getString("stringView");
     stringView.toCharArray(charArray, stringView.length());
     Serial.printf("Load string: %s \r\n",charArray);
   }   
}
void init_WebServer(void)
{
    // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  matrix.print("Wifi..");
  matrix.show();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting to WiFi...");
    delay(200);
  }
  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, WebServer_CallHTML);
  server.on("/update", HTTP_POST, WebServer_Update);
  server.begin();
}
// Handle area
void Save_UserData(String inputText)
{
     preferences.putString("stringView",inputText);
     inputText.toCharArray(charArray, inputText.length()+1);
     Serial.printf("Save string: %s \r\n",charArray);
}
void Matrix_Ws2812_Handle(void)
{
  matrix.fillScreen(0);
  matrix.setCursor(startView, 0);
  matrix.print(stringView);
  if (--startView < lengthTextForViewScroll)
  {
    startView = matrix.width();
    if (++indexColor >= 8) indexColor = 0;
    matrix.setTextColor(colorsText[indexColor]);
  }
  matrix.show();
  delay(50);
}

void WebServer_CallHTML(void)
{
  String message = "<html><head><meta charset='UTF-8'></head><body style='font-family:Arial, sans-serif; background-color:#f4f4f4; color:#333;'>";
  message += "<h1 style='color:#007BFF; text-align:center;'>Chào mừng đến Youtube channel NTN.ELECTRONIC </h1>";
  message += "<div id='content' style='max-width:1000px; margin:20px auto; padding:20px; background-color:#fff; border-radius:5px; box-shadow:0 0 10px rgba(0, 0, 0, 0.1);'>";
  message += "Chữ hiện tại: <span id='currentText' style='color:#00f;'>" + stringView + "</span><br>";
  message += "Chữ bạn muốn thay đổi: <input type='text' id='newText' style='padding:10px; margin-bottom:10px;'><br>";
  message += "<button onclick='updateText()' style='background-color:#007BFF; color:#fff; padding:10px 20px; border:none; border-radius:5px; cursor:pointer;'>Thay đổi chữ</button>";
  message += "</div>";

  // Add JavaScript
  message += "<script>";
  message += "function updateText() {";
  message += "  var newText = document.getElementById('newText').value;";
  message += "  var xhttp = new XMLHttpRequest();";
  message += "  xhttp.onreadystatechange = function() {";
  message += "    if (this.readyState == 4 && this.status == 200) {";
  message += "      var response = JSON.parse(this.responseText);";
  message += "      if (response.status === 'success') {";
  message += "        document.getElementById('currentText').innerText = response.text;";
  message += "      } else {";
  message += "        console.error('Update failed');";
  message += "      }";
  message += "    }";
  message += "  };";
  message += "  xhttp.open('POST', '/update', true);";
  message += "  xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
  message += "  xhttp.send('newText=' + newText);";
  message += "}";
  message += "</script>";

  message += "</body></html>";
  server.send(200, "text/html", message);
}



void WebServer_Update()
{
  if (server.hasArg("newText"))
  {
    stringView = server.arg("newText");
    lengthTextForViewScroll = - (stringView.length() * WIDTH_FONT);
    Save_UserData(stringView);
  }

  String response = "{\"status\":\"success\", \"text\":\"" + stringView + "\"}";
  server.send(200, "application/json", response);
}

void WebServer_Handle(void)
{
  server.handleClient();
}
void setup()
{
  Serial.begin(115200);
  init_UserData();
  init_Matrix_Ws2812();
  init_WebServer();
}

void loop()
{
  WebServer_Handle();
  Matrix_Ws2812_Handle();
}
