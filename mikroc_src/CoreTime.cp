#line 1 "D:/ACADS/EE188/Chron/mikroc_src/CoreTime.c"
#line 1 "d:/acads/ee188/chron/mikroc_src/coretime.h"
#line 1 "d:/acads/ee188/time/timelib.h"
#line 29 "d:/acads/ee188/time/timelib.h"
typedef struct
 {
 unsigned char ss ;
 unsigned char mn ;
 unsigned char hh ;
 unsigned char md ;
 unsigned char wd ;
 unsigned char mo ;
 unsigned int yy ;
 } TimeStruct ;
#line 43 "d:/acads/ee188/time/timelib.h"
extern long Time_jd1970 ;
#line 48 "d:/acads/ee188/time/timelib.h"
long Time_dateToEpoch(TimeStruct *ts) ;
void Time_epochToDate(long e, TimeStruct *ts) ;
#line 10 "d:/acads/ee188/chron/mikroc_src/coretime.h"
void Display_Time_Core(char *sec, char *min, char *hr, char *day, char *mn, char *year);
void Display_Time(char sec, char min, char hr, char week_day, char day, char mn, char year);
void Transform_Time(char *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year);
void Read_Time(char *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year);
void Write_Time(unsigned char min, unsigned char hours, unsigned char day, unsigned char dayofweek, unsigned char month, unsigned char year);

void GetTimeStruct(TimeStruct *time);
void MakeLastTwoChars(char *txt);
void DisplayTimeStruct(TimeStruct *time);
#line 7 "D:/ACADS/EE188/Chron/mikroc_src/CoreTime.c"
void Display_Time_Core(char *sec, char *min, char *hr, char *day, char *mn, char *year) {

 char txtSec[5] = "";
 char txtMin[5] = "";
 char txtHour[5] = "";
 char txtDay[5] = "";
 char txtMn[5] = "";
 char txtYear[5] = "";
 char txtDisplayRow1[16] = "";
 char txtDisplayRow2[16] = "";

 ShortToStr(*sec, txtSec);
 ShortToStr(*min, txtMin);
 ShortToStr(*hr, txtHour);
 ShortToStr(*day, txtDay);
 ShortToStr(*mn, txtMn);
 ShortToStr(*year, txtYear);

 MakeLastTwoChars(txtSec);
 MakeLastTwoChars(txtMin);
 MakeLastTwoChars(txtHour);
 MakeLastTwoChars(txtDay);
 MakeLastTwoChars(txtMn);
 MakeLastTwoChars(txtYear);

 strcat(txtDisplayRow1, "DATE: ");
 strcat(txtDisplayRow1, txtMn);
 strcat(txtDisplayRow1, "/");
 strcat(txtDisplayRow1, txtDay);
 strcat(txtDisplayRow1, "/");
 strcat(txtDisplayRow1, txtYear);

 strcat(txtDisplayRow2, "TIME: ");
 strcat(txtDisplayRow2, txtHour);
 strcat(txtDisplayRow2, ":");
 strcat(txtDisplayRow2, txtMin);
 strcat(txtDisplayRow2, ":");
 strcat(txtDisplayRow2, txtSec);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,1,txtDisplayRow1);
 Lcd_Out(2,1,txtDisplayRow2);
}

void Display_Time(char sec, char min, char hr, char week_day, char day, char mn, char year) {
 char *txt;
 switch(week_day){
 case 1: txt="Sun"; break;
 case 2: txt="Mon"; break;
 case 3: txt="Tue"; break;
 case 4: txt="Wed"; break;
 case 5: txt="Thu"; break;
 case 6: txt="Fri"; break;
 case 7: txt="Sat"; break;
 }

 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Lcd_Out(1,1,txt);
 Lcd_Chr(1, 6, (day / 10) + 48);
 Lcd_Chr(1, 7, (day % 10) + 48);
 Lcd_Chr(1, 9, (mn / 10) + 48);
 Lcd_Chr(1,10, (mn % 10) + 48);
 Lcd_Chr(1,12, (year / 10) + 48);
 Lcd_Chr(1,13, (year % 10) + 48);

 Lcd_Chr(2, 6, (hr / 10) + 48);
 Lcd_Chr(2, 7, (hr % 10) + 48);
 Lcd_Chr(2, 9, (min / 10) + 48);
 Lcd_Chr(2,10, (min % 10) + 48);
 Lcd_Chr(2,12, (sec / 10) + 48);
 Lcd_Chr(2,13, (sec % 10) + 48);
}

