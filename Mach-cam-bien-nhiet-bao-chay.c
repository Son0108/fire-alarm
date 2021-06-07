#include <Mach cam bien nhiet bao chay.h>
int16 read_adc_lap() // vong lap doc gia tri adc
{ 
   int8 i; 
   float32 adc2=0;                                  
   for (i=0;i<100;i++) // doc 100 lan de lay gia tri trung binh sau 100 lan doc 
   {
      delay_us(100); // tao thoi gian tre us 
      adc2=adc2+read_adc();    
   } 
   return (adc2/100); // he so nay em tinh lai nhe cho phu hop voi cau phan ap va dien ap 24V
}  
//======================================== 
void main() 
{ 
   setup_adc_ports(AN0_AN1_AN3); // thiet lap ADC su dung 3 kenh
   setup_adc(ADC_CLOCK_INTERNAL); // thiet lap xung nhip cho bo ADC là giao dong noi 
   lcd_init();
   lcd_gotoxy(1,1); // dua con tro LCD ve dong 1 cot 1;
   printf(lcd_putc,"HE THONG PHONG  ");
   lcd_gotoxy(1,2); 
   printf(lcd_putc,"  CHAY CHUA CHAY"); 
   delay_ms(1500);
   output_low(coi); // Tat coi
   output_low(rl); // Tat rl
//=======================================;
   while (true) // vong lap vo han
   {
      doc_cam_bien();
      if(canh_bao==0)
      {
         lcd_gotoxy(1,1); // dua con tro LCD ve dong 1 cot 1;
         printf(lcd_putc," NHIET DO PHONG ");
         ht_nhiet(nhiet);
         tao_tre(6);
      }
      if(canh_bao==1)
      {
         cht=0;
         lcd_gotoxy(1,1); // dua con tro LCD ve dong 1 cot 1;
         printf(lcd_putc,"    CANH BAO    ");
         if(bao_chay)
            hien_thi_chay();
         else
         {
            ht_nhiet(nhiet);
            tao_tre(6);
         }
      }
    }
}
//======================================== 
void kiem_tra()
{
   if(nhiet<30){
      output_low(rl);
         if(bao_coi==1)
         {
            output_low(coi);
            dang_bao_coi=0;
         }
      bao_chay=0;
      canh_bao=0;
   }
   if(nhiet>70)
   {
      if(xu_ly_chay==0) // khi chua duoc xu ly 
      {
         output_high(rl);
         if(bao_coi==0)
         {
            output_high(coi);
            dang_bao_coi=1;
         }
      }
      bao_chay=1;
      canh_bao=1;
   }
   else
   {
      if(xu_ly_chay==1)
      {
         xu_ly_chay=0;
         bao_chay=0;
      }
   }
}
//======================================== 
void hien_thi_chay()
{
   int8 xl;
   if(xu_ly_chay==0&&cht==0)
   {
      for(xl=6;xl>0;xl--)
      {
         lcd_gotoxy(1,2); // dua con tro LCD ve dong 1 cot 1;
         printf(lcd_putc,"CHAY - XU LY: %1u  ",xl);
         tao_tre2(2);
      }
   }
   if(xu_ly_chay==1&&cht==0)
   {
      for(xl=6;xl>0;xl--)
      {
         lcd_gotoxy(1,2); // dua con tro LCD ve dong 1 cot 1;
         printf(lcd_putc,"BAO XU LY LAI: %1u  ",xl);
         tao_tre2(2);
      }
   }
}
//======================================== 
void ht_nhiet(float n)
{
   lcd_gotoxy(1,2); // dua con tro LCD ve dong 1 cot 1;
   if(n<50)
   {
      printf(lcd_putc,"AN TOAN %3.0f",n);
   }
   else
   if(n<70)
   {
      printf(lcd_putc,"NGUY HIEM %3.0f",n);
      output_high(coi);
      tao_tre(1);
      tao_tre(1);
      tao_tre(1);
      output_low(coi);
   }
   else
   if(n>=70)
   {
      printf(lcd_putc,"CO CHAY %3.0f",n);
      tao_tre(1);
      tao_tre(1);
      tao_tre(1);
      tao_tre(1);
   }
   lcd_putc(0xdf);
   lcd_putc('C');
   printf(lcd_putc,"   ");
}
//======================================== 
void tao_tre2(int16 t)
{
   int16 i;
   int8 j;
   for(i=0;i<t;i++)
   {
      for(j=0;j<40;j++)
      {
         delay_ms(10);
         quet_phim();
      }
      doc_cam_bien();
      kiem_tra();
      if(canh_bao==0&&cht==0) break;
   }
}
//======================================== 
void tao_tre(int16 t)
{
   int16 i;
   int8 j;
   for(i=0;i<t;i++)
   {
      for(j=0;j<50;j++)
      {
         delay_ms(10);
         quet_phim();
      }
      doc_cam_bien();
      kiem_tra();
      if(canh_bao==1) break;
   }
}
//======================================== 
void doc_cam_bien()
{
   set_adc_channel(0); // chon kenh an0
   nhiet=1023-read_adc_lap(); // doc gia tri tu kenh an0
   nhiet=chuyen_doi_nhiet_ntc(nhiet);
}
//======================================== 
#define nn2 pin_B7
int1 np=0; // khai bao bit nho co phim nhan, np=0 co phim nhan, np=1 tat ca cac phim deu nha
//========================================
void quet_phim() // chuong trinh con quet nut nhan / quet phim nhan
{
   if (np)
   {
      if (!input(nn2))
      {
         np=0;
         //if(canh_bao>0)
         {
            
            if(cht==0)
            {
               bao_chay=0;
               canh_bao=0;
               kiem_tra();
               if(xu_ly_chay==0)
               {
                  xu_ly_chay=1; // bao da xu ly chay
                  output_low(rl);
                  output_low(coi);
                  bao_coi=0;
                  dang_bao_coi=0;
               }
               else
               {
                  xu_ly_chay=0;
               }
               if(bao_chay==0) // khi van con bao chay
               {
                  xu_ly_chay=0; // bao da xu ly chay
                  output_low(rl);
                  output_low(coi);
                  bao_coi=0;
                  dang_bao_coi=0;
               }
            }
          }
       }
   }
   else
   {
      if(input(nn2)==1)
      {
         np=1; // bao khong co nut nhan 
      }
   }
}
//======================================== 
float R;
float Thermister;
float c1 = 1.009249522e-03,c2 = 2.378405444e-04,c3 = 2.019202697e-07;
float chuyen_doi_nhiet_ntc(int16 analog_value)
{
   R=((10230000/analog_value) - 10000);/* calculate the resistance */
   Thermister = log(R);   /* calculate natural log of resistance */
   Thermister = 1 / (c1 + (c2 * Thermister) + (c3 * Thermister * Thermister * Thermister));
   Thermister = Thermister - 273.15;/* convert kelvin to °C */
   
   return Thermister;
}
