// ===== PIN DEFINITIONS =====
#define ENA 4    // Motor enable pin
#define IN1 16   // Motor direction 1  
#define IN2 17   // Motor direction 2

// ===== VARIABLES =====
unsigned long bootTime;
int taskCount = 0;
int failureCount = 0;
int recoveryCount = 0;
int successCount = 0;
bool taskRunning = false;
unsigned long motorStartTime = 0;

// ===== MOTOR CONTROL =====
void motorHardStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, LOW);
  Serial.println("[MOTOR] HARD STOP");
}

void motorForward(int speedPercent) {
  if (speedPercent > 100) speedPercent = 100;
  if (speedPercent < 0) speedPercent = 0;
  
  int pwmValue = map(speedPercent, 0, 100, 0, 255);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, pwmValue);
  
  Serial.print("[MOTOR] FORWARD at ");
  Serial.print(speedPercent);
  Serial.println("%");
  motorStartTime = millis();
}

void motorReverse(int speedPercent) {
  if (speedPercent > 100) speedPercent = 100;
  if (speedPercent < 0) speedPercent = 0;
  
  int pwmValue = map(speedPercent, 0, 100, 0, 255);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, pwmValue);
  
  Serial.print("[MOTOR] REVERSE at ");
  Serial.print(speedPercent);
  Serial.println("%");
  motorStartTime = millis();
}

void motorSoftStop() {
  Serial.println("[MOTOR] Soft stopping...");
  
  for (int speed = 100; speed >= 0; speed -= 10) {
    int pwmValue = map(speed, 0, 100, 0, 255);
    analogWrite(ENA, pwmValue);
    delay(50);
  }
  
  motorHardStop();
}

// ===== TASK SEQUENCES =====
void runBasicTask() {
  if (taskRunning) {
    Serial.println("[SYSTEM] Task already in progress!");
    return;
  }
  
  taskRunning = true;
  taskCount++;
  
  Serial.println("\n════════════════════════════════════════");
  Serial.print("  TASK #");
  Serial.println(taskCount);
  Serial.println("════════════════════════════════════════");
  
  // Phase 1: Start
  Serial.println("\n[PHASE 1] Starting forward...");
  motorForward(80);
  delay(2000);
  
  // Phase 2: Speed variation
  Serial.println("[PHASE 2] Adjusting speed...");
  motorForward(60);
  delay(1500);
  motorForward(90);
  delay(1500);
  
  // Phase 3: Simulated load
  Serial.println("[PHASE 3] Simulating load...");
  for (int i = 0; i < 3; i++) {
    Serial.print("  Load cycle ");
    Serial.println(i + 1);
    motorForward(70);
    delay(500);
    motorForward(85);
    delay(500);
  }
  
  // Random failure simulation (25% chance)
  bool simulateFailure = (random(0, 100) < 25);
  
  if (simulateFailure) {
    failureCount++;
    Serial.println("\n⚠️  FAULT DETECTED: Overload condition!");
    
    // Emergency response
    motorHardStop();
    delay(1000);
    
    Serial.println("🔄 Attempting recovery...");
    recoveryCount++;
    
    // Recovery sequence
    motorForward(40);
    delay(1000);
    motorSoftStop();
    
    Serial.println("✅ Recovery successful!");
  } else {
    // Normal completion
    Serial.println("\n[PHASE 4] Normal shutdown...");
    motorSoftStop();
    successCount++;
  }
  
  // Task completion
  Serial.println("\n────────────────────────────────────────");
  Serial.println("           TASK COMPLETE");
  Serial.println("────────────────────────────────────────");
  
  taskRunning = false;
  printStatistics();
}

// ===== STATISTICS & DISPLAY =====
void printStatistics() {
  Serial.println("\n📊 SYSTEM STATISTICS");
  Serial.println("────────────────────────────────────────");
  Serial.print("Total Tasks:       ");
  Serial.println(taskCount);
  Serial.print("Successful:        ");
  Serial.println(successCount);
  Serial.print("Failures:          ");
  Serial.println(failureCount);
  Serial.print("Recoveries:        ");
  Serial.println(recoveryCount);
  
  if (taskCount > 0) {
    Serial.print("Success Rate:      ");
    Serial.print((successCount * 100.0) / taskCount, 1);
    Serial.println("%");
  }
  
  Serial.print("System Uptime:     ");
  unsigned long uptime = (millis() - bootTime) / 1000;
  Serial.print(uptime / 60);
  Serial.print("m ");
  Serial.print(uptime % 60);
  Serial.println("s");
  Serial.println("────────────────────────────────────────\n");
}

void printHelp() {
  Serial.println("\n🎮 CONTROL PANEL");
  Serial.println("════════════════════════════════════════");
  Serial.println("Commands:");
  Serial.println("  r  - Run main actuator task");
  Serial.println("  f  - Forward (50%, 2s)");
  Serial.println("  b  - Reverse (50%, 2s)");
  Serial.println("  s  - Emergency STOP");
  Serial.println("  d  - Display statistics");
  Serial.println("  c  - Clear statistics");
  Serial.println("  h  - Show this help");
  Serial.println("════════════════════════════════════════\n");
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n╔══════════════════════════════════════╗");
  Serial.println("║     SMART ACTUATOR CONTROL SYSTEM    ║");
  Serial.println("╚══════════════════════════════════════╝");
  
  bootTime = millis();
  
  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Ensure motor is OFF
  motorHardStop();
  delay(500);
  
  // Initialize random seed
  randomSeed(analogRead(0));
  
  Serial.println("[SYSTEM] Ready for commands");
  Serial.println("[SYSTEM] Type 'h' for help\n");
}

// ===== MAIN LOOP =====
void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    
    // Clear buffer
    while (Serial.available()) {
      Serial.read();
    }
    
    switch (command) {
      case 'r':
      case 'R':
        runBasicTask();
        break;
        
      case 'f':
      case 'F':
        if (!taskRunning) {
          Serial.println("\n⏩ FORWARD (2 seconds)");
          motorForward(50);
          delay(2000);
          motorSoftStop();
        }
        break;
        
      case 'b':
      case 'B':
        if (!taskRunning) {
          Serial.println("\n⏪ REVERSE (2 seconds)");
          motorReverse(50);
          delay(2000);
          motorSoftStop();
        }
        break;
        
      case 's':
      case 'S':
        Serial.println("\n🛑 EMERGENCY STOP!");
        motorHardStop();
        taskRunning = false;
        break;
        
      case 'd':
      case 'D':
        printStatistics();
        break;
        
      case 'c':
      case 'C':
        taskCount = 0;
        failureCount = 0;
        recoveryCount = 0;
        successCount = 0;
        Serial.println("\n📈 Statistics cleared!");
        break;
        
      case 'h':
      case 'H':
      case '?':
        printHelp();
        break;
        
      default:
        if (command != '\n' && command != '\r') {
          Serial.print("\n❓ Unknown command: '");
          Serial.print(command);
          Serial.println("' - Type 'h' for help");
        }
        break;
    }
  }
  
  delay(10);
}
