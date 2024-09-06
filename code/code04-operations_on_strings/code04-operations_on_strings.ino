

void setup() {
  Serial.begin(9600);
}

void loop() {
  endString = str1.length();
  strFixed = str1.substring(1, endString-1);

  //x
  commaIndex1 = strFixed.indexOf(',');
  xStr = strFixed.substring(0, commaIndex1);
  strFixed = strFixed.substring(commaIndex1+1);

  //y
  commaIndex2 = strFixed.indexOf(',');
  yStr = strFixed.substring(0, commaIndex2);

  //bt
  btStr = strFixed.substring(commaIndex2+1);

  Serial.print("x: ");
  Serial.print(xStr);
  Serial.print(" y: ");
  Serial.print(yStr);
  Serial.print(" bt: ");
  Serial.println(btStr);
}
