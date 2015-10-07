
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
#include "libavrdude.h"
#include "config.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int yylex(void);
int yyerror(char * errmsg, ...);
int yywarning(char * errmsg, ...);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int assign_pin_list(int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);

static int pin_name;


/* Line 189 of yacc.c  */
#line 106 "config_gram.c"

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
     K_DEFAULT_BITCLOCK = 279,
     K_DEFAULT_PARALLEL = 280,
     K_DEFAULT_PROGRAMMER = 281,
     K_DEFAULT_SAFEMODE = 282,
     K_DEFAULT_SERIAL = 283,
     K_DESC = 284,
     K_DEVICECODE = 285,
     K_STK500_DEVCODE = 286,
     K_AVR910_DEVCODE = 287,
     K_EEPROM = 288,
     K_ERRLED = 289,
     K_FLASH = 290,
     K_ID = 291,
     K_IO = 292,
     K_LOADPAGE = 293,
     K_MAX_WRITE_DELAY = 294,
     K_MCU_BASE = 295,
     K_MIN_WRITE_DELAY = 296,
     K_MISO = 297,
     K_MOSI = 298,
     K_NUM_PAGES = 299,
     K_NVM_BASE = 300,
     K_OCDREV = 301,
     K_OFFSET = 302,
     K_PAGEL = 303,
     K_PARALLEL = 304,
     K_PARENT = 305,
     K_PART = 306,
     K_PGMLED = 307,
     K_PROGRAMMER = 308,
     K_PSEUDO = 309,
     K_PWROFF_AFTER_WRITE = 310,
     K_RDYLED = 311,
     K_READBACK_P1 = 312,
     K_READBACK_P2 = 313,
     K_READMEM = 314,
     K_RESET = 315,
     K_RETRY_PULSE = 316,
     K_SERIAL = 317,
     K_SCK = 318,
     K_SIGNATURE = 319,
     K_SIZE = 320,
     K_USB = 321,
     K_USBDEV = 322,
     K_USBSN = 323,
     K_USBPID = 324,
     K_USBPRODUCT = 325,
     K_USBVENDOR = 326,
     K_USBVID = 327,
     K_TYPE = 328,
     K_VCC = 329,
     K_VFYLED = 330,
     K_NO = 331,
     K_YES = 332,
     K_TIMEOUT = 333,
     K_STABDELAY = 334,
     K_CMDEXEDELAY = 335,
     K_HVSPCMDEXEDELAY = 336,
     K_SYNCHLOOPS = 337,
     K_BYTEDELAY = 338,
     K_POLLVALUE = 339,
     K_POLLINDEX = 340,
     K_PREDELAY = 341,
     K_POSTDELAY = 342,
     K_POLLMETHOD = 343,
     K_MODE = 344,
     K_DELAY = 345,
     K_BLOCKSIZE = 346,
     K_READSIZE = 347,
     K_HVENTERSTABDELAY = 348,
     K_PROGMODEDELAY = 349,
     K_LATCHCYCLES = 350,
     K_TOGGLEVTG = 351,
     K_POWEROFFDELAY = 352,
     K_RESETDELAYMS = 353,
     K_RESETDELAYUS = 354,
     K_HVLEAVESTABDELAY = 355,
     K_RESETDELAY = 356,
     K_SYNCHCYCLES = 357,
     K_HVCMDEXEDELAY = 358,
     K_CHIPERASEPULSEWIDTH = 359,
     K_CHIPERASEPOLLTIMEOUT = 360,
     K_CHIPERASETIME = 361,
     K_PROGRAMFUSEPULSEWIDTH = 362,
     K_PROGRAMFUSEPOLLTIMEOUT = 363,
     K_PROGRAMLOCKPULSEWIDTH = 364,
     K_PROGRAMLOCKPOLLTIMEOUT = 365,
     K_PP_CONTROLSTACK = 366,
     K_HVSP_CONTROLSTACK = 367,
     K_ALLOWFULLPAGEBITSTREAM = 368,
     K_ENABLEPAGEPROGRAMMING = 369,
     K_HAS_JTAG = 370,
     K_HAS_DW = 371,
     K_HAS_PDI = 372,
     K_HAS_TPI = 373,
     K_IDR = 374,
     K_IS_AT90S1200 = 375,
     K_IS_AVR32 = 376,
     K_RAMPZ = 377,
     K_SPMCR = 378,
     K_EECR = 379,
     K_FLASH_INSTR = 380,
     K_EEPROM_INSTR = 381,
     TKN_COMMA = 382,
     TKN_EQUAL = 383,
     TKN_SEMI = 384,
     TKN_TILDE = 385,
     TKN_LEFT_PAREN = 386,
     TKN_RIGHT_PAREN = 387,
     TKN_NUMBER = 388,
     TKN_NUMBER_REAL = 389,
     TKN_STRING = 390
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
#define K_DEFAULT_BITCLOCK 279
#define K_DEFAULT_PARALLEL 280
#define K_DEFAULT_PROGRAMMER 281
#define K_DEFAULT_SAFEMODE 282
#define K_DEFAULT_SERIAL 283
#define K_DESC 284
#define K_DEVICECODE 285
#define K_STK500_DEVCODE 286
#define K_AVR910_DEVCODE 287
#define K_EEPROM 288
#define K_ERRLED 289
#define K_FLASH 290
#define K_ID 291
#define K_IO 292
#define K_LOADPAGE 293
#define K_MAX_WRITE_DELAY 294
#define K_MCU_BASE 295
#define K_MIN_WRITE_DELAY 296
#define K_MISO 297
#define K_MOSI 298
#define K_NUM_PAGES 299
#define K_NVM_BASE 300
#define K_OCDREV 301
#define K_OFFSET 302
#define K_PAGEL 303
#define K_PARALLEL 304
#define K_PARENT 305
#define K_PART 306
#define K_PGMLED 307
#define K_PROGRAMMER 308
#define K_PSEUDO 309
#define K_PWROFF_AFTER_WRITE 310
#define K_RDYLED 311
#define K_READBACK_P1 312
#define K_READBACK_P2 313
#define K_READMEM 314
#define K_RESET 315
#define K_RETRY_PULSE 316
#define K_SERIAL 317
#define K_SCK 318
#define K_SIGNATURE 319
#define K_SIZE 320
#define K_USB 321
#define K_USBDEV 322
#define K_USBSN 323
#define K_USBPID 324
#define K_USBPRODUCT 325
#define K_USBVENDOR 326
#define K_USBVID 327
#define K_TYPE 328
#define K_VCC 329
#define K_VFYLED 330
#define K_NO 331
#define K_YES 332
#define K_TIMEOUT 333
#define K_STABDELAY 334
#define K_CMDEXEDELAY 335
#define K_HVSPCMDEXEDELAY 336
#define K_SYNCHLOOPS 337
#define K_BYTEDELAY 338
#define K_POLLVALUE 339
#define K_POLLINDEX 340
#define K_PREDELAY 341
#define K_POSTDELAY 342
#define K_POLLMETHOD 343
#define K_MODE 344
#define K_DELAY 345
#define K_BLOCKSIZE 346
#define K_READSIZE 347
#define K_HVENTERSTABDELAY 348
#define K_PROGMODEDELAY 349
#define K_LATCHCYCLES 350
#define K_TOGGLEVTG 351
#define K_POWEROFFDELAY 352
#define K_RESETDELAYMS 353
#define K_RESETDELAYUS 354
#define K_HVLEAVESTABDELAY 355
#define K_RESETDELAY 356
#define K_SYNCHCYCLES 357
#define K_HVCMDEXEDELAY 358
#define K_CHIPERASEPULSEWIDTH 359
#define K_CHIPERASEPOLLTIMEOUT 360
#define K_CHIPERASETIME 361
#define K_PROGRAMFUSEPULSEWIDTH 362
#define K_PROGRAMFUSEPOLLTIMEOUT 363
#define K_PROGRAMLOCKPULSEWIDTH 364
#define K_PROGRAMLOCKPOLLTIMEOUT 365
#define K_PP_CONTROLSTACK 366
#define K_HVSP_CONTROLSTACK 367
#define K_ALLOWFULLPAGEBITSTREAM 368
#define K_ENABLEPAGEPROGRAMMING 369
#define K_HAS_JTAG 370
#define K_HAS_DW 371
#define K_HAS_PDI 372
#define K_HAS_TPI 373
#define K_IDR 374
#define K_IS_AT90S1200 375
#define K_IS_AVR32 376
#define K_RAMPZ 377
#define K_SPMCR 378
#define K_EECR 379
#define K_FLASH_INSTR 380
#define K_EEPROM_INSTR 381
#define TKN_COMMA 382
#define TKN_EQUAL 383
#define TKN_SEMI 384
#define TKN_TILDE 385
#define TKN_LEFT_PAREN 386
#define TKN_RIGHT_PAREN 387
#define TKN_NUMBER 388
#define TKN_NUMBER_REAL 389
#define TKN_STRING 390




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 418 "config_gram.c"

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNRULES -- Number of states.  */
#define YYNSTATES  418

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   390

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
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     8,    10,    12,    15,    18,
      21,    26,    31,    36,    41,    46,    49,    51,    55,    58,
      60,    64,    66,    70,    72,    76,    79,    83,    87,    89,
      91,    93,    95,    99,   103,   107,   109,   111,   115,   117,
     119,   121,   125,   129,   133,   137,   141,   145,   147,   151,
     153,   156,   158,   159,   161,   166,   168,   172,   174,   175,
     176,   181,   182,   187,   188,   193,   194,   199,   200,   205,
     206,   211,   212,   217,   218,   223,   224,   229,   230,   235,
     237,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     257,   259,   262,   266,   268,   270,   272,   274,   276,   278,
     282,   286,   290,   294,   298,   304,   308,   312,   316,   320,
     324,   328,   332,   336,   340,   344,   348,   352,   356,   360,
     364,   368,   372,   376,   380,   384,   388,   392,   396,   400,
     404,   408,   412,   416,   420,   424,   428,   432,   436,   440,
     444,   448,   452,   456,   460,   464,   468,   472,   476,   480,
     484,   488,   492,   496,   500,   504,   508,   512,   516,   520,
     524,   525,   530,   534,   536,   538,   541,   545,   549,   553,
     557,   561,   565,   569,   573,   577,   581,   585,   589,   593,
     597,   601,   605
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     138,     0,    -1,   133,    -1,   134,    -1,    -1,   139,    -1,
     140,    -1,   139,   140,    -1,   141,   129,    -1,   143,   129,
      -1,    26,   128,   135,   129,    -1,    25,   128,   135,   129,
      -1,    28,   128,   135,   129,    -1,    24,   128,   137,   129,
      -1,    27,   128,   178,   129,    -1,   142,   147,    -1,    53,
      -1,    53,    50,   135,    -1,   144,   172,    -1,    51,    -1,
      51,    50,   135,    -1,   135,    -1,   145,   127,   135,    -1,
     133,    -1,   146,   127,   133,    -1,   148,   129,    -1,   147,
     148,   129,    -1,    36,   128,   145,    -1,   149,    -1,   160,
      -1,   153,    -1,   151,    -1,    29,   128,   135,    -1,    18,
     128,   133,    -1,    73,   128,   150,    -1,   135,    -1,     1,
      -1,    22,   128,   152,    -1,    49,    -1,    62,    -1,    66,
      -1,    67,   128,   135,    -1,    72,   128,   133,    -1,    69,
     128,   154,    -1,    68,   128,   135,    -1,    71,   128,   135,
      -1,    70,   128,   135,    -1,   133,    -1,   154,   127,   133,
      -1,   133,    -1,   130,   133,    -1,   155,    -1,    -1,   155,
      -1,   130,   131,   146,   132,    -1,   157,    -1,   158,   127,
     157,    -1,   158,    -1,    -1,    -1,    74,   128,   161,   159,
      -1,    -1,    20,   128,   162,   159,    -1,    -1,    60,   128,
     163,   156,    -1,    -1,    63,   128,   164,   156,    -1,    -1,
      43,   128,   165,   156,    -1,    -1,    42,   128,   166,   156,
      -1,    -1,    34,   128,   167,   156,    -1,    -1,    56,   128,
     168,   156,    -1,    -1,    52,   128,   169,   156,    -1,    -1,
      75,   128,   170,   156,    -1,     3,    -1,     4,    -1,     5,
      -1,     6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,   176,
     129,    -1,   172,   176,   129,    -1,    23,    -1,    37,    -1,
     178,    -1,    54,    -1,    60,    -1,    63,    -1,    36,   128,
     135,    -1,    29,   128,   135,    -1,    30,   128,   133,    -1,
      31,   128,   133,    -1,    32,   128,   133,    -1,    64,   128,
     133,   133,   133,    -1,    69,   128,   133,    -1,   111,   128,
     146,    -1,   112,   128,   146,    -1,   125,   128,   146,    -1,
     126,   128,   146,    -1,    21,   128,   133,    -1,    48,   128,
     133,    -1,    19,   128,   133,    -1,    60,   128,   173,    -1,
      78,   128,   133,    -1,    79,   128,   133,    -1,    80,   128,
     133,    -1,    81,   128,   133,    -1,    82,   128,   133,    -1,
      83,   128,   133,    -1,    84,   128,   133,    -1,    85,   128,
     133,    -1,    86,   128,   133,    -1,    87,   128,   133,    -1,
      88,   128,   133,    -1,    93,   128,   133,    -1,    94,   128,
     133,    -1,    95,   128,   133,    -1,    96,   128,   133,    -1,
      97,   128,   133,    -1,    98,   128,   133,    -1,    99,   128,
     133,    -1,   100,   128,   133,    -1,   101,   128,   133,    -1,
     104,   128,   133,    -1,   105,   128,   133,    -1,   106,   128,
     133,    -1,   107,   128,   133,    -1,   108,   128,   133,    -1,
     109,   128,   133,    -1,   110,   128,   133,    -1,   102,   128,
     133,    -1,   115,   128,   178,    -1,   116,   128,   178,    -1,
     117,   128,   178,    -1,   118,   128,   178,    -1,   120,   128,
     178,    -1,   121,   128,   178,    -1,   113,   128,   178,    -1,
     114,   128,   178,    -1,   119,   128,   133,    -1,   122,   128,
     133,    -1,   123,   128,   133,    -1,   124,   128,   133,    -1,
      40,   128,   133,    -1,    45,   128,   133,    -1,    46,   128,
     133,    -1,    62,   128,   178,    -1,    49,   128,   174,    -1,
      61,   128,   175,    -1,    -1,    15,   135,   177,   179,    -1,
     171,   128,   145,    -1,    77,    -1,    76,    -1,   180,   129,
      -1,   179,   180,   129,    -1,    17,   128,   178,    -1,    65,
     128,   133,    -1,    16,   128,   133,    -1,    44,   128,   133,
      -1,    47,   128,   133,    -1,    41,   128,   133,    -1,    39,
     128,   133,    -1,    55,   128,   178,    -1,    57,   128,   133,
      -1,    58,   128,   133,    -1,    89,   128,   133,    -1,    90,
     128,   133,    -1,    91,   128,   133,    -1,    92,   128,   133,
      -1,    85,   128,   133,    -1,   171,   128,   145,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   211,   211,   217,   221,   222,   226,   227,   232,   234,
     236,   242,   248,   254,   259,   270,   303,   313,   335,   393,
     403,   426,   427,   432,   433,   437,   438,   442,   465,   467,
     469,   471,   473,   478,   487,   491,   501,   509,   513,   514,
     515,   519,   526,   532,   533,   540,   547,   557,   572,   585,
     587,   591,   593,   597,   599,   603,   605,   610,   612,   616,
     616,   617,   617,   618,   618,   619,   619,   620,   620,   621,
     621,   622,   622,   623,   623,   624,   624,   625,   625,   629,
     630,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   645,   646,   651,   651,   655,   655,   659,   659,   663,
     670,   677,   685,   692,   699,   710,   717,   748,   779,   809,
     839,   845,   851,   857,   867,   873,   879,   885,   891,   897,
     903,   909,   915,   921,   927,   933,   939,   945,   951,   957,
     963,   969,   975,   981,   987,   993,   999,  1005,  1011,  1017,
    1023,  1029,  1035,  1045,  1055,  1065,  1075,  1085,  1095,  1105,
    1115,  1121,  1127,  1133,  1139,  1145,  1151,  1157,  1167,  1186,
    1210,  1209,  1234,  1261,  1261,  1266,  1267,  1272,  1278,  1285,
    1291,  1297,  1303,  1309,  1315,  1321,  1327,  1334,  1340,  1346,
    1352,  1358,  1365
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
  "K_DEFAULT_BITCLOCK", "K_DEFAULT_PARALLEL", "K_DEFAULT_PROGRAMMER",
  "K_DEFAULT_SAFEMODE", "K_DEFAULT_SERIAL", "K_DESC", "K_DEVICECODE",
  "K_STK500_DEVCODE", "K_AVR910_DEVCODE", "K_EEPROM", "K_ERRLED",
  "K_FLASH", "K_ID", "K_IO", "K_LOADPAGE", "K_MAX_WRITE_DELAY",
  "K_MCU_BASE", "K_MIN_WRITE_DELAY", "K_MISO", "K_MOSI", "K_NUM_PAGES",
  "K_NVM_BASE", "K_OCDREV", "K_OFFSET", "K_PAGEL", "K_PARALLEL",
  "K_PARENT", "K_PART", "K_PGMLED", "K_PROGRAMMER", "K_PSEUDO",
  "K_PWROFF_AFTER_WRITE", "K_RDYLED", "K_READBACK_P1", "K_READBACK_P2",
  "K_READMEM", "K_RESET", "K_RETRY_PULSE", "K_SERIAL", "K_SCK",
  "K_SIGNATURE", "K_SIZE", "K_USB", "K_USBDEV", "K_USBSN", "K_USBPID",
  "K_USBPRODUCT", "K_USBVENDOR", "K_USBVID", "K_TYPE", "K_VCC", "K_VFYLED",
  "K_NO", "K_YES", "K_TIMEOUT", "K_STABDELAY", "K_CMDEXEDELAY",
  "K_HVSPCMDEXEDELAY", "K_SYNCHLOOPS", "K_BYTEDELAY", "K_POLLVALUE",
  "K_POLLINDEX", "K_PREDELAY", "K_POSTDELAY", "K_POLLMETHOD", "K_MODE",
  "K_DELAY", "K_BLOCKSIZE", "K_READSIZE", "K_HVENTERSTABDELAY",
  "K_PROGMODEDELAY", "K_LATCHCYCLES", "K_TOGGLEVTG", "K_POWEROFFDELAY",
  "K_RESETDELAYMS", "K_RESETDELAYUS", "K_HVLEAVESTABDELAY", "K_RESETDELAY",
  "K_SYNCHCYCLES", "K_HVCMDEXEDELAY", "K_CHIPERASEPULSEWIDTH",
  "K_CHIPERASEPOLLTIMEOUT", "K_CHIPERASETIME", "K_PROGRAMFUSEPULSEWIDTH",
  "K_PROGRAMFUSEPOLLTIMEOUT", "K_PROGRAMLOCKPULSEWIDTH",
  "K_PROGRAMLOCKPOLLTIMEOUT", "K_PP_CONTROLSTACK", "K_HVSP_CONTROLSTACK",
  "K_ALLOWFULLPAGEBITSTREAM", "K_ENABLEPAGEPROGRAMMING", "K_HAS_JTAG",
  "K_HAS_DW", "K_HAS_PDI", "K_HAS_TPI", "K_IDR", "K_IS_AT90S1200",
  "K_IS_AVR32", "K_RAMPZ", "K_SPMCR", "K_EECR", "K_FLASH_INSTR",
  "K_EEPROM_INSTR", "TKN_COMMA", "TKN_EQUAL", "TKN_SEMI", "TKN_TILDE",
  "TKN_LEFT_PAREN", "TKN_RIGHT_PAREN", "TKN_NUMBER", "TKN_NUMBER_REAL",
  "TKN_STRING", "$accept", "number_real", "configuration", "config", "def",
  "prog_def", "prog_decl", "part_def", "part_decl", "string_list",
  "num_list", "prog_parms", "prog_parm", "prog_parm_type",
  "prog_parm_type_id", "prog_parm_conntype", "prog_parm_conntype_id",
  "prog_parm_usb", "usb_pid_list", "pin_number_non_empty", "pin_number",
  "pin_list_element", "pin_list_non_empty", "pin_list", "prog_parm_pins",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "opcode", "part_parms", "reset_disposition", "parallel_modes",
  "retry_lines", "part_parm", "$@11", "yesno", "mem_specs", "mem_spec", 0
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
     385,   386,   387,   388,   389,   390
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     140,   140,   140,   140,   140,   141,   142,   142,   143,   144,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   149,   150,   150,   151,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159,   161,
     160,   162,   160,   163,   160,   164,   160,   165,   160,   166,
     160,   167,   160,   168,   160,   169,   160,   170,   160,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   172,   172,   173,   173,   174,   174,   175,   175,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     177,   176,   176,   178,   178,   179,   179,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     1,     2,     2,     2,
       4,     4,     4,     4,     4,     2,     1,     3,     2,     1,
       3,     1,     3,     1,     3,     2,     3,     3,     1,     1,
       1,     1,     3,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       2,     1,     0,     1,     4,     1,     3,     1,     0,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,     0,    19,    16,     0,     5,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,    28,    31,
      30,    29,     9,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       2,     3,     0,     0,     0,   164,   163,     0,     0,    20,
      17,     0,    61,     0,     0,    71,     0,    69,    67,    75,
      73,    63,    65,     0,     0,     0,     0,     0,     0,     0,
      59,    77,     0,    25,   160,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    13,
      11,    10,    14,    12,    33,    58,    38,    39,    40,    37,
      32,    52,    21,    27,    52,    52,    52,    52,    52,    52,
      41,    44,    47,    43,    46,    45,    42,    36,    35,    34,
      58,    52,    26,     0,   112,   110,   100,   101,   102,   103,
      99,   154,   155,   156,   111,    96,   158,    95,    93,    94,
     113,    97,    98,   159,   157,     0,   105,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   141,   134,   135,
     136,   137,   138,   139,   140,    23,   106,   107,   148,   149,
     142,   143,   144,   145,   150,   146,   147,   151,   152,   153,
     108,   109,   162,    92,     0,    49,    53,    55,    57,    62,
       0,    51,    72,     0,    70,    68,    76,    74,    64,    66,
       0,    60,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   161,
       0,     0,     0,     0,    50,     0,    22,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165,   104,    24,     0,    56,
     169,   167,   173,   172,   170,   171,   174,   175,   176,   168,
     181,   177,   178,   179,   180,   182,   166,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   132,     8,     9,    10,    11,    12,    13,    14,   243,
     316,    46,    47,    48,   259,    49,   239,    50,   253,   341,
     342,   337,   338,   339,    51,   260,   235,   248,   249,   245,
     244,   241,   247,   246,   261,   127,   128,   280,   276,   283,
     129,   263,   137,   369,   370
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -258
static const yytype_int16 yypact[] =
{
      23,  -119,   -83,   -82,   -68,   -50,     2,    31,    82,    23,
    -258,   -39,    55,   -37,   166,   -99,   -42,   -41,   -63,   -40,
     -35,   -34,  -258,  -258,  -258,   -43,   -32,   -26,   -20,   -19,
     -18,   -15,   -14,   -12,   -11,    -9,    -8,    -7,     3,     5,
       6,     7,     8,     9,    10,    12,    55,    13,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,    -3,    15,    17,    18,    20,
      22,    24,    25,    26,    27,    28,    29,    30,    32,    33,
      34,    35,    37,    38,    39,    54,    56,    58,    60,    61,
      62,    63,    64,    65,    66,    71,    72,    73,    76,    77,
      79,    81,    85,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   101,   103,   104,   105,   106,   108,   109,
     110,   111,   112,   113,   114,   115,   127,   128,   166,   129,
    -258,  -258,   140,   164,   165,  -258,  -258,   167,   168,  -258,
    -258,    16,  -258,    21,    48,  -258,    75,  -258,  -258,  -258,
    -258,  -258,  -258,   122,   160,   169,   163,   170,   171,     4,
    -258,  -258,   172,  -258,  -258,   173,   174,   175,   176,   178,
     179,   180,   181,   183,   184,   185,   -44,    19,   -52,   -63,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   216,   -63,   -63,   -63,   -63,   -63,   -63,   217,   -63,
     -63,   218,   219,   220,   216,   216,    75,   225,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   -76,  -258,  -258,  -258,  -258,
    -258,   -71,  -258,   228,   -71,   -71,   -71,   -71,   -71,   -71,
    -258,  -258,  -258,   229,  -258,  -258,  -258,  -258,  -258,  -258,
     -76,   -71,  -258,    14,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   224,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,   231,   231,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
     231,   231,   228,  -258,   -45,  -258,  -258,  -258,   232,  -258,
     227,  -258,  -258,   226,  -258,  -258,  -258,  -258,  -258,  -258,
     230,  -258,  -258,   234,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,    14,
     251,   252,   253,   216,  -258,   -76,  -258,  -258,   254,   -63,
     255,   256,   257,   258,   -63,   259,   260,   261,   262,   263,
     264,   265,   266,    75,   271,  -258,  -258,  -258,  -120,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   228,  -258,  -258
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,   132,  -258,  -258,  -258,  -258,  -225,
    -209,  -258,   267,  -258,  -258,  -258,  -258,  -258,  -258,  -231,
    -181,  -228,  -258,  -109,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -257,  -258,  -258,  -258,  -258,
     273,  -258,  -176,  -258,  -210
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     277,   332,   317,   284,   336,   257,   368,   372,   281,    15,
     275,   282,   417,   135,   136,   330,   331,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   336,
     353,   354,   135,   136,   130,   131,   318,   319,   320,   321,
     322,   323,   278,   325,   326,    16,    17,     1,     2,     3,
       4,     5,    20,   355,   334,   356,   279,   335,   357,   340,
      18,   358,   335,   344,   345,   346,   347,   348,   349,   359,
     236,   360,   361,    25,     6,    26,     7,    27,    19,   362,
     352,    21,    22,   237,    28,   141,   373,   238,   374,    29,
      24,    30,    52,   133,   134,   138,   142,    31,    32,   363,
     139,   140,   143,   364,   365,   366,   367,    33,   144,   145,
     146,    34,   368,   147,   148,    35,   149,   150,    36,   151,
     152,   153,    37,    38,    39,    40,    41,    42,    43,    44,
      45,   154,   164,   155,   156,   157,   158,   159,   160,   258,
     161,    23,   163,   165,   336,   166,   167,   399,   168,   234,
     169,   351,   170,   171,   172,   173,   174,   175,   176,   394,
     177,   178,   179,   180,   398,   181,   182,   183,   415,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,   184,   240,   185,    66,   186,    67,   187,   188,
     189,   190,   191,   192,   193,    68,    69,    70,    71,   194,
     195,   196,    72,   401,   197,   198,    73,   199,   406,   200,
     242,    74,    75,   201,    76,    77,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,    78,    79,    80,   212,
      81,   213,   214,   215,   216,    82,   217,   218,   219,   220,
     221,   222,   223,   224,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   225,   226,   250,   228,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   229,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   230,   231,   251,   232,   233,   254,     0,
       0,   262,   252,     0,   256,   255,   264,   265,     0,   267,
     266,   268,   269,   162,   271,   270,   272,   273,   274,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     324,   327,   328,   329,   333,   343,   350,   371,   372,   375,
     374,   376,   378,   377,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,     0,
     395,     0,     0,     0,     0,   396,   397,   400,   402,   403,
     404,   405,   407,   408,   409,   410,   411,   412,   413,   414,
     416,   227
};

