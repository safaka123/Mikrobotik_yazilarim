/*-------------------------------------------------------------------------
 *      STM8 definitions of SFR registers
 *
 *      Used with STM8 IAR C/C++ Compiler and Assembler.
 *
 *      Copyright 2019 IAR Systems AB.
 *
 *-----------------------------------------------------------------------*/

#ifndef __IOSTM8S103F3_H__
#define __IOSTM8S103F3_H__

#if (((__TID__ >> 8) & 0x7F) != 0x38)     /* 0x38 = 56 dec */
#error This file should only be compiled by STM8 IAR compiler and assembler
#endif

/*-------------------------------------------------------------------------
 *      I/O register macros
 *-----------------------------------------------------------------------*/

#include "io_macros.h"


#ifdef __IAR_SYSTEMS_ICC__
#pragma system_include
#pragma language=save
#pragma language=extended
#endif

/*-------------------------------------------------------------------------
 *      Option byte attribute define
 *-----------------------------------------------------------------------*/
 
#define OPTION_BYTE_ATTRIBUTES __root const volatile __ro_placement
 
/*-------------------------------------------------------------------------
 *      Option bytes register definitions
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 *      Option bytes addresses
 *-----------------------------------------------------------------------*/
#define OPT0_ADDR        0x4800
#define OPT1_ADDR        0x4801
#define NOPT1_ADDR       0x4802
#define OPT2_ADDR        0x4803
#define NOPT2_ADDR       0x4804
#define OPT3_ADDR        0x4805
#define NOPT3_ADDR       0x4806
#define OPT4_ADDR        0x4807
#define NOPT4_ADDR       0x4808
#define OPT5_ADDR        0x4809
#define NOPT5_ADDR       0x480a

#define OPT0_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT0        @ OPT0_ADDR
#define OPT1_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT1        @ OPT1_ADDR
#define NOPT1_DECL       OPTION_BYTE_ATTRIBUTES unsigned char NOPT1       @ NOPT1_ADDR
#define OPT2_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT2        @ OPT2_ADDR
#define NOPT2_DECL       OPTION_BYTE_ATTRIBUTES unsigned char NOPT2       @ NOPT2_ADDR
#define OPT3_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT3        @ OPT3_ADDR
#define NOPT3_DECL       OPTION_BYTE_ATTRIBUTES unsigned char NOPT3       @ NOPT3_ADDR
#define OPT4_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT4        @ OPT4_ADDR
#define NOPT4_DECL       OPTION_BYTE_ATTRIBUTES unsigned char NOPT4       @ NOPT4_ADDR
#define OPT5_DECL        OPTION_BYTE_ATTRIBUTES unsigned char OPT5        @ OPT5_ADDR
#define NOPT5_DECL       OPTION_BYTE_ATTRIBUTES unsigned char NOPT5       @ NOPT5_ADDR


/*-------------------------------------------------------------------------
 *      Port A register definitions
 *-----------------------------------------------------------------------*/
/* Port A data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PA_ODR;
#endif
__IO_REG8_BIT(PA_ODR,      0x5000, __READ_WRITE, __BITS_PA_ODR);

/* Port A input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PA_IDR;
#endif
__IO_REG8_BIT(PA_IDR,      0x5001, __READ, __BITS_PA_IDR);

/* Port A data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PA_DDR;
#endif
__IO_REG8_BIT(PA_DDR,      0x5002, __READ_WRITE, __BITS_PA_DDR);

/* Port A control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PA_CR1;
#endif
__IO_REG8_BIT(PA_CR1,      0x5003, __READ_WRITE, __BITS_PA_CR1);

/* Port A control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PA_CR2;
#endif
__IO_REG8_BIT(PA_CR2,      0x5004, __READ_WRITE, __BITS_PA_CR2);


/*-------------------------------------------------------------------------
 *      Port A bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PA_ODR_ODR0              PA_ODR_bit.ODR0
#define PA_ODR_ODR1              PA_ODR_bit.ODR1
#define PA_ODR_ODR2              PA_ODR_bit.ODR2
#define PA_ODR_ODR3              PA_ODR_bit.ODR3
#define PA_ODR_ODR4              PA_ODR_bit.ODR4
#define PA_ODR_ODR5              PA_ODR_bit.ODR5
#define PA_ODR_ODR6              PA_ODR_bit.ODR6
#define PA_ODR_ODR7              PA_ODR_bit.ODR7

#define PA_IDR_IDR0              PA_IDR_bit.IDR0
#define PA_IDR_IDR1              PA_IDR_bit.IDR1
#define PA_IDR_IDR2              PA_IDR_bit.IDR2
#define PA_IDR_IDR3              PA_IDR_bit.IDR3
#define PA_IDR_IDR4              PA_IDR_bit.IDR4
#define PA_IDR_IDR5              PA_IDR_bit.IDR5
#define PA_IDR_IDR6              PA_IDR_bit.IDR6
#define PA_IDR_IDR7              PA_IDR_bit.IDR7

#define PA_DDR_DDR0              PA_DDR_bit.DDR0
#define PA_DDR_DDR1              PA_DDR_bit.DDR1
#define PA_DDR_DDR2              PA_DDR_bit.DDR2
#define PA_DDR_DDR3              PA_DDR_bit.DDR3
#define PA_DDR_DDR4              PA_DDR_bit.DDR4
#define PA_DDR_DDR5              PA_DDR_bit.DDR5
#define PA_DDR_DDR6              PA_DDR_bit.DDR6
#define PA_DDR_DDR7              PA_DDR_bit.DDR7

#define PA_CR1_C10               PA_CR1_bit.C10
#define PA_CR1_C11               PA_CR1_bit.C11
#define PA_CR1_C12               PA_CR1_bit.C12
#define PA_CR1_C13               PA_CR1_bit.C13
#define PA_CR1_C14               PA_CR1_bit.C14
#define PA_CR1_C15               PA_CR1_bit.C15
#define PA_CR1_C16               PA_CR1_bit.C16
#define PA_CR1_C17               PA_CR1_bit.C17

#define PA_CR2_C20               PA_CR2_bit.C20
#define PA_CR2_C21               PA_CR2_bit.C21
#define PA_CR2_C22               PA_CR2_bit.C22
#define PA_CR2_C23               PA_CR2_bit.C23
#define PA_CR2_C24               PA_CR2_bit.C24
#define PA_CR2_C25               PA_CR2_bit.C25
#define PA_CR2_C26               PA_CR2_bit.C26
#define PA_CR2_C27               PA_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port A bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PA_ODR_ODR0         0x01
#define MASK_PA_ODR_ODR1         0x02
#define MASK_PA_ODR_ODR2         0x04
#define MASK_PA_ODR_ODR3         0x08
#define MASK_PA_ODR_ODR4         0x10
#define MASK_PA_ODR_ODR5         0x20
#define MASK_PA_ODR_ODR6         0x40
#define MASK_PA_ODR_ODR7         0x80

#define MASK_PA_IDR_IDR0         0x01
#define MASK_PA_IDR_IDR1         0x02
#define MASK_PA_IDR_IDR2         0x04
#define MASK_PA_IDR_IDR3         0x08
#define MASK_PA_IDR_IDR4         0x10
#define MASK_PA_IDR_IDR5         0x20
#define MASK_PA_IDR_IDR6         0x40
#define MASK_PA_IDR_IDR7         0x80

#define MASK_PA_DDR_DDR0         0x01
#define MASK_PA_DDR_DDR1         0x02
#define MASK_PA_DDR_DDR2         0x04
#define MASK_PA_DDR_DDR3         0x08
#define MASK_PA_DDR_DDR4         0x10
#define MASK_PA_DDR_DDR5         0x20
#define MASK_PA_DDR_DDR6         0x40
#define MASK_PA_DDR_DDR7         0x80

#define MASK_PA_CR1_C10          0x01
#define MASK_PA_CR1_C11          0x02
#define MASK_PA_CR1_C12          0x04
#define MASK_PA_CR1_C13          0x08
#define MASK_PA_CR1_C14          0x10
#define MASK_PA_CR1_C15          0x20
#define MASK_PA_CR1_C16          0x40
#define MASK_PA_CR1_C17          0x80

#define MASK_PA_CR2_C20          0x01
#define MASK_PA_CR2_C21          0x02
#define MASK_PA_CR2_C22          0x04
#define MASK_PA_CR2_C23          0x08
#define MASK_PA_CR2_C24          0x10
#define MASK_PA_CR2_C25          0x20
#define MASK_PA_CR2_C26          0x40
#define MASK_PA_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Port B register definitions
 *-----------------------------------------------------------------------*/
/* Port B data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PB_ODR;
#endif
__IO_REG8_BIT(PB_ODR,      0x5005, __READ_WRITE, __BITS_PB_ODR);

/* Port B input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PB_IDR;
#endif
__IO_REG8_BIT(PB_IDR,      0x5006, __READ, __BITS_PB_IDR);

/* Port B data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PB_DDR;
#endif
__IO_REG8_BIT(PB_DDR,      0x5007, __READ_WRITE, __BITS_PB_DDR);

/* Port B control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PB_CR1;
#endif
__IO_REG8_BIT(PB_CR1,      0x5008, __READ_WRITE, __BITS_PB_CR1);

/* Port B control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PB_CR2;
#endif
__IO_REG8_BIT(PB_CR2,      0x5009, __READ_WRITE, __BITS_PB_CR2);


/*-------------------------------------------------------------------------
 *      Port B bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PB_ODR_ODR0              PB_ODR_bit.ODR0
#define PB_ODR_ODR1              PB_ODR_bit.ODR1
#define PB_ODR_ODR2              PB_ODR_bit.ODR2
#define PB_ODR_ODR3              PB_ODR_bit.ODR3
#define PB_ODR_ODR4              PB_ODR_bit.ODR4
#define PB_ODR_ODR5              PB_ODR_bit.ODR5
#define PB_ODR_ODR6              PB_ODR_bit.ODR6
#define PB_ODR_ODR7              PB_ODR_bit.ODR7

#define PB_IDR_IDR0              PB_IDR_bit.IDR0
#define PB_IDR_IDR1              PB_IDR_bit.IDR1
#define PB_IDR_IDR2              PB_IDR_bit.IDR2
#define PB_IDR_IDR3              PB_IDR_bit.IDR3
#define PB_IDR_IDR4              PB_IDR_bit.IDR4
#define PB_IDR_IDR5              PB_IDR_bit.IDR5
#define PB_IDR_IDR6              PB_IDR_bit.IDR6
#define PB_IDR_IDR7              PB_IDR_bit.IDR7

#define PB_DDR_DDR0              PB_DDR_bit.DDR0
#define PB_DDR_DDR1              PB_DDR_bit.DDR1
#define PB_DDR_DDR2              PB_DDR_bit.DDR2
#define PB_DDR_DDR3              PB_DDR_bit.DDR3
#define PB_DDR_DDR4              PB_DDR_bit.DDR4
#define PB_DDR_DDR5              PB_DDR_bit.DDR5
#define PB_DDR_DDR6              PB_DDR_bit.DDR6
#define PB_DDR_DDR7              PB_DDR_bit.DDR7

#define PB_CR1_C10               PB_CR1_bit.C10
#define PB_CR1_C11               PB_CR1_bit.C11
#define PB_CR1_C12               PB_CR1_bit.C12
#define PB_CR1_C13               PB_CR1_bit.C13
#define PB_CR1_C14               PB_CR1_bit.C14
#define PB_CR1_C15               PB_CR1_bit.C15
#define PB_CR1_C16               PB_CR1_bit.C16
#define PB_CR1_C17               PB_CR1_bit.C17

#define PB_CR2_C20               PB_CR2_bit.C20
#define PB_CR2_C21               PB_CR2_bit.C21
#define PB_CR2_C22               PB_CR2_bit.C22
#define PB_CR2_C23               PB_CR2_bit.C23
#define PB_CR2_C24               PB_CR2_bit.C24
#define PB_CR2_C25               PB_CR2_bit.C25
#define PB_CR2_C26               PB_CR2_bit.C26
#define PB_CR2_C27               PB_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port B bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PB_ODR_ODR0         0x01
#define MASK_PB_ODR_ODR1         0x02
#define MASK_PB_ODR_ODR2         0x04
#define MASK_PB_ODR_ODR3         0x08
#define MASK_PB_ODR_ODR4         0x10
#define MASK_PB_ODR_ODR5         0x20
#define MASK_PB_ODR_ODR6         0x40
#define MASK_PB_ODR_ODR7         0x80

#define MASK_PB_IDR_IDR0         0x01
#define MASK_PB_IDR_IDR1         0x02
#define MASK_PB_IDR_IDR2         0x04
#define MASK_PB_IDR_IDR3         0x08
#define MASK_PB_IDR_IDR4         0x10
#define MASK_PB_IDR_IDR5         0x20
#define MASK_PB_IDR_IDR6         0x40
#define MASK_PB_IDR_IDR7         0x80

#define MASK_PB_DDR_DDR0         0x01
#define MASK_PB_DDR_DDR1         0x02
#define MASK_PB_DDR_DDR2         0x04
#define MASK_PB_DDR_DDR3         0x08
#define MASK_PB_DDR_DDR4         0x10
#define MASK_PB_DDR_DDR5         0x20
#define MASK_PB_DDR_DDR6         0x40
#define MASK_PB_DDR_DDR7         0x80

#define MASK_PB_CR1_C10          0x01
#define MASK_PB_CR1_C11          0x02
#define MASK_PB_CR1_C12          0x04
#define MASK_PB_CR1_C13          0x08
#define MASK_PB_CR1_C14          0x10
#define MASK_PB_CR1_C15          0x20
#define MASK_PB_CR1_C16          0x40
#define MASK_PB_CR1_C17          0x80

#define MASK_PB_CR2_C20          0x01
#define MASK_PB_CR2_C21          0x02
#define MASK_PB_CR2_C22          0x04
#define MASK_PB_CR2_C23          0x08
#define MASK_PB_CR2_C24          0x10
#define MASK_PB_CR2_C25          0x20
#define MASK_PB_CR2_C26          0x40
#define MASK_PB_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Port C register definitions
 *-----------------------------------------------------------------------*/
/* Port C data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PC_ODR;
#endif
__IO_REG8_BIT(PC_ODR,      0x500A, __READ_WRITE, __BITS_PC_ODR);

/* Port C input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PC_IDR;
#endif
__IO_REG8_BIT(PC_IDR,      0x500B, __READ, __BITS_PC_IDR);

/* Port C data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PC_DDR;
#endif
__IO_REG8_BIT(PC_DDR,      0x500C, __READ_WRITE, __BITS_PC_DDR);

/* Port C control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PC_CR1;
#endif
__IO_REG8_BIT(PC_CR1,      0x500D, __READ_WRITE, __BITS_PC_CR1);

/* Port C control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PC_CR2;
#endif
__IO_REG8_BIT(PC_CR2,      0x500E, __READ_WRITE, __BITS_PC_CR2);


/*-------------------------------------------------------------------------
 *      Port C bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PC_ODR_ODR0              PC_ODR_bit.ODR0
#define PC_ODR_ODR1              PC_ODR_bit.ODR1
#define PC_ODR_ODR2              PC_ODR_bit.ODR2
#define PC_ODR_ODR3              PC_ODR_bit.ODR3
#define PC_ODR_ODR4              PC_ODR_bit.ODR4
#define PC_ODR_ODR5              PC_ODR_bit.ODR5
#define PC_ODR_ODR6              PC_ODR_bit.ODR6
#define PC_ODR_ODR7              PC_ODR_bit.ODR7

#define PC_IDR_IDR0              PC_IDR_bit.IDR0
#define PC_IDR_IDR1              PC_IDR_bit.IDR1
#define PC_IDR_IDR2              PC_IDR_bit.IDR2
#define PC_IDR_IDR3              PC_IDR_bit.IDR3
#define PC_IDR_IDR4              PC_IDR_bit.IDR4
#define PC_IDR_IDR5              PC_IDR_bit.IDR5
#define PC_IDR_IDR6              PC_IDR_bit.IDR6
#define PC_IDR_IDR7              PC_IDR_bit.IDR7

#define PC_DDR_DDR0              PC_DDR_bit.DDR0
#define PC_DDR_DDR1              PC_DDR_bit.DDR1
#define PC_DDR_DDR2              PC_DDR_bit.DDR2
#define PC_DDR_DDR3              PC_DDR_bit.DDR3
#define PC_DDR_DDR4              PC_DDR_bit.DDR4
#define PC_DDR_DDR5              PC_DDR_bit.DDR5
#define PC_DDR_DDR6              PC_DDR_bit.DDR6
#define PC_DDR_DDR7              PC_DDR_bit.DDR7

#define PC_CR1_C10               PC_CR1_bit.C10
#define PC_CR1_C11               PC_CR1_bit.C11
#define PC_CR1_C12               PC_CR1_bit.C12
#define PC_CR1_C13               PC_CR1_bit.C13
#define PC_CR1_C14               PC_CR1_bit.C14
#define PC_CR1_C15               PC_CR1_bit.C15
#define PC_CR1_C16               PC_CR1_bit.C16
#define PC_CR1_C17               PC_CR1_bit.C17

#define PC_CR2_C20               PC_CR2_bit.C20
#define PC_CR2_C21               PC_CR2_bit.C21
#define PC_CR2_C22               PC_CR2_bit.C22
#define PC_CR2_C23               PC_CR2_bit.C23
#define PC_CR2_C24               PC_CR2_bit.C24
#define PC_CR2_C25               PC_CR2_bit.C25
#define PC_CR2_C26               PC_CR2_bit.C26
#define PC_CR2_C27               PC_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port C bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PC_ODR_ODR0         0x01
#define MASK_PC_ODR_ODR1         0x02
#define MASK_PC_ODR_ODR2         0x04
#define MASK_PC_ODR_ODR3         0x08
#define MASK_PC_ODR_ODR4         0x10
#define MASK_PC_ODR_ODR5         0x20
#define MASK_PC_ODR_ODR6         0x40
#define MASK_PC_ODR_ODR7         0x80

#define MASK_PC_IDR_IDR0         0x01
#define MASK_PC_IDR_IDR1         0x02
#define MASK_PC_IDR_IDR2         0x04
#define MASK_PC_IDR_IDR3         0x08
#define MASK_PC_IDR_IDR4         0x10
#define MASK_PC_IDR_IDR5         0x20
#define MASK_PC_IDR_IDR6         0x40
#define MASK_PC_IDR_IDR7         0x80

#define MASK_PC_DDR_DDR0         0x01
#define MASK_PC_DDR_DDR1         0x02
#define MASK_PC_DDR_DDR2         0x04
#define MASK_PC_DDR_DDR3         0x08
#define MASK_PC_DDR_DDR4         0x10
#define MASK_PC_DDR_DDR5         0x20
#define MASK_PC_DDR_DDR6         0x40
#define MASK_PC_DDR_DDR7         0x80

#define MASK_PC_CR1_C10          0x01
#define MASK_PC_CR1_C11          0x02
#define MASK_PC_CR1_C12          0x04
#define MASK_PC_CR1_C13          0x08
#define MASK_PC_CR1_C14          0x10
#define MASK_PC_CR1_C15          0x20
#define MASK_PC_CR1_C16          0x40
#define MASK_PC_CR1_C17          0x80

#define MASK_PC_CR2_C20          0x01
#define MASK_PC_CR2_C21          0x02
#define MASK_PC_CR2_C22          0x04
#define MASK_PC_CR2_C23          0x08
#define MASK_PC_CR2_C24          0x10
#define MASK_PC_CR2_C25          0x20
#define MASK_PC_CR2_C26          0x40
#define MASK_PC_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Port D register definitions
 *-----------------------------------------------------------------------*/
