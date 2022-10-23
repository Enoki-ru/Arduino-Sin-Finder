
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {
  int i = analogRead(A0); 
  float A;
  static int num=0; // для циклов
  static int curr=0; // для запоминания номера сигнала
  static float max_time[2]={0,0};
  static float pi=3.14159265;
  num = num + 1;
  curr = curr + 1;  
  static float max_v[2]={0,0};
  static int max_num[2];
  float w0_hope=1000;
  float w0_experimental=w0_hope;
  float v = 5.0 * i / 1023.0 ;// Преобразовываем уровень i  в напряжение
  // Serial.print(v);  // выводим напряжение
  // Serial.println("В.\n");  // Выводим доп текст
  // Serial.print(num);  // выводим 
  // Serial.println(" - number \n");
  int max=1000;
  if (v>max_v[0])  // Запоминаем 2 максимальных значения в интервале max
  {
    max_v[0]=max_v[1];
    max_num[0]=max_num[1];
    max_time[0]=max_time[1];
    max_time[1]=millis();
    
    max_v[1]=v;
    max_num[1]=curr;
    
  }  
  if (num==max) // Экспорт на порт компа значения максимальных значений, и их номера
  {
    // Serial.print(max_v[0]);
    // Serial.println(" ");  
    // Serial.print(max_v[1]);  // выводим 
    // Serial.println(" Max V, В \n");
    float dt=max_time[1]-max_time[0];
    dt=round(dt);
    if (max_v[0]>=max_v[1])
      A=max_v[0];
    else
      A=max_v[1];
    Serial.print(A);
    Serial.println(" В - Амплитуда сигнала\n");
    int periods=round((dt)*w0_hope/(2*pi));
    float w0_experimental = periods*(2*pi)/dt;
    Serial.print(w0_experimental);
    Serial.println(" Гц - Частота сигнала\n");
    float tick=dt/periods;   // в миллисекундах длина одного периола
    Serial.print(tick);
    Serial.println(" мс - период одного сигнала\n");
    max_time[1]=max_time[1]-tick*floor(max_time[1]/tick);
    float phi=2*pi-w0_experimental*max_time[1];
    Serial.print(phi);
    Serial.println(" Радиан - Фаза сигнала\n");
    Serial.println(" ---------------------\n");
    num=0;
    max_v[0]=0;
    max_v[1]=0;
    max_time[0]=0;
    max_time[1]=0;
  }
  delay(1);
  //delay(10);                      // wait for a second
  // Serial.print(millis());
  // Serial.println(" - Time\n");
}
