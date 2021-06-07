#include <16F877a.h>
#FUSES hs
#device ADC=10 // ADC 10 bit (0-1023)
#use delay(clock=20000000)
#define rl pin_e1 // dinh nghia cac chan RElay su dung
#define coi pin_d1

#define LCD_ENABLE_PIN  PIN_D0 // dinh nghia cac chan LCD su dung
#define LCD_RS_PIN      PIN_D2
#define LCD_RW_PIN      PIN_D3
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7 
#include <lcd.c> // dinh kem thu vien LCD

// khai bao cac bien cho 3 vi tri khac nhau
//---------------------------------------- 
float nhiet; // nhiet do do duoc cho vi tri 1
int1 canh_bao=0; // canh bao (=0 nêu khong co cam bien bao loi, = 1 nêu 1 trong 2 cam bien bao)
int1 bao_chay=0; // = 0 neu chua co chay, = 1 neu có chay
int1 xu_ly_chay=0; // = 0 neu chay chua duoc xu ly, = 1 neu da duoc xu ly
int1 bao_coi=0; // =0 neu chua xac nhan, = 1 neu da xac nhan
int1 dang_bao_coi=0; // =0 neu chua bao coi, = 1 neu da bao coi

//---------------------------------------- 
int8 cht=0; // chon hien thi dia diem chay
//======================================== 
void doc_cam_bien(); // khai bao các hàm
void tao_tre(int16 t);
void ht_nhiet(float n);
void kiem_tra();
void quet_phim();
void hien_thi_chay();
void tao_tre2(int16 t);
//---------------------------------------- 
//long tro_ntc;
#define tro_mac_dih 10000
float chuyen_doi_nhiet_ntc(int16 analog_value);
#define B_coefficient 3950.00      /* B coefficient of NTC Thermistor*/
#include <math.h>

