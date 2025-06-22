#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "webserver.h"
#include "userdata.h"
#include "matrix.h"

ESP8266WebServer server(80);

void init_WebServer(void)
{
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

void WebServer_CallHTML(void)
{
    String message = "<html><head><meta charset='UTF-8'></head><body style='font-family:Arial, sans-serif; background-color:#f4f4f4; color:#333;'>";
    message += "<h1 style='color:#007BFF; text-align:center;'>Chào mừng đến Youtube channel NTN.ELECTRONIC </h1>";
    message += "<div id='content' style='max-width:1000px; margin:20px auto; padding:20px; background-color:#fff; border-radius:5px; box-shadow:0 0 10px rgba(0, 0, 0, 0.1);'>";
    message += "Chữ hiện tại: <span id='currentText' style='color:#00f;'>" + stringView + "</span><br>";
    message += "Chữ bạn muốn thay đổi: <input type='text' id='newText' style='padding:10px; margin-bottom:10px;'><br>";
    message += "Chế độ LED: <select id='ledModeSelect'></select><br>";
    message += "<br>";
    message += "<button onclick='updateText()' style='background-color:#007BFF; color:#fff; padding:10px 20px; border:none; border-radius:5px; cursor:pointer;'>Thay đổi chữ</button>";
    message += "</div>";

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
        String newText = server.arg("newText");
        Save_UserData(newText);
    }

    String response = "{\"status\":\"success\", \"text\":\"" + stringView + "\"}";
    server.send(200, "application/json", response);
}

void WebServer_Handle(void)
{
    server.handleClient();
}