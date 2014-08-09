
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 21 "config_gram.y"


#include "ac_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "avrdude.h"

#include "config.h"
#include "lists.h"
#include "par.h"
#include "serbb.h"
#include "pindefs.h"
#include "ppi.h"
#include "pgm.h"
#include "pgm_type.h"
#include "avr.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

int yylex(void);
int yyerror(char * errmsg);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int assign_pin_list(int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);

static int pin_name;


/* Line 189 of yacc.c  */
#line 110 "config_gram.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 420 "config_gram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   386

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  408

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   389

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     8,    10,    12,    15,    18,
      21,    26,    31,    36,    41,    44,    46,    50,    53,    55,
      59,    61,    65,    67,    71,    74,    78,    82,    84,    86,
      88,    90,    94,    98,   102,   104,   106,   110,   112,   114,
     116,   120,   124,   128,   132,   136,   140,   142,   145,   147,
     148,   150,   155,   157,   161,   163,   164,   165,   170,   171,
     176,   177,   182,   183,   188,   189,   194,   195,   200,   201,
     206,   207,   212,   213,   218,   219,   224,   226,   228,   230,
     232,   234,   236,   238,   240,   242,   244,   246,   248,   251,
     255,   257,   259,   261,   263,   265,   267,   271,   275,   279,
     283,   287,   293,   297,   301,   305,   309,   313,   317,   321,
     325,   329,   333,   337,   341,   345,   349,   353,   357,   361,
     365,   369,   373,   377,   381,   385,   389,   393,   397,   401,
     405,   409,   413,   417,   421,   425,   429,   433,   437,   441,
     445,   449,   453,   457,   461,   465,   469,   473,   477,   481,
     485,   489,   493,   497,   501,   505,   509,   510,   515,   519,
     521,   523,   526,   530,   534,   538,   542,   546,   550,   554,
     558,   562,   566,   570,   574,   578,   582,   586,   590
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     137,     0,    -1,   132,    -1,   133,    -1,    -1,   138,    -1,
     139,    -1,   138,   139,    -1,   140,   128,    -1,   142,   128,
      -1,    25,   127,   134,   128,    -1,    24,   127,   134,   128,
      -1,    26,   127,   134,   128,    -1,    27,   127,   136,   128,
      -1,   141,   146,    -1,    52,    -1,    52,    49,   134,    -1,
     143,   170,    -1,    50,    -1,    50,    49,   134,    -1,   134,
      -1,   144,   126,   134,    -1,   132,    -1,   145,   126,   132,
      -1,   147,   128,    -1,   146,   147,   128,    -1,    35,   127,
     144,    -1,   148,    -1,   158,    -1,   152,    -1,   150,    -1,
      28,   127,   134,    -1,    18,   127,   132,    -1,    72,   127,
     149,    -1,   134,    -1,     1,    -1,    22,   127,   151,    -1,
      48,    -1,    61,    -1,    65,    -1,    66,   127,   134,    -1,
      71,   127,   132,    -1,    68,   127,   132,    -1,    67,   127,
     134,    -1,    70,   127,   134,    -1,    69,   127,   134,    -1,
     132,    -1,   129,   132,    -1,   153,    -1,    -1,   153,    -1,
     129,   130,   145,   131,    -1,   155,    -1,   156,   126,   155,
      -1,   156,    -1,    -1,    -1,    73,   127,   159,   157,    -1,
      -1,    20,   127,   160,   157,    -1,    -1,    59,   127,   161,
     154,    -1,    -1,    62,   127,   162,   154,    -1,    -1,    42,
     127,   163,   154,    -1,    -1,    41,   127,   164,   154,    -1,
      -1,    33,   127,   165,   154,    -1,    -1,    55,   127,   166,
     154,    -1,    -1,    51,   127,   167,   154,    -1,    -1,    74,
     127,   168,   154,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    13,    -1,    14,    -1,   174,   128,
      -1,   170,   174,   128,    -1,    23,    -1,    36,    -1,   176,
      -1,    53,    -1,    59,    -1,    62,    -1,    35,   127,   134,
      -1,    28,   127,   134,    -1,    29,   127,   132,    -1,    30,
     127,   132,    -1,    31,   127,   132,    -1,    63,   127,   132,
     132,   132,    -1,   110,   127,   145,    -1,   111,   127,   145,
      -1,   124,   127,   145,    -1,   125,   127,   145,    -1,    21,
     127,   132,    -1,    47,   127,   132,    -1,    19,   127,   132,
      -1,    59,   127,   171,    -1,    77,   127,   132,    -1,    78,
     127,   132,    -1,    79,   127,   132,    -1,    80,   127,   132,
      -1,    81,   127,   132,    -1,    82,   127,   132,    -1,    83,
     127,   132,    -1,    84,   127,   132,    -1,    85,   127,   132,
      -1,    86,   127,   132,    -1,    87,   127,   132,    -1,    92,
     127,   132,    -1,    93,   127,   132,    -1,    94,   127,   132,
      -1,    95,   127,   132,    -1,    96,   127,   132,    -1,    97,
     127,   132,    -1,    98,   127,   132,    -1,    99,   127,   132,
      -1,   100,   127,   132,    -1,   103,   127,   132,    -1,   104,
     127,   132,    -1,   105,   127,   132,    -1,   106,   127,   132,
      -1,   107,   127,   132,    -1,   108,   127,   132,    -1,   109,
     127,   132,    -1,   101,   127,   132,    -1,   114,   127,   176,
      -1,   115,   127,   176,    -1,   116,   127,   176,    -1,   117,
     127,   176,    -1,   119,   127,   176,    -1,   120,   127,   176,
      -1,   112,   127,   176,    -1,   113,   127,   176,    -1,   118,
     127,   132,    -1,   121,   127,   132,    -1,   122,   127,   132,
      -1,   123,   127,   132,    -1,    39,   127,   132,    -1,    44,
     127,   132,    -1,    45,   127,   132,    -1,    61,   127,   176,
      -1,    48,   127,   172,    -1,    60,   127,   173,    -1,    -1,
      15,   134,   175,   177,    -1,   169,   127,   144,    -1,    76,
      -1,    75,    -1,   178,   128,    -1,   177,   178,   128,    -1,
      17,   127,   176,    -1,    64,   127,   132,    -1,    16,   127,
     132,    -1,    43,   127,   132,    -1,    46,   127,   132,    -1,
      40,   127,   132,    -1,    38,   127,   132,    -1,    54,   127,
     176,    -1,    56,   127,   132,    -1,    57,   127,   132,    -1,
      88,   127,   132,    -1,    89,   127,   132,    -1,    90,   127,
     132,    -1,    91,   127,   132,    -1,    84,   127,   132,    -1,
     169,   127,   144,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   214,   214,   220,   224,   225,   229,   230,   235,   237,
     239,   245,   251,   257,   265,   299,   305,   323,   388,   394,
     413,   414,   419,   420,   424,   425,   429,   439,   441,   443,
     445,   447,   452,   461,   465,   476,   486,   490,   491,   492,
     496,   503,   509,   515,   522,   529,   539,   541,   545,   547,
     551,   553,   557,   559,   564,   566,   570,   570,   571,   571,
     572,   572,   573,   573,   574,   574,   575,   575,   576,   576,
     577,   577,   578,   578,   579,   579,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   599,   600,
     605,   605,   609,   609,   613,   613,   617,   624,   631,   641,
     648,   655,   666,   700,   734,   767,   800,   806,   812,   818,
     828,   834,   840,   846,   852,   858,   864,   870,   876,   882,
     888,   894,   900,   906,   912,   918,   924,   930,   936,   942,
     948,   954,   960,   966,   972,   978,   984,   990,   996,  1006,
    1016,  1026,  1036,  1046,  1056,  1066,  1076,  1082,  1088,  1094,
    1100,  1106,  1112,  1118,  1128,  1147,  1171,  1170,  1190,  1213,
    1213,  1218,  1219,  1224,  1230,  1237,  1243,  1249,  1255,  1261,
    1267,  1273,  1279,  1286,  1292,  1298,  1304,  1310,  1317
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_READ", "K_WRITE", "K_READ_LO",
  "K_READ_HI", "K_WRITE_LO", "K_WRITE_HI", "K_LOADPAGE_LO",
  "K_LOADPAGE_HI", "K_LOAD_EXT_ADDR", "K_WRITEPAGE", "K_CHIP_ERASE",
  "K_PGM_ENABLE", "K_MEMORY", "K_PAGE_SIZE", "K_PAGED", "K_BAUDRATE",
  "K_BS2", "K_BUFF", "K_CHIP_ERASE_DELAY", "K_CONNTYPE", "K_DEDICATED",
  "K_DEFAULT_PARALLEL", "K_DEFAULT_PROGRAMMER", "K_DEFAULT_SERIAL",
  "K_DEFAULT_BITCLOCK", "K_DESC", "K_DEVICECODE", "K_STK500_DEVCODE",
  "K_AVR910_DEVCODE", "K_EEPROM", "K_ERRLED", "K_FLASH", "K_ID", "K_IO",
  "K_LOADPAGE", "K_MAX_WRITE_DELAY", "K_MCU_BASE", "K_MIN_WRITE_DELAY",
  "K_MISO", "K_MOSI", "K_NUM_PAGES", "K_NVM_BASE", "K_OCDREV", "K_OFFSET",
  "K_PAGEL", "K_PARALLEL", "K_PARENT", "K_PART", "K_PGMLED",
  "K_PROGRAMMER", "K_PSEUDO", "K_PWROFF_AFTER_WRITE", "K_RDYLED",
  "K_READBACK_P1", "K_READBACK_P2", "K_READMEM", "K_RESET",
  "K_RETRY_PULSE", "K_SERIAL", "K_SCK", "K_SIGNATURE", "K_SIZE", "K_USB",
  "K_USBDEV", "K_USBSN", "K_USBPID", "K_USBPRODUCT", "K_USBVENDOR",
  "K_USBVID", "K_TYPE", "K_VCC", "K_VFYLED", "K_NO", "K_YES", "K_TIMEOUT",
  "K_STABDELAY", "K_CMDEXEDELAY", "K_HVSPCMDEXEDELAY", "K_SYNCHLOOPS",
  "K_BYTEDELAY", "K_POLLVALUE", "K_POLLINDEX", "K_PREDELAY", "K_POSTDELAY",
  "K_POLLMETHOD", "K_MODE", "K_DELAY", "K_BLOCKSIZE", "K_READSIZE",
  "K_HVENTERSTABDELAY", "K_PROGMODEDELAY", "K_LATCHCYCLES", "K_TOGGLEVTG",
  "K_POWEROFFDELAY", "K_RESETDELAYMS", "K_RESETDELAYUS",
  "K_HVLEAVESTABDELAY", "K_RESETDELAY", "K_SYNCHCYCLES", "K_HVCMDEXEDELAY",
  "K_CHIPERASEPULSEWIDTH", "K_CHIPERASEPOLLTIMEOUT", "K_CHIPERASETIME",
  "K_PROGRAMFUSEPULSEWIDTH", "K_PROGRAMFUSEPOLLTIMEOUT",
  "K_PROGRAMLOCKPULSEWIDTH", "K_PROGRAMLOCKPOLLTIMEOUT",
  "K_PP_CONTROLSTACK", "K_HVSP_CONTROLSTACK", "K_ALLOWFULLPAGEBITSTREAM",
  "K_ENABLEPAGEPROGRAMMING", "K_HAS_JTAG", "K_HAS_DW", "K_HAS_PDI",
  "K_HAS_TPI", "K_IDR", "K_IS_AT90S1200", "K_IS_AVR32", "K_RAMPZ",
  "K_SPMCR", "K_EECR", "K_FLASH_INSTR", "K_EEPROM_INSTR", "TKN_COMMA",
  "TKN_EQUAL", "TKN_SEMI", "TKN_TILDE", "TKN_LEFT_PAREN",
  "TKN_RIGHT_PAREN", "TKN_NUMBER", "TKN_NUMBER_REAL", "TKN_STRING",
  "$accept", "number_real", "configuration", "config", "def", "prog_def",
  "prog_decl", "part_def", "part_decl", "string_list", "num_list",
  "prog_parms", "prog_parm", "prog_parm_type", "prog_parm_type_id",
  "prog_parm_conntype", "prog_parm_conntype_id", "prog_parm_usb",
  "pin_number_non_empty", "pin_number", "pin_list_element",
  "pin_list_non_empty", "pin_list", "prog_parm_pins", "$@1", "$@2", "$@3",
  "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "opcode", "part_parms",
  "reset_disposition", "parallel_modes", "retry_lines", "part_parm",
  "$@11", "yesno", "mem_specs", "mem_spec", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   139,   139,   139,   140,   141,   141,   142,   143,   143,
     144,   144,   145,   145,   146,   146,   147,   147,   147,   147,
     147,   147,   147,   148,   149,   149,   150,   151,   151,   151,
     152,   152,   152,   152,   152,   152,   153,   153,   154,   154,
     155,   155,   156,   156,   157,   157,   159,   158,   160,   158,
     161,   158,   162,   158,   163,   158,   164,   158,   165,   158,
     166,   158,   167,   158,   168,   158,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   175,   174,   174,   176,
     176,   177,   177,   178,   178,   178,   178,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   178,   178
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     1,     2,     2,     2,
       4,     4,     4,     4,     2,     1,     3,     2,     1,     3,
       1,     3,     1,     3,     2,     3,     3,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     0,
       1,     4,     1,     3,     1,     0,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     1,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,    18,    15,     0,     5,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,    27,    30,    29,    28,
       9,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
       2,     3,     0,    19,    16,     0,    58,     0,     0,    68,
       0,    66,    64,    72,    70,    60,    62,     0,     0,     0,
       0,     0,     0,     0,    56,    74,     0,    24,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    11,    10,    12,    13,    32,    55,    37,    38,
      39,    36,    31,    49,    20,    26,    49,    49,    49,    49,
      49,    49,    40,    43,    42,    45,    44,    41,    35,    34,
      33,    55,    49,    25,     0,   108,   106,    97,    98,    99,
     100,    96,   150,   151,   152,   107,    93,   160,   159,   154,
      92,    90,    91,   109,    94,    95,   155,   153,     0,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   137,
     130,   131,   132,   133,   134,   135,   136,    22,   102,   103,
     144,   145,   138,   139,   140,   141,   146,   142,   143,   147,
     148,   149,   104,   105,   158,    89,     0,    46,    50,    52,
      54,    59,     0,    48,    69,     0,    67,    65,    73,    71,
      61,    63,    57,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,     0,     0,    47,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   161,   101,    23,     0,    53,
     165,   163,   169,   168,   166,   167,   170,   171,   172,   164,
     177,   173,   174,   175,   176,   178,   162,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   132,     7,     8,     9,    10,    11,    12,    13,   235,
     308,    44,    45,    46,   250,    47,   231,    48,   333,   334,
     329,   330,   331,    49,   251,   227,   240,   241,   237,   236,
     233,   239,   238,   252,   124,   125,   273,   269,   276,   126,
     254,   270,   360,   361
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -250
static const yytype_int16 yypact[] =
{
      33,   -89,   -65,   -61,   -60,    19,    20,    70,    33,  -250,
     -57,   253,   -56,   145,   -59,   -55,   -54,  -114,   -52,   -48,
    -250,  -250,  -250,   -53,   -50,   -40,   -39,   -38,   -37,   -34,
     -31,   -30,   -29,   -28,   -27,   -26,   -24,   -23,   -22,   -21,
     -20,   -19,   -18,   -17,   253,   -16,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,   -43,   -14,   -13,   -12,   -11,   -10,    -9,
      -8,    -7,    -6,    -4,    -3,    -2,     4,     5,     6,     7,
       8,     9,    11,    12,    13,    14,    16,    17,    18,    34,
      36,    40,    41,    42,    43,    44,    45,    50,    51,    52,
      54,    55,    56,    58,    59,    60,    61,    64,    67,    68,
      71,    72,    73,    75,    76,    80,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   145,     2,    69,    91,    92,
    -250,  -250,    93,  -250,  -250,    15,  -250,   -41,    99,  -250,
     100,  -250,  -250,  -250,  -250,  -250,  -250,   101,   102,   115,
     138,   140,   144,     3,  -250,  -250,   149,  -250,  -250,   146,
     147,   148,   151,   152,   153,   155,   158,   159,   160,   161,
     -47,   -15,   -36,   -45,   164,   165,   166,   167,   168,   169,
     170,   171,   173,   174,   175,   177,   178,   179,   181,   182,
     184,   185,   186,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   206,   -45,   -45,   -45,   -45,   -45,
     -45,   207,   -45,   -45,   208,   209,   210,   206,   206,   100,
     215,  -250,  -250,  -250,  -250,  -250,  -250,   -76,  -250,  -250,
    -250,  -250,  -250,   -68,  -250,   154,   -68,   -68,   -68,   -68,
     -68,   -68,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,   -76,   -68,  -250,    38,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,   212,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,   219,   219,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,   219,   219,   154,  -250,   -67,  -250,  -250,  -250,
     220,  -250,   216,  -250,  -250,   213,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
      38,   238,   239,   240,   206,  -250,   -76,  -250,   241,   -45,
     242,   243,   244,   245,   -45,   246,   247,   248,   249,   250,
     251,   252,   254,   100,   257,  -250,  -250,  -250,  -109,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,   154,  -250,  -250
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,  -250,  -250,    65,  -250,  -250,  -250,  -250,  -218,
    -202,  -250,   321,  -250,  -250,  -250,  -250,  -250,  -224,  -227,
    -220,  -250,   -33,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -249,  -250,  -250,  -250,  -250,   162,
    -250,  -173,  -250,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     277,   324,   309,   328,   248,   359,   266,   228,   271,   336,
     337,   338,   339,   340,   341,   322,   323,   363,   130,   131,
     229,   272,   407,   274,   230,   343,   275,   328,   267,   268,
     267,   268,   310,   311,   312,   313,   314,   315,    14,   317,
     318,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   326,   344,   345,   327,     1,     2,     3,
       4,   332,    15,   364,   327,   365,    16,    17,    18,    19,
      20,    22,    50,    21,   135,   127,   346,   136,   347,   128,
     129,   348,   133,     5,   349,     6,   134,   137,   138,   139,
     140,   158,   350,   141,   351,   352,   142,   143,   144,   145,
     146,   147,   353,   148,   149,   150,   151,   152,   153,   154,
     155,   359,   157,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   354,   168,   169,   170,   355,   356,   357,   358,
     221,   171,   172,   173,   174,   175,   176,   249,   177,   178,
     179,   180,   328,   181,   182,   183,   389,   226,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,   184,   388,   185,    64,   405,    65,   186,   187,   188,
     189,   190,   191,    66,    67,    68,    69,   192,   193,   194,
      70,   195,   196,   197,    71,   198,   199,   200,   201,    72,
      73,   202,    74,    75,   203,   204,   391,   222,   205,   206,
     207,   396,   208,   209,    76,    77,    78,   210,    79,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   342,   223,
     224,   225,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,   232,   234,   242,   243,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   244,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,    23,   245,    24,   246,    25,   247,   253,   255,   256,
     335,    26,   257,   258,   259,   260,    27,   220,    28,   261,
     262,   263,   264,   265,    29,    30,   278,   279,   280,   281,
     282,   283,   284,   285,    31,   286,   287,   288,    32,   289,
     290,   291,    33,   292,   293,    34,   294,   295,   296,    35,
      36,    37,    38,    39,    40,    41,    42,    43,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   316,
     319,   320,   321,   325,   362,   363,   366,   367,   365,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   156,   385,     0,     0,     0,
     384,   386,   387,   390,   392,   393,   394,   395,   397,   398,
     399,   400,   401,   402,   403,   406,   404
};

