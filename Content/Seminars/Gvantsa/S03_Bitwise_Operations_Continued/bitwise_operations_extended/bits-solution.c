/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 * George Kobiashvili
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // 0 - 0; 1 - 8; 2 - 16; 3 - 24
  int bitsToShift = n << 3;
  return (x >> bitsToShift) & 0xFF;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  int bitsToClear;

/* ver 1: 9 operators
  bitsToClear = ~1 + 1;
  bitsToClear <<= n;
  bitsToClear = ~bitsToClear;
  bitsToClear = bitsToClear << (32 + ((~n) + 1));
  bitsToClear = ~bitsToClear;
*/

/* ver 2: 4 operators*/
  bitsToClear = ~(((1 << 31) >> n) << 1);

// << 32 is undefined
  //(1 << (32 - n )) -1;
//  int bitsToClear2 = (1 << (32 + ((~n) + 1))) + (~1) + 1;
  return (x >> n) & bitsToClear;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  //int bits = 0;
  //bits += x & 1;
  //x = x >> 1;
  int m1 = (0x55 << 24) + (0x55 << 16) + (0x55 << 8) + 0x55; //0x55555555
  int m2 = (0x33 << 24) + (0x33 << 16) + (0x33 << 8) + 0x33; //0x33333333
  int m4 = (0x0f << 24) + (0x0f << 16) + (0x0f << 8) + 0x0f; //0x0f0f0f0f

/*
  x  = (x & m1) + ((x >> 1) & m1);
  x  = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x  = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
  x  = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
  x  = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
  return x;
*/

//  x += ~((x >> 1) & m1) + 1;             //put count of each 2 bits into those 2 bits
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
  x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
  x += x >>  8;  //put count of each 16 bits into their lowest 8 bits
  x += x >> 16;  //put count of each 32 bits into their lowest 8 bits
  return x & 0x3f;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  //x  = (x & 0xAAAAAAAA) | ((x << 1)  & 0xAAAAAAAA);
  x |= x << 16;
  x |= x << 8;
  x |= x << 4;
  x |= x << 2;
  x |= x << 1;
  x = x >> 31;
  return x+1;

  // versia 2; 5 operatorshi
  // return ((x | (~x + 1)) >> 31) + 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift, ncheck, pcheck, minusone;
  int fx = x >> 31;

  minusone = ~0;
  shift = minusone << (n + minusone);  // 111100 (0 iqneba n-1 cali)
  pcheck = x & shift; // if pcheck == 1, does not fit;

// if negative number
  ncheck = ~x & shift; // if ncheck == 1, does not fit;
  return !((fx & ncheck) | (~fx & pcheck));

/*
  int fx = x >> 31;
  neg = (x & fx) + (((~x) + 1) & (~fx));
  */
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int r, firstbit;
  firstbit = x >> 31;
  // if there is an reminder we have to add 1
  int mask = ~0 + (1 << n); // gives mask 00011111 with n number 1s
  r = (!!(x & mask)) & firstbit; //calculate reminder
  x = x >> n;
  return x + r;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !(x >> 31) & (!!x); // if x == 0 !!x = 0, else !!x = 1
  // ვერსია 2; 4 ოპერატორი
  // return !(x >> 31) ^ (!x);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int delta, fd;
  int fx = x >> 31;
  int fy = y >> 31;
  int diff_sign = (fx & (fx ^ fy));

  int O11 = ~(1 << 31);
  x = x & O11;
  y = y & O11;
  delta = x + ((~y) + 1);
  fd = delta >> 31;
  int same_sign = ((!(fx ^ fy)) & (fd | (!(x ^ y))));

  return  !!(diff_sign | same_sign);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int s1, s2, s3, s4, s5;
  int m1, m2, m3, m4, m5;
  int minusone = ~1 + 1;
  int result = 0;
  m1 = minusone << 16;    // m1 == 11111111111111110000000000000000
  s1 = ~(!!(x & m1)) + 1; // gives 11111111 or 00000000
  result += 16 & s1;

  m2 = ((1 << 8) + minusone) << ((16 & s1) + 8);    // if s1 == 11111111 then m2 == 11111111000000000000000000000000 else m2 == 00000000000000001111111100000000
  s2 = ~(!!(x & m2)) + 1; // gives 11111111 or 00000000
  result += 8 & s2;

  m3 = ((1 << 4) + minusone) << ((16 & s1) + (8 & s2) + 4);
  s3 = ~(!!(x & m3)) + 1;
  result += 4 & s3;

  m4 = ((1 << 2) + minusone) << ((16 & s1) + (8 & s2) + (4 & s3) + 2);
  s4 = ~(!!(x & m4)) + 1;
  result += 2 & s4;

  m5 = ((1 << 1) + minusone) << ((16 & s1) + (8 & s2) + (4 & s3) + (2 & s4) + 1);
  s5 = ~(!!(x & m5)) + 1;
  result += 1 & s5;

  return result;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  int msbMask = 1 << 31;                      //10000000000000000000000000000000
  int temp = msbMask >> 8;                    //11111111100000000000000000000000
  int expMask = temp ^ msbMask;               //01111111100000000000000000000000
  int significantMask = ~temp;                //00000000011111111111111111111111

  if ((uf & expMask) == expMask)
     if (uf & significantMask)
  	return uf;

  return uf ^ msbMask;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {                   
  // es aris gasaketebeli:
  // float f = (float) x;
  // return *(unsigned int *)f;
  
  unsigned int result = 0;
  int exponent = 0;
  int mantisa = 0;
  int x_temp = x;
  int fx = x >> 31;
  int positiveX = (x & (~fx)) + (((~x) + 1) & fx);
  int lower_bound, upper_bound;
  
  if (x == 0)
    return 0;
  
  if (x < 0)
    result |= 0x80000000;
  
  while (x_temp)
  {
    exponent++;
    x_temp /= 2;
  }
  // 1 10011101 11111110000000000000000
  lower_bound = 1 << (exponent - 2);
  upper_bound = 1 << (exponent - 1);
  mantisa = (1 << 23) * ((positiveX - lower_bound) / (upper_bound - lower_bound));
  result |= (exponent + 127) << 23;
  result |= mantisa;
  return result;
  //   ----------------
  
  //                                                 1       8                     23
  //   int msbMask = 1 << 31;                      //10000000000000000000000000000000
  //   int temp = msbMask >> 8;                    //11111111100000000000000000000000
  // //  int expMask = temp ^ msbMask;               //01111111100000000000000000000000
  //   int significantMask = ~temp;                //00000000011111111111111111111111
//   unsigned result;
//   int log = 0;
//   int positiveX;
//   int round;

//   printf("x == %08x\n", x);

//   // make x positive
//   if (x) {
//     int fx = x >> 31;
//     positiveX = (x & (~fx)) + (((~x) + 1) & fx);

//     int i = 0;
//     while (i <= 31)
//     {
//       if (positiveX & (1 << i))
//     	log = i;
//       i += 1;
//     }

// //  log = 32 + ~log + 1;
//   printf ("log==%d\n", log);

//     result = x & msbMask;
//     result |= (127 + log) << 23;
//     if (log < 23)
//       result |= (positiveX << (23 + ~log + 1)) & significantMask;
//     else {
//         result |= (positiveX >> (log + ~23 + 1)) & significantMask;
// 	round = positiveX & ((1 << (log - 23 -1 )));
// 	result += !!round;
//       }
//   }
//   else
//     result = x;
//   return result;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
