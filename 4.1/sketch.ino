#define LED1_PIN 5
#define LED2_PIN 6

String cmd = "";

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char chr = Serial.read();
    if (chr == '#') {
      processCommand(cmd);
      cmd = "";
    } else {
      cmd += chr;
    }
  }
}

void processCommand(String command) {
  int firstDel = command.indexOf(';');
  String commandType = command.substring(0, firstDel);
  String args = command.substring(firstDel + 1);

  if (commandType == "setBrightINT") {
    SetBrightINT(args);
  } else if (commandType == "setBrightFLOAT") {
    SetBrightFLOAT(args);
  } else if (commandType == "launchAnimation") {
    LaunchAnimation(args);
  }
}

void SetBrightINT(String args) {
  int firstDel = args.indexOf(';');
  int ledNum = args.substring(0, firstDel).toInt();
  int brightness = args.substring(firstDel + 1).toInt();

  if (ledNum == 1) {
    analogWrite(LED1_PIN, brightness);
  } else if (ledNum == 2) {
    analogWrite(LED2_PIN, brightness);
  }
}

void SetBrightFLOAT(String args) {
  int firstDel = args.indexOf(';');
  int ledNum = args.substring(0, firstDel).toInt();
  float brightness = args.substring(firstDel + 1).toFloat();
  int pwmValue = brightness * 255;

  if (ledNum == 1) {
    analogWrite(LED1_PIN, pwmValue);
  } else if (ledNum == 2) {
    analogWrite(LED2_PIN, pwmValue);
  }
}

void LaunchAnimation(String args) {
  int firstDel = args.indexOf(';');
  String animType = args.substring(0, firstDel);
  int duration = args.substring(firstDel + 1).toInt();

  if (animType == "separately") {
    runSeparateAnimation(duration);
  } else if (animType == "together") {
    runTogetherAnimation(duration);
  }
}

void runSeparateAnimation(int duration) {
  int halfDuration = duration / 2;
  for (int i = 0; i < halfDuration / 250; i++) {
    analogWrite(LED1_PIN, 255);
    analogWrite(LED2_PIN, 0);
    delay(250);
    analogWrite(LED1_PIN, 0);
    analogWrite(LED2_PIN, 255);
    delay(250);
  }
  analogWrite(LED1_PIN, 0);
  analogWrite(LED2_PIN, 0);
}

void runTogetherAnimation(int duration) {
  for (int i = 0; i < duration / 500; i++) {
    analogWrite(LED1_PIN, 255);
    analogWrite(LED2_PIN, 255);
    delay(250);
    analogWrite(LED1_PIN, 0);
    analogWrite(LED2_PIN, 0);
    delay(250);
  }
}