/* Port D data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PD_ODR;
#endif
__IO_REG8_BIT(PD_ODR,      0x500F, __READ_WRITE, __BITS_PD_ODR);

/* Port D input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PD_IDR;
#endif
__IO_REG8_BIT(PD_IDR,      0x5010, __READ, __BITS_PD_IDR);

/* Port D data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PD_DDR;
#endif
__IO_REG8_BIT(PD_DDR,      0x5011, __READ_WRITE, __BITS_PD_DDR);

/* Port D control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PD_CR1;
#endif
__IO_REG8_BIT(PD_CR1,      0x5012, __READ_WRITE, __BITS_PD_CR1);

/* Port D control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PD_CR2;
#endif
__IO_REG8_BIT(PD_CR2,      0x5013, __READ_WRITE, __BITS_PD_CR2);


/*-------------------------------------------------------------------------
 *      Port D bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PD_ODR_ODR0              PD_ODR_bit.ODR0
#define PD_ODR_ODR1              PD_ODR_bit.ODR1
#define PD_ODR_ODR2              PD_ODR_bit.ODR2
#define PD_ODR_ODR3              PD_ODR_bit.ODR3
#define PD_ODR_ODR4              PD_ODR_bit.ODR4
#define PD_ODR_ODR5              PD_ODR_bit.ODR5
#define PD_ODR_ODR6              PD_ODR_bit.ODR6
#define PD_ODR_ODR7              PD_ODR_bit.ODR7

#define PD_IDR_IDR0              PD_IDR_bit.IDR0
#define PD_IDR_IDR1              PD_IDR_bit.IDR1
#define PD_IDR_IDR2              PD_IDR_bit.IDR2
#define PD_IDR_IDR3              PD_IDR_bit.IDR3
#define PD_IDR_IDR4              PD_IDR_bit.IDR4
#define PD_IDR_IDR5              PD_IDR_bit.IDR5
#define PD_IDR_IDR6              PD_IDR_bit.IDR6
#define PD_IDR_IDR7              PD_IDR_bit.IDR7

#define PD_DDR_DDR0              PD_DDR_bit.DDR0
#define PD_DDR_DDR1              PD_DDR_bit.DDR1
#define PD_DDR_DDR2              PD_DDR_bit.DDR2
#define PD_DDR_DDR3              PD_DDR_bit.DDR3
#define PD_DDR_DDR4              PD_DDR_bit.DDR4
#define PD_DDR_DDR5              PD_DDR_bit.DDR5
#define PD_DDR_DDR6              PD_DDR_bit.DDR6
#define PD_DDR_DDR7              PD_DDR_bit.DDR7

#define PD_CR1_C10               PD_CR1_bit.C10
#define PD_CR1_C11               PD_CR1_bit.C11
#define PD_CR1_C12               PD_CR1_bit.C12
#define PD_CR1_C13               PD_CR1_bit.C13
#define PD_CR1_C14               PD_CR1_bit.C14
#define PD_CR1_C15               PD_CR1_bit.C15
#define PD_CR1_C16               PD_CR1_bit.C16
#define PD_CR1_C17               PD_CR1_bit.C17

#define PD_CR2_C20               PD_CR2_bit.C20
#define PD_CR2_C21               PD_CR2_bit.C21
#define PD_CR2_C22               PD_CR2_bit.C22
#define PD_CR2_C23               PD_CR2_bit.C23
#define PD_CR2_C24               PD_CR2_bit.C24
#define PD_CR2_C25               PD_CR2_bit.C25
#define PD_CR2_C26               PD_CR2_bit.C26
#define PD_CR2_C27               PD_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port D bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PD_ODR_ODR0         0x01
#define MASK_PD_ODR_ODR1         0x02
#define MASK_PD_ODR_ODR2         0x04
#define MASK_PD_ODR_ODR3         0x08
#define MASK_PD_ODR_ODR4         0x10
#define MASK_PD_ODR_ODR5         0x20
#define MASK_PD_ODR_ODR6         0x40
#define MASK_PD_ODR_ODR7         0x80

#define MASK_PD_IDR_IDR0         0x01
#define MASK_PD_IDR_IDR1         0x02
#define MASK_PD_IDR_IDR2         0x04
#define MASK_PD_IDR_IDR3         0x08
#define MASK_PD_IDR_IDR4         0x10
#define MASK_PD_IDR_IDR5         0x20
#define MASK_PD_IDR_IDR6         0x40
#define MASK_PD_IDR_IDR7         0x80

#define MASK_PD_DDR_DDR0         0x01
#define MASK_PD_DDR_DDR1         0x02
#define MASK_PD_DDR_DDR2         0x04
#define MASK_PD_DDR_DDR3         0x08
#define MASK_PD_DDR_DDR4         0x10
#define MASK_PD_DDR_DDR5         0x20
#define MASK_PD_DDR_DDR6         0x40
#define MASK_PD_DDR_DDR7         0x80

#define MASK_PD_CR1_C10          0x01
#define MASK_PD_CR1_C11          0x02
#define MASK_PD_CR1_C12          0x04
#define MASK_PD_CR1_C13          0x08
#define MASK_PD_CR1_C14          0x10
#define MASK_PD_CR1_C15          0x20
#define MASK_PD_CR1_C16          0x40
#define MASK_PD_CR1_C17          0x80

#define MASK_PD_CR2_C20          0x01
#define MASK_PD_CR2_C21          0x02
#define MASK_PD_CR2_C22          0x04
#define MASK_PD_CR2_C23          0x08
#define MASK_PD_CR2_C24          0x10
#define MASK_PD_CR2_C25          0x20
#define MASK_PD_CR2_C26          0x40
#define MASK_PD_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Port E register definitions
 *-----------------------------------------------------------------------*/
/* Port E data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PE_ODR;
#endif
__IO_REG8_BIT(PE_ODR,      0x5014, __READ_WRITE, __BITS_PE_ODR);

/* Port E input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PE_IDR;
#endif
__IO_REG8_BIT(PE_IDR,      0x5015, __READ, __BITS_PE_IDR);

/* Port E data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PE_DDR;
#endif
__IO_REG8_BIT(PE_DDR,      0x5016, __READ_WRITE, __BITS_PE_DDR);

/* Port E control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PE_CR1;
#endif
__IO_REG8_BIT(PE_CR1,      0x5017, __READ_WRITE, __BITS_PE_CR1);

/* Port E control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PE_CR2;
#endif
__IO_REG8_BIT(PE_CR2,      0x5018, __READ_WRITE, __BITS_PE_CR2);


/*-------------------------------------------------------------------------
 *      Port E bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PE_ODR_ODR0              PE_ODR_bit.ODR0
#define PE_ODR_ODR1              PE_ODR_bit.ODR1
#define PE_ODR_ODR2              PE_ODR_bit.ODR2
#define PE_ODR_ODR3              PE_ODR_bit.ODR3
#define PE_ODR_ODR4              PE_ODR_bit.ODR4
#define PE_ODR_ODR5              PE_ODR_bit.ODR5
#define PE_ODR_ODR6              PE_ODR_bit.ODR6
#define PE_ODR_ODR7              PE_ODR_bit.ODR7

#define PE_IDR_IDR0              PE_IDR_bit.IDR0
#define PE_IDR_IDR1              PE_IDR_bit.IDR1
#define PE_IDR_IDR2              PE_IDR_bit.IDR2
#define PE_IDR_IDR3              PE_IDR_bit.IDR3
#define PE_IDR_IDR4              PE_IDR_bit.IDR4
#define PE_IDR_IDR5              PE_IDR_bit.IDR5
#define PE_IDR_IDR6              PE_IDR_bit.IDR6
#define PE_IDR_IDR7              PE_IDR_bit.IDR7

#define PE_DDR_DDR0              PE_DDR_bit.DDR0
#define PE_DDR_DDR1              PE_DDR_bit.DDR1
#define PE_DDR_DDR2              PE_DDR_bit.DDR2
#define PE_DDR_DDR3              PE_DDR_bit.DDR3
#define PE_DDR_DDR4              PE_DDR_bit.DDR4
#define PE_DDR_DDR5              PE_DDR_bit.DDR5
#define PE_DDR_DDR6              PE_DDR_bit.DDR6
#define PE_DDR_DDR7              PE_DDR_bit.DDR7

#define PE_CR1_C10               PE_CR1_bit.C10
#define PE_CR1_C11               PE_CR1_bit.C11
#define PE_CR1_C12               PE_CR1_bit.C12
#define PE_CR1_C13               PE_CR1_bit.C13
#define PE_CR1_C14               PE_CR1_bit.C14
#define PE_CR1_C15               PE_CR1_bit.C15
#define PE_CR1_C16               PE_CR1_bit.C16
#define PE_CR1_C17               PE_CR1_bit.C17

#define PE_CR2_C20               PE_CR2_bit.C20
#define PE_CR2_C21               PE_CR2_bit.C21
#define PE_CR2_C22               PE_CR2_bit.C22
#define PE_CR2_C23               PE_CR2_bit.C23
#define PE_CR2_C24               PE_CR2_bit.C24
#define PE_CR2_C25               PE_CR2_bit.C25
#define PE_CR2_C26               PE_CR2_bit.C26
#define PE_CR2_C27               PE_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port E bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PE_ODR_ODR0         0x01
#define MASK_PE_ODR_ODR1         0x02
#define MASK_PE_ODR_ODR2         0x04
#define MASK_PE_ODR_ODR3         0x08
#define MASK_PE_ODR_ODR4         0x10
#define MASK_PE_ODR_ODR5         0x20
#define MASK_PE_ODR_ODR6         0x40
#define MASK_PE_ODR_ODR7         0x80

#define MASK_PE_IDR_IDR0         0x01
#define MASK_PE_IDR_IDR1         0x02
#define MASK_PE_IDR_IDR2         0x04
#define MASK_PE_IDR_IDR3         0x08
#define MASK_PE_IDR_IDR4         0x10
#define MASK_PE_IDR_IDR5         0x20
#define MASK_PE_IDR_IDR6         0x40
#define MASK_PE_IDR_IDR7         0x80

#define MASK_PE_DDR_DDR0         0x01
#define MASK_PE_DDR_DDR1         0x02
#define MASK_PE_DDR_DDR2         0x04
#define MASK_PE_DDR_DDR3         0x08
#define MASK_PE_DDR_DDR4         0x10
#define MASK_PE_DDR_DDR5         0x20
#define MASK_PE_DDR_DDR6         0x40
#define MASK_PE_DDR_DDR7         0x80

#define MASK_PE_CR1_C10          0x01
#define MASK_PE_CR1_C11          0x02
#define MASK_PE_CR1_C12          0x04
#define MASK_PE_CR1_C13          0x08
#define MASK_PE_CR1_C14          0x10
#define MASK_PE_CR1_C15          0x20
#define MASK_PE_CR1_C16          0x40
#define MASK_PE_CR1_C17          0x80

#define MASK_PE_CR2_C20          0x01
#define MASK_PE_CR2_C21          0x02
#define MASK_PE_CR2_C22          0x04
#define MASK_PE_CR2_C23          0x08
#define MASK_PE_CR2_C24          0x10
#define MASK_PE_CR2_C25          0x20
#define MASK_PE_CR2_C26          0x40
#define MASK_PE_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Port F register definitions
 *-----------------------------------------------------------------------*/
/* Port F data output latch register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ODR0        : 1;
  unsigned char ODR1        : 1;
  unsigned char ODR2        : 1;
  unsigned char ODR3        : 1;
  unsigned char ODR4        : 1;
  unsigned char ODR5        : 1;
  unsigned char ODR6        : 1;
  unsigned char ODR7        : 1;
} __BITS_PF_ODR;
#endif
__IO_REG8_BIT(PF_ODR,      0x5019, __READ_WRITE, __BITS_PF_ODR);

/* Port F input pin value register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char IDR0        : 1;
  unsigned char IDR1        : 1;
  unsigned char IDR2        : 1;
  unsigned char IDR3        : 1;
  unsigned char IDR4        : 1;
  unsigned char IDR5        : 1;
  unsigned char IDR6        : 1;
  unsigned char IDR7        : 1;
} __BITS_PF_IDR;
#endif
__IO_REG8_BIT(PF_IDR,      0x501A, __READ, __BITS_PF_IDR);

/* Port F data direction register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char DDR0        : 1;
  unsigned char DDR1        : 1;
  unsigned char DDR2        : 1;
  unsigned char DDR3        : 1;
  unsigned char DDR4        : 1;
  unsigned char DDR5        : 1;
  unsigned char DDR6        : 1;
  unsigned char DDR7        : 1;
} __BITS_PF_DDR;
#endif
__IO_REG8_BIT(PF_DDR,      0x501B, __READ_WRITE, __BITS_PF_DDR);

/* Port F control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C10         : 1;
  unsigned char C11         : 1;
  unsigned char C12         : 1;
  unsigned char C13         : 1;
  unsigned char C14         : 1;
  unsigned char C15         : 1;
  unsigned char C16         : 1;
  unsigned char C17         : 1;
} __BITS_PF_CR1;
#endif
__IO_REG8_BIT(PF_CR1,      0x501C, __READ_WRITE, __BITS_PF_CR1);

/* Port F control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C20         : 1;
  unsigned char C21         : 1;
  unsigned char C22         : 1;
  unsigned char C23         : 1;
  unsigned char C24         : 1;
  unsigned char C25         : 1;
  unsigned char C26         : 1;
  unsigned char C27         : 1;
} __BITS_PF_CR2;
#endif
__IO_REG8_BIT(PF_CR2,      0x501D, __READ_WRITE, __BITS_PF_CR2);


/*-------------------------------------------------------------------------
 *      Port F bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define PF_ODR_ODR0              PF_ODR_bit.ODR0
#define PF_ODR_ODR1              PF_ODR_bit.ODR1
#define PF_ODR_ODR2              PF_ODR_bit.ODR2
#define PF_ODR_ODR3              PF_ODR_bit.ODR3
#define PF_ODR_ODR4              PF_ODR_bit.ODR4
#define PF_ODR_ODR5              PF_ODR_bit.ODR5
#define PF_ODR_ODR6              PF_ODR_bit.ODR6
#define PF_ODR_ODR7              PF_ODR_bit.ODR7

#define PF_IDR_IDR0              PF_IDR_bit.IDR0
#define PF_IDR_IDR1              PF_IDR_bit.IDR1
#define PF_IDR_IDR2              PF_IDR_bit.IDR2
#define PF_IDR_IDR3              PF_IDR_bit.IDR3
#define PF_IDR_IDR4              PF_IDR_bit.IDR4
#define PF_IDR_IDR5              PF_IDR_bit.IDR5
#define PF_IDR_IDR6              PF_IDR_bit.IDR6
#define PF_IDR_IDR7              PF_IDR_bit.IDR7

#define PF_DDR_DDR0              PF_DDR_bit.DDR0
#define PF_DDR_DDR1              PF_DDR_bit.DDR1
#define PF_DDR_DDR2              PF_DDR_bit.DDR2
#define PF_DDR_DDR3              PF_DDR_bit.DDR3
#define PF_DDR_DDR4              PF_DDR_bit.DDR4
#define PF_DDR_DDR5              PF_DDR_bit.DDR5
#define PF_DDR_DDR6              PF_DDR_bit.DDR6
#define PF_DDR_DDR7              PF_DDR_bit.DDR7

#define PF_CR1_C10               PF_CR1_bit.C10
#define PF_CR1_C11               PF_CR1_bit.C11
#define PF_CR1_C12               PF_CR1_bit.C12
#define PF_CR1_C13               PF_CR1_bit.C13
#define PF_CR1_C14               PF_CR1_bit.C14
#define PF_CR1_C15               PF_CR1_bit.C15
#define PF_CR1_C16               PF_CR1_bit.C16
#define PF_CR1_C17               PF_CR1_bit.C17

#define PF_CR2_C20               PF_CR2_bit.C20
#define PF_CR2_C21               PF_CR2_bit.C21
#define PF_CR2_C22               PF_CR2_bit.C22
#define PF_CR2_C23               PF_CR2_bit.C23
#define PF_CR2_C24               PF_CR2_bit.C24
#define PF_CR2_C25               PF_CR2_bit.C25
#define PF_CR2_C26               PF_CR2_bit.C26
#define PF_CR2_C27               PF_CR2_bit.C27

#endif

/*-------------------------------------------------------------------------
 *      Port F bit masks
 *-----------------------------------------------------------------------*/
#define MASK_PF_ODR_ODR0         0x01
#define MASK_PF_ODR_ODR1         0x02
#define MASK_PF_ODR_ODR2         0x04
#define MASK_PF_ODR_ODR3         0x08
#define MASK_PF_ODR_ODR4         0x10
#define MASK_PF_ODR_ODR5         0x20
#define MASK_PF_ODR_ODR6         0x40
#define MASK_PF_ODR_ODR7         0x80

#define MASK_PF_IDR_IDR0         0x01
#define MASK_PF_IDR_IDR1         0x02
#define MASK_PF_IDR_IDR2         0x04
#define MASK_PF_IDR_IDR3         0x08
#define MASK_PF_IDR_IDR4         0x10
#define MASK_PF_IDR_IDR5         0x20
#define MASK_PF_IDR_IDR6         0x40
#define MASK_PF_IDR_IDR7         0x80

#define MASK_PF_DDR_DDR0         0x01
#define MASK_PF_DDR_DDR1         0x02
#define MASK_PF_DDR_DDR2         0x04
#define MASK_PF_DDR_DDR3         0x08
#define MASK_PF_DDR_DDR4         0x10
#define MASK_PF_DDR_DDR5         0x20
#define MASK_PF_DDR_DDR6         0x40
#define MASK_PF_DDR_DDR7         0x80

#define MASK_PF_CR1_C10          0x01
#define MASK_PF_CR1_C11          0x02
#define MASK_PF_CR1_C12          0x04
#define MASK_PF_CR1_C13          0x08
#define MASK_PF_CR1_C14          0x10
#define MASK_PF_CR1_C15          0x20
#define MASK_PF_CR1_C16          0x40
#define MASK_PF_CR1_C17          0x80