static const yytype_int16 yycheck[] =
{
     173,   219,   204,   227,     1,   254,    53,    48,    23,   236,
     237,   238,   239,   240,   241,   217,   218,   126,   132,   133,
      61,    36,   131,    59,    65,   252,    62,   251,    75,    76,
      75,    76,   205,   206,   207,   208,   209,   210,   127,   212,
     213,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   129,    16,    17,   132,    24,    25,    26,
      27,   129,   127,   130,   132,   132,   127,   127,    49,    49,
       0,   128,   128,     8,   127,   134,    38,   127,    40,   134,
     134,    43,   134,    50,    46,    52,   134,   127,   127,   127,
     127,   134,    54,   127,    56,    57,   127,   127,   127,   127,
     127,   127,    64,   127,   127,   127,   127,   127,   127,   127,
     127,   360,   128,   127,   127,   127,   127,   127,   127,   127,
     127,   127,    84,   127,   127,   127,    88,    89,    90,    91,
     128,   127,   127,   127,   127,   127,   127,   134,   127,   127,
     127,   127,   366,   127,   127,   127,   366,   132,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   127,   364,   127,    19,   383,    21,   127,   127,   127,
     127,   127,   127,    28,    29,    30,    31,   127,   127,   127,
      35,   127,   127,   127,    39,   127,   127,   127,   127,    44,
      45,   127,    47,    48,   127,   127,   369,   128,   127,   127,
     127,   374,   127,   127,    59,    60,    61,   127,    63,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   251,   128,
     128,   128,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,   134,   134,   134,   134,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   132,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    18,   134,    20,   134,    22,   132,   128,   132,   132,
     126,    28,   134,   132,   132,   132,    33,   125,    35,   134,
     132,   132,   132,   132,    41,    42,   132,   132,   132,   132,
     132,   132,   132,   132,    51,   132,   132,   132,    55,   132,
     132,   132,    59,   132,   132,    62,   132,   132,   132,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   128,   132,   126,   126,   134,   132,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,    44,   128,    -1,    -1,    -1,
     360,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   128,   132
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    26,    27,    50,    52,   137,   138,   139,
     140,   141,   142,   143,   127,   127,   127,   127,    49,    49,
       0,   139,   128,    18,    20,    22,    28,    33,    35,    41,
      42,    51,    55,    59,    62,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   146,   147,   148,   150,   152,   158,
     128,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    19,    21,    28,    29,    30,    31,
      35,    39,    44,    45,    47,    48,    59,    60,    61,    63,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   169,   170,   174,   134,   134,   134,
     132,   133,   136,   134,   134,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   147,   128,   134,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     174,   128,   128,   128,   128,   128,   132,   160,    48,    61,
      65,   151,   134,   165,   134,   144,   164,   163,   167,   166,
     161,   162,   134,   134,   132,   134,   134,   132,     1,   134,
     149,   159,   168,   128,   175,   132,   132,   134,   132,   132,
     132,   134,   132,   132,   132,   132,    53,    75,    76,   172,
     176,    23,    36,   171,    59,    62,   173,   176,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   145,   145,
     176,   176,   176,   176,   176,   176,   132,   176,   176,   132,
     132,   132,   145,   145,   144,   128,   129,   132,   153,   155,
     156,   157,   129,   153,   154,   126,   154,   154,   154,   154,
     154,   154,   157,   154,    16,    17,    38,    40,    43,    46,
      54,    56,    57,    64,    84,    88,    89,    90,    91,   169,
     177,   178,   132,   126,   130,   132,   126,   134,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   178,   128,   132,   132,   145,   155,
     132,   176,   132,   132,   132,   132,   176,   132,   132,   132,
     132,   132,   132,   132,   132,   144,   128,   131
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 214 "config_gram.y"
    {
    (yyval) = (yyvsp[(1) - (1)]);
    /* convert value to real */
    (yyval)->value.number_real = (yyval)->value.number;
    (yyval)->value.type = V_NUM_REAL;
  }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 220 "config_gram.y"
    {
    (yyval) = (yyvsp[(1) - (1)]);
  }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 239 "config_gram.y"
    {
    strncpy(default_programmer, (yyvsp[(3) - (4)])->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 245 "config_gram.y"
    {
    strncpy(default_parallel, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 251 "config_gram.y"
    {
    strncpy(default_serial, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 257 "config_gram.y"
    {
    default_bitclock = (yyvsp[(3) - (4)])->value.number_real;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 266 "config_gram.y"
    {
      PROGRAMMER * existing_prog;
      char * id;
      if (lsize(current_prog->id) == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      if (current_prog->initpgm == NULL) {
        fprintf(stderr, "%s: error at %s:%d: programmer type not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      id = ldata(lfirst(current_prog->id));
      existing_prog = locate_programmer(programmers, id);
      if (existing_prog) {
        fprintf(stderr, "%s: warning at %s:%d: programmer %s overwrites "
                "previous definition %s:%d.\n",
                progname, infile, current_prog->lineno,
                id, existing_prog->config_file, existing_prog->lineno);
        lrmv_d(programmers, existing_prog);
        pgm_free(existing_prog);
      }
      PUSH(programmers, current_prog);
//      pgm_fill_old_pins(current_prog); // TODO to be removed if old pin data no longer needed
//      pgm_display_generic(current_prog, id);
      current_prog = NULL;
    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 300 "config_gram.y"
    { current_prog = pgm_new();
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 306 "config_gram.y"
    {
      struct programmer_t * pgm = locate_programmer(programmers, (yyvsp[(3) - (3)])->value.string);
      if (pgm == NULL) {
        fprintf(stderr,
                "%s: error at %s:%d: parent programmer %s not found\n",
                progname, infile, lineno, (yyvsp[(3) - (3)])->value.string);
        exit(1);
      }
      current_prog = pgm_dup(pgm);
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 324 "config_gram.y"
    { 
      LNODEID ln;
      AVRMEM * m;
      AVRPART * existing_part;

      if (current_part->id[0] == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }

      /*
       * perform some sanity checking, and compute the number of bits
       * to shift a page for constructing the page address for
       * page-addressed memories.
       */
      for (ln=lfirst(current_part->mem); ln; ln=lnext(ln)) {
        m = ldata(ln);
        if (m->paged) {
          if (m->page_size == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify page_size for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->num_pages == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify num_pages for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->size != m->page_size * m->num_pages) {
            fprintf(stderr, 
                    "%s: error at %s:%d: page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)\n",
                    progname, infile, lineno,
                    m->page_size, 
                    m->num_pages, 
                    m->page_size * m->num_pages,
                    m->size);
            exit(1);
          }

        }
      }

      existing_part = locate_part(part_list, current_part->id);
      if (existing_part) {
        fprintf(stderr, "%s: warning at %s:%d: part %s overwrites "
                "previous definition %s:%d.\n",
                progname, infile, current_part->lineno, current_part->id,
                existing_part->config_file, existing_part->lineno);
        lrmv_d(part_list, existing_part);
        avr_free_part(existing_part);
      }
      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 389 "config_gram.y"
    {
      current_part = avr_new_part();
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 395 "config_gram.y"
    {
      AVRPART * parent_part = locate_part(part_list, (yyvsp[(3) - (3)])->value.string);
      if (parent_part == NULL) {
        fprintf(stderr, 
              "%s: error at %s:%d: can't find parent part",
              progname, infile, lineno);
        exit(1);
      }

      current_part = avr_dup_part(parent_part);
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 413 "config_gram.y"
    { ladd(string_list, (yyvsp[(1) - (1)])); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 414 "config_gram.y"
    { ladd(string_list, (yyvsp[(3) - (3)])); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 419 "config_gram.y"
    { ladd(number_list, (yyvsp[(1) - (1)])); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 420 "config_gram.y"
    { ladd(number_list, (yyvsp[(3) - (3)])); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 429 "config_gram.y"
    {
    {
      TOKEN * t;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        ladd(current_prog->id, dup_string(t->value.string));
        free_token(t);
      }
    }
  }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 447 "config_gram.y"
    {
    strncpy(current_prog->desc, (yyvsp[(3) - (3)])->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token((yyvsp[(3) - (3)]));
  }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 452 "config_gram.y"
    {
    {
      current_prog->baudrate = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 465 "config_gram.y"
    {
  const struct programmer_type_t * pgm_type = locate_programmer_type((yyvsp[(1) - (1)])->value.string);
    if (pgm_type == NULL) {
        fprintf(stderr,
                "%s: error at %s:%d: programmer type %s not found\n",
                progname, infile, lineno, (yyvsp[(1) - (1)])->value.string);
        exit(1);
    }
    current_prog->initpgm = pgm_type->initpgm;
    free_token((yyvsp[(1) - (1)])); 
}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 477 "config_gram.y"
    {
        fprintf(stderr,
                "%s: error at %s:%d: programmer type must be written as \"id_type\"\n",
                progname, infile, lineno);
        exit(1);
}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 490 "config_gram.y"
    { current_prog->conntype = CONNTYPE_PARALLEL; }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 491 "config_gram.y"
    { current_prog->conntype = CONNTYPE_SERIAL; }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 492 "config_gram.y"
    { current_prog->conntype = CONNTYPE_USB; }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 496 "config_gram.y"
    {
    {
      strncpy(current_prog->usbdev, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbdev[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 503 "config_gram.y"
    {
    {
      current_prog->usbvid = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 509 "config_gram.y"
    {
    {
      current_prog->usbpid = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 515 "config_gram.y"
    {
    {
      strncpy(current_prog->usbsn, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbsn[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 522 "config_gram.y"
    {
    {
      strncpy(current_prog->usbvendor, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbvendor[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 529 "config_gram.y"
    {
    {
      strncpy(current_prog->usbproduct, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbproduct[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 539 "config_gram.y"
    { assign_pin(pin_name, (yyvsp[(1) - (1)]), 0);  }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 541 "config_gram.y"
    { assign_pin(pin_name, (yyvsp[(2) - (2)]), 1); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 547 "config_gram.y"
    { pin_clear_all(&(current_prog->pin[pin_name])); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 553 "config_gram.y"
    { assign_pin_list(1); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 566 "config_gram.y"
    { pin_clear_all(&(current_prog->pin[pin_name])); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 570 "config_gram.y"
    {pin_name = PPI_AVR_VCC;  }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 571 "config_gram.y"
    {pin_name = PPI_AVR_BUFF; }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 572 "config_gram.y"
    {pin_name = PIN_AVR_RESET;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 572 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 573 "config_gram.y"
    {pin_name = PIN_AVR_SCK;  }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 573 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 574 "config_gram.y"
    {pin_name = PIN_AVR_MOSI; }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 575 "config_gram.y"
    {pin_name = PIN_AVR_MISO; }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 576 "config_gram.y"
    {pin_name = PIN_LED_ERR;  }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 577 "config_gram.y"
    {pin_name = PIN_LED_RDY;  }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 578 "config_gram.y"
    {pin_name = PIN_LED_PGM;  }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 579 "config_gram.y"
    {pin_name = PIN_LED_VFY;  }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 618 "config_gram.y"
    {
      strncpy(current_part->id, (yyvsp[(3) - (3)])->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 625 "config_gram.y"
    {
      strncpy(current_part->desc, (yyvsp[(3) - (3)])->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 631 "config_gram.y"
    {
    {
      fprintf(stderr, 
              "%s: error at %s:%d: devicecode is deprecated, use "
              "stk500_devcode instead\n",
              progname, infile, lineno);
      exit(1);
    }
  }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 641 "config_gram.y"
    {
    {
      current_part->stk500_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 648 "config_gram.y"
    {
    {
      current_part->avr910_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 655 "config_gram.y"
    {
    {
      current_part->signature[0] = (yyvsp[(3) - (5)])->value.number;
      current_part->signature[1] = (yyvsp[(4) - (5)])->value.number;
      current_part->signature[2] = (yyvsp[(5) - (5)])->value.number;
      free_token((yyvsp[(3) - (5)]));
      free_token((yyvsp[(4) - (5)]));
      free_token((yyvsp[(5) - (5)]));
    }
  }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 666 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      current_part->ctl_stack_type = CTL_STACK_PP;
      nbytes = 0;
      ok = 1;

      memset(current_part->controlstack, 0, CTL_STACK_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 700 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      current_part->ctl_stack_type = CTL_STACK_HVSP;
      nbytes = 0;
      ok = 1;

      memset(current_part->controlstack, 0, CTL_STACK_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 734 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      memset(current_part->flash_instr, 0, FLASH_INSTR_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < FLASH_INSTR_SIZE)
	  {
	    current_part->flash_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in flash instructions\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 767 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      memset(current_part->eeprom_instr, 0, EEPROM_INSTR_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < EEPROM_INSTR_SIZE)
	  {
	    current_part->eeprom_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in EEPROM instructions\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 801 "config_gram.y"
    {
      current_part->chip_erase_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 807 "config_gram.y"
    {
      current_part->pagel = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 813 "config_gram.y"
    {
      current_part->bs2 = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 819 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if ((yyvsp[(3) - (3)])->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
    }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 829 "config_gram.y"
    {
      current_part->timeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 835 "config_gram.y"
    {
      current_part->stabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 841 "config_gram.y"
    {
      current_part->cmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 847 "config_gram.y"
    {
      current_part->hvspcmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 853 "config_gram.y"
    {
      current_part->synchloops = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 859 "config_gram.y"
    {
      current_part->bytedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 865 "config_gram.y"
    {
      current_part->pollvalue = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 871 "config_gram.y"
    {
      current_part->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 877 "config_gram.y"
    {
      current_part->predelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 883 "config_gram.y"
    {
      current_part->postdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 889 "config_gram.y"
    {
      current_part->pollmethod = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 895 "config_gram.y"
    {
      current_part->hventerstabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 901 "config_gram.y"
    {
      current_part->progmodedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 907 "config_gram.y"
    {
      current_part->latchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 913 "config_gram.y"
    {
      current_part->togglevtg = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 919 "config_gram.y"
    {
      current_part->poweroffdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 925 "config_gram.y"
    {
      current_part->resetdelayms = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 931 "config_gram.y"
    {
      current_part->resetdelayus = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 937 "config_gram.y"
    {
      current_part->hvleavestabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 943 "config_gram.y"
    {
      current_part->resetdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 949 "config_gram.y"
    {
      current_part->chiperasepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 955 "config_gram.y"
    {
      current_part->chiperasepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 961 "config_gram.y"
    {
      current_part->chiperasetime = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 967 "config_gram.y"
    {
      current_part->programfusepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 973 "config_gram.y"
    {
      current_part->programfusepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 979 "config_gram.y"
    {
      current_part->programlockpulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 985 "config_gram.y"
    {
      current_part->programlockpolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 991 "config_gram.y"
    {
      current_part->synchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 997 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1007 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1017 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1027 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1037 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_IS_AT90S1200;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_IS_AT90S1200;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1047 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_AVR32;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1057 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1067 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1077 "config_gram.y"
    {
      current_part->idr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1083 "config_gram.y"
    {
      current_part->rampz = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1089 "config_gram.y"
    {
      current_part->spmcr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1095 "config_gram.y"
    {
      current_part->eecr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1101 "config_gram.y"
    {
      current_part->mcu_base = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1107 "config_gram.y"
    {
      current_part->nvm_base = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1113 "config_gram.y"
    {
      current_part->ocdrev = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1119 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1129 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[(3) - (3)])->primary == K_NO) {
        current_part->flags &= ~AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[(3) - (3)])->primary == K_PSEUDO) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags |= AVRPART_PSEUDOPARALLEL;
      }


      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1148 "config_gram.y"
    {
      switch ((yyvsp[(3) - (3)])->primary) {
        case K_RESET :
          current_part->retry_pulse = PIN_AVR_RESET;
          break;
        case K_SCK :
          current_part->retry_pulse = PIN_AVR_SCK;
          break;
      }

      free_token((yyvsp[(1) - (3)]));
    }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1171 "config_gram.y"
    { 
      current_mem = avr_new_memtype(); 
      strncpy(current_mem->desc, (yyvsp[(2) - (2)])->value.string, AVR_MEMDESCLEN); 
      current_mem->desc[AVR_MEMDESCLEN-1] = 0;
      free_token((yyvsp[(2) - (2)])); 
    }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1178 "config_gram.y"
    { 
      AVRMEM * existing_mem;

      existing_mem = avr_locate_mem(current_part, current_mem->desc);
      if (existing_mem != NULL) {
        lrmv_d(current_part->mem, existing_mem);
        avr_free_mem(existing_mem);
      }
      ladd(current_part->mem, current_mem); 
      current_mem = NULL; 
    }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1190 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      if (current_part->op[opnum] != NULL) {
        /*fprintf(stderr,
              "%s: warning at %s:%d: operation redefined\n",
              progname, infile, lineno);*/
        avr_free_opcode(current_part->op[opnum]);
      }
      current_part->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1225 "config_gram.y"
    {
      current_mem->paged = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1231 "config_gram.y"
    {
      current_mem->size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1238 "config_gram.y"
    {
      current_mem->page_size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1244 "config_gram.y"
    {
      current_mem->num_pages = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1250 "config_gram.y"
    {
      current_mem->offset = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1256 "config_gram.y"
    {
      current_mem->min_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1262 "config_gram.y"
    {
      current_mem->max_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1268 "config_gram.y"
    {
      current_mem->pwroff_after_write = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1274 "config_gram.y"
    {
      current_mem->readback[0] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1280 "config_gram.y"
    {
      current_mem->readback[1] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1287 "config_gram.y"
    {
      current_mem->mode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1293 "config_gram.y"
    {
      current_mem->delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1299 "config_gram.y"
    {
      current_mem->blocksize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1305 "config_gram.y"
    {
      current_mem->readsize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1311 "config_gram.y"
    {
      current_mem->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1317 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      if (current_mem->op[opnum] != NULL) {
        /*fprintf(stderr,
              "%s: warning at %s:%d: operation redefined\n",
              progname, infile, lineno);*/
        avr_free_opcode(current_mem->op[opnum]);
      }
      current_mem->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;



/* Line 1455 of yacc.c  */
#line 3552 "config_gram.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1339 "config_gram.y"


#if 0
static char * vtypestr(int type)
{
  switch (type) {
    case V_NUM : return "INTEGER";
    case V_NUM_REAL: return "REAL";
    case V_STR : return "STRING";
    default:
      return "<UNKNOWN>";
  }
}
#endif


static int assign_pin(int pinno, TOKEN * v, int invert)
{
  int value;

  value = v->value.number;
  free_token(v);

  if ((value < PIN_MIN) || (value > PIN_MAX)) {
    fprintf(stderr, 
            "%s: error at line %d of %s: pin must be in the "
            "range %d-%d\n",
            progname, lineno, infile, PIN_MIN, PIN_MAX);
    exit(1);
  }

  pin_set_value(&(current_prog->pin[pinno]), value, invert);

  return 0;
}

static int assign_pin_list(int invert)
{
  TOKEN * t;
  int pin;

  current_prog->pinno[pin_name] = 0;
  while (lsize(number_list)) {
    t = lrmv_n(number_list, 1);
    pin = t->value.number;
    if ((pin < PIN_MIN) || (pin > PIN_MAX)) {
      fprintf(stderr, 
            "%s: error at line %d of %s: pin must be in the "
            "range %d-%d\n",
            progname, lineno, infile, PIN_MIN, PIN_MAX);
      exit(1);
      /* TODO clear list and free tokens if no exit is done */
    }
    pin_set_value(&(current_prog->pin[pin_name]), pin, invert);
    free_token(t);
  }

  return 0;
}

static int which_opcode(TOKEN * opcode)
{
  switch (opcode->primary) {
    case K_READ        : return AVR_OP_READ; break;
    case K_WRITE       : return AVR_OP_WRITE; break;
    case K_READ_LO     : return AVR_OP_READ_LO; break;
    case K_READ_HI     : return AVR_OP_READ_HI; break;
    case K_WRITE_LO    : return AVR_OP_WRITE_LO; break;
    case K_WRITE_HI    : return AVR_OP_WRITE_HI; break;
    case K_LOADPAGE_LO : return AVR_OP_LOADPAGE_LO; break;
    case K_LOADPAGE_HI : return AVR_OP_LOADPAGE_HI; break;
    case K_LOAD_EXT_ADDR : return AVR_OP_LOAD_EXT_ADDR; break;
    case K_WRITEPAGE   : return AVR_OP_WRITEPAGE; break;
    case K_CHIP_ERASE  : return AVR_OP_CHIP_ERASE; break;
    case K_PGM_ENABLE  : return AVR_OP_PGM_ENABLE; break;
    default :
      fprintf(stderr, 
              "%s: error at %s:%d: invalid opcode\n",
              progname, infile, lineno);
      exit(1);
      break;
  }
}


static int parse_cmdbits(OPCODE * op)
{
  TOKEN * t;
  int bitno;
  char ch;
  char * e;
  char * q;
  int len;
  char * s, *brkt = NULL;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (s != NULL) {

      bitno--;
      if (bitno < 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: too many opcode bits for instruction\n",
                progname, infile, lineno);
        exit(1);
      }

      len = strlen(s);

      if (len == 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: invalid bit specifier \"\"\n",
                progname, infile, lineno);
        exit(1);
      }

      ch = s[0];

      if (len == 1) {
        switch (ch) {
          case '1':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 1;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case '0':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'x':
            op->bit[bitno].type  = AVR_CMDBIT_IGNORE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'a':
            op->bit[bitno].type  = AVR_CMDBIT_ADDRESS;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = 8*(bitno/8) + bitno % 8;
            break;
          case 'i':
            op->bit[bitno].type  = AVR_CMDBIT_INPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'o':
            op->bit[bitno].type  = AVR_CMDBIT_OUTPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          default :
            fprintf(stderr, 
                    "%s: error at %s:%d: invalid bit specifier '%c'\n",
                    progname, infile, lineno, ch);
            exit(1);
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            fprintf(stderr, 
                    "%s: error at %s:%d: can't parse bit number from \"%s\"\n",
                    progname, infile, lineno, q);
            exit(1);
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          fprintf(stderr, 
                  "%s: error at %s:%d: invalid bit specifier \"%s\"\n",
                  progname, infile, lineno, s);
          exit(1);
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    }

    free_token(t);

  }  /* while */

  return 0;
}



