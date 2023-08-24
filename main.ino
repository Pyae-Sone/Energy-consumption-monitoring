#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* apSSID = "";
const char* apPassword = "";
const IPAddress apIP(192, 168, 10, 1); // Change this to your desired IP address

const int currentPin = A0;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(currentPin, INPUT);


  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // Specify subnet mask
  // Set the ESP8266 as an Access Point
  WiFi.softAP(apSSID, apPassword);

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float electricCurrent = analogRead(currentPin) * 0.0049; // Convert ADC reading to current (adjust as needed)

  String html = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Electricity Current Monitor</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
  <div class="container">
    <h1>Electricity Current Monitor</h1>
    <p>Current: <span id="currentValue">0 A</span></p>
    <canvas id="currentGraph" width="400" height="200"></canvas>
  </div>
  <script>
    const currentValueElement = document.getElementById('currentValue');
    const currentGraph = new Chart(document.getElementById('currentGraph').getContext('2d'), {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          label: 'Current (A)',
          data: [],
          borderColor: 'blue',
          backgroundColor: 'rgba(0, 0, 255, 0.1)',
          fill: true
        }]
      },
      options: {
        responsive: true,
        maintainAspectRatio: false,
        scales: {
          x: {
            type: 'linear',
            position: 'bottom'
          },
          y: {
            min: 0,
            max: 10 // Adjust as needed
          }
        }
      }
    });

    // Update the current value and graph with the C variable's value
    function updateData(current) {
      currentValueElement.textContent = current + ' A';
      currentGraph.data.labels.push('');
      currentGraph.data.datasets[0].data.push(current);
      currentGraph.update();
    }

    // Initialize with the C variable's value
    updateData(parseFloat(`)html" + String(electricCurrent) + R"html(`));

    // Simulate receiving data and updating the UI
    function simulateDataUpdate() {
      const randomCurrent = Math.random() * 10; // Random value between 0 and 10
      updateData(randomCurrent);
      setTimeout(simulateDataUpdate, 1000); // Update every 1 second
    }

    // Start simulating data updates
    simulateDataUpdate();
  </script>
</body>
</html>
)html";

  server.send(200, "text/html", html);
}