#define MASK_PF_CR2_C20          0x01
#define MASK_PF_CR2_C21          0x02
#define MASK_PF_CR2_C22          0x04
#define MASK_PF_CR2_C23          0x08
#define MASK_PF_CR2_C24          0x10
#define MASK_PF_CR2_C25          0x20
#define MASK_PF_CR2_C26          0x40
#define MASK_PF_CR2_C27          0x80


/*-------------------------------------------------------------------------
 *      Flash register definitions
 *-----------------------------------------------------------------------*/
/* Flash control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char FIX         : 1;
  unsigned char IE          : 1;
  unsigned char AHALT       : 1;
  unsigned char HALT        : 1;
} __BITS_FLASH_CR1;
#endif
__IO_REG8_BIT(FLASH_CR1,   0x505A, __READ_WRITE, __BITS_FLASH_CR1);

/* Flash control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PRG         : 1;
  unsigned char             : 3;
  unsigned char FPRG        : 1;
  unsigned char ERASE       : 1;
  unsigned char WPRG        : 1;
        unsigned char OOPT         : 1;
} __BITS_FLASH_CR2;
#endif
__IO_REG8_BIT(FLASH_CR2,   0x505B, __READ_WRITE, __BITS_FLASH_CR2);

/* Flash complementary control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char NPRG        : 1;
  unsigned char             : 3;
  unsigned char NFPRG       : 1;
  unsigned char NERASE      : 1;
  unsigned char NWPRG       : 1;
  unsigned char NOPT        : 1;
} __BITS_FLASH_NCR2;
#endif
__IO_REG8_BIT(FLASH_NCR2,  0x505C, __READ_WRITE, __BITS_FLASH_NCR2);

/* Flash protection register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char WPB0        : 1;
  unsigned char WPB1        : 1;
  unsigned char WPB2        : 1;
  unsigned char WPB3        : 1;
  unsigned char WPB4        : 1;
  unsigned char WPB5        : 1;
} __BITS_FLASH_FPR;
#endif
__IO_REG8_BIT(FLASH_FPR,   0x505D, __READ, __BITS_FLASH_FPR);

/* Flash complementary protection register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char NWPB0       : 1;
  unsigned char NWPB1       : 1;
  unsigned char NWPB2       : 1;
  unsigned char NWPB3       : 1;
  unsigned char NWPB4       : 1;
  unsigned char NWPB5       : 1;
} __BITS_FLASH_NFPR;
#endif
__IO_REG8_BIT(FLASH_NFPR,  0x505E, __READ, __BITS_FLASH_NFPR);

/* Flash in-application programming status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char WR_PG_DIS   : 1;
  unsigned char PUL         : 1;
  unsigned char EOP         : 1;
  unsigned char DUL         : 1;
  unsigned char             : 2;
  unsigned char HVOFF       : 1;
} __BITS_FLASH_IAPSR;
#endif
__IO_REG8_BIT(FLASH_IAPSR, 0x505F, __READ_WRITE, __BITS_FLASH_IAPSR);

/* Flash program memory unprotection register */
__IO_REG8    (FLASH_PUKR,  0x5062, __READ_WRITE);
/* Data EEPROM unprotection register */
__IO_REG8    (FLASH_DUKR,  0x5064, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      Flash bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define FLASH_CR1_FIX            FLASH_CR1_bit.FIX
#define FLASH_CR1_IE             FLASH_CR1_bit.IE
#define FLASH_CR1_AHALT          FLASH_CR1_bit.AHALT
#define FLASH_CR1_HALT           FLASH_CR1_bit.HALT

#define FLASH_CR2_PRG            FLASH_CR2_bit.PRG
#define FLASH_CR2_FPRG           FLASH_CR2_bit.FPRG
#define FLASH_CR2_ERASE          FLASH_CR2_bit.ERASE
#define FLASH_CR2_WPRG           FLASH_CR2_bit.WPRG
#define FLASH_CR2_OPT            FLASH_CR2_bit.OPT

#define FLASH_NCR2_NPRG          FLASH_NCR2_bit.NPRG
#define FLASH_NCR2_NFPRG         FLASH_NCR2_bit.NFPRG
#define FLASH_NCR2_NERASE        FLASH_NCR2_bit.NERASE
#define FLASH_NCR2_NWPRG         FLASH_NCR2_bit.NWPRG
#define FLASH_NCR2_NOPT          FLASH_NCR2_bit.NOPT

#define FLASH_FPR_WPB0           FLASH_FPR_bit.WPB0
#define FLASH_FPR_WPB1           FLASH_FPR_bit.WPB1
#define FLASH_FPR_WPB2           FLASH_FPR_bit.WPB2
#define FLASH_FPR_WPB3           FLASH_FPR_bit.WPB3
#define FLASH_FPR_WPB4           FLASH_FPR_bit.WPB4
#define FLASH_FPR_WPB5           FLASH_FPR_bit.WPB5

#define FLASH_NFPR_NWPB0         FLASH_NFPR_bit.NWPB0
#define FLASH_NFPR_NWPB1         FLASH_NFPR_bit.NWPB1
#define FLASH_NFPR_NWPB2         FLASH_NFPR_bit.NWPB2
#define FLASH_NFPR_NWPB3         FLASH_NFPR_bit.NWPB3
#define FLASH_NFPR_NWPB4         FLASH_NFPR_bit.NWPB4
#define FLASH_NFPR_NWPB5         FLASH_NFPR_bit.NWPB5

#define FLASH_IAPSR_WR_PG_DIS    FLASH_IAPSR_bit.WR_PG_DIS
#define FLASH_IAPSR_PUL          FLASH_IAPSR_bit.PUL
#define FLASH_IAPSR_EOP          FLASH_IAPSR_bit.EOP
#define FLASH_IAPSR_DUL          FLASH_IAPSR_bit.DUL
#define FLASH_IAPSR_HVOFF        FLASH_IAPSR_bit.HVOFF

#endif

/*-------------------------------------------------------------------------
 *      Flash bit masks
 *-----------------------------------------------------------------------*/
#define MASK_FLASH_CR1_FIX       0x01
#define MASK_FLASH_CR1_IE        0x02
#define MASK_FLASH_CR1_AHALT     0x04
#define MASK_FLASH_CR1_HALT      0x08

#define MASK_FLASH_CR2_PRG       0x01
#define MASK_FLASH_CR2_FPRG      0x10
#define MASK_FLASH_CR2_ERASE     0x20
#define MASK_FLASH_CR2_WPRG      0x40
#define MASK_FLASH_CR2_OPT       0x80

#define MASK_FLASH_NCR2_NPRG     0x01
#define MASK_FLASH_NCR2_NFPRG    0x10
#define MASK_FLASH_NCR2_NERASE   0x20
#define MASK_FLASH_NCR2_NWPRG    0x40
#define MASK_FLASH_NCR2_NOPT     0x80

#define MASK_FLASH_FPR_WPB0      0x01
#define MASK_FLASH_FPR_WPB1      0x02
#define MASK_FLASH_FPR_WPB2      0x04
#define MASK_FLASH_FPR_WPB3      0x08
#define MASK_FLASH_FPR_WPB4      0x10
#define MASK_FLASH_FPR_WPB5      0x20

#define MASK_FLASH_NFPR_NWPB0    0x01
#define MASK_FLASH_NFPR_NWPB1    0x02
#define MASK_FLASH_NFPR_NWPB2    0x04
#define MASK_FLASH_NFPR_NWPB3    0x08
#define MASK_FLASH_NFPR_NWPB4    0x10
#define MASK_FLASH_NFPR_NWPB5    0x20

#define MASK_FLASH_IAPSR_WR_PG_DIS 0x01
#define MASK_FLASH_IAPSR_PUL     0x02
#define MASK_FLASH_IAPSR_EOP     0x04
#define MASK_FLASH_IAPSR_DUL     0x08
#define MASK_FLASH_IAPSR_HVOFF   0x40


/*-------------------------------------------------------------------------
 *      ITC register definitions
 *-----------------------------------------------------------------------*/
/* External interrupt control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PAIS        : 2;
  unsigned char PBIS        : 2;
  unsigned char PCIS        : 2;
  unsigned char PDIS        : 2;
} __BITS_EXTI_CR1;
#endif
__IO_REG8_BIT(EXTI_CR1,    0x50A0, __READ_WRITE, __BITS_EXTI_CR1);

/* External interrupt control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PEIS        : 2;
  unsigned char TLIS        : 1;
} __BITS_EXTI_CR2;
#endif
__IO_REG8_BIT(EXTI_CR2,    0x50A1, __READ_WRITE, __BITS_EXTI_CR2);

/* Reset status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char WWDGF       : 1;
  unsigned char IWDGF       : 1;
  unsigned char ILLOPF      : 1;
  unsigned char SWIMF       : 1;
  unsigned char EMCF        : 1;
} __BITS_RST_SR;
#endif
__IO_REG8_BIT(RST_SR,      0x50B3, __READ_WRITE, __BITS_RST_SR);

/* Interrupt software priority register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT0SPR    : 2;
  unsigned char VECT1SPR    : 2;
  unsigned char VECT2SPR    : 2;
  unsigned char VECT3SPR    : 2;
} __BITS_ITC_SPR1;
#endif
__IO_REG8_BIT(ITC_SPR1,    0x7F70, __READ_WRITE, __BITS_ITC_SPR1);

/* Interrupt software priority register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT4SPR    : 2;
  unsigned char VECT5SPR    : 2;
  unsigned char VECT6SPR    : 2;
  unsigned char VECT7SPR    : 2;
} __BITS_ITC_SPR2;
#endif
__IO_REG8_BIT(ITC_SPR2,    0x7F71, __READ_WRITE, __BITS_ITC_SPR2);

/* Interrupt software priority register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT8SPR    : 2;
  unsigned char VECT9SPR    : 2;
  unsigned char VECT10SPR   : 2;
  unsigned char VECT11SPR   : 2;
} __BITS_ITC_SPR3;
#endif
__IO_REG8_BIT(ITC_SPR3,    0x7F72, __READ_WRITE, __BITS_ITC_SPR3);

/* Interrupt software priority register 4 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT12SPR   : 2;
  unsigned char VECT13SPR   : 2;
  unsigned char VECT14SPR   : 2;
  unsigned char VECT15SPR   : 2;
} __BITS_ITC_SPR4;
#endif
__IO_REG8_BIT(ITC_SPR4,    0x7F73, __READ_WRITE, __BITS_ITC_SPR4);

/* Interrupt software priority register 5 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT16SPR   : 2;
  unsigned char VECT17SPR   : 2;
  unsigned char VECT18SPR   : 2;
  unsigned char VECT19SPR   : 2;
} __BITS_ITC_SPR5;
#endif
__IO_REG8_BIT(ITC_SPR5,    0x7F74, __READ_WRITE, __BITS_ITC_SPR5);

/* Interrupt software priority register 6 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT20SPR   : 2;
  unsigned char VECT21SPR   : 2;
  unsigned char VECT22SPR   : 2;
  unsigned char VECT23SPR   : 2;
} __BITS_ITC_SPR6;
#endif
__IO_REG8_BIT(ITC_SPR6,    0x7F75, __READ_WRITE, __BITS_ITC_SPR6);

/* Interrupt software priority register 7 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT24SPR   : 2;
  unsigned char VECT25SPR   : 2;
  unsigned char VECT26SPR   : 2;
  unsigned char VECT27SPR   : 2;
} __BITS_ITC_SPR7;
#endif
__IO_REG8_BIT(ITC_SPR7,    0x7F76, __READ_WRITE, __BITS_ITC_SPR7);

/* Interrupt software priority register 8 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char VECT28SPR   : 2;
  unsigned char VECT29SPR   : 2;
} __BITS_ITC_SPR8;
#endif
__IO_REG8_BIT(ITC_SPR8,    0x7F77, __READ_WRITE, __BITS_ITC_SPR8);


/*-------------------------------------------------------------------------
 *      ITC bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define EXTI_CR1_PAIS            EXTI_CR1_bit.PAIS
#define EXTI_CR1_PBIS            EXTI_CR1_bit.PBIS
#define EXTI_CR1_PCIS            EXTI_CR1_bit.PCIS
#define EXTI_CR1_PDIS            EXTI_CR1_bit.PDIS

#define EXTI_CR2_PEIS            EXTI_CR2_bit.PEIS
#define EXTI_CR2_TLIS            EXTI_CR2_bit.TLIS

#define RST_SR_WWDGF             RST_SR_bit.WWDGF
#define RST_SR_IWDGF             RST_SR_bit.IWDGF
#define RST_SR_ILLOPF            RST_SR_bit.ILLOPF
#define RST_SR_SWIMF             RST_SR_bit.SWIMF
#define RST_SR_EMCF              RST_SR_bit.EMCF

#define ITC_SPR1_VECT0SPR        ITC_SPR1_bit.VECT0SPR
#define ITC_SPR1_VECT1SPR        ITC_SPR1_bit.VECT1SPR
#define ITC_SPR1_VECT2SPR        ITC_SPR1_bit.VECT2SPR
#define ITC_SPR1_VECT3SPR        ITC_SPR1_bit.VECT3SPR

#define ITC_SPR2_VECT4SPR        ITC_SPR2_bit.VECT4SPR
#define ITC_SPR2_VECT5SPR        ITC_SPR2_bit.VECT5SPR
#define ITC_SPR2_VECT6SPR        ITC_SPR2_bit.VECT6SPR
#define ITC_SPR2_VECT7SPR        ITC_SPR2_bit.VECT7SPR

#define ITC_SPR3_VECT8SPR        ITC_SPR3_bit.VECT8SPR
#define ITC_SPR3_VECT9SPR        ITC_SPR3_bit.VECT9SPR
#define ITC_SPR3_VECT10SPR       ITC_SPR3_bit.VECT10SPR
#define ITC_SPR3_VECT11SPR       ITC_SPR3_bit.VECT11SPR

#define ITC_SPR4_VECT12SPR       ITC_SPR4_bit.VECT12SPR
#define ITC_SPR4_VECT13SPR       ITC_SPR4_bit.VECT13SPR
#define ITC_SPR4_VECT14SPR       ITC_SPR4_bit.VECT14SPR
#define ITC_SPR4_VECT15SPR       ITC_SPR4_bit.VECT15SPR

#define ITC_SPR5_VECT16SPR       ITC_SPR5_bit.VECT16SPR
#define ITC_SPR5_VECT17SPR       ITC_SPR5_bit.VECT17SPR
#define ITC_SPR5_VECT18SPR       ITC_SPR5_bit.VECT18SPR
#define ITC_SPR5_VECT19SPR       ITC_SPR5_bit.VECT19SPR

#define ITC_SPR6_VECT20SPR       ITC_SPR6_bit.VECT20SPR
#define ITC_SPR6_VECT21SPR       ITC_SPR6_bit.VECT21SPR
#define ITC_SPR6_VECT22SPR       ITC_SPR6_bit.VECT22SPR
#define ITC_SPR6_VECT23SPR       ITC_SPR6_bit.VECT23SPR

#define ITC_SPR7_VECT24SPR       ITC_SPR7_bit.VECT24SPR
#define ITC_SPR7_VECT25SPR       ITC_SPR7_bit.VECT25SPR
#define ITC_SPR7_VECT26SPR       ITC_SPR7_bit.VECT26SPR
#define ITC_SPR7_VECT27SPR       ITC_SPR7_bit.VECT27SPR

#define ITC_SPR8_VECT28SPR       ITC_SPR8_bit.VECT28SPR
#define ITC_SPR8_VECT29SPR       ITC_SPR8_bit.VECT29SPR

#endif

/*-------------------------------------------------------------------------
 *      ITC bit masks
 *-----------------------------------------------------------------------*/
#define MASK_EXTI_CR1_PAIS       0x03
#define MASK_EXTI_CR1_PBIS       0x0C
#define MASK_EXTI_CR1_PCIS       0x30
#define MASK_EXTI_CR1_PDIS       0xC0

#define MASK_EXTI_CR2_PEIS       0x03
#define MASK_EXTI_CR2_TLIS       0x04

#define MASK_RST_SR_WWDGF        0x01
#define MASK_RST_SR_IWDGF        0x02
#define MASK_RST_SR_ILLOPF       0x04
#define MASK_RST_SR_SWIMF        0x08
#define MASK_RST_SR_EMCF         0x10

#define MASK_ITC_SPR1_VECT0SPR   0x03
#define MASK_ITC_SPR1_VECT1SPR   0x0C
#define MASK_ITC_SPR1_VECT2SPR   0x30
#define MASK_ITC_SPR1_VECT3SPR   0xC0

#define MASK_ITC_SPR2_VECT4SPR   0x03
#define MASK_ITC_SPR2_VECT5SPR   0x0C
#define MASK_ITC_SPR2_VECT6SPR   0x30
#define MASK_ITC_SPR2_VECT7SPR   0xC0

#define MASK_ITC_SPR3_VECT8SPR   0x03
#define MASK_ITC_SPR3_VECT9SPR   0x0C
#define MASK_ITC_SPR3_VECT10SPR  0x30
#define MASK_ITC_SPR3_VECT11SPR  0xC0

#define MASK_ITC_SPR4_VECT12SPR  0x03
#define MASK_ITC_SPR4_VECT13SPR  0x0C
#define MASK_ITC_SPR4_VECT14SPR  0x30
#define MASK_ITC_SPR4_VECT15SPR  0xC0

#define MASK_ITC_SPR5_VECT16SPR  0x03
#define MASK_ITC_SPR5_VECT17SPR  0x0C
#define MASK_ITC_SPR5_VECT18SPR  0x30
#define MASK_ITC_SPR5_VECT19SPR  0xC0

#define MASK_ITC_SPR6_VECT20SPR  0x03
#define MASK_ITC_SPR6_VECT21SPR  0x0C
#define MASK_ITC_SPR6_VECT22SPR  0x30
#define MASK_ITC_SPR6_VECT23SPR  0xC0

#define MASK_ITC_SPR7_VECT24SPR  0x03
#define MASK_ITC_SPR7_VECT25SPR  0x0C
#define MASK_ITC_SPR7_VECT26SPR  0x30
#define MASK_ITC_SPR7_VECT27SPR  0xC0

#define MASK_ITC_SPR8_VECT28SPR  0x03
#define MASK_ITC_SPR8_VECT29SPR  0x0C


/*-------------------------------------------------------------------------
 *      CLK register definitions
 *-----------------------------------------------------------------------*/
/* Internal clock control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char HSIEN       : 1;
  unsigned char HSIRDY      : 1;
  unsigned char FHW         : 1;
  unsigned char LSIEN       : 1;
  unsigned char LSIRDY      : 1;
  unsigned char REGAH       : 1;
} __BITS_CLK_ICKR;
#endif
__IO_REG8_BIT(CLK_ICKR,    0x50C0, __READ_WRITE, __BITS_CLK_ICKR);

/* External clock control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char HSEEN       : 1;
  unsigned char HSERDY      : 1;
} __BITS_CLK_ECKR;
#endif
__IO_REG8_BIT(CLK_ECKR,    0x50C1, __READ_WRITE, __BITS_CLK_ECKR);

/* Clock master status register */
__IO_REG8    (CLK_CMSR,    0x50C3, __READ);
/* Clock master switch register */
__IO_REG8    (CLK_SWR,     0x50C4, __READ_WRITE);
/* Clock switch control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SWBSY       : 1;
  unsigned char SWEN        : 1;
  unsigned char SWIEN       : 1;
  unsigned char SWIF        : 1;
} __BITS_CLK_SWCR;
#endif
__IO_REG8_BIT(CLK_SWCR,    0x50C5, __READ_WRITE, __BITS_CLK_SWCR);

/* Clock divider register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CPUDIV      : 3;
  unsigned char HSIDIV      : 2;
} __BITS_CLK_CKDIVR;
#endif
__IO_REG8_BIT(CLK_CKDIVR,  0x50C6, __READ_WRITE, __BITS_CLK_CKDIVR);

/* Peripheral clock gating register 1 */
__IO_REG8    (CLK_PCKENR1, 0x50C7, __READ_WRITE);
/* Clock security system register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CSSEN       : 1;
  unsigned char AUX         : 1;
  unsigned char CSSDIE      : 1;
  unsigned char CSSD        : 1;
} __BITS_CLK_CSSR;
#endif
__IO_REG8_BIT(CLK_CSSR,    0x50C8, __READ_WRITE, __BITS_CLK_CSSR);

/* Configurable clock control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CCOEN       : 1;
  unsigned char CCOSEL      : 4;
  unsigned char CCORDY      : 1;
  unsigned char CC0BSY      : 1;
} __BITS_CLK_CCOR;
#endif
__IO_REG8_BIT(CLK_CCOR,    0x50C9, __READ_WRITE, __BITS_CLK_CCOR);

/* Peripheral clock gating register 2 */
__IO_REG8    (CLK_PCKENR2, 0x50CA, __READ_WRITE);
/* CAN clock control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CANDIV      : 3;
} __BITS_CLK_CANCCR;
#endif
__IO_REG8_BIT(CLK_CANCCR,  0x50CB, __READ_WRITE, __BITS_CLK_CANCCR);

/* HSI clock calibration trimming register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char HSITRIM     : 4;
} __BITS_CLK_HSITRIMR;
#endif
__IO_REG8_BIT(CLK_HSITRIMR, 0x50CC, __READ_WRITE, __BITS_CLK_HSITRIMR);

/* SWIM clock control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SWIMCLK     : 1;
} __BITS_CLK_SWIMCCR;
#endif
__IO_REG8_BIT(CLK_SWIMCCR, 0x50CD, __READ_WRITE, __BITS_CLK_SWIMCCR);


/*-------------------------------------------------------------------------
 *      CLK bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define CLK_ICKR_HSIEN           CLK_ICKR_bit.HSIEN
#define CLK_ICKR_HSIRDY          CLK_ICKR_bit.HSIRDY
#define CLK_ICKR_FHW             CLK_ICKR_bit.FHW
#define CLK_ICKR_LSIEN           CLK_ICKR_bit.LSIEN
#define CLK_ICKR_LSIRDY          CLK_ICKR_bit.LSIRDY
#define CLK_ICKR_REGAH           CLK_ICKR_bit.REGAH

#define CLK_ECKR_HSEEN           CLK_ECKR_bit.HSEEN
#define CLK_ECKR_HSERDY          CLK_ECKR_bit.HSERDY

#define CLK_SWCR_SWBSY           CLK_SWCR_bit.SWBSY
#define CLK_SWCR_SWEN            CLK_SWCR_bit.SWEN
#define CLK_SWCR_SWIEN           CLK_SWCR_bit.SWIEN
#define CLK_SWCR_SWIF            CLK_SWCR_bit.SWIF

#define CLK_CKDIVR_CPUDIV        CLK_CKDIVR_bit.CPUDIV
#define CLK_CKDIVR_HSIDIV        CLK_CKDIVR_bit.HSIDIV

#define CLK_CSSR_CSSEN           CLK_CSSR_bit.CSSEN
#define CLK_CSSR_AUX             CLK_CSSR_bit.AUX
#define CLK_CSSR_CSSDIE          CLK_CSSR_bit.CSSDIE
#define CLK_CSSR_CSSD            CLK_CSSR_bit.CSSD

#define CLK_CCOR_CCOEN           CLK_CCOR_bit.CCOEN
#define CLK_CCOR_CCOSEL          CLK_CCOR_bit.CCOSEL
#define CLK_CCOR_CCORDY          CLK_CCOR_bit.CCORDY
#define CLK_CCOR_CC0BSY          CLK_CCOR_bit.CC0BSY

#define CLK_CANCCR_CANDIV        CLK_CANCCR_bit.CANDIV

#define CLK_HSITRIMR_HSITRIM     CLK_HSITRIMR_bit.HSITRIM

#define CLK_SWIMCCR_SWIMCLK      CLK_SWIMCCR_bit.SWIMCLK

#endif

/*-------------------------------------------------------------------------
 *      CLK bit masks
 *-----------------------------------------------------------------------*/
#define MASK_CLK_ICKR_HSIEN      0x01
#define MASK_CLK_ICKR_HSIRDY     0x02
#define MASK_CLK_ICKR_FHW        0x04
#define MASK_CLK_ICKR_LSIEN      0x08
#define MASK_CLK_ICKR_LSIRDY     0x10
#define MASK_CLK_ICKR_REGAH      0x20

#define MASK_CLK_ECKR_HSEEN      0x01
#define MASK_CLK_ECKR_HSERDY     0x02

#define MASK_CLK_SWCR_SWBSY      0x01
#define MASK_CLK_SWCR_SWEN       0x02
#define MASK_CLK_SWCR_SWIEN      0x04
#define MASK_CLK_SWCR_SWIF       0x08

#define MASK_CLK_CKDIVR_CPUDIV   0x07
#define MASK_CLK_CKDIVR_HSIDIV   0x18

#define MASK_CLK_CSSR_CSSEN      0x01
#define MASK_CLK_CSSR_AUX        0x02
#define MASK_CLK_CSSR_CSSDIE     0x04
#define MASK_CLK_CSSR_CSSD       0x08

#define MASK_CLK_CCOR_CCOEN      0x01
#define MASK_CLK_CCOR_CCOSEL     0x1E
#define MASK_CLK_CCOR_CCORDY     0x20
#define MASK_CLK_CCOR_CC0BSY     0x40

#define MASK_CLK_CANCCR_CANDIV   0x07

#define MASK_CLK_HSITRIMR_HSITRIM 0x0F

#define MASK_CLK_SWIMCCR_SWIMCLK 0x01


/*-------------------------------------------------------------------------
 *      WWDG register definitions
 *-----------------------------------------------------------------------*/
/* WWDG control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char T0          : 1;
  unsigned char T1          : 1;
  unsigned char T2          : 1;
  unsigned char T3          : 1;
  unsigned char T4          : 1;
  unsigned char T5          : 1;
  unsigned char T6          : 1;
  unsigned char WDGA        : 1;
} __BITS_WWDG_CR;
#endif
__IO_REG8_BIT(WWDG_CR,     0x50D1, __READ_WRITE, __BITS_WWDG_CR);

/* WWDR window register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char W0          : 1;
  unsigned char W1          : 1;
  unsigned char W2          : 1;
  unsigned char W3          : 1;
  unsigned char W4          : 1;
  unsigned char W5          : 1;
  unsigned char W6          : 1;
} __BITS_WWDG_WR;
#endif
__IO_REG8_BIT(WWDG_WR,     0x50D2, __READ_WRITE, __BITS_WWDG_WR);


/*-------------------------------------------------------------------------
 *      WWDG bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define WWDG_CR_T0               WWDG_CR_bit.T0
#define WWDG_CR_T1               WWDG_CR_bit.T1
#define WWDG_CR_T2               WWDG_CR_bit.T2
#define WWDG_CR_T3               WWDG_CR_bit.T3
#define WWDG_CR_T4               WWDG_CR_bit.T4
#define WWDG_CR_T5               WWDG_CR_bit.T5
#define WWDG_CR_T6               WWDG_CR_bit.T6
#define WWDG_CR_WDGA             WWDG_CR_bit.WDGA

#define WWDG_WR_W0               WWDG_WR_bit.W0
#define WWDG_WR_W1               WWDG_WR_bit.W1
#define WWDG_WR_W2               WWDG_WR_bit.W2
#define WWDG_WR_W3               WWDG_WR_bit.W3
#define WWDG_WR_W4               WWDG_WR_bit.W4
#define WWDG_WR_W5               WWDG_WR_bit.W5
#define WWDG_WR_W6               WWDG_WR_bit.W6

#endif

/*-------------------------------------------------------------------------
 *      WWDG bit masks
 *-----------------------------------------------------------------------*/
#define MASK_WWDG_CR_T0          0x01
#define MASK_WWDG_CR_T1          0x02
#define MASK_WWDG_CR_T2          0x04
#define MASK_WWDG_CR_T3          0x08
#define MASK_WWDG_CR_T4          0x10
#define MASK_WWDG_CR_T5          0x20
#define MASK_WWDG_CR_T6          0x40
#define MASK_WWDG_CR_WDGA        0x80

#define MASK_WWDG_WR_W0          0x01
#define MASK_WWDG_WR_W1          0x02
#define MASK_WWDG_WR_W2          0x04
#define MASK_WWDG_WR_W3          0x08
#define MASK_WWDG_WR_W4          0x10
#define MASK_WWDG_WR_W5          0x20
#define MASK_WWDG_WR_W6          0x40


/*-------------------------------------------------------------------------
 *      IWDG register definitions
 *-----------------------------------------------------------------------*/
/* IWDG key register */
__IO_REG8    (IWDG_KR,     0x50E0, __WRITE);
/* IWDG prescaler register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PR          : 3;
} __BITS_IWDG_PR;
#endif
__IO_REG8_BIT(IWDG_PR,     0x50E1, __READ_WRITE, __BITS_IWDG_PR);

/* IWDG reload register */
__IO_REG8    (IWDG_RLR,    0x50E2, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      IWDG bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define IWDG_PR_PR               IWDG_PR_bit.PR

#endif

/*-------------------------------------------------------------------------
 *      IWDG bit masks
 *-----------------------------------------------------------------------*/
#define MASK_IWDG_PR_PR          0x07


/*-------------------------------------------------------------------------
 *      AWU register definitions
 *-----------------------------------------------------------------------*/
/* AWU control/status register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char MSR         : 1;
  unsigned char             : 3;
  unsigned char AWUEN       : 1;
  unsigned char AWUF        : 1;
} __BITS_AWU_CSR1;
#endif
__IO_REG8_BIT(AWU_CSR1,    0x50F0, __READ_WRITE, __BITS_AWU_CSR1);

/* AWU asynchronous prescaler buffer register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char APR         : 6;
} __BITS_AWU_APR;
#endif
__IO_REG8_BIT(AWU_APR,     0x50F1, __READ_WRITE, __BITS_AWU_APR);

/* AWU timebase selection register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char AWUTB       : 4;
} __BITS_AWU_TBR;
#endif
__IO_REG8_BIT(AWU_TBR,     0x50F2, __READ_WRITE, __BITS_AWU_TBR);


/*-------------------------------------------------------------------------
 *      AWU bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define AWU_CSR1_MSR             AWU_CSR1_bit.MSR
#define AWU_CSR1_AWUEN           AWU_CSR1_bit.AWUEN
#define AWU_CSR1_AWUF            AWU_CSR1_bit.AWUF

#define AWU_APR_APR              AWU_APR_bit.APR

#define AWU_TBR_AWUTB            AWU_TBR_bit.AWUTB

#endif

/*-------------------------------------------------------------------------
 *      AWU bit masks
 *-----------------------------------------------------------------------*/
#define MASK_AWU_CSR1_MSR        0x01
#define MASK_AWU_CSR1_AWUEN      0x10
#define MASK_AWU_CSR1_AWUF       0x20

#define MASK_AWU_APR_APR         0x3F

#define MASK_AWU_TBR_AWUTB       0x0F


/*-------------------------------------------------------------------------
 *      BEEP register definitions
 *-----------------------------------------------------------------------*/
/* BEEP control/status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char BEEPDIV     : 5;
  unsigned char BEEPEN      : 1;
  unsigned char BEEPSEL     : 2;
} __BITS_BEEP_CSR;
#endif
__IO_REG8_BIT(BEEP_CSR,    0x50F3, __READ_WRITE, __BITS_BEEP_CSR);


/*-------------------------------------------------------------------------
 *      BEEP bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define BEEP_CSR_BEEPDIV         BEEP_CSR_bit.BEEPDIV
#define BEEP_CSR_BEEPEN          BEEP_CSR_bit.BEEPEN
#define BEEP_CSR_BEEPSEL         BEEP_CSR_bit.BEEPSEL

#endif

/*-------------------------------------------------------------------------
 *      BEEP bit masks
 *-----------------------------------------------------------------------*/
#define MASK_BEEP_CSR_BEEPDIV    0x1F
#define MASK_BEEP_CSR_BEEPEN     0x20
#define MASK_BEEP_CSR_BEEPSEL    0xC0


/*-------------------------------------------------------------------------
 *      SPI register definitions
 *-----------------------------------------------------------------------*/
/* SPI control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CPHA        : 1;
  unsigned char CPOL        : 1;
  unsigned char MSTR        : 1;
  unsigned char BR          : 3;
  unsigned char SPE         : 1;
  unsigned char LSBFIRST    : 1;
} __BITS_SPI_CR1;
#endif
__IO_REG8_BIT(SPI_CR1,     0x5200, __READ_WRITE, __BITS_SPI_CR1);

/* SPI control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SSI         : 1;
  unsigned char SSM         : 1;
  unsigned char RXONLY      : 1;
  unsigned char             : 1;
  unsigned char CRCNEXT     : 1;
  unsigned char CECEN       : 1;
  unsigned char BDOE        : 1;
  unsigned char BDM         : 1;
} __BITS_SPI_CR2;
#endif
__IO_REG8_BIT(SPI_CR2,     0x5201, __READ_WRITE, __BITS_SPI_CR2);

/* SPI interrupt control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 4;
  unsigned char WKIE        : 1;
  unsigned char ERRIE       : 1;
  unsigned char RXIE        : 1;
  unsigned char TXIE        : 1;
} __BITS_SPI_ICR;
#endif
__IO_REG8_BIT(SPI_ICR,     0x5202, __READ_WRITE, __BITS_SPI_ICR);

/* SPI status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char RXNE        : 1;
  unsigned char TXE         : 1;
  unsigned char             : 1;
  unsigned char WKUP        : 1;
  unsigned char CRCERR      : 1;
  unsigned char MODF        : 1;
  unsigned char OVR         : 1;
  unsigned char BSY         : 1;
} __BITS_SPI_SR;
#endif
__IO_REG8_BIT(SPI_SR,      0x5203, __READ_WRITE, __BITS_SPI_SR);

/* SPI data register */
__IO_REG8    (SPI_DR,      0x5204, __READ_WRITE);
/* SPI CRC polynomial register */
__IO_REG8    (SPI_CRCPR,   0x5205, __READ_WRITE);
/* SPI Rx CRC register */
__IO_REG8    (SPI_RXCRCR,  0x5206, __READ);
/* SPI Tx CRC register */
__IO_REG8    (SPI_TXCRCR,  0x5207, __READ);

/*-------------------------------------------------------------------------
 *      SPI bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define SPI_CR1_CPHA             SPI_CR1_bit.CPHA
#define SPI_CR1_CPOL             SPI_CR1_bit.CPOL
#define SPI_CR1_MSTR             SPI_CR1_bit.MSTR
#define SPI_CR1_BR               SPI_CR1_bit.BR
#define SPI_CR1_SPE              SPI_CR1_bit.SPE
#define SPI_CR1_LSBFIRST         SPI_CR1_bit.LSBFIRST

#define SPI_CR2_SSI              SPI_CR2_bit.SSI
#define SPI_CR2_SSM              SPI_CR2_bit.SSM
#define SPI_CR2_RXONLY           SPI_CR2_bit.RXONLY
#define SPI_CR2_CRCNEXT          SPI_CR2_bit.CRCNEXT
#define SPI_CR2_CECEN            SPI_CR2_bit.CECEN
#define SPI_CR2_BDOE             SPI_CR2_bit.BDOE
#define SPI_CR2_BDM              SPI_CR2_bit.BDM

#define SPI_ICR_WKIE             SPI_ICR_bit.WKIE
#define SPI_ICR_ERRIE            SPI_ICR_bit.ERRIE
#define SPI_ICR_RXIE             SPI_ICR_bit.RXIE
#define SPI_ICR_TXIE             SPI_ICR_bit.TXIE

#define SPI_SR_RXNE              SPI_SR_bit.RXNE
#define SPI_SR_TXE               SPI_SR_bit.TXE
#define SPI_SR_WKUP              SPI_SR_bit.WKUP
#define SPI_SR_CRCERR            SPI_SR_bit.CRCERR
#define SPI_SR_MODF              SPI_SR_bit.MODF
#define SPI_SR_OVR               SPI_SR_bit.OVR
#define SPI_SR_BSY               SPI_SR_bit.BSY

#endif

/*-------------------------------------------------------------------------
 *      SPI bit masks
 *-----------------------------------------------------------------------*/
#define MASK_SPI_CR1_CPHA        0x01
#define MASK_SPI_CR1_CPOL        0x02
#define MASK_SPI_CR1_MSTR        0x04
#define MASK_SPI_CR1_BR          0x38
#define MASK_SPI_CR1_SPE         0x40
#define MASK_SPI_CR1_LSBFIRST    0x80

#define MASK_SPI_CR2_SSI         0x01
#define MASK_SPI_CR2_SSM         0x02
#define MASK_SPI_CR2_RXONLY      0x04
#define MASK_SPI_CR2_CRCNEXT     0x10
#define MASK_SPI_CR2_CECEN       0x20
#define MASK_SPI_CR2_BDOE        0x40
#define MASK_SPI_CR2_BDM         0x80

#define MASK_SPI_ICR_WKIE        0x10
#define MASK_SPI_ICR_ERRIE       0x20
#define MASK_SPI_ICR_RXIE        0x40
#define MASK_SPI_ICR_TXIE        0x80

#define MASK_SPI_SR_RXNE         0x01
#define MASK_SPI_SR_TXE          0x02
#define MASK_SPI_SR_WKUP         0x08
#define MASK_SPI_SR_CRCERR       0x10
#define MASK_SPI_SR_MODF         0x20
#define MASK_SPI_SR_OVR          0x40
#define MASK_SPI_SR_BSY          0x80


/*-------------------------------------------------------------------------
 *      I2C register definitions
 *-----------------------------------------------------------------------*/
/* I2C control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PE          : 1;
  unsigned char             : 5;
  unsigned char ENGC        : 1;
  unsigned char NOSTRETCH   : 1;
} __BITS_I2C_CR1;
#endif
__IO_REG8_BIT(I2C_CR1,     0x5210, __READ_WRITE, __BITS_I2C_CR1);

/* I2C control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char START       : 1;
  unsigned char STOP        : 1;
  unsigned char ACK         : 1;
  unsigned char POS         : 1;
  unsigned char             : 3;
  unsigned char SWRST       : 1;
} __BITS_I2C_CR2;
#endif
__IO_REG8_BIT(I2C_CR2,     0x5211, __READ_WRITE, __BITS_I2C_CR2);

/* I2C frequency register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char FREQ        : 6;
} __BITS_I2C_FREQR;
#endif
__IO_REG8_BIT(I2C_FREQR,   0x5212, __READ_WRITE, __BITS_I2C_FREQR);

/* I2C Own address register low */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ADD0        : 1;
  unsigned char ADD         : 7;
} __BITS_I2C_OARL;
#endif
__IO_REG8_BIT(I2C_OARL,    0x5213, __READ_WRITE, __BITS_I2C_OARL);

/* I2C Own address register high */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 1;
  unsigned char ADD         : 2;
  unsigned char             : 3;
  unsigned char ADDCONF     : 1;
  unsigned char ADDMODE     : 1;
} __BITS_I2C_OARH;
#endif
__IO_REG8_BIT(I2C_OARH,    0x5214, __READ_WRITE, __BITS_I2C_OARH);

