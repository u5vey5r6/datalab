/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !(!x^!y)&&!(!(x>>31)^!(y>>31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int x1,x2,x3,x4,x5,s1,s2,s3,s4,s5;
    x1=(v>>16)>0;
    s1=x1<<4;
    v>>=s1;
    x2=(v>>8)>0;
    s2=x2<<3;
    v>>=s2;
    x3=(v>>4)>0;
    s3=x3<<2;
    v>>=s3;
    x4=(v>>2)>0;
    s4=x4<<1;
    v>>=s4;
    x5=(v>>1)>0;
    s5=x5;
    return s1|s2|s3|s4|s5;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n3=n<<3;
    int m3=m<<3;
    int xn=(x>>n3)&255;
    int xm=(x>>m3)&255;
    int mn=xn^xm;
    return x^(mn<<n3)^(mn<<m3);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned a=v>>31;
    v|=1<<31;
    unsigned rv=0,tem;
    while(v)
    {
        tem=v&1;
        v>>=1;
        rv<<=1;
        rv|=tem;
    }
    rv>>=1;
    rv<<=1;
    rv|=a;
    return rv;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int y=x>>n;
    int z=(((x>>31)<<31)>>n)<<1;
    return y^z;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int a1=(x>>31)&1;
    a1=~a1+1;
    int y=~x;
    int s1=!!(y>>16);
    s1=s1<<4;
    y>>=s1;
    int s2=!!(y>>8);
    s2=s2<<3;
    y>>=s2;
    int s3=!!(y>>4);
    s3=s3<<2;
    y>>=s3;
    int s4=!!(y>>2);
    s4=s4<<1;
    y>>=s4;
    int s5=!!(y>>1);
    y>>=s5;
    int y1=!y+((s1|s2|s3|s4|s5)^31);
    return y1&a1;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux=x;
    unsigned sign=ux&(1<<31);
    unsigned abs=ux;
    if(sign) abs=~ux+1;
    if(!abs) return 0;
    int e=31;
    while (!(abs>>e)) e--;
    unsigned exp=e+127;
    unsigned frac;
    if (e<=23)
        frac=(abs<<(23-e))&0x7fffff;
    else 
    {
        int shift=e-23;
        frac=(abs>>shift)&0x7fffff;
        unsigned rem=abs&((1<<shift)-1);
        unsigned half=1<<(shift-1);
        if (rem+(frac&1)>half) 
        {
            frac++;
            if (frac==0x800000) 
            {
                frac=0;
                exp++;
            }
        }
    }
    return sign|(exp<<23)|frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf)
{
    unsigned sign=uf&0x80000000;
    unsigned exp=(uf>>23)&0xff;
    if (exp==0xff) return uf;
    if (exp==0)
        return sign|((uf & 0x7fffffff)<<1);
    if(exp==0xfe)
        return sign|0x7f800000;
    return uf+0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign=uf2>>31;
    unsigned exp=(uf2>>20)&0x7ff;
    if(exp>=0x7ff) return 0x80000000;
    if(!exp) return 0;
    int E=exp-1023;
    if(E<0) return 0;
    if(E>30) return 0x80000000;
    unsigned mant_high = uf2 & 0xfffff;
    unsigned mant_low = uf1;
    unsigned val;
    
    if(E <= 20)
        val=(1<<E)|(mant_high>>(20-E));
    else
    {
        unsigned shift=52-E;
        val=(1<<E)|(mant_high<<(E-20))|(mant_low>>shift);
    }
    if(sign) 
    {
        if(val>0x80000000) return 0x80000000;
        return ~val+1;
    }
    else
    {
        if (val>0x7fffffff) return 0x80000000;
        return val;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x>127) return 0x7f800000;
    if (x<-149) return 0;
    if (x<-126) return 1<<(x+149);
    return (x+127)<<23;
}