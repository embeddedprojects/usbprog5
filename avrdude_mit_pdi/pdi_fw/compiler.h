/**
 * \file
 *
 * \brief Commonly used includes, types and macros.
 *
 * Copyright (C) 2010 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef UTILS_COMPILER_H
#define UTILS_COMPILER_H

#if defined(__GNUC__)
#  include <avr/io.h>
#elif defined(__ICCAVR__)
#  include <ioavr.h>
#  include <intrinsics.h>
#else
#  error Unsupported compiler.
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

// TODO: clean up this file. What belongs where?

#ifdef __ICCAVR__
/*! \name Compiler Keywords
 *
 * Port of some keywords from GCC to IAR Embedded Workbench.
 */
//! @{
#define __asm__            asm
#define __inline__         inline
#define __volatile__
//! @}
#endif

/**
 * \def barrier
 * \brief Memory barrier
 */
#ifdef __GNUC__
#  define barrier()        asm volatile("" ::: "memory")
#else
#  define barrier()        asm ("")
#endif

/**
 * \brief Emit the compiler pragma \a arg.
 *
 * \param arg The pragma directive as it would appear after \e \#pragma
 * (i.e. not stringified).
 */
#define COMPILER_PRAGMA(arg)            _Pragma(#arg)

/*
 * AVR arch does not care about alignment anyway.
 */
#define COMPILER_PACK_RESET(alignment)
#define COMPILER_PACK_SET(alignment)

/**
 * \brief Set word-aligned boundary.
 */
#if (defined __GNUC__)
#define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(2)))
#elif (defined __ICCAVR__)
#define COMPILER_WORD_ALIGNED    COMPILER_PRAGMA(data_alignment = 2)
#endif



/*! \name Usual Types
 */
//! @{
typedef unsigned char           Bool; //!< Boolean.
#ifndef __cplusplus
#if !defined(__bool_true_false_are_defined)
typedef unsigned char           bool; //!< Boolean.
#endif
#endif
typedef signed char             S8 ;  //!< 8-bit signed integer.
typedef unsigned char           U8 ;  //!< 8-bit unsigned integer.
typedef signed short int        S16;  //!< 16-bit signed integer.
typedef unsigned short int      U16;  //!< 16-bit unsigned integer.
typedef unsigned short int      le16_t;
typedef unsigned short int      be16_t;
typedef signed long int         S32;  //!< 32-bit signed integer.
typedef unsigned long int       U32;  //!< 32-bit unsigned integer.
typedef uint32_t                le32_t;
typedef uint32_t                be32_t;
typedef signed long long int    S64;  //!< 64-bit signed integer.
typedef unsigned long long int  U64;  //!< 64-bit unsigned integer.
typedef float                   F32;  //!< 32-bit floating-point number.
typedef double                  F64;  //!< 64-bit floating-point number.
typedef uint16_t                iram_size_t;
//! @}


/*! \name Status Types
 */
//! @{
typedef Bool                Status_bool_t;  //!< Boolean status.
typedef U8                  Status_t;       //!< 8-bit-coded status.
//! @}

//_____ M A C R O S ________________________________________________________

/*! \name Usual Constants
 */
//! @{
#define DISABLE   0
#define ENABLE    1
#define DISABLED  0
#define ENABLED   1
#define OFF       0
#define ON        1
#define FALSE     0
#define TRUE      1
#ifndef __cplusplus
#if !defined(__bool_true_false_are_defined)
#define false     FALSE
#define true      TRUE
#endif
#endif
#define KO        0
#define OK        1
#define PASS      0
#define FAIL      1
#define LOW       0
#define HIGH      1
#define CLR       0
#define SET       1
//! @}


//! \name Compile time error handling
//@{

/**
 * \internal
 * \def ERROR_FUNC(name, msg)
 * \brief Fail compilation if function call isn't eliminated
 *
 * If the compiler fails to optimize away all calls to the function \a
 * name, terminate compilation and display \a msg to the user.
 *
 * \note Not all compilers support this, so this is best-effort only.
 * Sometimes, there may be a linker error instead, and when optimization
 * is disabled, this mechanism will be completely disabled.
 */
#ifndef ERROR_FUNC
# define ERROR_FUNC(name, msg)                      \
	extern int name(void)
#endif

//@}

//! \name Function call demultiplexing
//@{

//! Error function for failed demultiplexing.
ERROR_FUNC(compiler_demux_bad_size, "Invalid parameter size");

/**
 * \internal
 * \brief Demultiplex function call based on size of datatype
 *
 * Evaluates to a function call to a function name with suffix 8, 16 or 32
 * depending on the size of the datatype. Any number of parameters can be
 * passed to the function.
 *
 * Usage:
 * \code
 * void foo8(uint8_t a, void *b);
 * void foo16(uint16_t a, void *b);
 * void foo32(uint32_t a, void *b);
 *
 * #define foo(x, y)    compiler_demux_size(sizeof(x), foo, x, y)
 * \endcode
 *
 * \param size Size of the datatype.
 * \param func Base function name.
 * \param ... List of parameters to pass to the function.
 */
