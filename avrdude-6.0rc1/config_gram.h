
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     K_READ = 258,
     K_WRITE = 259,
     K_READ_LO = 260,
     K_READ_HI = 261,
     K_WRITE_LO = 262,
     K_WRITE_HI = 263,
     K_LOADPAGE_LO = 264,
     K_LOADPAGE_HI = 265,
     K_LOAD_EXT_ADDR = 266,
     K_WRITEPAGE = 267,
     K_CHIP_ERASE = 268,
     K_PGM_ENABLE = 269,
     K_MEMORY = 270,
     K_PAGE_SIZE = 271,
     K_PAGED = 272,
     K_BAUDRATE = 273,
     K_BS2 = 274,
     K_BUFF = 275,
     K_CHIP_ERASE_DELAY = 276,
     K_CONNTYPE = 277,
     K_DEDICATED = 278,
     K_DEFAULT_PARALLEL = 279,
     K_DEFAULT_PROGRAMMER = 280,
     K_DEFAULT_SERIAL = 281,
     K_DEFAULT_BITCLOCK = 282,
     K_DESC = 283,
     K_DEVICECODE = 284,
     K_STK500_DEVCODE = 285,
     K_AVR910_DEVCODE = 286,
     K_EEPROM = 287,
     K_ERRLED = 288,
     K_FLASH = 289,
     K_ID = 290,
     K_IO = 291,
     K_LOADPAGE = 292,
     K_MAX_WRITE_DELAY = 293,
     K_MCU_BASE = 294,
     K_MIN_WRITE_DELAY = 295,
     K_MISO = 296,
     K_MOSI = 297,
     K_NUM_PAGES = 298,
     K_NVM_BASE = 299,
     K_OCDREV = 300,
     K_OFFSET = 301,
     K_PAGEL = 302,
     K_PARALLEL = 303,
     K_PARENT = 304,
     K_PART = 305,
     K_PGMLED = 306,
     K_PROGRAMMER = 307,
     K_PSEUDO = 308,
     K_PWROFF_AFTER_WRITE = 309,
     K_RDYLED = 310,
     K_READBACK_P1 = 311,
     K_READBACK_P2 = 312,
     K_READMEM = 313,
     K_RESET = 314,
     K_RETRY_PULSE = 315,
     K_SERIAL = 316,
     K_SCK = 317,
     K_SIGNATURE = 318,
     K_SIZE = 319,
     K_USB = 320,
     K_USBDEV = 321,
     K_USBSN = 322,
     K_USBPID = 323,
     K_USBPRODUCT = 324,
     K_USBVENDOR = 325,
     K_USBVID = 326,
     K_TYPE = 327,
     K_VCC = 328,
     K_VFYLED = 329,
     K_NO = 330,
     K_YES = 331,
     K_TIMEOUT = 332,
     K_STABDELAY = 333,
     K_CMDEXEDELAY = 334,
     K_HVSPCMDEXEDELAY = 335,
     K_SYNCHLOOPS = 336,
     K_BYTEDELAY = 337,
     K_POLLVALUE = 338,
     K_POLLINDEX = 339,
     K_PREDELAY = 340,
     K_POSTDELAY = 341,
     K_POLLMETHOD = 342,
     K_MODE = 343,
     K_DELAY = 344,
     K_BLOCKSIZE = 345,
     K_READSIZE = 346,
     K_HVENTERSTABDELAY = 347,
     K_PROGMODEDELAY = 348,
     K_LATCHCYCLES = 349,
     K_TOGGLEVTG = 350,
     K_POWEROFFDELAY = 351,
     K_RESETDELAYMS = 352,
     K_RESETDELAYUS = 353,
     K_HVLEAVESTABDELAY = 354,
     K_RESETDELAY = 355,
     K_SYNCHCYCLES = 356,
     K_HVCMDEXEDELAY = 357,
     K_CHIPERASEPULSEWIDTH = 358,
     K_CHIPERASEPOLLTIMEOUT = 359,
     K_CHIPERASETIME = 360,
     K_PROGRAMFUSEPULSEWIDTH = 361,
     K_PROGRAMFUSEPOLLTIMEOUT = 362,
     K_PROGRAMLOCKPULSEWIDTH = 363,
     K_PROGRAMLOCKPOLLTIMEOUT = 364,
     K_PP_CONTROLSTACK = 365,
     K_HVSP_CONTROLSTACK = 366,
     K_ALLOWFULLPAGEBITSTREAM = 367,
     K_ENABLEPAGEPROGRAMMING = 368,
     K_HAS_JTAG = 369,
     K_HAS_DW = 370,
     K_HAS_PDI = 371,
     K_HAS_TPI = 372,
     K_IDR = 373,
     K_IS_AT90S1200 = 374,
     K_IS_AVR32 = 375,
     K_RAMPZ = 376,
     K_SPMCR = 377,
     K_EECR = 378,
     K_FLASH_INSTR = 379,
     K_EEPROM_INSTR = 380,
     TKN_COMMA = 381,
     TKN_EQUAL = 382,
     TKN_SEMI = 383,
     TKN_TILDE = 384,
     TKN_LEFT_PAREN = 385,
     TKN_RIGHT_PAREN = 386,
     TKN_NUMBER = 387,
     TKN_NUMBER_REAL = 388,
     TKN_STRING = 389
   };