/* I2C data register */
__IO_REG8    (I2C_DR,      0x5216, __READ_WRITE);
/* I2C status register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SB          : 1;
  unsigned char ADDR        : 1;
  unsigned char BTF         : 1;
  unsigned char ADD10       : 1;
  unsigned char STOPF       : 1;
  unsigned char             : 1;
  unsigned char RXNE        : 1;
  unsigned char TXE         : 1;
} __BITS_I2C_SR1;
#endif
__IO_REG8_BIT(I2C_SR1,     0x5217, __READ, __BITS_I2C_SR1);

/* I2C status register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char BERR        : 1;
  unsigned char ARLO        : 1;
  unsigned char AF          : 1;
  unsigned char OVR         : 1;
  unsigned char             : 1;
  unsigned char WUFH        : 1;
} __BITS_I2C_SR2;
#endif
__IO_REG8_BIT(I2C_SR2,     0x5218, __READ_WRITE, __BITS_I2C_SR2);

/* I2C status register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char MSL         : 1;
  unsigned char BUSY        : 1;
  unsigned char TRA         : 1;
  unsigned char             : 1;
  unsigned char GENCALL     : 1;
} __BITS_I2C_SR3;
#endif
__IO_REG8_BIT(I2C_SR3,     0x5219, __READ, __BITS_I2C_SR3);

/* I2C interrupt control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ITERREN     : 1;
  unsigned char ITEVTEN     : 1;
  unsigned char ITBUFEN     : 1;
} __BITS_I2C_ITR;
#endif
__IO_REG8_BIT(I2C_ITR,     0x521A, __READ_WRITE, __BITS_I2C_ITR);

/* I2C Clock control register low */
__IO_REG8    (I2C_CCRL,    0x521B, __READ_WRITE);
/* I2C Clock control register high */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CCR         : 4;
  unsigned char             : 2;
  unsigned char DUTY        : 1;
  unsigned char F_S         : 1;
} __BITS_I2C_CCRH;
#endif
__IO_REG8_BIT(I2C_CCRH,    0x521C, __READ_WRITE, __BITS_I2C_CCRH);