#define compiler_demux_size(size, func, ...)        \
	(((size) == 1) ? func##8(__VA_ARGS__) :     \
	 ((size) == 2) ? func##16(__VA_ARGS__) :    \
	 ((size) == 4) ? func##32(__VA_ARGS__) :    \
	 compiler_demux_bad_size())

//@}

/**
 * \def __always_inline
 * \brief The function should always be inlined.
 *
 * This annotation instructs the compiler to ignore its inlining
 * heuristics and inline the function no matter how big it thinks it
 * becomes.
 */
#if (defined __GNUC__)
	#define __always_inline     inline __attribute__((__always_inline__))
#elif (defined __ICCAVR__)
	#define __always_inline     _Pragma("inline=forced") 
#endif

//! \name Optimization Control
//@{

/**
 * \def likely(exp)
 * \brief The expression \a exp is likely to be true
 */
#ifndef likely
# define likely(exp)    (exp)
#endif

/**
 * \def unlikely(exp)
 * \brief The expression \a exp is unlikely to be true
 */
#ifndef unlikely
# define unlikely(exp)  (exp)
#endif

/**
 * \def is_constant(exp)
 * \brief Determine if an expression evaluates to a constant value.
 *
 * \param exp Any expression
 *
 * \return true if \a exp is constant, false otherwise.
 */
#ifdef __GNUC__
# define is_constant(exp)       __builtin_constant_p(exp)
#else
# define is_constant(exp)       (0)
#endif

/*! \brief This macro is used to test fatal errors.
 *
 * The macro tests if the expression is FALSE. If it is, a fatal error is
 * detected and the application hangs up.
 *
 * \param expr  Expression to evaluate and supposed to be nonzero.
 */
#ifdef _ASSERT_ENABLE_
  #define Assert(expr) \
  {\
    if (!(expr)) while (TRUE);\
  }
#else
  #define Assert(expr)
#endif

/*! \name Bit Reversing
 */
//! @{

/*! \brief Reverses the bits of \a u8.
 *
 * \param u8  U8 of which to reverse the bits.
 *
 * \return Value resulting from \a u8 with reversed bits.
 */
#define bit_reverse8(u8)    ((U8)(bit_reverse32((U8)(u8)) >> 24))

/*! \brief Reverses the bits of \a u16.
 *
 * \param u16 U16 of which to reverse the bits.
 *
 * \return Value resulting from \a u16 with reversed bits.
 */
#define bit_reverse16(u16)  ((U16)(bit_reverse32((U16)(u16)) >> 16))

/*! \brief Reverses the bits of \a u32.
 *
 * \param u32 U32 of which to reverse the bits.
 *
 * \return Value resulting from \a u32 with reversed bits.
 */
#if (defined __GNUC__)
  #define bit_reverse32(u32) \
  (\
    {\
      unsigned int __value = (U32)(u32);\
      __asm__ ("brev\t%0" : "+r" (__value) :  : "cc");\
      (U32)__value;\
    }\
  )
#elif (defined __ICCAVR__)
  #define bit_reverse32(u32)  ((U32)__bit_reverse((U32)(u32)))
#endif

/*! \brief Reverses the bits of \a u64.
 *
 * \param u64 U64 of which to reverse the bits.
 *
 * \return Value resulting from \a u64 with reversed bits.
 */
#define bit_reverse64(u64)  ((U64)(((U64)bit_reverse32((U64)(u64) >> 32)) |\
                                   ((U64)bit_reverse32((U64)(u64)) << 32)))

//! @}

//! \name Logarithmic functions
//! @{

/**
 * \internal
 * Undefined function. Will cause a link failure if ilog2() is called
 * with an invalid constant value.
 */
int_fast8_t ilog2_undefined(void);

//! @}

/*! \name Alignment
 */
//! @{

/*! \brief Tests alignment of the number \a val with the \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return \c 1 if the number \a val is aligned with the \a n boundary, else \c 0.
 */
#define Test_align(val, n     ) (!Tst_bits( val, (n) - 1     )   )

/*! \brief Gets alignment of the number \a val with respect to the \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Alignment of the number \a val with respect to the \a n boundary.
 */
#define Get_align( val, n     ) (  Rd_bits( val, (n) - 1     )   )

/*! \brief Sets alignment of the lvalue number \a lval to \a alg with respect to the \a n boundary.
 *
 * \param lval  Input/output lvalue.
 * \param n     Boundary.
 * \param alg   Alignment.
 *
 * \return New value of \a lval resulting from its alignment set to \a alg with respect to the \a n boundary.
 */