#endif
/* Tokens.  */
#define K_READ 258
#define K_WRITE 259
#define K_READ_LO 260
#define K_READ_HI 261
#define K_WRITE_LO 262
#define K_WRITE_HI 263
#define K_LOADPAGE_LO 264
#define K_LOADPAGE_HI 265
#define K_LOAD_EXT_ADDR 266
#define K_WRITEPAGE 267
#define K_CHIP_ERASE 268
#define K_PGM_ENABLE 269
#define K_MEMORY 270
#define K_PAGE_SIZE 271
#define K_PAGED 272
#define K_BAUDRATE 273
#define K_BS2 274
#define K_BUFF 275
#define K_CHIP_ERASE_DELAY 276
#define K_CONNTYPE 277
#define K_DEDICATED 278
#define K_DEFAULT_PARALLEL 279
#define K_DEFAULT_PROGRAMMER 280
#define K_DEFAULT_SERIAL 281
#define K_DEFAULT_BITCLOCK 282
#define K_DESC 283
#define K_DEVICECODE 284
#define K_STK500_DEVCODE 285
#define K_AVR910_DEVCODE 286
#define K_EEPROM 287
#define K_ERRLED 288
#define K_FLASH 289
#define K_ID 290
#define K_IO 291
#define K_LOADPAGE 292
#define K_MAX_WRITE_DELAY 293
#define K_MCU_BASE 294
#define K_MIN_WRITE_DELAY 295
#define K_MISO 296
#define K_MOSI 297
#define K_NUM_PAGES 298
#define K_NVM_BASE 299
#define K_OCDREV 300
#define K_OFFSET 301
#define K_PAGEL 302
#define K_PARALLEL 303
#define K_PARENT 304
#define K_PART 305
#define K_PGMLED 306
#define K_PROGRAMMER 307
#define K_PSEUDO 308
#define K_PWROFF_AFTER_WRITE 309
#define K_RDYLED 310
#define K_READBACK_P1 311
#define K_READBACK_P2 312
#define K_READMEM 313
#define K_RESET 314
#define K_RETRY_PULSE 315
#define K_SERIAL 316
#define K_SCK 317
#define K_SIGNATURE 318
#define K_SIZE 319
#define K_USB 320
#define K_USBDEV 321
#define K_USBSN 322
#define K_USBPID 323
#define K_USBPRODUCT 324
#define K_USBVENDOR 325
#define K_USBVID 326
#define K_TYPE 327
#define K_VCC 328
#define K_VFYLED 329
#define K_NO 330
#define K_YES 331
#define K_TIMEOUT 332
#define K_STABDELAY 333
#define K_CMDEXEDELAY 334
#define K_HVSPCMDEXEDELAY 335
#define K_SYNCHLOOPS 336
#define K_BYTEDELAY 337
#define K_POLLVALUE 338
#define K_POLLINDEX 339
#define K_PREDELAY 340
#define K_POSTDELAY 341
#define K_POLLMETHOD 342
#define K_MODE 343
#define K_DELAY 344
#define K_BLOCKSIZE 345
#define K_READSIZE 346
#define K_HVENTERSTABDELAY 347
#define K_PROGMODEDELAY 348
#define K_LATCHCYCLES 349
#define K_TOGGLEVTG 350
#define K_POWEROFFDELAY 351
#define K_RESETDELAYMS 352
#define K_RESETDELAYUS 353
#define K_HVLEAVESTABDELAY 354
#define K_RESETDELAY 355
#define K_SYNCHCYCLES 356
#define K_HVCMDEXEDELAY 357
#define K_CHIPERASEPULSEWIDTH 358
#define K_CHIPERASEPOLLTIMEOUT 359
#define K_CHIPERASETIME 360
#define K_PROGRAMFUSEPULSEWIDTH 361
#define K_PROGRAMFUSEPOLLTIMEOUT 362
#define K_PROGRAMLOCKPULSEWIDTH 363
#define K_PROGRAMLOCKPOLLTIMEOUT 364
#define K_PP_CONTROLSTACK 365
#define K_HVSP_CONTROLSTACK 366
#define K_ALLOWFULLPAGEBITSTREAM 367
#define K_ENABLEPAGEPROGRAMMING 368
#define K_HAS_JTAG 369
#define K_HAS_DW 370
#define K_HAS_PDI 371
#define K_HAS_TPI 372
#define K_IDR 373
#define K_IS_AT90S1200 374
#define K_IS_AVR32 375
#define K_RAMPZ 376
#define K_SPMCR 377
#define K_EECR 378
#define K_FLASH_INSTR 379
#define K_EEPROM_INSTR 380
#define TKN_COMMA 381
#define TKN_EQUAL 382
#define TKN_SEMI 383
#define TKN_TILDE 384
#define TKN_LEFT_PAREN 385
#define TKN_RIGHT_PAREN 386
#define TKN_NUMBER 387
#define TKN_NUMBER_REAL 388
#define TKN_STRING 389




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