/* I2C TRISE register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char TRISE       : 6;
} __BITS_I2C_TRISER;
#endif
__IO_REG8_BIT(I2C_TRISER,  0x521D, __READ_WRITE, __BITS_I2C_TRISER);

/* I2C packet error checking register */
__IO_REG8    (I2C_PECR,    0x521E, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      I2C bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define I2C_CR1_PE               I2C_CR1_bit.PE
#define I2C_CR1_ENGC             I2C_CR1_bit.ENGC
#define I2C_CR1_NOSTRETCH        I2C_CR1_bit.NOSTRETCH

#define I2C_CR2_START            I2C_CR2_bit.START
#define I2C_CR2_STOP             I2C_CR2_bit.STOP
#define I2C_CR2_ACK              I2C_CR2_bit.ACK
#define I2C_CR2_POS              I2C_CR2_bit.POS
#define I2C_CR2_SWRST            I2C_CR2_bit.SWRST

#define I2C_FREQR_FREQ           I2C_FREQR_bit.FREQ

#define I2C_OARL_ADD0            I2C_OARL_bit.ADD0
#define I2C_OARL_ADD             I2C_OARL_bit.ADD

#define I2C_OARH_ADD             I2C_OARH_bit.ADD
#define I2C_OARH_ADDCONF         I2C_OARH_bit.ADDCONF
#define I2C_OARH_ADDMODE         I2C_OARH_bit.ADDMODE

#define I2C_SR1_SB               I2C_SR1_bit.SB
#define I2C_SR1_ADDR             I2C_SR1_bit.ADDR
#define I2C_SR1_BTF              I2C_SR1_bit.BTF
#define I2C_SR1_ADD10            I2C_SR1_bit.ADD10
#define I2C_SR1_STOPF            I2C_SR1_bit.STOPF
#define I2C_SR1_RXNE             I2C_SR1_bit.RXNE
#define I2C_SR1_TXE              I2C_SR1_bit.TXE

#define I2C_SR2_BERR             I2C_SR2_bit.BERR
#define I2C_SR2_ARLO             I2C_SR2_bit.ARLO
#define I2C_SR2_AF               I2C_SR2_bit.AF
#define I2C_SR2_OVR              I2C_SR2_bit.OVR
#define I2C_SR2_WUFH             I2C_SR2_bit.WUFH

#define I2C_SR3_MSL              I2C_SR3_bit.MSL
#define I2C_SR3_BUSY             I2C_SR3_bit.BUSY
#define I2C_SR3_TRA              I2C_SR3_bit.TRA
#define I2C_SR3_GENCALL          I2C_SR3_bit.GENCALL

#define I2C_ITR_ITERREN          I2C_ITR_bit.ITERREN
#define I2C_ITR_ITEVTEN          I2C_ITR_bit.ITEVTEN
#define I2C_ITR_ITBUFEN          I2C_ITR_bit.ITBUFEN

#define I2C_CCRH_CCR             I2C_CCRH_bit.CCR
#define I2C_CCRH_DUTY            I2C_CCRH_bit.DUTY
#define I2C_CCRH_F_S             I2C_CCRH_bit.F_S

#define I2C_TRISER_TRISE         I2C_TRISER_bit.TRISE

#endif

/*-------------------------------------------------------------------------
 *      I2C bit masks
 *-----------------------------------------------------------------------*/
#define MASK_I2C_CR1_PE          0x01
#define MASK_I2C_CR1_ENGC        0x40
#define MASK_I2C_CR1_NOSTRETCH   0x80

#define MASK_I2C_CR2_START       0x01
#define MASK_I2C_CR2_STOP        0x02
#define MASK_I2C_CR2_ACK         0x04
#define MASK_I2C_CR2_POS         0x08
#define MASK_I2C_CR2_SWRST       0x80

#define MASK_I2C_FREQR_FREQ      0x3F

#define MASK_I2C_OARL_ADD0       0x01
#define MASK_I2C_OARL_ADD        0xFE

#define MASK_I2C_OARH_ADD        0x06
#define MASK_I2C_OARH_ADDCONF    0x40
#define MASK_I2C_OARH_ADDMODE    0x80

#define MASK_I2C_SR1_SB          0x01
#define MASK_I2C_SR1_ADDR        0x02
#define MASK_I2C_SR1_BTF         0x04
#define MASK_I2C_SR1_ADD10       0x08
#define MASK_I2C_SR1_STOPF       0x10
#define MASK_I2C_SR1_RXNE        0x40
#define MASK_I2C_SR1_TXE         0x80

#define MASK_I2C_SR2_BERR        0x01
#define MASK_I2C_SR2_ARLO        0x02
#define MASK_I2C_SR2_AF          0x04
#define MASK_I2C_SR2_OVR         0x08
#define MASK_I2C_SR2_WUFH        0x20

#define MASK_I2C_SR3_MSL         0x01
#define MASK_I2C_SR3_BUSY        0x02
#define MASK_I2C_SR3_TRA         0x04
#define MASK_I2C_SR3_GENCALL     0x10

#define MASK_I2C_ITR_ITERREN     0x01
#define MASK_I2C_ITR_ITEVTEN     0x02
#define MASK_I2C_ITR_ITBUFEN     0x04

#define MASK_I2C_CCRH_CCR        0x0F
#define MASK_I2C_CCRH_DUTY       0x40
#define MASK_I2C_CCRH_F_S        0x80

#define MASK_I2C_TRISER_TRISE    0x3F


/*-------------------------------------------------------------------------
 *      UART1 register definitions
 *-----------------------------------------------------------------------*/
/* UART1 status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PE          : 1;
  unsigned char FE          : 1;
  unsigned char NF          : 1;
  unsigned char OR_LHE      : 1;
  unsigned char IDLE        : 1;
  unsigned char RXNE        : 1;
  unsigned char TC          : 1;
  unsigned char TXE         : 1;
} __BITS_UART1_SR;
#endif
__IO_REG8_BIT(UART1_SR,    0x5230, __READ_WRITE, __BITS_UART1_SR);

/* UART1 data register */
__IO_REG8    (UART1_DR,    0x5231, __READ_WRITE);
/* UART1 baud rate register 1 */
__IO_REG8    (UART1_BRR1,  0x5232, __READ_WRITE);
/* UART1 baud rate register 2 */
__IO_REG8    (UART1_BRR2,  0x5233, __READ_WRITE);
/* UART1 control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PIEN        : 1;
  unsigned char PS          : 1;
  unsigned char PCEN        : 1;
  unsigned char WAKE        : 1;
  unsigned char M           : 1;
  unsigned char UART0       : 1;
  unsigned char T8          : 1;
  unsigned char R8          : 1;
} __BITS_UART1_CR1;
#endif
__IO_REG8_BIT(UART1_CR1,   0x5234, __READ_WRITE, __BITS_UART1_CR1);

/* UART1 control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SBK         : 1;
  unsigned char RWU         : 1;
  unsigned char REN         : 1;
  unsigned char TEN         : 1;
  unsigned char ILIEN       : 1;
  unsigned char RIEN        : 1;
  unsigned char TCIEN       : 1;
  unsigned char TIEN        : 1;
} __BITS_UART1_CR2;
#endif
__IO_REG8_BIT(UART1_CR2,   0x5235, __READ_WRITE, __BITS_UART1_CR2);

/* UART1 control register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char LBCL        : 1;
  unsigned char CPHA        : 1;
  unsigned char CPOL        : 1;
  unsigned char CKEN        : 1;
  unsigned char STOP        : 2;
  unsigned char             : 1;
  unsigned char LINEN       : 1;
} __BITS_UART1_CR3;
#endif
__IO_REG8_BIT(UART1_CR3,   0x5236, __READ_WRITE, __BITS_UART1_CR3);

/* UART1 control register 4 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ADD         : 4;
  unsigned char LBDF        : 1;
  unsigned char LBDL        : 1;
  unsigned char LBDIEN      : 1;
} __BITS_UART1_CR4;
#endif
__IO_REG8_BIT(UART1_CR4,   0x5237, __READ_WRITE, __BITS_UART1_CR4);

/* UART1 control register 5 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 1;
  unsigned char IREN        : 1;
  unsigned char IRLP        : 1;
  unsigned char HDSEL       : 1;
  unsigned char NACK        : 1;
  unsigned char SCEN        : 1;
} __BITS_UART1_CR5;
#endif
__IO_REG8_BIT(UART1_CR5,   0x5238, __READ_WRITE, __BITS_UART1_CR5);

/* UART1 guard time register */
__IO_REG8    (UART1_GTR,   0x5239, __READ_WRITE);
/* UART1 prescaler register */
__IO_REG8    (UART1_PSCR,  0x523A, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      UART1 bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define UART1_SR_PE              UART1_SR_bit.PE
#define UART1_SR_FE              UART1_SR_bit.FE
#define UART1_SR_NF              UART1_SR_bit.NF
#define UART1_SR_OR_LHE          UART1_SR_bit.OR_LHE
#define UART1_SR_IDLE            UART1_SR_bit.IDLE
#define UART1_SR_RXNE            UART1_SR_bit.RXNE
#define UART1_SR_TC              UART1_SR_bit.TC
#define UART1_SR_TXE             UART1_SR_bit.TXE

#define UART1_CR1_PIEN           UART1_CR1_bit.PIEN
#define UART1_CR1_PS             UART1_CR1_bit.PS
#define UART1_CR1_PCEN           UART1_CR1_bit.PCEN
#define UART1_CR1_WAKE           UART1_CR1_bit.WAKE
#define UART1_CR1_M              UART1_CR1_bit.M
#define UART1_CR1_UART0          UART1_CR1_bit.UART0
#define UART1_CR1_T8             UART1_CR1_bit.T8
#define UART1_CR1_R8             UART1_CR1_bit.R8

#define UART1_CR2_SBK            UART1_CR2_bit.SBK
#define UART1_CR2_RWU            UART1_CR2_bit.RWU
#define UART1_CR2_REN            UART1_CR2_bit.REN
#define UART1_CR2_TEN            UART1_CR2_bit.TEN
#define UART1_CR2_ILIEN          UART1_CR2_bit.ILIEN
#define UART1_CR2_RIEN           UART1_CR2_bit.RIEN
#define UART1_CR2_TCIEN          UART1_CR2_bit.TCIEN
#define UART1_CR2_TIEN           UART1_CR2_bit.TIEN

#define UART1_CR3_LBCL           UART1_CR3_bit.LBCL
#define UART1_CR3_CPHA           UART1_CR3_bit.CPHA
#define UART1_CR3_CPOL           UART1_CR3_bit.CPOL
#define UART1_CR3_CKEN           UART1_CR3_bit.CKEN
#define UART1_CR3_STOP           UART1_CR3_bit.STOP
#define UART1_CR3_LINEN          UART1_CR3_bit.LINEN

#define UART1_CR4_ADD            UART1_CR4_bit.ADD
#define UART1_CR4_LBDF           UART1_CR4_bit.LBDF
#define UART1_CR4_LBDL           UART1_CR4_bit.LBDL
#define UART1_CR4_LBDIEN         UART1_CR4_bit.LBDIEN

#define UART1_CR5_IREN           UART1_CR5_bit.IREN
#define UART1_CR5_IRLP           UART1_CR5_bit.IRLP
#define UART1_CR5_HDSEL          UART1_CR5_bit.HDSEL
#define UART1_CR5_NACK           UART1_CR5_bit.NACK
#define UART1_CR5_SCEN           UART1_CR5_bit.SCEN

#endif

/*-------------------------------------------------------------------------
 *      UART1 bit masks
 *-----------------------------------------------------------------------*/
#define MASK_UART1_SR_PE         0x01
#define MASK_UART1_SR_FE         0x02
#define MASK_UART1_SR_NF         0x04
#define MASK_UART1_SR_OR_LHE     0x08
#define MASK_UART1_SR_IDLE       0x10
#define MASK_UART1_SR_RXNE       0x20
#define MASK_UART1_SR_TC         0x40
#define MASK_UART1_SR_TXE        0x80

#define MASK_UART1_CR1_PIEN      0x01
#define MASK_UART1_CR1_PS        0x02
#define MASK_UART1_CR1_PCEN      0x04
#define MASK_UART1_CR1_WAKE      0x08
#define MASK_UART1_CR1_M         0x10
#define MASK_UART1_CR1_UART0     0x20
#define MASK_UART1_CR1_T8        0x40
#define MASK_UART1_CR1_R8        0x80

#define MASK_UART1_CR2_SBK       0x01
#define MASK_UART1_CR2_RWU       0x02
#define MASK_UART1_CR2_REN       0x04
#define MASK_UART1_CR2_TEN       0x08
#define MASK_UART1_CR2_ILIEN     0x10
#define MASK_UART1_CR2_RIEN      0x20
#define MASK_UART1_CR2_TCIEN     0x40
#define MASK_UART1_CR2_TIEN      0x80

#define MASK_UART1_CR3_LBCL      0x01
#define MASK_UART1_CR3_CPHA      0x02
#define MASK_UART1_CR3_CPOL      0x04
#define MASK_UART1_CR3_CKEN      0x08
#define MASK_UART1_CR3_STOP      0x30
#define MASK_UART1_CR3_LINEN     0x80

#define MASK_UART1_CR4_ADD       0x0F
#define MASK_UART1_CR4_LBDF      0x10
#define MASK_UART1_CR4_LBDL      0x20
#define MASK_UART1_CR4_LBDIEN    0x40

#define MASK_UART1_CR5_IREN      0x02
#define MASK_UART1_CR5_IRLP      0x04
#define MASK_UART1_CR5_HDSEL     0x08
#define MASK_UART1_CR5_NACK      0x10
#define MASK_UART1_CR5_SCEN      0x20


/*-------------------------------------------------------------------------
 *      TIM1 register definitions
 *-----------------------------------------------------------------------*/
/* TIM1 control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CEN         : 1;
  unsigned char UDIS        : 1;
  unsigned char URS         : 1;
  unsigned char OPM         : 1;
  unsigned char DIR         : 1;
  unsigned char CMS         : 2;
  unsigned char ARPE        : 1;
} __BITS_TIM1_CR1;
#endif
__IO_REG8_BIT(TIM1_CR1,    0x5250, __READ_WRITE, __BITS_TIM1_CR1);

/* TIM1 control register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CCPG        : 1;
  unsigned char             : 1;
  unsigned char COMS        : 1;
  unsigned char             : 1;
  unsigned char MMS         : 3;
} __BITS_TIM1_CR2;
#endif
__IO_REG8_BIT(TIM1_CR2,    0x5251, __READ_WRITE, __BITS_TIM1_CR2);

/* TIM1 slave mode control register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SMS         : 3;
  unsigned char             : 1;
  unsigned char TS          : 3;
  unsigned char MSM         : 1;
} __BITS_TIM1_SMCR;
#endif
__IO_REG8_BIT(TIM1_SMCR,   0x5252, __READ_WRITE, __BITS_TIM1_SMCR);

/* TIM1 external trigger register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ETF         : 4;
  unsigned char ETPS        : 2;
  unsigned char ECE         : 1;
  unsigned char ETP         : 1;
} __BITS_TIM1_ETR;
#endif
__IO_REG8_BIT(TIM1_ETR,    0x5253, __READ_WRITE, __BITS_TIM1_ETR);

/* TIM1 interrupt enable register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIE         : 1;
  unsigned char CC1IE       : 1;
  unsigned char CC2IE       : 1;
  unsigned char CC3IE       : 1;
  unsigned char CC4IE       : 1;
  unsigned char COMIE       : 1;
  unsigned char TIE         : 1;
  unsigned char BIE         : 1;
} __BITS_TIM1_IER;
#endif
__IO_REG8_BIT(TIM1_IER,    0x5254, __READ_WRITE, __BITS_TIM1_IER);

/* TIM1 status register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIF         : 1;
  unsigned char CC1IF       : 1;
  unsigned char CC2IF       : 1;
  unsigned char CC3IF       : 1;
  unsigned char CC4IF       : 1;
  unsigned char COMIF       : 1;
  unsigned char TIF         : 1;
  unsigned char BIF         : 1;
} __BITS_TIM1_SR1;
#endif
__IO_REG8_BIT(TIM1_SR1,    0x5255, __READ_WRITE, __BITS_TIM1_SR1);

/* TIM1 status register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 1;
  unsigned char CC1OF       : 1;
  unsigned char CC2OF       : 1;
  unsigned char CC3OF       : 1;
  unsigned char CC4OF       : 1;
} __BITS_TIM1_SR2;
#endif
__IO_REG8_BIT(TIM1_SR2,    0x5256, __READ_WRITE, __BITS_TIM1_SR2);

/* TIM1 event generation register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UG          : 1;
  unsigned char CC1G        : 1;
  unsigned char CC2G        : 1;
  unsigned char CC3G        : 1;
  unsigned char CC4G        : 1;
  unsigned char COMG        : 1;
  unsigned char TG          : 1;
  unsigned char BG          : 1;
} __BITS_TIM1_EGR;
#endif
__IO_REG8_BIT(TIM1_EGR,    0x5257, __WRITE, __BITS_TIM1_EGR);

/* TIM1 capture/compare mode register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC1S        : 2;
  unsigned char OC1FE       : 1;
  unsigned char OC1PE       : 1;
  unsigned char OC1M        : 3;
  unsigned char OC1CE       : 1;
} __BITS_TIM1_CCMR1;
#endif
__IO_REG8_BIT(TIM1_CCMR1,  0x5258, __READ_WRITE, __BITS_TIM1_CCMR1);

/* TIM1 capture/compare mode register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC2S        : 2;
  unsigned char OC2FE       : 1;
  unsigned char OC2PE       : 1;
  unsigned char OC2M        : 3;
  unsigned char OC2CE       : 1;
} __BITS_TIM1_CCMR2;
#endif
__IO_REG8_BIT(TIM1_CCMR2,  0x5259, __READ_WRITE, __BITS_TIM1_CCMR2);

/* TIM1 capture/compare mode register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC3S        : 2;
  unsigned char OC3FE       : 1;
  unsigned char OC3PE       : 1;
  unsigned char OC3M        : 3;
  unsigned char OC3CE       : 1;
} __BITS_TIM1_CCMR3;
#endif
__IO_REG8_BIT(TIM1_CCMR3,  0x525A, __READ_WRITE, __BITS_TIM1_CCMR3);

/* TIM1 capture/compare mode register 4 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC4S        : 2;
  unsigned char OC4FE       : 1;
  unsigned char OC4PE       : 1;
  unsigned char OC4M        : 3;
  unsigned char OC4CE       : 1;
} __BITS_TIM1_CCMR4;
#endif
__IO_REG8_BIT(TIM1_CCMR4,  0x525B, __READ_WRITE, __BITS_TIM1_CCMR4);

/* TIM1 capture/compare enable register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC1E        : 1;
  unsigned char CC1P        : 1;
  unsigned char CC1NE       : 1;
  unsigned char CC1NP       : 1;
  unsigned char CC2E        : 1;
  unsigned char CC2P        : 1;
  unsigned char CC2NE       : 1;
  unsigned char CC2NP       : 1;
} __BITS_TIM1_CCER1;
#endif
__IO_REG8_BIT(TIM1_CCER1,  0x525C, __READ_WRITE, __BITS_TIM1_CCER1);

/* TIM1 capture/compare enable register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC3E        : 1;
  unsigned char CC3P        : 1;
  unsigned char CC3NE       : 1;
  unsigned char CC3NP       : 1;
  unsigned char CC4E        : 1;
  unsigned char CC4P        : 1;
} __BITS_TIM1_CCER2;
#endif
__IO_REG8_BIT(TIM1_CCER2,  0x525D, __READ_WRITE, __BITS_TIM1_CCER2);

/* TIM1 counter high */
__IO_REG8    (TIM1_CNTRH,  0x525E, __READ_WRITE);
/* TIM1 counter low */
__IO_REG8    (TIM1_CNTRL,  0x525F, __READ_WRITE);
/* TIM1 prescaler register high */
__IO_REG8    (TIM1_PSCRH,  0x5260, __READ_WRITE);
/* TIM1 prescaler register low */
__IO_REG8    (TIM1_PSCRL,  0x5261, __READ_WRITE);
/* TIM1 auto-reload register high */
__IO_REG8    (TIM1_ARRH,   0x5262, __READ_WRITE);
/* TIM1 auto-reload register low */
__IO_REG8    (TIM1_ARRL,   0x5263, __READ_WRITE);
/* TIM1 repetition counter register */
__IO_REG8    (TIM1_RCR,    0x5264, __READ_WRITE);
/* TIM1 capture/compare register 1 high */
__IO_REG8    (TIM1_CCR1H,  0x5265, __READ_WRITE);
/* TIM1 capture/compare register 1 low */
__IO_REG8    (TIM1_CCR1L,  0x5266, __READ_WRITE);
/* TIM1 capture/compare register 2 high */
__IO_REG8    (TIM1_CCR2H,  0x5267, __READ_WRITE);
/* TIM1 capture/compare register 2 low */
__IO_REG8    (TIM1_CCR2L,  0x5268, __READ_WRITE);
/* TIM1 capture/compare register 3 high */
__IO_REG8    (TIM1_CCR3H,  0x5269, __READ_WRITE);
/* TIM1 capture/compare register 3 low */
__IO_REG8    (TIM1_CCR3L,  0x526A, __READ_WRITE);
/* TIM1 capture/compare register 4 high */
__IO_REG8    (TIM1_CCR4H,  0x526B, __READ_WRITE);
/* TIM1 capture/compare register 4 low */
__IO_REG8    (TIM1_CCR4L,  0x526C, __READ_WRITE);
/* TIM1 break register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char LOCK        : 2;
  unsigned char OSSI        : 1;
  unsigned char OSSR        : 1;
  unsigned char BKE         : 1;
  unsigned char BKP         : 1;
  unsigned char AOE         : 1;
  unsigned char MOE         : 1;
} __BITS_TIM1_BKR;
#endif
__IO_REG8_BIT(TIM1_BKR,    0x526D, __READ_WRITE, __BITS_TIM1_BKR);

/* TIM1 dead-time register */
__IO_REG8    (TIM1_DTR,    0x526E, __READ_WRITE);
/* TIM1 output idle state register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char OIS1        : 1;
  unsigned char OIS1N       : 1;
  unsigned char OIS2        : 1;
  unsigned char OIS2N       : 1;
  unsigned char OIS3        : 1;
  unsigned char OIS3N       : 1;
  unsigned char OIS4        : 1;
} __BITS_TIM1_OISR;
#endif
__IO_REG8_BIT(TIM1_OISR,   0x526F, __READ_WRITE, __BITS_TIM1_OISR);


/*-------------------------------------------------------------------------
 *      TIM1 bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define TIM1_CR1_CEN             TIM1_CR1_bit.CEN
#define TIM1_CR1_UDIS            TIM1_CR1_bit.UDIS
#define TIM1_CR1_URS             TIM1_CR1_bit.URS
#define TIM1_CR1_OPM             TIM1_CR1_bit.OPM
#define TIM1_CR1_DIR             TIM1_CR1_bit.DIR
#define TIM1_CR1_CMS             TIM1_CR1_bit.CMS
#define TIM1_CR1_ARPE            TIM1_CR1_bit.ARPE

#define TIM1_CR2_CCPG            TIM1_CR2_bit.CCPG
#define TIM1_CR2_COMS            TIM1_CR2_bit.COMS
#define TIM1_CR2_MMS             TIM1_CR2_bit.MMS

#define TIM1_SMCR_SMS            TIM1_SMCR_bit.SMS
#define TIM1_SMCR_TS             TIM1_SMCR_bit.TS
#define TIM1_SMCR_MSM            TIM1_SMCR_bit.MSM

#define TIM1_ETR_ETF             TIM1_ETR_bit.ETF
#define TIM1_ETR_ETPS            TIM1_ETR_bit.ETPS
#define TIM1_ETR_ECE             TIM1_ETR_bit.ECE
#define TIM1_ETR_ETP             TIM1_ETR_bit.ETP

#define TIM1_IER_UIE             TIM1_IER_bit.UIE
#define TIM1_IER_CC1IE           TIM1_IER_bit.CC1IE
#define TIM1_IER_CC2IE           TIM1_IER_bit.CC2IE
#define TIM1_IER_CC3IE           TIM1_IER_bit.CC3IE
#define TIM1_IER_CC4IE           TIM1_IER_bit.CC4IE
#define TIM1_IER_COMIE           TIM1_IER_bit.COMIE
#define TIM1_IER_TIE             TIM1_IER_bit.TIE
#define TIM1_IER_BIE             TIM1_IER_bit.BIE

#define TIM1_SR1_UIF             TIM1_SR1_bit.UIF
#define TIM1_SR1_CC1IF           TIM1_SR1_bit.CC1IF
#define TIM1_SR1_CC2IF           TIM1_SR1_bit.CC2IF
#define TIM1_SR1_CC3IF           TIM1_SR1_bit.CC3IF
#define TIM1_SR1_CC4IF           TIM1_SR1_bit.CC4IF
#define TIM1_SR1_COMIF           TIM1_SR1_bit.COMIF
#define TIM1_SR1_TIF             TIM1_SR1_bit.TIF
#define TIM1_SR1_BIF             TIM1_SR1_bit.BIF

#define TIM1_SR2_CC1OF           TIM1_SR2_bit.CC1OF
#define TIM1_SR2_CC2OF           TIM1_SR2_bit.CC2OF
#define TIM1_SR2_CC3OF           TIM1_SR2_bit.CC3OF
#define TIM1_SR2_CC4OF           TIM1_SR2_bit.CC4OF

#define TIM1_EGR_UG              TIM1_EGR_bit.UG
#define TIM1_EGR_CC1G            TIM1_EGR_bit.CC1G
#define TIM1_EGR_CC2G            TIM1_EGR_bit.CC2G
#define TIM1_EGR_CC3G            TIM1_EGR_bit.CC3G
#define TIM1_EGR_CC4G            TIM1_EGR_bit.CC4G
#define TIM1_EGR_COMG            TIM1_EGR_bit.COMG
#define TIM1_EGR_TG              TIM1_EGR_bit.TG
#define TIM1_EGR_BG              TIM1_EGR_bit.BG

#define TIM1_CCMR1_CC1S          TIM1_CCMR1_bit.CC1S
#define TIM1_CCMR1_OC1FE         TIM1_CCMR1_bit.OC1FE
#define TIM1_CCMR1_OC1PE         TIM1_CCMR1_bit.OC1PE
#define TIM1_CCMR1_OC1M          TIM1_CCMR1_bit.OC1M
#define TIM1_CCMR1_OC1CE         TIM1_CCMR1_bit.OC1CE

#define TIM1_CCMR2_CC2S          TIM1_CCMR2_bit.CC2S
#define TIM1_CCMR2_OC2FE         TIM1_CCMR2_bit.OC2FE
#define TIM1_CCMR2_OC2PE         TIM1_CCMR2_bit.OC2PE
#define TIM1_CCMR2_OC2M          TIM1_CCMR2_bit.OC2M
#define TIM1_CCMR2_OC2CE         TIM1_CCMR2_bit.OC2CE

#define TIM1_CCMR3_CC3S          TIM1_CCMR3_bit.CC3S
#define TIM1_CCMR3_OC3FE         TIM1_CCMR3_bit.OC3FE
#define TIM1_CCMR3_OC3PE         TIM1_CCMR3_bit.OC3PE
#define TIM1_CCMR3_OC3M          TIM1_CCMR3_bit.OC3M
#define TIM1_CCMR3_OC3CE         TIM1_CCMR3_bit.OC3CE

#define TIM1_CCMR4_CC4S          TIM1_CCMR4_bit.CC4S
#define TIM1_CCMR4_OC4FE         TIM1_CCMR4_bit.OC4FE
#define TIM1_CCMR4_OC4PE         TIM1_CCMR4_bit.OC4PE
#define TIM1_CCMR4_OC4M          TIM1_CCMR4_bit.OC4M
#define TIM1_CCMR4_OC4CE         TIM1_CCMR4_bit.OC4CE

#define TIM1_CCER1_CC1E          TIM1_CCER1_bit.CC1E
#define TIM1_CCER1_CC1P          TIM1_CCER1_bit.CC1P
#define TIM1_CCER1_CC1NE         TIM1_CCER1_bit.CC1NE
#define TIM1_CCER1_CC1NP         TIM1_CCER1_bit.CC1NP
#define TIM1_CCER1_CC2E          TIM1_CCER1_bit.CC2E
#define TIM1_CCER1_CC2P          TIM1_CCER1_bit.CC2P
#define TIM1_CCER1_CC2NE         TIM1_CCER1_bit.CC2NE
#define TIM1_CCER1_CC2NP         TIM1_CCER1_bit.CC2NP

#define TIM1_CCER2_CC3E          TIM1_CCER2_bit.CC3E
#define TIM1_CCER2_CC3P          TIM1_CCER2_bit.CC3P
#define TIM1_CCER2_CC3NE         TIM1_CCER2_bit.CC3NE
#define TIM1_CCER2_CC3NP         TIM1_CCER2_bit.CC3NP
#define TIM1_CCER2_CC4E          TIM1_CCER2_bit.CC4E
#define TIM1_CCER2_CC4P          TIM1_CCER2_bit.CC4P

#define TIM1_BKR_LOCK            TIM1_BKR_bit.LOCK
#define TIM1_BKR_OSSI            TIM1_BKR_bit.OSSI
#define TIM1_BKR_OSSR            TIM1_BKR_bit.OSSR
#define TIM1_BKR_BKE             TIM1_BKR_bit.BKE
#define TIM1_BKR_BKP             TIM1_BKR_bit.BKP
#define TIM1_BKR_AOE             TIM1_BKR_bit.AOE
#define TIM1_BKR_MOE             TIM1_BKR_bit.MOE

#define TIM1_OISR_OIS1           TIM1_OISR_bit.OIS1
#define TIM1_OISR_OIS1N          TIM1_OISR_bit.OIS1N
#define TIM1_OISR_OIS2           TIM1_OISR_bit.OIS2
#define TIM1_OISR_OIS2N          TIM1_OISR_bit.OIS2N
#define TIM1_OISR_OIS3           TIM1_OISR_bit.OIS3
#define TIM1_OISR_OIS3N          TIM1_OISR_bit.OIS3N
#define TIM1_OISR_OIS4           TIM1_OISR_bit.OIS4

#endif

/*-------------------------------------------------------------------------
 *      TIM1 bit masks
 *-----------------------------------------------------------------------*/
#define MASK_TIM1_CR1_CEN        0x01
#define MASK_TIM1_CR1_UDIS       0x02
#define MASK_TIM1_CR1_URS        0x04
#define MASK_TIM1_CR1_OPM        0x08
#define MASK_TIM1_CR1_DIR        0x10
#define MASK_TIM1_CR1_CMS        0x60
#define MASK_TIM1_CR1_ARPE       0x80

#define MASK_TIM1_CR2_CCPG       0x01
#define MASK_TIM1_CR2_COMS       0x04
#define MASK_TIM1_CR2_MMS        0x70

#define MASK_TIM1_SMCR_SMS       0x07
#define MASK_TIM1_SMCR_TS        0x70
#define MASK_TIM1_SMCR_MSM       0x80

#define MASK_TIM1_ETR_ETF        0x0F
#define MASK_TIM1_ETR_ETPS       0x30
#define MASK_TIM1_ETR_ECE        0x40
#define MASK_TIM1_ETR_ETP        0x80

#define MASK_TIM1_IER_UIE        0x01
#define MASK_TIM1_IER_CC1IE      0x02
#define MASK_TIM1_IER_CC2IE      0x04
#define MASK_TIM1_IER_CC3IE      0x08
#define MASK_TIM1_IER_CC4IE      0x10
#define MASK_TIM1_IER_COMIE      0x20
#define MASK_TIM1_IER_TIE        0x40
#define MASK_TIM1_IER_BIE        0x80

#define MASK_TIM1_SR1_UIF        0x01
#define MASK_TIM1_SR1_CC1IF      0x02
#define MASK_TIM1_SR1_CC2IF      0x04
#define MASK_TIM1_SR1_CC3IF      0x08
#define MASK_TIM1_SR1_CC4IF      0x10
#define MASK_TIM1_SR1_COMIF      0x20
#define MASK_TIM1_SR1_TIF        0x40
#define MASK_TIM1_SR1_BIF        0x80

#define MASK_TIM1_SR2_CC1OF      0x02
#define MASK_TIM1_SR2_CC2OF      0x04
#define MASK_TIM1_SR2_CC3OF      0x08
#define MASK_TIM1_SR2_CC4OF      0x10

#define MASK_TIM1_EGR_UG         0x01
#define MASK_TIM1_EGR_CC1G       0x02
#define MASK_TIM1_EGR_CC2G       0x04
#define MASK_TIM1_EGR_CC3G       0x08
#define MASK_TIM1_EGR_CC4G       0x10
#define MASK_TIM1_EGR_COMG       0x20
#define MASK_TIM1_EGR_TG         0x40
#define MASK_TIM1_EGR_BG         0x80

#define MASK_TIM1_CCMR1_CC1S     0x03
#define MASK_TIM1_CCMR1_OC1FE    0x04
#define MASK_TIM1_CCMR1_OC1PE    0x08
#define MASK_TIM1_CCMR1_OC1M     0x70
#define MASK_TIM1_CCMR1_OC1CE    0x80

#define MASK_TIM1_CCMR2_CC2S     0x03
#define MASK_TIM1_CCMR2_OC2FE    0x04
#define MASK_TIM1_CCMR2_OC2PE    0x08
#define MASK_TIM1_CCMR2_OC2M     0x70
#define MASK_TIM1_CCMR2_OC2CE    0x80

#define MASK_TIM1_CCMR3_CC3S     0x03
#define MASK_TIM1_CCMR3_OC3FE    0x04
#define MASK_TIM1_CCMR3_OC3PE    0x08
#define MASK_TIM1_CCMR3_OC3M     0x70
#define MASK_TIM1_CCMR3_OC3CE    0x80

#define MASK_TIM1_CCMR4_CC4S     0x03
#define MASK_TIM1_CCMR4_OC4FE    0x04
#define MASK_TIM1_CCMR4_OC4PE    0x08
#define MASK_TIM1_CCMR4_OC4M     0x70
#define MASK_TIM1_CCMR4_OC4CE    0x80

#define MASK_TIM1_CCER1_CC1E     0x01
#define MASK_TIM1_CCER1_CC1P     0x02
#define MASK_TIM1_CCER1_CC1NE    0x04
#define MASK_TIM1_CCER1_CC1NP    0x08
#define MASK_TIM1_CCER1_CC2E     0x10
#define MASK_TIM1_CCER1_CC2P     0x20
#define MASK_TIM1_CCER1_CC2NE    0x40
#define MASK_TIM1_CCER1_CC2NP    0x80

#define MASK_TIM1_CCER2_CC3E     0x01
#define MASK_TIM1_CCER2_CC3P     0x02
#define MASK_TIM1_CCER2_CC3NE    0x04
#define MASK_TIM1_CCER2_CC3NP    0x08
#define MASK_TIM1_CCER2_CC4E     0x10
#define MASK_TIM1_CCER2_CC4P     0x20

#define MASK_TIM1_BKR_LOCK       0x03
#define MASK_TIM1_BKR_OSSI       0x04
#define MASK_TIM1_BKR_OSSR       0x08
#define MASK_TIM1_BKR_BKE        0x10
#define MASK_TIM1_BKR_BKP        0x20
#define MASK_TIM1_BKR_AOE        0x40
#define MASK_TIM1_BKR_MOE        0x80

#define MASK_TIM1_OISR_OIS1      0x01
#define MASK_TIM1_OISR_OIS1N     0x02
#define MASK_TIM1_OISR_OIS2      0x04
#define MASK_TIM1_OISR_OIS2N     0x08
#define MASK_TIM1_OISR_OIS3      0x10
#define MASK_TIM1_OISR_OIS3N     0x20
#define MASK_TIM1_OISR_OIS4      0x40


/*-------------------------------------------------------------------------
 *      TIM2 register definitions
 *-----------------------------------------------------------------------*/
/* TIM2 control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CEN         : 1;
  unsigned char UDIS        : 1;
  unsigned char URS         : 1;
  unsigned char OPM         : 1;
  unsigned char             : 3;
  unsigned char ARPE        : 1;
} __BITS_TIM2_CR1;
#endif
__IO_REG8_BIT(TIM2_CR1,    0x5300, __READ_WRITE, __BITS_TIM2_CR1);

/* TIM2 Interrupt enable register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIE         : 1;
  unsigned char CC1IE       : 1;
  unsigned char CC2IE       : 1;
  unsigned char CC3IE       : 1;
  unsigned char             : 2;
  unsigned char TIE         : 1;
} __BITS_TIM2_IER;
#endif
__IO_REG8_BIT(TIM2_IER,    0x5303, __READ_WRITE, __BITS_TIM2_IER);

/* TIM2 status register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIF         : 1;
  unsigned char CC1IF       : 1;
  unsigned char CC2IF       : 1;
  unsigned char CC3IF       : 1;
  unsigned char             : 2;
  unsigned char TIF         : 1;
} __BITS_TIM2_SR1;
#endif
__IO_REG8_BIT(TIM2_SR1,    0x5304, __READ_WRITE, __BITS_TIM2_SR1);

/* TIM2 status register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 1;
  unsigned char CC1OF       : 1;
  unsigned char CC2OF       : 1;
  unsigned char CC3OF       : 1;
} __BITS_TIM2_SR2;
#endif
__IO_REG8_BIT(TIM2_SR2,    0x5305, __READ_WRITE, __BITS_TIM2_SR2);

/* TIM2 event generation register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UG          : 1;
  unsigned char CC1G        : 1;
  unsigned char CC2G        : 1;
  unsigned char CC3G        : 1;
  unsigned char             : 2;
  unsigned char TG          : 1;
} __BITS_TIM2_EGR;
#endif
__IO_REG8_BIT(TIM2_EGR,    0x5306, __WRITE, __BITS_TIM2_EGR);

/* TIM2 capture/compare mode register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC1S        : 2;
  unsigned char             : 1;
  unsigned char OC1PE       : 1;
  unsigned char OC1M        : 3;
} __BITS_TIM2_CCMR1;
#endif
__IO_REG8_BIT(TIM2_CCMR1,  0x5307, __READ_WRITE, __BITS_TIM2_CCMR1);

/* TIM2 capture/compare mode register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC2S        : 2;
  unsigned char             : 1;
  unsigned char OC2PE       : 1;
  unsigned char OC2M        : 3;
} __BITS_TIM2_CCMR2;
#endif
__IO_REG8_BIT(TIM2_CCMR2,  0x5308, __READ_WRITE, __BITS_TIM2_CCMR2);

/* TIM2 capture/compare mode register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC3S        : 2;
  unsigned char             : 1;
  unsigned char OC3PE       : 1;
  unsigned char OC3M        : 3;
} __BITS_TIM2_CCMR3;
#endif
__IO_REG8_BIT(TIM2_CCMR3,  0x5309, __READ_WRITE, __BITS_TIM2_CCMR3);

/* TIM2 capture/compare enable register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC1E        : 1;
  unsigned char CC1P        : 1;
  unsigned char             : 2;
  unsigned char CC2E        : 1;
  unsigned char CC2P        : 1;
} __BITS_TIM2_CCER1;
#endif
__IO_REG8_BIT(TIM2_CCER1,  0x530A, __READ_WRITE, __BITS_TIM2_CCER1);

/* TIM2 capture/compare enable register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CC3E        : 1;
  unsigned char CC3P        : 1;
} __BITS_TIM2_CCER2;
#endif
__IO_REG8_BIT(TIM2_CCER2,  0x530B, __READ_WRITE, __BITS_TIM2_CCER2);

/* TIM2 counter high */
__IO_REG8    (TIM2_CNTRH,  0x530C, __READ_WRITE);
/* TIM2 counter low */
__IO_REG8    (TIM2_CNTRL,  0x530D, __READ_WRITE);
/* TIM2 prescaler register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PSC         : 4;
} __BITS_TIM2_PSCR;
#endif
__IO_REG8_BIT(TIM2_PSCR,   0x530E, __READ_WRITE, __BITS_TIM2_PSCR);

/* TIM2 auto-reload register high */
__IO_REG8    (TIM2_ARRH,   0x530F, __READ_WRITE);
/* TIM2 auto-reload register low */
__IO_REG8    (TIM2_ARRL,   0x5310, __READ_WRITE);
/* TIM2 capture/compare register 1 high */
__IO_REG8    (TIM2_CCR1H,  0x5311, __READ_WRITE);
/* TIM2 capture/compare register 1 low */
__IO_REG8    (TIM2_CCR1L,  0x5312, __READ_WRITE);
/* TIM2 capture/compare reg */
__IO_REG8    (TIM2_CCR2H,  0x5313, __READ_WRITE);
/* TIM2 capture/compare register 2 low */
__IO_REG8    (TIM2_CCR2L,  0x5314, __READ_WRITE);
/* TIM2 capture/compare register 3 high */
__IO_REG8    (TIM2_CCR3H,  0x5315, __READ_WRITE);
/* TIM2 capture/compare register 3 low */
__IO_REG8    (TIM2_CCR3L,  0x5316, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      TIM2 bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define TIM2_CR1_CEN             TIM2_CR1_bit.CEN
#define TIM2_CR1_UDIS            TIM2_CR1_bit.UDIS
#define TIM2_CR1_URS             TIM2_CR1_bit.URS
#define TIM2_CR1_OPM             TIM2_CR1_bit.OPM
#define TIM2_CR1_ARPE            TIM2_CR1_bit.ARPE

#define TIM2_IER_UIE             TIM2_IER_bit.UIE
#define TIM2_IER_CC1IE           TIM2_IER_bit.CC1IE
#define TIM2_IER_CC2IE           TIM2_IER_bit.CC2IE
#define TIM2_IER_CC3IE           TIM2_IER_bit.CC3IE
#define TIM2_IER_TIE             TIM2_IER_bit.TIE

#define TIM2_SR1_UIF             TIM2_SR1_bit.UIF
#define TIM2_SR1_CC1IF           TIM2_SR1_bit.CC1IF
#define TIM2_SR1_CC2IF           TIM2_SR1_bit.CC2IF
#define TIM2_SR1_CC3IF           TIM2_SR1_bit.CC3IF
#define TIM2_SR1_TIF             TIM2_SR1_bit.TIF

#define TIM2_SR2_CC1OF           TIM2_SR2_bit.CC1OF
#define TIM2_SR2_CC2OF           TIM2_SR2_bit.CC2OF
#define TIM2_SR2_CC3OF           TIM2_SR2_bit.CC3OF

#define TIM2_EGR_UG              TIM2_EGR_bit.UG
#define TIM2_EGR_CC1G            TIM2_EGR_bit.CC1G
#define TIM2_EGR_CC2G            TIM2_EGR_bit.CC2G
#define TIM2_EGR_CC3G            TIM2_EGR_bit.CC3G
#define TIM2_EGR_TG              TIM2_EGR_bit.TG

#define TIM2_CCMR1_CC1S          TIM2_CCMR1_bit.CC1S
#define TIM2_CCMR1_OC1PE         TIM2_CCMR1_bit.OC1PE
#define TIM2_CCMR1_OC1M          TIM2_CCMR1_bit.OC1M

#define TIM2_CCMR2_CC2S          TIM2_CCMR2_bit.CC2S
#define TIM2_CCMR2_OC2PE         TIM2_CCMR2_bit.OC2PE
#define TIM2_CCMR2_OC2M          TIM2_CCMR2_bit.OC2M

#define TIM2_CCMR3_CC3S          TIM2_CCMR3_bit.CC3S
#define TIM2_CCMR3_OC3PE         TIM2_CCMR3_bit.OC3PE
#define TIM2_CCMR3_OC3M          TIM2_CCMR3_bit.OC3M

#define TIM2_CCER1_CC1E          TIM2_CCER1_bit.CC1E
#define TIM2_CCER1_CC1P          TIM2_CCER1_bit.CC1P
#define TIM2_CCER1_CC2E          TIM2_CCER1_bit.CC2E
#define TIM2_CCER1_CC2P          TIM2_CCER1_bit.CC2P

#define TIM2_CCER2_CC3E          TIM2_CCER2_bit.CC3E
#define TIM2_CCER2_CC3P          TIM2_CCER2_bit.CC3P

#define TIM2_PSCR_PSC            TIM2_PSCR_bit.PSC

#endif

/*-------------------------------------------------------------------------
 *      TIM2 bit masks
 *-----------------------------------------------------------------------*/
#define MASK_TIM2_CR1_CEN        0x01
#define MASK_TIM2_CR1_UDIS       0x02
#define MASK_TIM2_CR1_URS        0x04
#define MASK_TIM2_CR1_OPM        0x08
#define MASK_TIM2_CR1_ARPE       0x80

#define MASK_TIM2_IER_UIE        0x01
#define MASK_TIM2_IER_CC1IE      0x02
#define MASK_TIM2_IER_CC2IE      0x04
#define MASK_TIM2_IER_CC3IE      0x08
#define MASK_TIM2_IER_TIE        0x40

#define MASK_TIM2_SR1_UIF        0x01
#define MASK_TIM2_SR1_CC1IF      0x02
#define MASK_TIM2_SR1_CC2IF      0x04
#define MASK_TIM2_SR1_CC3IF      0x08
#define MASK_TIM2_SR1_TIF        0x40

#define MASK_TIM2_SR2_CC1OF      0x02
#define MASK_TIM2_SR2_CC2OF      0x04
#define MASK_TIM2_SR2_CC3OF      0x08

#define MASK_TIM2_EGR_UG         0x01
#define MASK_TIM2_EGR_CC1G       0x02
#define MASK_TIM2_EGR_CC2G       0x04
#define MASK_TIM2_EGR_CC3G       0x08
#define MASK_TIM2_EGR_TG         0x40

#define MASK_TIM2_CCMR1_CC1S     0x03
#define MASK_TIM2_CCMR1_OC1PE    0x08
#define MASK_TIM2_CCMR1_OC1M     0x70

#define MASK_TIM2_CCMR2_CC2S     0x03
#define MASK_TIM2_CCMR2_OC2PE    0x08
#define MASK_TIM2_CCMR2_OC2M     0x70

#define MASK_TIM2_CCMR3_CC3S     0x03
#define MASK_TIM2_CCMR3_OC3PE    0x08
#define MASK_TIM2_CCMR3_OC3M     0x70

#define MASK_TIM2_CCER1_CC1E     0x01
#define MASK_TIM2_CCER1_CC1P     0x02
#define MASK_TIM2_CCER1_CC2E     0x10
#define MASK_TIM2_CCER1_CC2P     0x20

#define MASK_TIM2_CCER2_CC3E     0x01
#define MASK_TIM2_CCER2_CC3P     0x02

#define MASK_TIM2_PSCR_PSC       0x0F


/*-------------------------------------------------------------------------
 *      TIM4 register definitions
 *-----------------------------------------------------------------------*/
/* TIM4 control register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CEN         : 1;
  unsigned char UDIS        : 1;
  unsigned char URS         : 1;
  unsigned char OPM         : 1;
  unsigned char             : 3;
  unsigned char ARPE        : 1;
} __BITS_TIM4_CR1;
#endif
__IO_REG8_BIT(TIM4_CR1,    0x5340, __READ_WRITE, __BITS_TIM4_CR1);

/* TIM4 interrupt enable register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIE         : 1;
  unsigned char             : 5;
  unsigned char TIE         : 1;
} __BITS_TIM4_IER;
#endif
__IO_REG8_BIT(TIM4_IER,    0x5343, __READ_WRITE, __BITS_TIM4_IER);

/* TIM4 status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UIF         : 1;
  unsigned char             : 5;
  unsigned char TIF         : 1;
} __BITS_TIM4_SR;
#endif
__IO_REG8_BIT(TIM4_SR,     0x5344, __READ_WRITE, __BITS_TIM4_SR);

/* TIM4 event generation register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char UG          : 1;
  unsigned char             : 5;
  unsigned char TG          : 1;
} __BITS_TIM4_EGR;
#endif
__IO_REG8_BIT(TIM4_EGR,    0x5345, __WRITE, __BITS_TIM4_EGR);

/* TIM4 counter */
__IO_REG8    (TIM4_CNTR,   0x5346, __READ_WRITE);
/* TIM4 prescaler register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char PSC         : 3;
} __BITS_TIM4_PSCR;
#endif
__IO_REG8_BIT(TIM4_PSCR,   0x5347, __READ_WRITE, __BITS_TIM4_PSCR);

/* TIM4 auto-reload register */
__IO_REG8    (TIM4_ARR,    0x5348, __READ_WRITE);

/*-------------------------------------------------------------------------
 *      TIM4 bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define TIM4_CR1_CEN             TIM4_CR1_bit.CEN
#define TIM4_CR1_UDIS            TIM4_CR1_bit.UDIS
#define TIM4_CR1_URS             TIM4_CR1_bit.URS
#define TIM4_CR1_OPM             TIM4_CR1_bit.OPM
#define TIM4_CR1_ARPE            TIM4_CR1_bit.ARPE

#define TIM4_IER_UIE             TIM4_IER_bit.UIE
#define TIM4_IER_TIE             TIM4_IER_bit.TIE

#define TIM4_SR_UIF              TIM4_SR_bit.UIF
#define TIM4_SR_TIF              TIM4_SR_bit.TIF

#define TIM4_EGR_UG              TIM4_EGR_bit.UG
#define TIM4_EGR_TG              TIM4_EGR_bit.TG

#define TIM4_PSCR_PSC            TIM4_PSCR_bit.PSC

#endif

/*-------------------------------------------------------------------------
 *      TIM4 bit masks
 *-----------------------------------------------------------------------*/
#define MASK_TIM4_CR1_CEN        0x01
#define MASK_TIM4_CR1_UDIS       0x02
#define MASK_TIM4_CR1_URS        0x04
#define MASK_TIM4_CR1_OPM        0x08
#define MASK_TIM4_CR1_ARPE       0x80

#define MASK_TIM4_IER_UIE        0x01
#define MASK_TIM4_IER_TIE        0x40

#define MASK_TIM4_SR_UIF         0x01
#define MASK_TIM4_SR_TIF         0x40

#define MASK_TIM4_EGR_UG         0x01
#define MASK_TIM4_EGR_TG         0x40

#define MASK_TIM4_PSCR_PSC       0x07


/*-------------------------------------------------------------------------
 *      ADC1 register definitions
 *-----------------------------------------------------------------------*/
/* ADC data buffer registers */
__IO_REG8    (ADC_DB0RH,   0x53E0, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB0RL,   0x53E1, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB1RH,   0x53E2, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB1RL,   0x53E3, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB2RH,   0x53E4, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB2RL,   0x53E5, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB3RH,   0x53E6, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB3RL,   0x53E7, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB4RH,   0x53E8, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB4RL,   0x53E9, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB5RH,   0x53EA, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB5RL,   0x53EB, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB6RH,   0x53EC, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB6RL,   0x53ED, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB7RH,   0x53EE, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB7RL,   0x53EF, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB8RH,   0x53F0, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB8RL,   0x53F1, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB9RH,   0x53F2, __READ);
/* ADC data buffer registers */
__IO_REG8    (ADC_DB9RL,   0x53F3, __READ);
/* ADC control/status register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char CH          : 4;
  unsigned char AWDIE       : 1;
  unsigned char EOCIE       : 1;
  unsigned char AWD         : 1;
  unsigned char EOC         : 1;
} __BITS_ADC_CSR;
#endif
__IO_REG8_BIT(ADC_CSR,     0x5400, __READ_WRITE, __BITS_ADC_CSR);

/* ADC configuration register 1 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char ADON        : 1;
  unsigned char CONT        : 1;
  unsigned char             : 2;
  unsigned char SPSEL       : 3;
} __BITS_ADC_CR1;
#endif
__IO_REG8_BIT(ADC_CR1,     0x5401, __READ_WRITE, __BITS_ADC_CR1);

/* ADC configuration register 2 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 1;
  unsigned char SCAN        : 1;
  unsigned char             : 1;
  unsigned char ALIGN       : 1;
  unsigned char EXTSEL      : 2;
  unsigned char EXTTRIG     : 1;
} __BITS_ADC_CR2;
#endif
__IO_REG8_BIT(ADC_CR2,     0x5402, __READ_WRITE, __BITS_ADC_CR2);

/* ADC configuration register 3 */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char             : 6;
  unsigned char OVR         : 1;
  unsigned char DBUF        : 1;
} __BITS_ADC_CR3;
#endif
__IO_REG8_BIT(ADC_CR3,     0x5403, __READ_WRITE, __BITS_ADC_CR3);

/* ADC data register high */
__IO_REG8    (ADC_DRH,     0x5404, __READ);
/* ADC data register low */
__IO_REG8    (ADC_DRL,     0x5405, __READ);
/* ADC Schmitt trigger disable register high */
__IO_REG8    (ADC_TDRH,    0x5406, __READ_WRITE);
/* ADC Schmitt trigger disable register low */
__IO_REG8    (ADC_TDRL,    0x5407, __READ_WRITE);
/* ADC high threshold register high */
__IO_REG8    (ADC_HTRH,    0x5408, __READ_WRITE);
/* ADC high threshold register low */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char HT          : 2;
} __BITS_ADC_HTRL;
#endif
__IO_REG8_BIT(ADC_HTRL,    0x5409, __READ_WRITE, __BITS_ADC_HTRL);

/* ADC low threshold register high */
__IO_REG8    (ADC_LTRH,    0x540A, __READ_WRITE);
/* ADC low threshold register low */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char LT          : 2;
} __BITS_ADC_LTRL;
#endif
__IO_REG8_BIT(ADC_LTRL,    0x540B, __READ_WRITE, __BITS_ADC_LTRL);