#define Set_align(lval, n, alg) (  Wr_bits(lval, (n) - 1, alg)   )

/*! \brief Aligns the number \a val with the upper \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Value resulting from the number \a val aligned with the upper \a n boundary.
 */
#define Align_up(  val, n     ) (((val) + ((n) - 1)) & ~((n) - 1))

/*! \brief Aligns the number \a val with the lower \a n boundary.
 *
 * \param val Input value.
 * \param n   Boundary.
 *
 * \return Value resulting from the number \a val aligned with the lower \a n boundary.
 */
#define Align_down(val, n     ) ( (val)              & ~((n) - 1))

//! @}


/*! \name Mathematics
 *
 * Compiler optimization for non-constant expressions, only for abs under WinAVR
 */
//! @{

/*! \brief Takes the absolute value of \a a.
 *
 * \param a Input value.
 *
 * \return Absolute value of \a a.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Abs(a)              (((a) <  0 ) ? -(a) : (a))
#ifndef abs
#define abs(a)              Abs(a)
#endif

/*! \brief Takes the minimal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Minimal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Min(a, b)           (((a) < (b)) ?  (a) : (b))
#define min(a, b)           Min(a, b)

/*! \brief Takes the maximal value of \a a and \a b.
 *
 * \param a Input value.
 * \param b Input value.
 *
 * \return Maximal value of \a a and \a b.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Max(a, b)           (((a) > (b)) ?  (a) : (b))
#define max(a, b)           Max(a, b)

//! @}


/*! \brief Calls the routine at address \a addr.
 *
 * It generates a long call opcode.
 *
 * For example, `Long_call(0x80000000)' generates a software reset on a UC3 if
 * it is invoked from the CPU supervisor mode.
 *
 * \param addr  Address of the routine to call.
 *
 * \note It may be used as a long jump opcode in some special cases.
 */
#define Long_call(addr)                   ((*(void (*)(void))(addr))())

/*! \name System Register Access
 */
//! @{

/*! \brief Gets the value of the \a sysreg system register.
 *
 * \param sysreg  Address of the system register of which to get the value.
 *
 * \return Value of the \a sysreg system register.
 */
#if (defined __GNUC__)
  #define Get_system_register(sysreg)         __builtin_mfsr(sysreg)
#elif (defined __ICCAVR__)
  #define Get_system_register(sysreg)         __get_system_register(sysreg)
#endif

/*! \brief Sets the value of the \a sysreg system register to \a value.
 *
 * \param sysreg  Address of the system register of which to set the value.
 * \param value   Value to set the \a sysreg system register to.
 */
#if (defined __GNUC__)
  #define Set_system_register(sysreg, value)  __builtin_mtsr(sysreg, value)
#elif (defined __ICCAVR__)
  #define Set_system_register(sysreg, value)  __set_system_register(sysreg, value)
#endif

//! @}

/*! \name Debug Register Access
 */
//! @{

/*! \brief Gets the value of the \a dbgreg debug register.
 *
 * \param dbgreg  Address of the debug register of which to get the value.
 *
 * \return Value of the \a dbgreg debug register.
 */
#if (defined __GNUC__)
  #define Get_debug_register(dbgreg)          __builtin_mfdr(dbgreg)
#elif (defined __ICCAVR__)
  #define Get_debug_register(dbgreg)          __get_debug_register(dbgreg)
#endif

/*! \brief Sets the value of the \a dbgreg debug register to \a value.
 *
 * \param dbgreg  Address of the debug register of which to set the value.
 * \param value   Value to set the \a dbgreg debug register to.
 */
#if (defined __GNUC__)
  #define Set_debug_register(dbgreg, value)   __builtin_mtdr(dbgreg, value)
#elif (defined __ICCAVR__)
  #define Set_debug_register(dbgreg, value)   __set_debug_register(dbgreg, value)
#endif

//! @}


/*! \name MCU Endianism Handling
 * xmega is a MCU little endianism.
 */
//! @{
#define  MSB(u16)          (((uint8_t* )&u16)[1])
#define  LSB(u16)          (((uint8_t* )&u16)[0])

#define  MSW(u32)          (((uint16_t*)&u32)[1])
#define  LSW(u32)          (((uint16_t*)&u32)[0])
#define  MSB0W(u32)        (((U8  *)&(u32))[3])  //!< Most significant byte of 1st rank of \a u32.
#define  MSB1W(u32)        (((U8  *)&(u32))[2])  //!< Most significant byte of 2nd rank of \a u32.
#define  MSB2W(u32)        (((U8  *)&(u32))[1])  //!< Most significant byte of 3rd rank of \a u32.
#define  MSB3W(u32)        (((U8  *)&(u32))[0])  //!< Most significant byte of 4th rank of \a u32.
#define  LSB3W(u32)        MSB0W(u32)            //!< Least significant byte of 4th rank of \a u32.
#define  LSB2W(u32)        MSB1W(u32)            //!< Least significant byte of 3rd rank of \a u32.
#define  LSB1W(u32)        MSB2W(u32)            //!< Least significant byte of 2nd rank of \a u32.
#define  LSB0W(u32)        MSB3W(u32)            //!< Least significant byte of 1st rank of \a u32.

