/* Generated by Keyboard.java */

#include "virtual_keyboard_plus4.h"

#include "emux_api.h"

struct vkbd_key vkbd[] = {
   {7 ,0 ,27 ,33 ,7 ,7 ,0 ,0 ,0 ,-25 ,-25 ,-25 ,0 ,17 ,0 ,1 ,0 ,},  /* 0 Esc */
   {35 ,0 ,27 ,33 ,0 ,7 ,0 ,1 ,0 ,49 ,33 ,49 ,1 ,18 ,0 ,2 ,0 ,},  /* 1 1 */
   {63 ,0 ,27 ,33 ,3 ,7 ,0 ,2 ,0 ,50 ,34 ,50 ,2 ,18 ,1 ,3 ,0 ,},  /* 2 2 */
   {91 ,0 ,27 ,33 ,0 ,1 ,0 ,3 ,0 ,51 ,35 ,51 ,3 ,19 ,2 ,4 ,0 ,},  /* 3 3 */
   {119 ,0 ,27 ,33 ,3 ,1 ,0 ,4 ,0 ,52 ,36 ,52 ,4 ,20 ,3 ,5 ,0 ,},  /* 4 4 */
   {147 ,0 ,27 ,33 ,0 ,2 ,0 ,5 ,0 ,53 ,37 ,53 ,5 ,21 ,4 ,6 ,0 ,},  /* 5 5 */
   {175 ,0 ,27 ,33 ,3 ,2 ,0 ,6 ,0 ,54 ,38 ,54 ,6 ,22 ,5 ,7 ,0 ,},  /* 6 6 */
   {203 ,0 ,27 ,33 ,0 ,3 ,0 ,7 ,0 ,55 ,39 ,55 ,7 ,23 ,6 ,8 ,0 ,},  /* 7 7 */
   {231 ,0 ,27 ,33 ,3 ,3 ,0 ,8 ,0 ,56 ,40 ,56 ,8 ,24 ,7 ,9 ,0 ,},  /* 8 8 */
   {259 ,0 ,27 ,33 ,0 ,4 ,0 ,9 ,0 ,57 ,41 ,57 ,9 ,25 ,8 ,10 ,0 ,},  /* 9 9 */
   {287 ,0 ,27 ,33 ,3 ,4 ,0 ,10 ,0 ,48 ,48 ,48 ,10 ,26 ,9 ,11 ,0 ,},  /* 10 0 */
   {315 ,0 ,27 ,33 ,6 ,6 ,0 ,11 ,0 ,43 ,91 ,43 ,11 ,27 ,10 ,12 ,0 ,},  /* 11 Plus */
   {343 ,0 ,27 ,33 ,6 ,5 ,0 ,12 ,0 ,45 ,93 ,45 ,12 ,28 ,11 ,13 ,0 ,},  /* 12 Minus */
   {371 ,0 ,27 ,33 ,5 ,6 ,0 ,13 ,0 ,61 ,31 ,94 ,13 ,29 ,12 ,14 ,0 ,},  /* 13 Equals */
   {399 ,0 ,27 ,33 ,1 ,7 ,0 ,14 ,0 ,-2 ,-23 ,-23 ,14 ,30 ,13 ,15 ,0 ,},  /* 14 Home */
   {427 ,0 ,27 ,33 ,0 ,0 ,0 ,15 ,0 ,-3 ,-24 ,-24 ,15 ,31 ,14 ,16 ,0 ,},  /* 15 Del */
   {470 ,0 ,41 ,33 ,4 ,0 ,0 ,16 ,0 ,-4 ,-5 ,-5 ,16 ,32 ,15 ,17 ,0 ,},  /* 16 F1 */
   {7 ,35 ,40 ,33 ,2 ,7 ,1 ,0 ,1 ,-12 ,-12 ,-12 ,0 ,33 ,16 ,18 ,0 ,},  /* 17 Cntrl */
   {49 ,35 ,27 ,33 ,6 ,7 ,1 ,1 ,0 ,17 ,81 ,107 ,1 ,35 ,17 ,19 ,0 ,},  /* 18 Q */
   {77 ,35 ,27 ,33 ,1 ,1 ,1 ,2 ,0 ,23 ,87 ,115 ,2 ,36 ,18 ,20 ,0 ,},  /* 19 W */
   {105 ,35 ,27 ,33 ,6 ,1 ,1 ,3 ,0 ,5 ,69 ,113 ,3 ,37 ,19 ,21 ,0 ,},  /* 20 E */
   {133 ,35 ,27 ,33 ,1 ,2 ,1 ,4 ,0 ,18 ,82 ,114 ,4 ,38 ,20 ,22 ,0 ,},  /* 21 R */
   {161 ,35 ,27 ,33 ,6 ,2 ,1 ,5 ,0 ,20 ,84 ,99 ,5 ,39 ,21 ,23 ,0 ,},  /* 22 T */
   {189 ,35 ,27 ,33 ,1 ,3 ,1 ,6 ,0 ,25 ,89 ,119 ,6 ,40 ,22 ,24 ,0 ,},  /* 23 Y */
   {217 ,35 ,27 ,33 ,6 ,3 ,1 ,7 ,0 ,21 ,85 ,120 ,7 ,41 ,23 ,25 ,0 ,},  /* 24 U */
   {245 ,35 ,27 ,33 ,1 ,4 ,1 ,8 ,0 ,9 ,73 ,98 ,8 ,42 ,24 ,26 ,0 ,},  /* 25 I */
   {273 ,35 ,27 ,33 ,6 ,4 ,1 ,9 ,0 ,15 ,79 ,121 ,9 ,43 ,25 ,27 ,0 ,},  /* 26 O */
   {301 ,35 ,27 ,33 ,1 ,5 ,1 ,10 ,0 ,16 ,80 ,111 ,10 ,44 ,26 ,28 ,0 ,},  /* 27 P */
   {329 ,35 ,27 ,33 ,7 ,0 ,1 ,11 ,0 ,0 ,122 ,100 ,11 ,45 ,27 ,29 ,0 ,},  /* 28 At */
   {357 ,35 ,27 ,33 ,2 ,0 ,1 ,12 ,0 ,28 ,105 ,104 ,12 ,45 ,28 ,30 ,0 ,},  /* 29 Pound */
   {385 ,35 ,27 ,33 ,1 ,6 ,1 ,13 ,0 ,42 ,64 ,95 ,13 ,46 ,29 ,31 ,0 ,},  /* 30 Asterisk */
   {414 ,35 ,40 ,33 ,2 ,7 ,1 ,14 ,1 ,-12 ,-12 ,-12 ,15 ,46 ,30 ,32 ,0 ,},  /* 31 Cntrl */
   {470 ,35 ,41 ,33 ,6 ,0 ,1 ,15 ,0 ,-6 ,-7 ,-7 ,16 ,47 ,31 ,33 ,0 ,},  /* 32 F3 */
   {0 ,70 ,27 ,33 ,7 ,7 ,2 ,0 ,1 ,-14 ,-14 ,-14 ,17 ,48 ,32 ,34 ,0 ,},  /* 33 RunStop */
   {28 ,70 ,27 ,33 ,-1 ,-4 ,2 ,1 ,1 ,-15 ,-15 ,-15 ,17 ,49 ,33 ,35 ,0 ,},  /* 34 ShiftLock */
   {56 ,70 ,27 ,33 ,2 ,1 ,2 ,2 ,0 ,1 ,65 ,112 ,18 ,50 ,34 ,36 ,0 ,},  /* 35 A */
   {84 ,70 ,27 ,33 ,5 ,1 ,2 ,3 ,0 ,19 ,83 ,110 ,19 ,50 ,35 ,37 ,0 ,},  /* 36 S */
   {112 ,70 ,27 ,33 ,2 ,2 ,2 ,4 ,0 ,4 ,68 ,108 ,20 ,51 ,36 ,38 ,0 ,},  /* 37 D */
   {140 ,70 ,27 ,33 ,5 ,2 ,2 ,5 ,0 ,6 ,70 ,123 ,21 ,52 ,37 ,39 ,0 ,},  /* 38 F */
   {168 ,70 ,27 ,33 ,2 ,3 ,2 ,6 ,0 ,7 ,71 ,101 ,22 ,53 ,38 ,40 ,0 ,},  /* 39 G */
   {196 ,70 ,27 ,33 ,5 ,3 ,2 ,7 ,0 ,8 ,72 ,116 ,23 ,54 ,39 ,41 ,0 ,},  /* 40 H */
   {224 ,70 ,27 ,33 ,2 ,4 ,2 ,8 ,0 ,10 ,74 ,117 ,24 ,55 ,40 ,42 ,0 ,},  /* 41 J */
   {252 ,70 ,27 ,33 ,5 ,4 ,2 ,9 ,0 ,11 ,75 ,97 ,25 ,56 ,41 ,43 ,0 ,},  /* 42 K */
   {280 ,70 ,27 ,33 ,2 ,5 ,2 ,10 ,0 ,12 ,76 ,118 ,26 ,57 ,42 ,44 ,0 ,},  /* 43 L */
   {308 ,70 ,27 ,33 ,5 ,5 ,2 ,11 ,0 ,58 ,27 ,27 ,27 ,58 ,43 ,45 ,0 ,},  /* 44 Colon */
   {336 ,70 ,27 ,33 ,2 ,6 ,2 ,12 ,0 ,59 ,29 ,29 ,28 ,59 ,44 ,46 ,0 ,},  /* 45 SemiColon */
   {364 ,70 ,54 ,33 ,1 ,0 ,2 ,13 ,0 ,-16 ,-16 ,-16 ,30 ,60 ,45 ,47 ,0 ,},  /* 46 Return */
   {470 ,70 ,41 ,33 ,5 ,0 ,2 ,14 ,0 ,-8 ,-9 ,-9 ,32 ,61 ,46 ,48 ,0 ,},  /* 47 F5 */
   {0 ,105 ,27 ,33 ,5 ,7 ,3 ,0 ,1 ,-17 ,-17 ,-17 ,33 ,62 ,47 ,49 ,0 ,},  /* 48 Commodore */
   {28 ,105 ,40 ,33 ,7 ,1 ,3 ,1 ,1 ,-18 ,-18 ,-18 ,34 ,62 ,48 ,50 ,0 ,},  /* 49 LeftShift */
   {70 ,105 ,27 ,33 ,4 ,1 ,3 ,2 ,0 ,26 ,90 ,109 ,35 ,62 ,49 ,51 ,0 ,},  /* 50 Z */
   {98 ,105 ,27 ,33 ,7 ,2 ,3 ,3 ,0 ,24 ,88 ,125 ,36 ,62 ,50 ,52 ,0 ,},  /* 51 X */
   {126 ,105 ,27 ,33 ,4 ,2 ,3 ,4 ,0 ,3 ,67 ,124 ,37 ,62 ,51 ,53 ,0 ,},  /* 52 C */
   {154 ,105 ,27 ,33 ,7 ,3 ,3 ,5 ,0 ,22 ,86 ,126 ,38 ,62 ,52 ,54 ,0 ,},  /* 53 V */
   {182 ,105 ,27 ,33 ,4 ,3 ,3 ,6 ,0 ,2 ,66 ,127 ,39 ,62 ,53 ,55 ,0 ,},  /* 54 B */
   {210 ,105 ,27 ,33 ,7 ,4 ,3 ,7 ,0 ,14 ,78 ,106 ,40 ,62 ,54 ,56 ,0 ,},  /* 55 N */
   {238 ,105 ,27 ,33 ,4 ,4 ,3 ,8 ,0 ,13 ,77 ,103 ,41 ,62 ,55 ,57 ,0 ,},  /* 56 M */
   {266 ,105 ,27 ,33 ,7 ,5 ,3 ,9 ,0 ,44 ,60 ,60 ,42 ,62 ,56 ,58 ,0 ,},  /* 57 Comma */
   {294 ,105 ,27 ,33 ,4 ,5 ,3 ,10 ,0 ,46 ,62 ,62 ,43 ,63 ,57 ,59 ,0 ,},  /* 58 Period */
   {322 ,105 ,27 ,33 ,7 ,6 ,3 ,11 ,0 ,47 ,63 ,63 ,44 ,63 ,58 ,60 ,0 ,},  /* 59 Slash */
   {350 ,105 ,40 ,33 ,7 ,1 ,3 ,12 ,1 ,-19 ,-19 ,-19 ,45 ,63 ,59 ,61 ,0 ,},  /* 60 RightShift */
   {470 ,105 ,41 ,33 ,3 ,0 ,3 ,13 ,0 ,-10 ,-11 ,-11 ,47 ,66 ,60 ,62 ,0 ,},  /* 61 F7 */
   {96 ,140 ,236 ,33 ,4 ,7 ,4 ,0 ,0 ,-22 ,-22 ,-22 ,55 ,62 ,61 ,63 ,0 ,},  /* 62 Space */
   {350 ,140 ,27 ,33 ,0 ,6 ,4 ,1 ,0 ,-26 ,-26 ,-26 ,60 ,63 ,62 ,64 ,0 ,},  /* 63 CursorUp */
   {378 ,140 ,27 ,33 ,3 ,6 ,4 ,2 ,0 ,-20 ,-20 ,-20 ,60 ,64 ,63 ,65 ,0 ,},  /* 64 CursorDown */
   {406 ,140 ,27 ,33 ,0 ,5 ,4 ,3 ,0 ,-27 ,-27 ,-27 ,60 ,65 ,64 ,66 ,0 ,},  /* 65 CursorLeft */
   {434 ,140 ,27 ,33 ,3 ,5 ,4 ,4 ,0 ,-21 ,-21 ,-21 ,61 ,66 ,65 ,66 ,0 ,},  /* 66 CursorRight */
};

vkbd_key_array emux_get_vkbd(void) {
  return &vkbd[0];
}

int emux_get_vkbd_width(void) {
  return VKBD_WIDTH;
}

int emux_get_vkbd_height(void) {
  return VKBD_HEIGHT;
}

int emux_get_vkbd_size(void) {
  return NUM_KEYS;
}