/* ADC analog watchdog status register high */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char AWS8        : 1;
  unsigned char AWS9        : 1;
} __BITS_ADC_AWSRH;
#endif
__IO_REG8_BIT(ADC_AWSRH,   0x540C, __READ_WRITE, __BITS_ADC_AWSRH);

/* ADC analog watchdog status register low */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char AWS0        : 1;
  unsigned char AWS1        : 1;
  unsigned char AWS2        : 1;
  unsigned char AWS3        : 1;
  unsigned char AWS4        : 1;
  unsigned char AWS5        : 1;
  unsigned char AWS6        : 1;
  unsigned char AWS7        : 1;
} __BITS_ADC_AWSRL;
#endif
__IO_REG8_BIT(ADC_AWSRL,   0x540D, __READ_WRITE, __BITS_ADC_AWSRL);

/* ADC analog watchdog control register high */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char AWEN8       : 1;
  unsigned char AWEN9       : 1;
} __BITS_ADC_AWCRH;
#endif
__IO_REG8_BIT(ADC_AWCRH,   0x540E, __READ_WRITE, __BITS_ADC_AWCRH);

/* ADC analog watchdog control register low */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char AWEN0       : 1;
  unsigned char AWEN1       : 1;
  unsigned char AWEN2       : 1;
  unsigned char AWEN3       : 1;
  unsigned char AWEN4       : 1;
  unsigned char AWEN5       : 1;
  unsigned char AWEN6       : 1;
  unsigned char AWEN7       : 1;
} __BITS_ADC_AWCRL;
#endif
__IO_REG8_BIT(ADC_AWCRL,   0x540F, __READ_WRITE, __BITS_ADC_AWCRL);