#define  MSB0(u32)         (((uint8_t* )&u32)[3])
#define  MSB1(u32)         (((uint8_t* )&u32)[2])
#define  MSB2(u32)         (((uint8_t* )&u32)[1])
#define  MSB3(u32)         (((uint8_t* )&u32)[0])
#define  LSB0(u32)         MSB3(u32)
#define  LSB1(u32)         MSB2(u32)
#define  LSB2(u32)         MSB1(u32)
#define  LSB3(u32)         MSB0(u32)

#define  LE16(x)        (x)        
#define  le16_to_cpu(x) (x)
#define  cpu_to_le16(x) (x)
#define  LE16_TO_CPU(x) (x)
#define  CPU_TO_LE16(x) (x)
        
#define  BE16(x)        Swap16(x)        
#define  be16_to_cpu(x) swap16(x)
#define  cpu_to_be16(x) swap16(x)
#define  BE16_TO_CPU(x) Swap16(x)
#define  CPU_TO_BE16(x) Swap16(x)
        
#define  LE32(x)        (x)        
#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)
        
#define  BE32(x)        Swap32(x)        
#define  be32_to_cpu(x) swap32(x)
#define  cpu_to_be32(x) swap32(x)
#define  BE32_TO_CPU(x) Swap32(x)
#define  CPU_TO_BE32(x) Swap32(x)



//! @}


/*! \name Endianism Conversion
 *
 * The same considerations as for clz and ctz apply here but AVR32-GCC's
 * __builtin_bswap_16 and __builtin_bswap_32 do not behave like macros when
 * applied to constant expressions, so two sets of macros are defined here:
 *   - Swap16, Swap32 and Swap64 to apply to constant expressions (values known
 *     at compile time);
 *   - swap16, swap32 and swap64 to apply to non-constant expressions (values
 *     unknown at compile time).
 */
//! @{

/*! \brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * \param u16 U16 of which to toggle the endianism.
 *
 * \return Value resulting from \a u16 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap16(u16) ((U16)(((U16)(u16) >> 8) |\
                           ((U16)(u16) << 8)))

/*! \brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * \param u32 U32 of which to toggle the endianism.
 *
 * \return Value resulting from \a u32 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap32(u32) ((U32)(((U32)Swap16((U32)(u32) >> 16)) |\
                           ((U32)Swap16((U32)(u32)) << 16)))

/*! \brief Toggles the endianism of \a u64 (by swapping its bytes).
 *
 * \param u64 U64 of which to toggle the endianism.
 *
 * \return Value resulting from \a u64 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define Swap64(u64) ((U64)(((U64)Swap32((U64)(u64) >> 32)) |\
                           ((U64)Swap32((U64)(u64)) << 32)))

/*! \brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * \param u16 U16 of which to toggle the endianism.
 *
 * \return Value resulting from \a u16 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define swap16(u16) Swap16(u16)

/*! \brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * \param u32 U32 of which to toggle the endianism.
 *
 * \return Value resulting from \a u32 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define swap32(u32) Swap32(u32)

/*! \brief Toggles the endianism of \a u64 (by swapping its bytes).
 *
 * \param u64 U64 of which to toggle the endianism.
 *
 * \return Value resulting from \a u64 with toggled endianism.
 *
 * \note More optimized if only used with values unknown at compile time.
 */
#define swap64(u64) ((U64)(((U64)swap32((U64)(u64) >> 32)) |\
                           ((U64)swap32((U64)(u64)) << 32)))

//! @}


/*! \name Target Abstraction
 */
//! @{

#define _GLOBEXT_           extern      //!< extern storage-class specifier.
#define _CONST_TYPE_        const       //!< const type qualifier.
#define _MEM_TYPE_SLOW_                 //!< Slow memory type.
#define _MEM_TYPE_MEDFAST_              //!< Fairly fast memory type.
#define _MEM_TYPE_FAST_                 //!< Fast memory type.

typedef U8                  Byte;       //!< 8-bit unsigned integer.

#define memcmp_ram2ram      memcmp      //!< Target-specific memcmp of RAM to RAM.
#define memcmp_code2ram     memcmp      //!< Target-specific memcmp of RAM to NVRAM.
#define memcpy_ram2ram      memcpy      //!< Target-specific memcpy from RAM to RAM.
#define memcpy_code2ram     memcpy      //!< Target-specific memcpy from NVRAM to RAM.

//! @}

#endif  // UTILS_COMPILER_H
