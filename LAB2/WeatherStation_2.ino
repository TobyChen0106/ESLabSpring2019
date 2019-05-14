#include <SoftwareSerial.h>   // 引用程式庫

 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(10, 11); // RX, TX
char val = ' ';  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!"); //98D3:31:F569C9
  BT.begin(9600);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    Serial.print(val);
    Serial.print("\n");
    BT.write(val);
    BT.print(val);
    BT.println(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  while (BT.available()) {
    Serial.print("available\n");
    val = BT.read();
    Serial.print("read value");
    Serial.println(val);
    Serial.write(val);
  }
  delay(100);
}