/*-------------------------------------------------------------------------
 *      ADC1 bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define ADC_CSR_CH               ADC_CSR_bit.CH
#define ADC_CSR_AWDIE            ADC_CSR_bit.AWDIE
#define ADC_CSR_EOCIE            ADC_CSR_bit.EOCIE
#define ADC_CSR_AWD              ADC_CSR_bit.AWD
#define ADC_CSR_EOC              ADC_CSR_bit.EOC

#define ADC_CR1_ADON             ADC_CR1_bit.ADON
#define ADC_CR1_CONT             ADC_CR1_bit.CONT
#define ADC_CR1_SPSEL            ADC_CR1_bit.SPSEL

#define ADC_CR2_SCAN             ADC_CR2_bit.SCAN
#define ADC_CR2_ALIGN            ADC_CR2_bit.ALIGN
#define ADC_CR2_EXTSEL           ADC_CR2_bit.EXTSEL
#define ADC_CR2_EXTTRIG          ADC_CR2_bit.EXTTRIG

#define ADC_CR3_OVR              ADC_CR3_bit.OVR
#define ADC_CR3_DBUF             ADC_CR3_bit.DBUF

#define ADC_HTRL_HT              ADC_HTRL_bit.HT

#define ADC_LTRL_LT              ADC_LTRL_bit.LT

#define ADC_AWSRH_AWS8           ADC_AWSRH_bit.AWS8
#define ADC_AWSRH_AWS9           ADC_AWSRH_bit.AWS9

#define ADC_AWSRL_AWS0           ADC_AWSRL_bit.AWS0
#define ADC_AWSRL_AWS1           ADC_AWSRL_bit.AWS1
#define ADC_AWSRL_AWS2           ADC_AWSRL_bit.AWS2
#define ADC_AWSRL_AWS3           ADC_AWSRL_bit.AWS3
#define ADC_AWSRL_AWS4           ADC_AWSRL_bit.AWS4
#define ADC_AWSRL_AWS5           ADC_AWSRL_bit.AWS5
#define ADC_AWSRL_AWS6           ADC_AWSRL_bit.AWS6
#define ADC_AWSRL_AWS7           ADC_AWSRL_bit.AWS7

#define ADC_AWCRH_AWEN8          ADC_AWCRH_bit.AWEN8
#define ADC_AWCRH_AWEN9          ADC_AWCRH_bit.AWEN9

#define ADC_AWCRL_AWEN0          ADC_AWCRL_bit.AWEN0
#define ADC_AWCRL_AWEN1          ADC_AWCRL_bit.AWEN1
#define ADC_AWCRL_AWEN2          ADC_AWCRL_bit.AWEN2
#define ADC_AWCRL_AWEN3          ADC_AWCRL_bit.AWEN3
#define ADC_AWCRL_AWEN4          ADC_AWCRL_bit.AWEN4
#define ADC_AWCRL_AWEN5          ADC_AWCRL_bit.AWEN5
#define ADC_AWCRL_AWEN6          ADC_AWCRL_bit.AWEN6
#define ADC_AWCRL_AWEN7          ADC_AWCRL_bit.AWEN7

#endif

/*-------------------------------------------------------------------------
 *      ADC1 bit masks
 *-----------------------------------------------------------------------*/