void Transform_Time(char *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
 *sec = ((*sec & 0x70) >> 4)*10 + (*sec & 0x0F);
 *min = ((*min & 0xF0) >> 4)*10 + (*min & 0x0F);
 *hr = ((*hr & 0x30) >> 4)*10 + (*hr & 0x0F);
 *week_day =(*week_day & 0x07);
 *day = ((*day & 0xF0) >> 4)*10 + (*day & 0x0F);
 *mn = ((*mn & 0x10) >> 4)*10 + (*mn & 0x0F);
 *year = ((*year & 0xF0)>>4)*10+(*year & 0x0F);
}

void Read_Time(char *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
 I2C1_Start();
 I2C1_Wr(0xD0);
 I2C1_Wr(0);
 I2C1_Repeated_Start();
 I2C1_Wr(0xD1);
 *sec =I2C1_Rd(1);
 *min =I2C1_Rd(1);
 *hr =I2C1_Rd(1);
 *week_day =I2C1_Rd(1);
 *day =I2C1_Rd(1);
 *mn =I2C1_Rd(1);
 *year =I2C1_Rd(0);
 I2C1_Stop();
}

void Write_Time(unsigned char min, unsigned char hours, unsigned char day, unsigned char dayofweek, unsigned char month, unsigned char year) {
 I2C1_Start();
 I2C1_Wr(0xD0);
 I2C1_Wr(0);
 I2C1_Wr(0x80);
 I2C1_Wr(min);
 I2C1_Wr(hours);

 I2C1_Wr(dayofweek);
 I2C1_Wr(day);
 I2C1_Wr(month);
 I2C1_Wr(year);
 I2C1_Stop();

 I2C1_Start();
 I2C1_Wr(0xD0);
 I2C1_Wr(0);
 I2C1_Wr(0);
 I2C1_Stop();
}

void GetTimeStruct(TimeStruct *time) {
 unsigned char local_sec, local_min1, local_hr, local_week_day, local_day, local_mn, local_year;
 char txtSec[5] = "";
 char txtMin[5] = "";
 char txtHour[5] = "";
 char txtDay[5] = "";
 char txtMn[5] = "";
 char txtYear[5] = "";
 char txtWeekDay[5] = "";

 Read_Time(&local_sec,&local_min1,&local_hr,&local_week_day,&local_day,&local_mn,&local_year);

 WordToHex(local_sec, txtSec);
 WordToHex(local_min1, txtMin);
 WordToHex(local_hr, txtHour);
 WordToHex(local_day, txtDay);
 WordToHex(local_mn, txtMn);
 WordToHex(local_year, txtYear);
 WordToHex(local_week_day, txtWeekDay);

 MakeLastTwoChars(txtSec);
 MakeLastTwoChars(txtMin);
 MakeLastTwoChars(txtHour);
 MakeLastTwoChars(txtDay);
 MakeLastTwoChars(txtMn);
 MakeLastTwoChars(txtYear);
 MakeLastTwoChars(txtWeekDay);

 local_sec = atoi(txtSec);
 local_min1 = atoi(txtMin);
 local_hr = atoi(txtHour);
 local_day = atoi(txtDay);
 local_mn = atoi(txtMn);
 local_year = atoi(txtYear);
 local_week_day = atoi(txtWeekDay);

 time->ss = local_sec;
 time->mn = local_min1;
 time->hh = local_hr;
 time->md = local_day;
 time->mo = local_mn;
 time->yy = local_year;
 time->wd = local_week_day;
}

void MakeLastTwoChars(char *txt){
 char txtSec[10];
 strcpy(txtSec, txt);
 txtSec[0] = txtSec[2];
 txtSec[1] = txtSec[3];
 txtSec[2] = '\0';
 strcpy(txt, txtSec);
}

void DisplayTimeStruct(TimeStruct *time) {
 Display_Time_Core(&(time->ss), &(time->mn), &(time->hh), &(time->md), &(time->mo), &(time->yy));
}
