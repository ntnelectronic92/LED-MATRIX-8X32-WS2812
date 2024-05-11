#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
const char *ssid = "WiFiA8";
const char *password = "ngoc931874";


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
 uint16_t rgbBitmap[] = {
    0xFF00, 0x00FF, 0xFFFF,  // Row 1: Red, Blue, White
    0x00FF, 0xFF00, 0xFFFF   // Row 2: Blue, Red, White
  };


typedef enum
{
  TEST,
  TEXT_ROLLING,
  IMAGE_VIEW,
  IMAGE_FULL_COLOR,

} MODE_LED;
MODE_LED modeLEDWS2812 = IMAGE_VIEW;
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
  matrix.setBrightness(100);
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
static const unsigned char PROGMEM image_Bluetooth_Idle_5x8_bits[] = {0x20,0xb0,0x68,0x30,0x30,0x68,0xb0,0x20};
static const unsigned char PROGMEM image_Lock_7x8_bits[] = {0x38,0x44,0x44,0xfe,0xfe,0xee,0xfe,0x7c};
static const unsigned char PROGMEM image_Unlock_7x8_bits[] = {0x38,0x44,0x40,0xf2,0xe6,0xce,0x9e,0x3c};
static const unsigned char PROGMEM image_Pin_star_7x7_bits[] = {0x92,0x54,0x38,0xfe,0x38,0x54,0x92};

void Matrix_Ws2812_Handle(void)
{
  switch (modeLEDWS2812)
  {
  case TEST:
    matrix.fillScreen(0);
    matrix.drawCircle(4,4,2, matrix.Color(255,0,0));
    matrix.drawPixel(0,0, matrix.Color(0,255,0));
    matrix.drawPixel(31,0, matrix.Color(0,255,255));
    matrix.show();
    delay(50);
    break;
  case TEXT_ROLLING:
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
   break;
  case IMAGE_VIEW:
    matrix.fillScreen(0);
    matrix.drawBitmap(25, 0, image_Bluetooth_Idle_5x8_bits, 5, 8, matrix.Color(0,255,0));
    matrix.drawBitmap(17, 0, image_Lock_7x8_bits, 7, 8, matrix.Color(0,255,255));
    matrix.drawBitmap(9, 0, image_Unlock_7x8_bits, 7, 8, matrix.Color(255,255,0));
    matrix.drawBitmap(1, 1, image_Pin_star_7x7_bits, 7, 7, matrix.Color(255,255,255));
    // matrix.drawBitmap(0,0,2,32,8)
    matrix.show();
    //delay(50);
   break;
  case IMAGE_FULL_COLOR:
   matrix.fillScreen(0);
    // Draw the RGB bitmap at coordinates (10, 10)
  matrix.drawRGBBitmap(0, 0, rgbBitmap, 3, 2);
   matrix.show();
  break;
  default:
    break;
  }
}

void WebServer_CallHTML(void)
{
  String message = "<html><head><meta charset='UTF-8'></head><body style='font-family:Arial, sans-serif; background-color:#f4f4f4; color:#333;'>";
  message += "<h1 style='color:#007BFF; text-align:center;'>Chào mừng đến Youtube channel NTN.ELECTRONIC </h1>";
  message += "<div id='content' style='max-width:1000px; margin:20px auto; padding:20px; background-color:#fff; border-radius:5px; box-shadow:0 0 10px rgba(0, 0, 0, 0.1);'>";
  message += "Chữ hiện tại: <span id='currentText' style='color:#00f;'>" + stringView + "</span><br>";
  message += "Chữ bạn muốn thay đổi: <input type='text' id='newText' style='padding:10px; margin-bottom:10px;'><br>";
  // Dropdown list for LED mode
  message += "Chế độ LED: <select id='ledModeSelect'>";
  // message += "  <option value='0' " + (modeLEDWS2812 == TEST ? "selected" : "") + ">Test Mode</option>";
  // message += "  <option value='1' " + (modeLEDWS2812 == TEXT_ROLLING ? "selected" : "") + ">Text Rolling Mode</option>";
  // message += "  <option value='2' " + (modeLEDWS2812 == IMAGE_VIEW ? "selected" : "") + ">Image View Mode</option>";
  // message += "  <option value='3' " + (modeLEDWS2812 == IMAGE_FULL_COLOR ? "selected" : "") + ">Full Color Mode</option>";
  message += "</select><br>";
  message += "<br>";
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
 //   stringView = server.arg("newText");
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
