#define F_CPU 8000000

#define BAT_THRESHOLD   512

int pwm = 1;
int solar = A1;
int batIn = A2;
int vdd = A3;
int vSolar, vDD, vBatIn;
int feedbackinputval;
//int pwmval;
float supplyVoltage, outputVoltage, ratio;
const float buck_out_volt = 8.8;
float ref_voltage = 5.11;
float input_voltage1 = 0;
float pwm_val;
int duty_cycle;

void setup() {
  TCCR0A = 2 << COM0A0 | 2 << COM0B0 | 3 << WGM00;
  TCCR0B = 0 << WGM02 | 1 << CS00;
  TCCR1 = 0 << PWM1A | 0 << COM1A0 | 1 << CS10;
  GTCCR = 1 << PWM1B | 2 << COM1B0;
  pinMode(pwm, OUTPUT);
  pinMode(solar, INPUT);
  pinMode(batIn, INPUT);
  pinMode(vdd, INPUT);
//  digitalWrite(pwm, LOW);
  pwm_val = 0;
  outputVoltage = 8.8;
//  buck_out_volt = 8.8;
  ref_voltage = 5.11;
  input_voltage1 = 0;
}

void loop() {
    
  input_voltage1 = analogRead(vdd);
  input_voltage1 = input_voltage1/1024;
  input_voltage1 = input_voltage1*ref_voltage*(973+4540)/973;
  if(input_voltage1 > (buck_out_volt + 0.2))
  {
    pwm_val = buck_out_volt/input_voltage1 * 255;
  }
  else
  {
    pwm_val = 255.0;
  }
  
  duty_cycle = (int)(abs(pwm_val));
  if(duty_cycle>255)
  {
    duty_cycle = 255;
  }
  if(duty_cycle<0)
  {
    duty_cycle = 0;
  }
  analogWrite(pwm, duty_cycle);
}