static const yytype_int16 yycheck[] =
{
     176,   226,   211,   179,   235,     1,   263,   127,    60,   128,
      54,    63,   132,    76,    77,   224,   225,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   260,
      16,    17,    76,    77,   133,   134,   212,   213,   214,   215,
     216,   217,    23,   219,   220,   128,   128,    24,    25,    26,
      27,    28,    50,    39,   130,    41,    37,   133,    44,   130,
     128,    47,   133,   244,   245,   246,   247,   248,   249,    55,
      49,    57,    58,    18,    51,    20,    53,    22,   128,    65,
     261,    50,     0,    62,    29,   128,   131,    66,   133,    34,
     129,    36,   129,   135,   135,   135,   128,    42,    43,    85,
     135,   135,   128,    89,    90,    91,    92,    52,   128,   128,
     128,    56,   369,   128,   128,    60,   128,   128,    63,   128,
     128,   128,    67,    68,    69,    70,    71,    72,    73,    74,
      75,   128,   135,   128,   128,   128,   128,   128,   128,   135,
     128,     9,   129,   128,   375,   128,   128,   375,   128,   133,
     128,   260,   128,   128,   128,   128,   128,   128,   128,   369,
     128,   128,   128,   128,   373,   128,   128,   128,   393,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,   128,   135,   128,    19,   128,    21,   128,   128,
     128,   128,   128,   128,   128,    29,    30,    31,    32,   128,
     128,   128,    36,   379,   128,   128,    40,   128,   384,   128,
     135,    45,    46,   128,    48,    49,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,    60,    61,    62,   128,
      64,   128,   128,   128,   128,    69,   128,   128,   128,   128,
     128,   128,   128,   128,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   128,   128,   135,   129,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   129,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   129,   129,   135,   129,   129,   135,    -1,
      -1,   129,   133,    -1,   133,   135,   133,   133,    -1,   133,
     135,   133,   133,    46,   133,   135,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   129,   127,   127,   133,   127,   127,
     133,   135,   128,   133,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,    -1,
     129,    -1,    -1,    -1,    -1,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     129,   128
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    26,    27,    28,    51,    53,   138,   139,
     140,   141,   142,   143,   144,   128,   128,   128,   128,   128,
      50,    50,     0,   140,   129,    18,    20,    22,    29,    34,
      36,    42,    43,    52,    56,    60,    63,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   147,   148,   149,   151,
     153,   160,   129,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    19,    21,    29,    30,
      31,    32,    36,    40,    45,    46,    48,    49,    60,    61,
      62,    64,    69,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   171,   172,   176,
     133,   134,   137,   135,   135,    76,    77,   178,   135,   135,
     135,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   148,   129,   135,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   176,   129,   129,
     129,   129,   129,   129,   133,   162,    49,    62,    66,   152,
     135,   167,   135,   145,   166,   165,   169,   168,   163,   164,
     135,   135,   133,   154,   135,   135,   133,     1,   135,   150,
     161,   170,   129,   177,   133,   133,   135,   133,   133,   133,
     135,   133,   133,   133,   133,    54,   174,   178,    23,    37,
     173,    60,    63,   175,   178,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   146,   146,   178,   178,
     178,   178,   178,   178,   133,   178,   178,   133,   133,   133,
     146,   146,   145,   129,   130,   133,   155,   157,   158,   159,
     130,   155,   156,   127,   156,   156,   156,   156,   156,   156,
     127,   159,   156,    16,    17,    39,    41,    44,    47,    55,
      57,    58,    65,    85,    89,    90,    91,    92,   171,   179,
     180,   133,   127,   131,   133,   127,   135,   133,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   180,   129,   133,   133,   146,   157,
     133,   178,   133,   133,   133,   133,   178,   133,   133,   133,
     133,   133,   133,   133,   133,   145,   129,   132
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
#line 211 "config_gram.y"
    {
    (yyval) = (yyvsp[(1) - (1)]);
    /* convert value to real */
    (yyval)->value.number_real = (yyval)->value.number;
    (yyval)->value.type = V_NUM_REAL;
  }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 217 "config_gram.y"
    {
    (yyval) = (yyvsp[(1) - (1)]);
  }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 236 "config_gram.y"
    {
    strncpy(default_programmer, (yyvsp[(3) - (4)])->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 242 "config_gram.y"
    {
    strncpy(default_parallel, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 248 "config_gram.y"
    {
    strncpy(default_serial, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 254 "config_gram.y"
    {
    default_bitclock = (yyvsp[(3) - (4)])->value.number_real;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 259 "config_gram.y"
    {
    if ((yyvsp[(3) - (4)])->primary == K_YES)
      default_safemode = 1;
    else if ((yyvsp[(3) - (4)])->primary == K_NO)
      default_safemode = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 271 "config_gram.y"
    {
      PROGRAMMER * existing_prog;
      char * id;
      if (lsize(current_prog->id) == 0) {
        yyerror("required parameter id not specified");
        YYABORT;
      }
      if (current_prog->initpgm == NULL) {
        yyerror("programmer type not specified");
        YYABORT;
      }
      id = ldata(lfirst(current_prog->id));
      existing_prog = locate_programmer(programmers, id);
      if (existing_prog) {
        { /* temporarly set lineno to lineno of programmer start */
          int temp = lineno; lineno = current_prog->lineno;
          yywarning("programmer %s overwrites previous definition %s:%d.",
                id, existing_prog->config_file, existing_prog->lineno);
          lineno = temp;
        }
        lrmv_d(programmers, existing_prog);
        pgm_free(existing_prog);
      }
      PUSH(programmers, current_prog);
//      pgm_fill_old_pins(current_prog); // TODO to be removed if old pin data no longer needed
//      pgm_display_generic(current_prog, id);
      current_prog = NULL;
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 304 "config_gram.y"
    { current_prog = pgm_new();
      if (current_prog == NULL) {
        yyerror("could not create pgm instance");
        YYABORT;
      }
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 314 "config_gram.y"
    {
      struct programmer_t * pgm = locate_programmer(programmers, (yyvsp[(3) - (3)])->value.string);
      if (pgm == NULL) {
        yyerror("parent programmer %s not found", (yyvsp[(3) - (3)])->value.string);
        free_token((yyvsp[(3) - (3)]));
        YYABORT;
      }
      current_prog = pgm_dup(pgm);
      if (current_prog == NULL) {
        yyerror("could not duplicate pgm instance");
        free_token((yyvsp[(3) - (3)]));
        YYABORT;
      }
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 336 "config_gram.y"
    { 
      LNODEID ln;
      AVRMEM * m;
      AVRPART * existing_part;

      if (current_part->id[0] == 0) {
        yyerror("required parameter id not specified");
        YYABORT;
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
            yyerror("must specify page_size for paged memory");
            YYABORT;
          }
          if (m->num_pages == 0) {
            yyerror("must specify num_pages for paged memory");
            YYABORT;
          }
          if (m->size != m->page_size * m->num_pages) {
            yyerror("page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)",
                    m->page_size,
                    m->num_pages,
                    m->page_size * m->num_pages,
                    m->size);
            YYABORT;
          }

        }
      }

      existing_part = locate_part(part_list, current_part->id);
      if (existing_part) {
        { /* temporarly set lineno to lineno of part start */
          int temp = lineno; lineno = current_part->lineno;
          yywarning("part %s overwrites previous definition %s:%d.",
                current_part->id,
                existing_part->config_file, existing_part->lineno);
          lineno = temp;
        }
        lrmv_d(part_list, existing_part);
        avr_free_part(existing_part);
      }
      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 394 "config_gram.y"
    {
      current_part = avr_new_part();
      if (current_part == NULL) {
        yyerror("could not create part instance");
        YYABORT;
      }
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 404 "config_gram.y"
    {
      AVRPART * parent_part = locate_part(part_list, (yyvsp[(3) - (3)])->value.string);
      if (parent_part == NULL) {
        yyerror("can't find parent part");
        free_token((yyvsp[(3) - (3)]));
        YYABORT;
      }

      current_part = avr_dup_part(parent_part);
      if (current_part == NULL) {
        yyerror("could not duplicate part instance");
        free_token((yyvsp[(3) - (3)]));
        YYABORT;
      }
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 426 "config_gram.y"
    { ladd(string_list, (yyvsp[(1) - (1)])); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 427 "config_gram.y"
    { ladd(string_list, (yyvsp[(3) - (3)])); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 432 "config_gram.y"
    { ladd(number_list, (yyvsp[(1) - (1)])); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 433 "config_gram.y"
    { ladd(number_list, (yyvsp[(3) - (3)])); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 442 "config_gram.y"
    {
    {
      TOKEN * t;
      char *s;
      int do_yyabort = 0;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        if (!do_yyabort) {
          s = dup_string(t->value.string);
          if (s == NULL) {
            do_yyabort = 1;
          } else {
            ladd(current_prog->id, s);
          }
        }
        /* if do_yyabort == 1 just make the list empty */
        free_token(t);
      }
      if (do_yyabort) {
        YYABORT;
      }
    }
  }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 473 "config_gram.y"
    {
    strncpy(current_prog->desc, (yyvsp[(3) - (3)])->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token((yyvsp[(3) - (3)]));
  }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 478 "config_gram.y"
    {
    {
      current_prog->baudrate = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 491 "config_gram.y"
    {
  const struct programmer_type_t * pgm_type = locate_programmer_type((yyvsp[(1) - (1)])->value.string);
    if (pgm_type == NULL) {
        yyerror("programmer type %s not found", (yyvsp[(1) - (1)])->value.string);
        free_token((yyvsp[(1) - (1)])); 
        YYABORT;
    }
    current_prog->initpgm = pgm_type->initpgm;
    free_token((yyvsp[(1) - (1)])); 
}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 502 "config_gram.y"
    {
        yyerror("programmer type must be written as \"id_type\"");
        YYABORT;
}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 513 "config_gram.y"
    { current_prog->conntype = CONNTYPE_PARALLEL; }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 514 "config_gram.y"
    { current_prog->conntype = CONNTYPE_SERIAL; }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 515 "config_gram.y"
    { current_prog->conntype = CONNTYPE_USB; }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 519 "config_gram.y"
    {
    {
      strncpy(current_prog->usbdev, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbdev[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 526 "config_gram.y"
    {
    {
      current_prog->usbvid = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 533 "config_gram.y"
    {
    {
      strncpy(current_prog->usbsn, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbsn[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 540 "config_gram.y"
    {
    {
      strncpy(current_prog->usbvendor, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbvendor[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 547 "config_gram.y"
    {
    {
      strncpy(current_prog->usbproduct, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbproduct[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 557 "config_gram.y"
    {
    {
      /* overwrite pids, so clear the existing entries */
      ldestroy_cb(current_prog->usbpid, free);
      current_prog->usbpid = lcreat(NULL, 0);
    }
    {
      int *ip = malloc(sizeof(int));
      if (ip) {
        *ip = (yyvsp[(1) - (1)])->value.number;
        ladd(current_prog->usbpid, ip);
      }
      free_token((yyvsp[(1) - (1)]));
    }
  }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 572 "config_gram.y"
    {
    {
      int *ip = malloc(sizeof(int));
      if (ip) {
        *ip = (yyvsp[(3) - (3)])->value.number;
        ladd(current_prog->usbpid, ip);
      }
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 585 "config_gram.y"
    { if(0 != assign_pin(pin_name, (yyvsp[(1) - (1)]), 0)) YYABORT;  }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 587 "config_gram.y"
    { if(0 != assign_pin(pin_name, (yyvsp[(2) - (2)]), 1)) YYABORT; }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 593 "config_gram.y"
    { pin_clear_all(&(current_prog->pin[pin_name])); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 599 "config_gram.y"
    { if(0 != assign_pin_list(1)) YYABORT; }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 612 "config_gram.y"
    { pin_clear_all(&(current_prog->pin[pin_name])); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 616 "config_gram.y"
    {pin_name = PPI_AVR_VCC;  }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 617 "config_gram.y"
    {pin_name = PPI_AVR_BUFF; }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 618 "config_gram.y"
    {pin_name = PIN_AVR_RESET;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 618 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 619 "config_gram.y"
    {pin_name = PIN_AVR_SCK;  }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 619 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 620 "config_gram.y"
    {pin_name = PIN_AVR_MOSI; }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 621 "config_gram.y"
    {pin_name = PIN_AVR_MISO; }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 622 "config_gram.y"
    {pin_name = PIN_LED_ERR;  }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 623 "config_gram.y"
    {pin_name = PIN_LED_RDY;  }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 624 "config_gram.y"
    {pin_name = PIN_LED_PGM;  }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 625 "config_gram.y"
    {pin_name = PIN_LED_VFY;  }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 664 "config_gram.y"
    {
      strncpy(current_part->id, (yyvsp[(3) - (3)])->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 671 "config_gram.y"
    {
      strncpy(current_part->desc, (yyvsp[(3) - (3)])->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 677 "config_gram.y"
    {
    {
      yyerror("devicecode is deprecated, use "
              "stk500_devcode instead");
      YYABORT;
    }
  }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 685 "config_gram.y"
    {
    {
      current_part->stk500_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 692 "config_gram.y"
    {
    {
      current_part->avr910_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 699 "config_gram.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 710 "config_gram.y"
    {
    {
      current_part->usbpid = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 717 "config_gram.y"
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
	  yywarning("too many bytes in control stack");
        }
    }
  }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 748 "config_gram.y"
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
	  yywarning("too many bytes in control stack");
        }
    }
  }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 779 "config_gram.y"
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
	  yywarning("too many bytes in flash instructions");
        }
    }
  }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 809 "config_gram.y"
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
	  yywarning("too many bytes in EEPROM instructions");
        }
    }
  }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 840 "config_gram.y"
    {
      current_part->chip_erase_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 846 "config_gram.y"
    {
      current_part->pagel = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 852 "config_gram.y"
    {
      current_part->bs2 = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 858 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if ((yyvsp[(3) - (3)])->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 868 "config_gram.y"
    {
      current_part->timeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 874 "config_gram.y"
    {
      current_part->stabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 880 "config_gram.y"
    {
      current_part->cmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 886 "config_gram.y"
    {
      current_part->hvspcmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 892 "config_gram.y"
    {
      current_part->synchloops = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 898 "config_gram.y"
    {
      current_part->bytedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 904 "config_gram.y"
    {
      current_part->pollvalue = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 910 "config_gram.y"
    {
      current_part->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 916 "config_gram.y"
    {
      current_part->predelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 922 "config_gram.y"
    {
      current_part->postdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 928 "config_gram.y"
    {
      current_part->pollmethod = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 934 "config_gram.y"
    {
      current_part->hventerstabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 940 "config_gram.y"
    {
      current_part->progmodedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 946 "config_gram.y"
    {
      current_part->latchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 952 "config_gram.y"
    {
      current_part->togglevtg = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 958 "config_gram.y"
    {
      current_part->poweroffdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 964 "config_gram.y"
    {
      current_part->resetdelayms = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 970 "config_gram.y"
    {
      current_part->resetdelayus = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 976 "config_gram.y"
    {
      current_part->hvleavestabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 982 "config_gram.y"
    {
      current_part->resetdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 988 "config_gram.y"
    {
      current_part->chiperasepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 994 "config_gram.y"
    {
      current_part->chiperasepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1000 "config_gram.y"
    {
      current_part->chiperasetime = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1006 "config_gram.y"
    {
      current_part->programfusepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1012 "config_gram.y"
    {
      current_part->programfusepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1018 "config_gram.y"
    {
      current_part->programlockpulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1024 "config_gram.y"
    {
      current_part->programlockpolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1030 "config_gram.y"
    {
      current_part->synchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1036 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1046 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1056 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1066 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1076 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_IS_AT90S1200;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_IS_AT90S1200;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1086 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_AVR32;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1096 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1106 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1116 "config_gram.y"
    {
      current_part->idr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1122 "config_gram.y"
    {
      current_part->rampz = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1128 "config_gram.y"
    {
      current_part->spmcr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1134 "config_gram.y"
    {
      current_part->eecr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1140 "config_gram.y"
    {
      current_part->mcu_base = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1146 "config_gram.y"
    {
      current_part->nvm_base = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1152 "config_gram.y"
    {
      current_part->ocdrev = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1158 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1168 "config_gram.y"
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

  case 159:

/* Line 1455 of yacc.c  */
#line 1187 "config_gram.y"
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

  case 160:

/* Line 1455 of yacc.c  */
#line 1210 "config_gram.y"
    {
      current_mem = avr_new_memtype();
      if (current_mem == NULL) {
        yyerror("could not create mem instance");
        free_token((yyvsp[(2) - (2)]));
        YYABORT;
      }
      strncpy(current_mem->desc, (yyvsp[(2) - (2)])->value.string, AVR_MEMDESCLEN);
      current_mem->desc[AVR_MEMDESCLEN-1] = 0;
      free_token((yyvsp[(2) - (2)]));
    }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1222 "config_gram.y"
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

  case 162:

/* Line 1455 of yacc.c  */
#line 1234 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      if (opnum < 0) YYABORT;
      op = avr_new_opcode();
      if (op == NULL) {
        yyerror("could not create opcode instance");
        free_token((yyvsp[(1) - (3)]));
        YYABORT;
      }
      if(0 != parse_cmdbits(op)) YYABORT;
      if (current_part->op[opnum] != NULL) {
        /*yywarning("operation redefined");*/
        avr_free_opcode(current_part->op[opnum]);
      }
      current_part->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1273 "config_gram.y"
    {
      current_mem->paged = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1279 "config_gram.y"
    {
      current_mem->size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1286 "config_gram.y"
    {
      current_mem->page_size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1292 "config_gram.y"
    {
      current_mem->num_pages = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1298 "config_gram.y"
    {
      current_mem->offset = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1304 "config_gram.y"
    {
      current_mem->min_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1310 "config_gram.y"
    {
      current_mem->max_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1316 "config_gram.y"
    {
      current_mem->pwroff_after_write = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1322 "config_gram.y"
    {
      current_mem->readback[0] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1328 "config_gram.y"
    {
      current_mem->readback[1] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1335 "config_gram.y"
    {
      current_mem->mode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1341 "config_gram.y"
    {
      current_mem->delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1347 "config_gram.y"
    {
      current_mem->blocksize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1353 "config_gram.y"
    {
      current_mem->readsize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1359 "config_gram.y"
    {
      current_mem->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1365 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      if (opnum < 0) YYABORT;
      op = avr_new_opcode();
      if (op == NULL) {
        yyerror("could not create opcode instance");
        free_token((yyvsp[(1) - (3)]));
        YYABORT;
      }
      if(0 != parse_cmdbits(op)) YYABORT;
      if (current_mem->op[opnum] != NULL) {
        /*yywarning("operation redefined");*/
        avr_free_opcode(current_mem->op[opnum]);
      }
      current_mem->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;



/* Line 1455 of yacc.c  */
#line 3630 "config_gram.c"
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
#line 1391 "config_gram.y"


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
    yyerror("pin must be in the range " TOSTRING(PIN_MIN) "-"  TOSTRING(PIN_MAX));
    return -1;
  }

  pin_set_value(&(current_prog->pin[pinno]), value, invert);

  return 0;
}

static int assign_pin_list(int invert)
{
  TOKEN * t;
  int pin;
  int rv = 0;

  current_prog->pinno[pin_name] = 0;
  while (lsize(number_list)) {
    t = lrmv_n(number_list, 1);
    if (rv == 0) {
      pin = t->value.number;
      if ((pin < PIN_MIN) || (pin > PIN_MAX)) {
        yyerror("pin must be in the range " TOSTRING(PIN_MIN) "-"  TOSTRING(PIN_MAX));
        rv = -1;
      /* loop clears list and frees tokens */
      }
      pin_set_value(&(current_prog->pin[pin_name]), pin, invert);
    }
    free_token(t);
  }
  return rv;
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
      yyerror("invalid opcode");
      return -1;
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
  int rv = 0;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (rv == 0 && s != NULL) {

      bitno--;
      if (bitno < 0) {
        yyerror("too many opcode bits for instruction");
        rv = -1;
        break;
      }

      len = strlen(s);

      if (len == 0) {
        yyerror("invalid bit specifier \"\"");
        rv = -1;
        break;
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
            yyerror("invalid bit specifier '%c'", ch);
            rv = -1;
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            yyerror("can't parse bit number from \"%s\"", q);
            rv = -1;
            break;
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          yyerror("invalid bit specifier \"%s\"", s);
          rv = -1;
          break;
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    } /* while */

    free_token(t);

  }  /* while */

  return rv;
}