#define MASK_ADC_CSR_CH          0x0F
#define MASK_ADC_CSR_AWDIE       0x10
#define MASK_ADC_CSR_EOCIE       0x20
#define MASK_ADC_CSR_AWD         0x40
#define MASK_ADC_CSR_EOC         0x80

#define MASK_ADC_CR1_ADON        0x01
#define MASK_ADC_CR1_CONT        0x02
#define MASK_ADC_CR1_SPSEL       0x70

#define MASK_ADC_CR2_SCAN        0x02
#define MASK_ADC_CR2_ALIGN       0x08
#define MASK_ADC_CR2_EXTSEL      0x30
#define MASK_ADC_CR2_EXTTRIG     0x40

#define MASK_ADC_CR3_OVR         0x40
#define MASK_ADC_CR3_DBUF        0x80

#define MASK_ADC_HTRL_HT         0x03

#define MASK_ADC_LTRL_LT         0x03

#define MASK_ADC_AWSRH_AWS8      0x01
#define MASK_ADC_AWSRH_AWS9      0x02

#define MASK_ADC_AWSRL_AWS0      0x01
#define MASK_ADC_AWSRL_AWS1      0x02
#define MASK_ADC_AWSRL_AWS2      0x04
#define MASK_ADC_AWSRL_AWS3      0x08
#define MASK_ADC_AWSRL_AWS4      0x10
#define MASK_ADC_AWSRL_AWS5      0x20
#define MASK_ADC_AWSRL_AWS6      0x40
#define MASK_ADC_AWSRL_AWS7      0x80

#define MASK_ADC_AWCRH_AWEN8     0x01
#define MASK_ADC_AWCRH_AWEN9     0x02

#define MASK_ADC_AWCRL_AWEN0     0x01
#define MASK_ADC_AWCRL_AWEN1     0x02
#define MASK_ADC_AWCRL_AWEN2     0x04
#define MASK_ADC_AWCRL_AWEN3     0x08
#define MASK_ADC_AWCRL_AWEN4     0x10
#define MASK_ADC_AWCRL_AWEN5     0x20
#define MASK_ADC_AWCRL_AWEN6     0x40
#define MASK_ADC_AWCRL_AWEN7     0x80


/*-------------------------------------------------------------------------
 *      CPU register definitions
 *-----------------------------------------------------------------------*/
/* Accumulator */
__IO_REG8    (CPU_A,       0x7F00, __READ_WRITE);
/* Program counter extended */
__IO_REG8    (CPU_PCE,     0x7F01, __READ_WRITE);
/* Program counter high */
__IO_REG8    (CPU_PCH,     0x7F02, __READ_WRITE);
/* Program counter low */
__IO_REG8    (CPU_PCL,     0x7F03, __READ_WRITE);
/* X index register high */
__IO_REG8    (CPU_XH,      0x7F04, __READ_WRITE);
/* X index register low */
__IO_REG8    (CPU_XL,      0x7F05, __READ_WRITE);
/* Y index register high */
__IO_REG8    (CPU_YH,      0x7F06, __READ_WRITE);
/* Y index register low */
__IO_REG8    (CPU_YL,      0x7F07, __READ_WRITE);
/* Stack pointer high */
__IO_REG8    (CPU_SPH,     0x7F08, __READ_WRITE);
/* Stack pointer low */
__IO_REG8    (CPU_SPL,     0x7F09, __READ_WRITE);
/* Condition code register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char C           : 1;
  unsigned char Z           : 1;
  unsigned char NF          : 1;
  unsigned char I0          : 1;
  unsigned char H           : 1;
  unsigned char I1          : 1;
  unsigned char             : 1;
  unsigned char V           : 1;
} __BITS_CPU_CCR;
#endif
__IO_REG8_BIT(CPU_CCR,     0x7F0A, __READ_WRITE, __BITS_CPU_CCR);

/* Global configuration register */
#ifdef __IAR_SYSTEMS_ICC__
typedef struct
{
  unsigned char SWO         : 1;
  unsigned char AL          : 1;
} __BITS_CPU_CFG_GCR;
#endif
__IO_REG8_BIT(CPU_CFG_GCR, 0x7F60, __READ_WRITE, __BITS_CPU_CFG_GCR);


/*-------------------------------------------------------------------------
 *      CPU bit fields
 *-----------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__

#define CPU_CCR_C                CPU_CCR_bit.C
#define CPU_CCR_Z                CPU_CCR_bit.Z
#define CPU_CCR_NF               CPU_CCR_bit.NF
#define CPU_CCR_I0               CPU_CCR_bit.I0
#define CPU_CCR_H                CPU_CCR_bit.H
#define CPU_CCR_I1               CPU_CCR_bit.I1
#define CPU_CCR_V                CPU_CCR_bit.V

#define CPU_CFG_GCR_SWO          CPU_CFG_GCR_bit.SWO
#define CPU_CFG_GCR_AL           CPU_CFG_GCR_bit.AL

#endif

/*-------------------------------------------------------------------------
 *      CPU bit masks
 *-----------------------------------------------------------------------*/
#define MASK_CPU_CCR_C           0x01
#define MASK_CPU_CCR_Z           0x02
#define MASK_CPU_CCR_NF          0x04
#define MASK_CPU_CCR_I0          0x08
#define MASK_CPU_CCR_H           0x10
#define MASK_CPU_CCR_I1          0x20
#define MASK_CPU_CCR_V           0x80

#define MASK_CPU_CFG_GCR_SWO     0x01
#define MASK_CPU_CFG_GCR_AL      0x02


/*-------------------------------------------------------------------------
 *      SWIM register definitions
 *-----------------------------------------------------------------------*/
/* SWIM control status register */
__IO_REG8    (SWIM_CSR,    0x7F80, __READ_WRITE);


/*-------------------------------------------------------------------------
 *      DM register definitions
 *-----------------------------------------------------------------------*/
/* DM breakpoint 1 register extended byte */
__IO_REG8    (DM_BK1RE,    0x7F90, __READ_WRITE);
/* DM breakpoint 1 register high byte */
__IO_REG8    (DM_BK1RH,    0x7F91, __READ_WRITE);
/* DM breakpoint 1 register low byte */
__IO_REG8    (DM_BK1RL,    0x7F92, __READ_WRITE);
/* DM breakpoint 2 register extended byte */
__IO_REG8    (DM_BK2RE,    0x7F93, __READ_WRITE);
/* DM breakpoint 2 register high byte */
__IO_REG8    (DM_BK2RH,    0x7F94, __READ_WRITE);
/* DM breakpoint 2 register low byte */
__IO_REG8    (DM_BK2RL,    0x7F95, __READ_WRITE);
/* DM debug module control register 1 */
__IO_REG8    (DM_CR1,      0x7F96, __READ_WRITE);
/* DM debug module control register 2 */
__IO_REG8    (DM_CR2,      0x7F97, __READ_WRITE);
/* DM debug module control/status register 1 */
__IO_REG8    (DM_CSR1,     0x7F98, __READ_WRITE);
/* DM debug module control/status register 2 */
__IO_REG8    (DM_CSR2,     0x7F99, __READ_WRITE);
/* DM enable function register */
__IO_REG8    (DM_ENFCTR,   0x7F9A, __READ_WRITE);


/*-------------------------------------------------------------------------
 *      Interrupt vector numbers
 *
 *  Note: The vector numbers listed in ST's manuals for STM8 are offset
 *        by 2 compared to the vector numbers used by EWSTM8.
 *-----------------------------------------------------------------------*/
#define AWU_vector                            3 /* IRQ No. in STM8 manual:  1 */
#define CLK_CSS_vector                        4 /* IRQ No. in STM8 manual:  2 */
#define CLK_SWITCH_vector                     4 /* IRQ No. in STM8 manual:  2 */
#define EXTI0_vector                          5 /* IRQ No. in STM8 manual:  3 */
#define EXTI1_vector                          6 /* IRQ No. in STM8 manual:  4 */
#define EXTI2_vector                          7 /* IRQ No. in STM8 manual:  5 */
#define EXTI3_vector                          8 /* IRQ No. in STM8 manual:  6 */
#define EXTI4_vector                          9 /* IRQ No. in STM8 manual:  7 */
#define SPI_CRCERR_vector                    12 /* IRQ No. in STM8 manual: 10 */
#define SPI_MODF_vector                      12 /* IRQ No. in STM8 manual: 10 */
#define SPI_OVR_vector                       12 /* IRQ No. in STM8 manual: 10 */
#define SPI_RXNE_vector                      12 /* IRQ No. in STM8 manual: 10 */
#define SPI_TXE_vector                       12 /* IRQ No. in STM8 manual: 10 */
#define SPI_WKUP_vector                      12 /* IRQ No. in STM8 manual: 10 */
#define TIM1_CAPCOM_BIF_vector               13 /* IRQ No. in STM8 manual: 11 */
#define TIM1_CAPCOM_TIF_vector               13 /* IRQ No. in STM8 manual: 11 */
#define TIM1_OVR_UIF_vector                  13 /* IRQ No. in STM8 manual: 11 */
#define TIM1_CAPCOM_CC1IF_vector             14 /* IRQ No. in STM8 manual: 12 */
#define TIM1_CAPCOM_CC2IF_vector             14 /* IRQ No. in STM8 manual: 12 */
#define TIM1_CAPCOM_CC3IF_vector             14 /* IRQ No. in STM8 manual: 12 */
#define TIM1_CAPCOM_CC4IF_vector             14 /* IRQ No. in STM8 manual: 12 */
#define TIM1_CAPCOM_COMIF_vector             14 /* IRQ No. in STM8 manual: 12 */
#define TIM2_OVR_UIF_vector                  15 /* IRQ No. in STM8 manual: 13 */
#define TIM2_CAPCOM_CC1IF_vector             16 /* IRQ No. in STM8 manual: 14 */
#define TIM2_CAPCOM_CC2IF_vector             16 /* IRQ No. in STM8 manual: 14 */
#define TIM2_CAPCOM_CC3IF_vector             16 /* IRQ No. in STM8 manual: 14 */
#define TIM2_CAPCOM_TIF_vector               16 /* IRQ No. in STM8 manual: 14 */
#define UART1_T_TC_vector                    19 /* IRQ No. in STM8 manual: 17 */
#define UART1_T_TXE_vector                   19 /* IRQ No. in STM8 manual: 17 */
#define UART1_R_IDLE_vector                  20 /* IRQ No. in STM8 manual: 18 */
#define UART1_R_LBDF_vector                  20 /* IRQ No. in STM8 manual: 18 */
#define UART1_R_OR_vector                    20 /* IRQ No. in STM8 manual: 18 */
#define UART1_R_PE_vector                    20 /* IRQ No. in STM8 manual: 18 */
#define UART1_R_RXNE_vector                  20 /* IRQ No. in STM8 manual: 18 */
#define I2C_ADD10_vector                     21 /* IRQ No. in STM8 manual: 19 */
#define I2C_ADDR_vector                      21 /* IRQ No. in STM8 manual: 19 */
#define I2C_AF_vector                        21 /* IRQ No. in STM8 manual: 19 */
#define I2C_ARLO_vector                      21 /* IRQ No. in STM8 manual: 19 */
#define I2C_BERR_vector                      21 /* IRQ No. in STM8 manual: 19 */
#define I2C_BTF_vector                       21 /* IRQ No. in STM8 manual: 19 */
#define I2C_OVR_vector                       21 /* IRQ No. in STM8 manual: 19 */
#define I2C_RXNE_vector                      21 /* IRQ No. in STM8 manual: 19 */
#define I2C_SB_vector                        21 /* IRQ No. in STM8 manual: 19 */
#define I2C_STOPF_vector                     21 /* IRQ No. in STM8 manual: 19 */
#define I2C_TXE_vector                       21 /* IRQ No. in STM8 manual: 19 */
#define I2C_WUFH_vector                      21 /* IRQ No. in STM8 manual: 19 */
#define ADC1_AWDG_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS0_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS1_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS2_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS3_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS4_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS5_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS6_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS7_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS8_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_AWS9_vector                     24 /* IRQ No. in STM8 manual: 22 */
#define ADC1_EOC_vector                      24 /* IRQ No. in STM8 manual: 22 */
#define TIM4_OVR_UIF_vector                  25 /* IRQ No. in STM8 manual: 23 */
#define FLASH_EOP_vector                     26 /* IRQ No. in STM8 manual: 24 */
#define FLASH_WR_PG_DIS_vector               26 /* IRQ No. in STM8 manual: 24 */

#ifdef __IAR_SYSTEMS_ICC__
#pragma language=restore
#endif

#endif    /* __IOSTM8S103F3_H__ */

/*----------------------------------------------
 *      End of file
 *--------------------------------------------*/
