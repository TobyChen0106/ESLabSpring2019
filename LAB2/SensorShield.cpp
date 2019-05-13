/* Includes */
#include "mbed.h"
#include "XNucleoIKS01A3.h"

/* Instantiate the expansion board */
static XNucleoIKS01A3 *mems_expansion_board = XNucleoIKS01A3::instance(D14, D15, D4, D5, A3, D6, A4);

/* Retrieve the composing elements of the expansion board */
static LIS2MDLSensor *magnetometer = mems_expansion_board->magnetometer;
static HTS221Sensor *hum_temp = mems_expansion_board->ht_sensor;
static LPS22HHSensor *press_temp = mems_expansion_board->pt_sensor;
static LSM6DSOSensor *acc_gyro = mems_expansion_board->acc_gyro;
static LIS2DW12Sensor *accelerometer = mems_expansion_board->accelerometer;
static STTS751Sensor *temp = mems_expansion_board->t_sensor;

/* Helper function for printing floats & doubles */
static char *print_double(char* str, double v, int decimalDigits=2)
{
  int i = 1;
  int intPart, fractPart;
  int len;
  char *ptr;

  /* prepare decimal digits multiplicator */
  for (;decimalDigits!=0; i*=10, decimalDigits--);

  /* calculate integer & fractinal parts */
  intPart = (int)v;
  fractPart = (int)((v-(double)(int)v)*i);

  /* fill in integer part */
  sprintf(str, "%i.", intPart);

  /* prepare fill in of fractional part */
  len = strlen(str);
  ptr = &str[len];

  /* fill in leading fractional zeros */
  for (i/=10;i>1; i/=10, ptr++) {
    if (fractPart >= i) {
      break;
    }
    *ptr = '0';
  }

  /* fill in (rest of) fractional part */
  sprintf(ptr, "%i", fractPart);

  return str;
}

/* Simple main function */
int main() {
  uint8_t id;
  float value1, value2;
  char buffer1[32], buffer2[32];
  int32_t axes[3];
  
  /* Enable all sensors */
  hum_temp->enable();
  press_temp->enable();
  temp->enable();
  magnetometer->enable();
  accelerometer->enable_x();
  acc_gyro->enable_x();
  acc_gyro->enable_g();
  
  printf("\r\n--- Starting new run ---\r\n");

  hum_temp->read_id(&id);
  printf("HTS221  humidity & temperature    = 0x%X\r\n", id);
  press_temp->read_id(&id);
  printf("LPS22HH  pressure & temperature   = 0x%X\r\n", id);
  temp->read_id(&id);
  printf("STTS751 temperature               = 0x%X\r\n", id);
  magnetometer->read_id(&id);
  printf("LIS2MDL magnetometer              = 0x%X\r\n", id);
  accelerometer->read_id(&id);
  printf("LIS2DW12 accelerometer            = 0x%X\r\n", id);
  acc_gyro->read_id(&id);
  printf("LSM6DSO accelerometer & gyroscope = 0x%X\r\n", id);
 
  while(1) {
    printf("\r\n");

    hum_temp->get_temperature(&value1);
    hum_temp->get_humidity(&value2);
    printf("HTS221: [temp] %7s C,   [hum] %s%%\r\n", print_double(buffer1, value1), print_double(buffer2, value2));
    
    press_temp->get_temperature(&value1);
    press_temp->get_pressure(&value2);
    printf("LPS22HH: [temp] %7s C, [press] %s mbar\r\n", print_double(buffer1, value1), print_double(buffer2, value2));

    temp->get_temperature(&value1);
    printf("STTS751: [temp] %7s C\r\n", print_double(buffer1, value1));

    magnetometer->get_m_axes(axes);
    printf("LIS2MDL [mag/mgauss]:  %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
    
    accelerometer->get_x_axes(axes);
    printf("LIS2DW12 [acc/mg]:  %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

    acc_gyro->get_x_axes(axes);
    printf("LSM6DSO [acc/mg]:      %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

    acc_gyro->get_g_axes(axes);
    printf("LSM6DSO [gyro/mdps]:   %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

//    wait(1.5);
  }
}
