#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ==========================================
// CONFIGURATION
// ==========================================
const char* ssid = "iPhone";
const char* password = "aassddff";

// Pins
const int LATCH_PIN = 2;  
const int CLOCK_PIN = 4;  
const int DATA_PIN  = 15; 

WebServer server(80);

// ==========================================
// BITMAP LIBRARY (80+ Shapes)
// ==========================================
const uint8_t SHAPES[][8] = {
    // --- 0-9: Geometric ---
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0: OFF
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // 1: FULL ON
    {0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C}, // 2: Circle
    {0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF}, // 3: Square
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 4: Diamond
    {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81}, // 5: X Shape
    {0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18}, // 6: Plus
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}, // 7: Diagonal 1
    {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}, // 8: Diagonal 2
    {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}, // 9: Checkerboard

    // --- 10-19: Icons ---
    {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00}, // 10: Heart
    {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C}, // 11: Smile
    {0x3C, 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C}, // 12: Sad
    {0x00, 0x01, 0x03, 0x16, 0x8C, 0xD8, 0x70, 0x20}, // 13: Checkmark
    {0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18}, // 14: Arrow Up
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18}, // 15: Arrow Down
    {0x10, 0x30, 0x70, 0xFF, 0xFF, 0x70, 0x30, 0x10}, // 16: Arrow Left
    {0x08, 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C, 0x08}, // 17: Arrow Right
    {0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18}, // 18: Hollow Diamond
    {0x7E, 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x81}, // 19: Letter A box

    // --- 20-29: Nature/Weather ---
    {0x00, 0x42, 0x3C, 0x42, 0x00, 0x42, 0x3C, 0x42}, // 20: Flowers
    {0x24, 0x5A, 0x24, 0x00, 0x42, 0x3C, 0x00, 0x00}, // 21: Sun Small
    {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81}, // 22: Star
    {0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0xDB, 0x81, 0x00}, // 23: Mushroom
    {0x08, 0x1C, 0x3E, 0x7F, 0x1C, 0x1C, 0x1C, 0x1C}, // 24: Tree
    {0x0C, 0x1E, 0x3E, 0xFE, 0xFE, 0x00, 0x00, 0x00}, // 25: Cloud
    {0x00, 0x00, 0x6C, 0xFE, 0xFE, 0x7C, 0x38, 0x10}, // 26: Heart Inverse
    {0x10, 0x38, 0x54, 0x10, 0x10, 0x54, 0x38, 0x10}, // 27: Snowflake
    {0x08, 0x14, 0x22, 0x41, 0x22, 0x14, 0x08, 0x00}, // 28: Diamond outline
    {0x3C, 0x42, 0x99, 0xBD, 0xBD, 0x99, 0x42, 0x3C}, // 29: Face Neutral

    // --- 30-39: Game/Fun ---
    {0x3C, 0x7E, 0xDB, 0xFF, 0xFF, 0xDB, 0x42, 0x3C}, // 30: Alien/Invader
    {0x00, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, 0x00}, // 31: Coin
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 32: Jewel
    {0x00, 0x66, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00}, // 33: Heart Filled
    {0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C}, // 34: Target
    {0x00, 0x18, 0x3C, 0x5A, 0x99, 0x18, 0x18, 0x18}, // 35: Sword
    {0x18, 0x3C, 0x7E, 0xDB, 0xFF, 0x24, 0x5A, 0xA5}, // 36: Ghost
    {0x3C, 0x7E, 0xFF, 0xFF, 0xE7, 0xC3, 0x81, 0x00}, // 37: Pacman Open
    {0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C}, // 38: Pacman Closed
    {0x81, 0xC3, 0xE7, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 39: Shield

    // --- 40-49: Islamic/Abstract ---
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 40: Rub El Hizb
    {0x3C, 0x66, 0x42, 0x42, 0x42, 0x42, 0x66, 0x3C}, // 41: Mosque Dome
    {0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00}, // 42: Chevron Left
    {0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x00}, // 43: Chevron Right
    {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00}, // 44: Stripes Horz
    {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}, // 45: Mesh
    {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00}, // 46: Box
    {0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00}, // 47: Diamond Filled
    {0x10, 0x10, 0x10, 0xFF, 0x10, 0x10, 0x10, 0x00}, // 48: Cross Thin
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, // 49: Dot

    // --- 50-59: Numbers 0-9 ---
    {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00}, // 50: Number 0
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00}, // 51: Number 1
    {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00}, // 52: Number 2
    {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00}, // 53: Number 3
    {0x0C, 0x1C, 0x3C, 0x6C, 0x7E, 0x0C, 0x0C, 0x00}, // 54: Number 4
    {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00}, // 55: Number 5
    {0x1C, 0x30, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00}, // 56: Number 6
    {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00}, // 57: Number 7
    {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00}, // 58: Number 8
    {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x0C, 0x38, 0x00}, // 59: Number 9

    // --- 60-69: More Patterns ---
    {0x81, 0x81, 0x42, 0x24, 0x18, 0x18, 0x18, 0x18}, // 60: Hourglass Top
    {0x18, 0x18, 0x18, 0x18, 0x24, 0x42, 0x81, 0x81}, // 61: Hourglass Bottom
    {0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF}, // 62: Fancy Box
    {0x00, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00}, // 63: Ring
    {0xDB, 0xDB, 0xDB, 0x00, 0xDB, 0xDB, 0xDB, 0x00}, // 64: Equal Bars
    {0x7E, 0x99, 0x99, 0x7E, 0x18, 0x18, 0x18, 0x00}, // 65: Lollipop
    {0x08, 0x08, 0x14, 0x22, 0x22, 0x41, 0x7F, 0x00}, // 66: Christmas Tree
    {0x7F, 0x41, 0x41, 0x41, 0x41, 0x41, 0x7F, 0x00}, // 67: Tall Box
    {0x00, 0x3C, 0x42, 0x81, 0x81, 0x42, 0x3C, 0x00}, // 68: Bullseye
    {0x18, 0x24, 0x42, 0xFF, 0x42, 0x24, 0x18, 0x00}, // 69: Diamond Cross

    // --- 70-79: More Fun Shapes ---
    {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00}, // 70: Horizontal Band
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, // 71: Vertical Band
    {0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3}, // 72: Double Vertical
    {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF}, // 73: Horizontal Stripes
    {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA}, // 74: Fine Checker
    {0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC, 0x33, 0x33}, // 75: Block Pattern
    {0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0, 0xF0}, // 76: Half Split
    {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // 77: Top Bottom
    {0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, // 78: Corners
    {0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00}  // 79: Filled Center
};

// Alphabet (A-Z)
const uint8_t ALPHABET[][8] = {
  {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // A
  {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00}, // B
  {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, // C
  {0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00}, // D
  {0x7E, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00, 0x00}, // E
  {0x7E, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00, 0x00}, // F
  {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3C, 0x00}, // G
  {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // H
  {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // I
  {0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00}, // J
  {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, // K
  {0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00, 0x00}, // L
  {0xC3, 0xE7, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3, 0x00}, // M
  {0xC3, 0xE3, 0xF3, 0xDB, 0xCF, 0xC7, 0xC3, 0x00}, // N
  {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // O
  {0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, // P
  {0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x0E, 0x00}, // Q
  {0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x00}, // R
  {0x3C, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x3C, 0x00}, // S
  {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // T
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // U
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // V
  {0xC3, 0xC3, 0xC3, 0xDB, 0xFF, 0xE7, 0xC3, 0x00}, // W
  {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}, // X
  {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, // Y
  {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00}  // Z
};

// ==========================================
// SYSTEM STATE
// ==========================================
// 999 = Global Demo Mode (Cycles everything)
// 888 = Animation Only Loop
// 777 = Shapes Only Loop
// 500 = Custom Text Display
int activeMode = 999; 

uint8_t frameBuffer[8] = {0};
unsigned long lastUpdate = 0;
int step = 0;
int demoIndex = 0;

// Custom Text
String customText = "HELLO";
int textScrollPos = 0;

// ==========================================
// CORE FUNCTIONS
// ==========================================

void applyMode8(const uint8_t input[8]) {
    memset(frameBuffer, 0, 8);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (input[i] & (1 << j)) frameBuffer[7 - j] |= (1 << (7 - i));
        }
    }
}

void sendData(uint8_t r, uint8_t c) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, r);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, ~c);
    digitalWrite(LATCH_PIN, HIGH);
}

void render() {
    for (int c = 0; c < 8; c++) {
        sendData(frameBuffer[c], (1 << c));
        delayMicroseconds(250);
        sendData(0, 0);
    }
}

// ==========================================
// TEXT DISPLAY FUNCTIONS
// ==========================================

void displayChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        applyMode8(ALPHABET[c - 'A']);
    } else if (c >= 'a' && c <= 'z') {
        applyMode8(ALPHABET[c - 'a']);
    } else if (c >= '0' && c <= '9') {
        applyMode8(SHAPES[50 + (c - '0')]);
    } else if (c == ' ') {
        applyMode8(SHAPES[0]); // Blank
    } else {
        applyMode8(SHAPES[49]); // Dot for unknown
    }
}

void scrollText() {
    unsigned long now = millis();
    if (now - lastUpdate > 500) {
        if (customText.length() > 0) {
            char currentChar = customText[textScrollPos % customText.length()];
            displayChar(currentChar);
            textScrollPos++;
            if (textScrollPos >= customText.length() * 2) textScrollPos = 0;
        }
        lastUpdate = now;
    }
}

// ==========================================
// ANIMATION LOGIC
// ==========================================

void runAnimations() {
    unsigned long now = millis();

    // --- GLOBAL DEMO MODE (999) ---
    if (activeMode == 999) {
        if (now - lastUpdate > 1000) { // Change every 1 second
            if (demoIndex < 50) {
                applyMode8(SHAPES[demoIndex]); // Show static shapes
            } else if (demoIndex == 50) {
                activeMode = 101; step = 0; // Trigger Gear
                lastUpdate = now; return;
            }
            demoIndex++;
            if (demoIndex > 50) demoIndex = 2; // Loop back to shapes
            lastUpdate = now;
        }
    }

    // --- AUTO SHAPES LOOP (777) ---
    else if (activeMode == 777) {
        if (now - lastUpdate > 800) {
            if (step < 2) step = 2;
            applyMode8(SHAPES[step]);
            step++;
            if (step > 49) step = 2;
            lastUpdate = now;
        }
    }

    // --- AUTO ANIMATION LOOP (888) ---
    else if (activeMode == 888) {
        if (step == 0) activeMode = 101; // Start Gear
        else if (step == 1) activeMode = 102; // Start Pacman
        else if (step == 2) activeMode = 103; // Start Musashi
        // Logic handles switching back to 888 after anim finishes
    }

    // --- SPECIFIC ANIMATIONS ---
    
    // Gear (101)
    else if (activeMode == 101) {
        if (now - lastUpdate > 150) {
            if (step % 2 == 0) { uint8_t g1[8]={0x3C,0x42,0x99,0xA5,0xA5,0x99,0x42,0x3C}; applyMode8(g1); }
            else { uint8_t g2[8]={0x3C,0x52,0x89,0xBD,0xBD,0x91,0x4A,0x3C}; applyMode8(g2); }
            step++;
            lastUpdate = now;
            // Return to Demo if running
            if (step > 20 && demoIndex > 0) { activeMode=999; demoIndex=51; step=0; } 
        }
    }
    // Pacman (102)
    else if (activeMode == 102) {
        if (now - lastUpdate > 200) {
            if (step % 2 == 0) applyMode8(SHAPES[37]); else applyMode8(SHAPES[38]);
            step++;
            lastUpdate = now;
        }
    }
    // Musashi (103)
    else if (activeMode == 103) {
        if (now - lastUpdate > 500) {
            int seq[] = {12, 20, 18, 0, 18, 7, 8}; int len = 7;
            if (step >= len) step = 0;
            applyMode8(ALPHABET[seq[step]]);
            step++;
            lastUpdate = now;
        }
    }
    // Rahman (104)
    else if (activeMode == 104) {
        if (now - lastUpdate > 500) {
            int seq[] = {17, 0, 7, 12, 0, 13}; int len = 6;
            if (step >= len) step = 0;
            applyMode8(ALPHABET[seq[step]]);
            step++;
            lastUpdate = now;
        }
    }
    // Custom Text Scroll (500)
    else if (activeMode == 500) {
        scrollText();
    }
}

// ==========================================
// WEB DASHBOARD
// ==========================================

void handleRoot() {
    String h = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    h += "<style>";
    h += "body{background:linear-gradient(135deg, #1a1a2e 0%, #16213e 100%);color:#e0e0e0;font-family:'Segoe UI',Tahoma,sans-serif;text-align:center;margin:0;padding:0;min-height:100vh;}";
    h += "h1{background:linear-gradient(90deg, #00e676 0%, #00b8d4 100%);padding:25px;margin:0;color:#000;font-size:28px;letter-spacing:2px;box-shadow:0 4px 6px rgba(0,0,0,0.3);}";
    h += ".container{max-width:1200px;margin:0 auto;padding:20px;}";
    h += ".sec{padding:15px 10px;text-align:left;color:#00e676;font-weight:bold;text-transform:uppercase;border-bottom:2px solid #00b8d4;margin-top:20px;font-size:14px;letter-spacing:1px;}";
    h += ".grid{display:grid;grid-template-columns:repeat(auto-fill, minmax(110px, 1fr));gap:10px;padding:15px 10px;}";
    h += "button{background:linear-gradient(145deg, #2c3e50, #34495e);color:#fff;border:2px solid #34495e;padding:14px;border-radius:8px;font-size:13px;cursor:pointer;transition:all 0.3s;box-shadow:0 2px 5px rgba(0,0,0,0.3);font-weight:600;}";
    h += "button:hover{transform:translateY(-2px);box-shadow:0 4px 8px rgba(0,230,118,0.4);border-color:#00e676;}";
    h += "button:active{background:#00e676;color:#000;transform:translateY(0);}";
    h += ".auto{background:linear-gradient(145deg, #6200ea, #7c4dff);border-color:#7c4dff;}";
    h += ".auto:hover{border-color:#b388ff;}";
    h += ".anim{background:linear-gradient(145deg, #ff6f00, #ff9100);border-color:#ff9100;}";
    h += ".anim:hover{border-color:#ffab40;}";
    h += ".stop{background:linear-gradient(145deg, #d32f2f, #f44336);color:#fff;font-weight:bold;width:calc(100% - 20px);margin:20px 10px;padding:18px;font-size:18px;border:none;box-shadow:0 4px 8px rgba(0,0,0,0.4);}";
    h += ".text-control{background:#1f1f1f;padding:20px;margin:20px 10px;border-radius:10px;border:2px solid #00b8d4;box-shadow:0 4px 8px rgba(0,0,0,0.3);}";
    h += "input[type='text']{width:calc(100% - 20px);padding:12px;font-size:16px;border:2px solid #00b8d4;border-radius:6px;background:#2c3e50;color:#fff;margin:10px 0;}";
    h += ".text-btn{background:linear-gradient(145deg, #00b8d4, #0097a7);border-color:#00b8d4;width:100%;margin-top:10px;padding:14px;font-size:15px;}";
    h += ".info{color:#b0b0b0;font-size:12px;margin-top:5px;font-style:italic;}";
    h += "</style>";
    h += "<script>";
    h += "function s(id){fetch('/set?id='+id);}";
    h += "function sendText(){var t=document.getElementById('txt').value.toUpperCase();if(t){fetch('/text?msg='+encodeURIComponent(t)).then(()=>{s(500);});}}";
    h += "</script></head><body><div class='container'>";
    
    h += "<h1>✨ MUSASHI STUDIO ✨</h1>";

    // Custom Text Input
    h += "<div class='text-control'>";
    h += "<div class='sec' style='border:none;margin:0;padding-bottom:10px;'>📝 Custom Text Display</div>";
    h += "<input type='text' id='txt' placeholder='Enter text (A-Z, 0-9)' maxlength='20'>";
    h += "<button class='text-btn' onclick='sendText()'>📤 Display Text</button>";
    h += "<div class='info'>Text will scroll on the matrix. Current: <span id='curr'>" + customText + "</span></div>";
    h += "</div>";

    // Auto Modes
    h += "<div class='sec'>🎬 Auto Modes</div><div class='grid'>";
    h += "<button class='auto' onclick='s(999)'>🌟 FULL DEMO</button>";
    h += "<button class='auto' onclick='s(777)'>🎨 ALL SHAPES</button>";
    h += "<button class='auto' onclick='s(888)'>🎭 ANIMATIONS</button>";
    h += "</div>";

    // Animations
    h += "<div class='sec'>🎬 Animations</div><div class='grid'>";
    h += "<button class='anim' onclick='s(101)'>⚙️ GEAR</button>";
    h += "<button class='anim' onclick='s(102)'>👾 PACMAN</button>";
    h += "<button class='anim' onclick='s(103)'>🤋 MUSASHI</button>";
    h += "<button class='anim' onclick='s(104)'>🌙 RAHMAN</button>";
    h += "</div>";

    // Geometric
    h += "<div class='sec'>📐 Geometric Shapes</div><div class='grid'>";
    h += "<button onclick='s(2)'>⭕ Circle</button><button onclick='s(3)'>⬜ Square</button>";
    h += "<button onclick='s(4)'>🔷 Diamond</button><button onclick='s(5)'>❌ X-Cross</button>";
    h += "<button onclick='s(6)'>➕ Plus</button><button onclick='s(9)'>🏁 Checker</button>";
    h += "<button onclick='s(7)'>📐 Diagonal \\</button><button onclick='s(8)'>📐 Diagonal /</button>";
    h += "<button onclick='s(18)'>◇ Hollow</button><button onclick='s(46)'>⬚ Box</button>";
    h += "<button onclick='s(63)'>🔘 Ring</button><button onclick='s(68)'>🎯 Bullseye</button>";
    h += "</div>";

    // Icons
    h += "<div class='sec'>🎯 Icons & Symbols</div><div class='grid'>";
    h += "<button onclick='s(10)'>❤️ Heart</button><button onclick='s(11)'>😊 Smile</button>";
    h += "<button onclick='s(12)'>😢 Sad</button><button onclick='s(13)'>✓ Check</button>";
    h += "<button onclick='s(14)'>⬆️ Up</button><button onclick='s(15)'>⬇️ Down</button>";
    h += "<button onclick='s(16)'>⬅️ Left</button><button onclick='s(17)'>➡️ Right</button>";
    h += "<button onclick='s(22)'>⭐ Star</button><button onclick='s(33)'>💖 Heart+</button>";
    h += "</div>";

    // Numbers
    h += "<div class='sec'>🔢 Numbers (0-9)</div><div class='grid'>";
    for(int i = 0; i < 10; i++) {
        h += "<button onclick='s(" + String(50 + i) + ")'># " + String(i) + "</button>";
    }
    h += "</div>";

    // Fun
    h += "<div class='sec'>🎮 Games & Fun</div><div class='grid'>";
    h += "<button onclick='s(30)'>👾 Invader</button><button onclick='s(31)'>💰 Coin</button>";
    h += "<button onclick='s(35)'>⚔️ Sword</button><button onclick='s(36)'>👻 Ghost</button>";
    h += "<button onclick='s(39)'>🛡️ Shield</button><button onclick='s(34)'>🎯 Target</button>";
    h += "<button onclick='s(37)'>👄 Pac O</button><button onclick='s(38)'>⚪ Pac C</button>";
    h += "</div>";

    // Nature
    h += "<div class='sec'>🌿 Nature & Weather</div><div class='grid'>";
    h += "<button onclick='s(20)'>🌸 Flower</button><button onclick='s(21)'>☀️ Sun</button>";
    h += "<button onclick='s(23)'>🍄 Mushroom</button><button onclick='s(24)'>🌲 Tree</button>";
    h += "<button onclick='s(25)'>☁️ Cloud</button><button onclick='s(27)'>❄️ Snow</button>";
    h += "</div>";

    // Patterns
    h += "<div class='sec'>🎨 Patterns & Textures</div><div class='grid'>";
    h += "<button onclick='s(44)'>═ Stripes H</button><button onclick='s(73)'>≡ Stripes</button>";
    h += "<button onclick='s(45)'>▦ Mesh</button><button onclick='s(74)'>▦ Fine Check</button>";
    h += "<button onclick='s(75)'>▦ Blocks</button><button onclick='s(76)'>▦ Half Split</button>";
    h += "<button onclick='s(70)'>▬ H-Band</button><button onclick='s(71)'>▐ V-Band</button>";
    h += "<button onclick='s(72)'>║ Double V</button><button onclick='s(78)'>◰ Corners</button>";
    h += "</div>";

    // Islamic
    h += "<div class='sec'>🕌 Islamic Art & Abstract</div><div class='grid'>";
    h += "<button onclick='s(40)'>✵ Rub El Hizb</button><button onclick='s(41)'>🕌 Mosque</button>";
    h += "<button onclick='s(42)'>‹ Chevron L</button><button onclick='s(43)'>› Chevron R</button>";
    h += "<button onclick='s(47)'>◆ Fill Diamond</button><button onclick='s(32)'>💎 Jewel</button>";
    h += "<button onclick='s(60)'>⌛ HG Top</button><button onclick='s(61)'>⏳ HG Bottom</button>";
    h += "</div>";

    h += "<button class='stop' onclick='s(0)'>⏹️ STOP DISPLAY</button>";
    h += "</div></body></html>";
    server.send(200, "text/html", h);
}

void setup() {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(100);
    MDNS.begin("musashi");

    server.on("/", handleRoot);
    server.on("/set", [](){
        activeMode = server.arg("id").toInt();
        step = 0; // Reset animation step
        demoIndex = 0; // Reset demo state
        textScrollPos = 0; // Reset text scroll
        if (activeMode < 100 && activeMode > 0) {
            applyMode8(SHAPES[activeMode]);
        }
        if (activeMode == 0) memset(frameBuffer, 0, 8);
        server.send(200, "text/plain", "OK");
    });
    server.on("/text", [](){
        if (server.hasArg("msg")) {
            customText = server.arg("msg");
            customText.toUpperCase();
            if (customText.length() == 0) customText = "HELLO";
            textScrollPos = 0;
            server.send(200, "text/plain", "Text set: " + customText);
        } else {
            server.send(400, "text/plain", "Missing msg parameter");
        }
    });
    server.begin();
    
    // Start with Full Demo Mode
    activeMode = 999;
    Serial.println(WiFi.localIP());
}

void loop() {
    server.handleClient();
    runAnimations();
    render();
}
