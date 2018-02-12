/**
 **********************************************************************
 * Copyright (c) 1988-2018 $organization$
 *
 * This software is provided by the author and contributors ``as is'' 
 * and any express or implied warranties, including, but not limited to, 
 * the implied warranties of merchantability and fitness for a particular 
 * purpose are disclaimed. In no event shall the author or contributors 
 * be liable for any direct, indirect, incidental, special, exemplary, 
 * or consequential damages (including, but not limited to, procurement 
 * of substitute goods or services; loss of use, data, or profits; or 
 * business interruption) however caused and on any theory of liability, 
 * whether in contract, strict liability, or tort (including negligence 
 * or otherwise) arising in any way out of the use of this software, 
 * even if advised of the possibility of such damage.
 *
 *   File: mbuint.c
 *
 * Author: $author$
 *   Date: 10/19/98, 2/11/2018
 **********************************************************************
 */
#include <mbuint.h>
#include <dbprintf.h>
#include <dbdump.h>
#include <stdio.h>
#include <string.h>

const uint8 mbu_zero[MBU_EXT]={0};

unsigned mbu_bits(const uint8 *a,unsigned bytes)
{
    unsigned i,bits;
    uint8 byte;

    for (bits=bytes*8,i=0; i<bytes; i++,bits-=8)
    {
        if ((byte=a[i])!=0)
        {
            while ((byte&128)==0)
            {
                --bits;
                byte<<=1;
            }
            break;
        }
    }
    return bits;
}

unsigned mbu_get_u(const uint8 *a,unsigned bytes)
{
    unsigned size,i,n;

    if ((size=bytes)>sizeof(n))
        size=sizeof(n);
    for (n=0,i=bytes-size; i<bytes; i++)
        n=(n<<8)|a[i];
    return n;
}

void mbu_set_u(uint8 *r,unsigned a,unsigned bytes)
{
    unsigned i,n;

    if (bytes>sizeof(a))
        memset(r,0,n=bytes-sizeof(a));
    else n=0;
    for (i=bytes; i>n; a>>=8)
        r[--i]=(uint8)a;
}

void mbu_x(uint8 *r,const uint8 *a,unsigned bytes,unsigned xbytes)
{
    memset(r,0,xbytes-bytes);
    memcpy(r+xbytes-bytes,a,bytes);
}

void mbu_or(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    unsigned i;

    for (i=0; i<bytes; i++)
        r[i]=a[i]&b[i];
}

void mbu_and(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    unsigned i;

    for (i=0; i<bytes; i++)
        r[i]=a[i]&b[i];
}

void mbu_add_u8(uint8 *r,const uint8 *a,uint8 b,unsigned bytes)
{
    uint8 c;
    unsigned s;

    for (c=b; bytes>0; --bytes)
    {
        s=(unsigned)a[bytes-1]+c;
        c=(uint8)(s>>8);
        r[bytes-1]=s;
    }
}

void mbu_add(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 c;
    unsigned s;

    for (c=0; bytes>0; --bytes)
    {
        s=(unsigned)a[bytes-1]+b[bytes-1]+c;
        c=(uint8)(s>>8);
        r[bytes-1]=s;
    }
}

void mbu_add_x(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 c;
    unsigned s;

    for (c=0; bytes>0; --bytes)
    {
        s=(unsigned)a[bytes-1]+b[bytes-1]+c;
        c=(uint8)(s>>8);
        r[bytes]=s;
    }
    r[0]=c;
}

void mbu_sub_u8(uint8 *r,const uint8 *a,uint8 b,unsigned bytes)
{
    uint8 c;
    unsigned s;

    if (bytes>0)
    {
        s=(unsigned)a[bytes-1]+((uint8)~b)+1;
        c=(uint8)(s>>8);
        r[bytes-1]=s;
        for (--bytes; bytes>0; --bytes)
        {
            s=(unsigned)a[bytes-1]+255+c;
            c=(uint8)(s>>8);
            r[bytes-1]=s;
        }
    }
}

void mbu_sub(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 c;
    unsigned s;

    for (c=1; bytes>0; --bytes)
    {
        s=(unsigned)a[bytes-1]+((uint8)~b[bytes-1])+c;
        c=(uint8)(s>>8);
        r[bytes-1]=s;
    }
}

void mbu_mul_u8(uint8 *r,const uint8 *a,uint8 b,unsigned bytes)
{
    uint8 c;
    unsigned short m;

    for (c=0; bytes>0; --bytes)
    {
        m=((unsigned short)a[bytes-1])*b+c;
        c=(uint8)(m>>8);
        r[bytes-1]=(uint8)m;
    }
}

void mbu_mul(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
/*
    uint8 p[MBU_EXT];
    unsigned i,n;

    memset(r,0,bytes);
    for (i=0,n=bytes; n>0; --n, ++i)
    {
        mbu_mul_u8(p,&a[i],b[n-1],n);
        mbu_add(r,r,p,n);
    }
*/
    uint8 p[MBU_EXT];
    unsigned ia,ib,ip,iip;
    unsigned short s,c,c1;

    memset(p,0,bytes);
    for (iip=bytes,ib=bytes; ib>0; --iip)
    {
        --ib;
        for (c=0,ip=iip,ia=bytes; ip>0; )
        {
            --ia; --ip;
//            dbprintf(("r[%u]=%u*%u+%u+%u ",ip,a[ia],b[ib],p[ip],c));
            s=(((unsigned short)a[ia])*b[ib]);
            c1=(s>>8);
            s=(s&255)+p[ip]+c;
            c=(s>>8)+c1;
            p[ip]=(uint8)s;
        }
//        dbprintf(("\n"));
    }
    memcpy(r,p,bytes);
}

void mbu_mul_x(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
/*
    uint8 p[MBU_EXT];
    uint8 q[MBU_EXT];
    unsigned i,j,n;

    memset(q,0,bytes);
    memcpy(&q[bytes],a,bytes);
    memset(r,0,n=bytes+bytes);
    for (i=0,j=bytes; j>0; --n,--j,++i)
    {
        mbu_mul_u8(p,&q[i],b[j-1],n);
        mbu_add(r,r,p,n);
    }
*/
    uint8 p[MBU_EXT];
    unsigned ia,ib,ip,iip;
    unsigned short s,c,c1;

    memset(p,0,bytes+bytes);
    for (iip=bytes+bytes,ib=bytes; ib>0; --iip)
    {
        --ib;
        for (c=0,ip=iip,ia=bytes; ia>0;)
        {
            --ia; --ip;
//            dbprintf(("r[%u]=%u*%u+%u+%u ",ip,a[ia],b[ib],p[ip],c));
            s=(((unsigned short)a[ia])*b[ib]);
            c1=(s>>8);
            s=(s&255)+p[ip]+c;
            c=(s>>8)+c1;
            p[ip]=(uint8)s;
        }
        while (ip>0)
        {
            --ip;
//            dbprintf(("r[%u]=%u+%u ",ip,p[ip],c));
            s=p[ip]+c;
            c=(s>>8);
            p[ip]=(uint8)s;
        }
//        dbprintf(("\n"));
    }
    memcpy(r,p,bytes+bytes);
}

void mbu_lshift(uint8 *r,const uint8 *a,unsigned bytes,unsigned bits)
{
    uint8 c1,c2;
    unsigned i,nbytes;

    nbytes=bits/8;
    bits=bits%8;
    if (nbytes>=bytes)
        memset(r,0,bytes);
    else
    {
        for (c1=0,i=bytes-nbytes; i>0;)
        {
            c2=a[--i+nbytes]>>(8-bits);
            r[i]=(a[i+nbytes]<<bits)|c1;
            c1=c2;
        }
        memset(r+bytes-nbytes,0,bytes-nbytes);
    }
}

void mbu_rshift(uint8 *r,const uint8 *a,unsigned bytes,unsigned bits)
{
    uint8 c1,c2;
    unsigned i,nbytes;

    nbytes=bits/8;
    bits=bits%8;
    if (nbytes>=bytes)
        memset(r,0,bytes);
    else
    {
        for (c1=0,i=nbytes; i<bytes; i++)
        {
            c2=a[i-nbytes]<<(8-bits);
            r[i]=(a[i-nbytes]>>bits)|c1;
            c1=c2;
        }
        memset(r,0,nbytes);
    }
}

void mbu_lshift_8(uint8 *r,const uint8 *a,unsigned bytes)
{
    unsigned i,j;

    if (bytes>0)
    {
        for (--bytes,j=0,i=0; i<bytes; i++)
            r[i]=a[++j];
        r[bytes]=0;
    }
}

void mbu_rshift_8(uint8 *r,const uint8 *a,unsigned bytes)
{
    unsigned i,j;

    if (bytes>0)
    {
        for (--bytes,j=bytes,i=bytes; i>0; --i)
            r[i]=a[--j];
        r[0]=0;
    }
}

void mbu_lshift_1(uint8 *r,const uint8 *a,unsigned bytes)
{
    uint8 c1,c2;
    unsigned i;

    for (c1=0,i=bytes; i>0;)
    {
        c2=((a[--i]&128)!=0)&1;
        r[i]=(a[i]<<1)|c1;
        c1=c2;
    }
}

void mbu_rshift_1(uint8 *r,const uint8 *a,unsigned bytes)
{
    uint8 c1,c2;
    unsigned i;

    for (c1=0,i=0; i<bytes; i++)
    {
        c2=((a[i]&1)?128:0);
        r[i]=(a[i]>>1)|c1;
        c1=c2;
    }
}

/*
void mbu_div_rem(uint8 *q,uint8 *r,uint8 *a,uint8 *b,unsigned bytes)
{
    uint8 one,msb,quo[MBU_EXT],rem[MBU_EXT];
    unsigned i,j;

    memset(rem,0,bytes);
    for (i=0; i<bytes; i++)
    {
        one=128; msb=a[i]; quo[i]=0;
        for (j=0; j<8; j++, msb<<=1, one>>=1)
        {
            mbu_lshift_1(rem,rem,bytes);
            rem[bytes-1]|=(((msb&128)!=0)&1);
            if (memcmp(rem,b,bytes)>=0)
            {
//                dbprintf(("1"));
                quo[i]|=one;
                mbu_sub(rem,rem,b,bytes);
            }
//            else dbprintf(("0"));
        }
    }
    memcpy(q,quo,bytes);
    memcpy(r,rem,bytes);
//    dbprintf(("\n"));
}
*/

void mbu_div_rem(uint8 *q,uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 div[MBU_EXT],quo[MBU_EXT],rem[MBU_EXT];
    unsigned i,bits;

    if (memcmp(b,mbu_zero,bytes)==0)
    {
        memset(q,-1,bytes);
        memset(r,0,bytes);
        return;
    }

    if (memcmp(a,b,bytes)<0)
    {
        memset(q,0,bytes);
        memcpy(r,a,bytes);
        return;
    }

    bits=mbu_bits(a,bytes)-mbu_bits(b,bytes);
    memset(quo,0,bytes);
    memcpy(rem,a,bytes);
    mbu_lshift(div,b,bytes,bits);
    for (i=0; i<=bits; i++)
    {
        mbu_lshift_1(quo,quo,bytes);
        if (memcmp(rem,div,bytes)>=0)
        {
//            dbprintf(("1"));
            quo[bytes-1]|=1;
            mbu_sub(rem,rem,div,bytes);
        }
//        else dbprintf(("0"));
        mbu_rshift_1(div,div,bytes);
    }
    memcpy(q,quo,bytes);
    memcpy(r,rem,bytes);
//    dbprintf(("\n"));
}

/*
void mbu_div(uint8 *q,uint8 *a,uint8 *b,unsigned bytes)
{
    uint8 one,msb,quo[MBU_EXT],rem[MBU_EXT];
    unsigned i,j;

    memset(rem,0,bytes);
    for (i=0; i<bytes; i++)
    {
        one=128; msb=a[i]; quo[i]=0;
        for (j=0; j<8; j++, msb<<=1, one>>=1)
        {
            mbu_lshift_1(rem,rem,bytes);
            rem[bytes-1]|=(((msb&128)!=0)&1);
            if (memcmp(rem,b,bytes)>=0)
            {
//                dbprintf(("1"));
                quo[i]|=one;
                mbu_sub(rem,rem,b,bytes);
            }
//            else dbprintf(("0"));
        }
    }
    memcpy(q,quo,bytes);
//    dbprintf(("\n"));
}
*/

void mbu_div(uint8 *q,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 div[MBU_EXT],quo[MBU_EXT],rem[MBU_EXT];
    unsigned i,bits;

    if (memcmp(b,mbu_zero,bytes)==0)
    {
        memset(q,-1,bytes);
        return;
    }

    if (memcmp(a,b,bytes)<0)
    {
        memset(q,0,bytes);
        return;
    }

    bits=mbu_bits(a,bytes)-mbu_bits(b,bytes);
    memset(quo,0,bytes);
    memcpy(rem,a,bytes);
    mbu_lshift(div,b,bytes,bits);
    for (i=0; i<=bits; i++)
    {
        mbu_lshift_1(quo,quo,bytes);
        if (memcmp(rem,div,bytes)>=0)
        {
//            dbprintf(("1"));
            quo[bytes-1]|=1;
            mbu_sub(rem,rem,div,bytes);
        }
//        else dbprintf(("0"));
        mbu_rshift_1(div,div,bytes);
    }
    memcpy(q,quo,bytes);
//    dbprintf(("\n"));
}

/*
void mbu_mod(uint8 *r,uint8 *a,uint8 *b,unsigned bytes)
{
    uint8 msb,rem[MBU_EXT];
    unsigned i,j;

    memset(rem,0,bytes);
    for (i=0; i<bytes; i++)
    {
        for (msb=a[i], j=0; j<8; j++, msb<<=1)
        {
            mbu_lshift_1(rem,rem,bytes);
            rem[bytes-1]|=(((msb&128)!=0)&1);
            if (memcmp(rem,b,bytes)>=0)
            {
//                dbprintf(("1"));
                mbu_sub(rem,rem,b,bytes);
            }
//            else dbprint(("0"));
        }
    }
    memcpy(r,rem,bytes);
//    dbprintf(("\n"));
}
*/

void mbu_mod(uint8 *r,const uint8 *a,const uint8 *b,unsigned bytes)
{
    uint8 div[MBU_EXT],rem[MBU_EXT];
    unsigned i,bits;

    if (memcmp(b,mbu_zero,bytes)==0)
    {
        memset(r,0,bytes);
        return;
    }

    if (memcmp(a,b,bytes)<0)
    {
        memcpy(r,a,bytes);
        return;
    }

    bits=mbu_bits(a,bytes)-mbu_bits(b,bytes);
    memcpy(rem,a,bytes);
    mbu_lshift(div,b,bytes,bits);
    for (i=0; i<=bits; i++)
    {
        if (memcmp(rem,div,bytes)>=0)
        {
//            dbprintf(("1"));
            mbu_sub(rem,rem,div,bytes);
        }
//        else dbprintf(("0"));
        mbu_rshift_1(div,div,bytes);
    }
    memcpy(r,rem,bytes);
//    dbprintf(("\n"));
}

void mbu_exp2_x(uint8 *r,const uint8 *a,unsigned bytes)
{
    unsigned i,j,k,n;
    unsigned short s,c,c1;

    memset(r,0,bytes+bytes);
    for (j=bytes+bytes,n=bytes; n>0; --j)
    {
        --n; --j;
//        dbprintf(("r[%u]=%u*%u+%u  ",j,a[n],a[n],r[j]));
        s=(((unsigned short)a[n])*a[n]);
        c=(s>>8);
        s=(s&255)+r[j];
        c=c+(s>>8);
        r[j]=(uint8)s;
        for (k=j,i=n; i>0; )
        {
            --i;--k;
//            dbprintf(("r[%u]=%u*%u*2+%u+%u ",k,a[i],a[n],r[k],c));
            s=(((unsigned short)a[i])*a[n]);
            c1=(s>>7);
            s=((s<<1)&255)+r[k]+c;
            c=(s>>8)+c1;
            r[k]=(uint8)s;
        }
        while (k>0)
        {
            --k;
//            dbprintf(("r[%u]=%u+%u ",k,r[k],c));
            s=r[k]+c;
            c=(s>>8);
            r[k]=(uint8)s;
        }
//        dbprintf(("\n"));
    }
}

void mbu_mod_exp(uint8 *r,const uint8 *a,const uint8 *m,const uint8 *e,unsigned bytes,unsigned expbytes)
{
    uint8 n[MBU_EXT];
    uint8 t[MBU_EXT];
    uint8 v[MBU_EXT];
    uint8 x[MBU_EXT];
    unsigned bits,i;

    memset(n,0,bytes);
    memcpy(&n[bytes],m,bytes);
//    dbdump(n,bytes+bytes);
    memcpy(&v[bytes],a,bytes);
    if (e[expbytes-1]&1)
        memcpy(&x[bytes],a,bytes);
    else 
    {
        memset(&x[bytes],0,bytes);
        x[bytes+bytes-1]|=1;
    }
    bits=((unsigned)expbytes)<<3;
    for (i=1; i<bits; i++)
    {
//        dbprintf(("\n"));
//        dbdump(v,bytes+bytes);dbprintf(("\n"));
        mbu_exp2_x(t,&v[bytes],bytes);
//        mbu_mul_x(t,&v[bytes],&v[bytes],bytes);
//        dbdump(t,bytes+bytes);dbprintf(("\n"));
        mbu_mod(v,t,n,bytes+bytes);
//        dbdump(v,bytes+bytes);dbprintf(("\n"));
        if ((e[expbytes-(i>>3)-1]>>(i&7))&1)
        {
//            dbdump(x,bytes+bytes);dbprintf(("\n"));
            mbu_mul_x(t,&x[bytes],&v[bytes],bytes);
//            dbdump(t,bytes+bytes);dbprintf(("\n"));
            mbu_mod(x,t,n,bytes+bytes);
//            dbdump(x,bytes+bytes);dbprintf(("\n"));
        }
    }
    memcpy(r,&x[bytes],bytes);
}

void mbu_mod_mul(uint8 *r,const uint8 *a,const uint8 *b,const uint8 *n,unsigned bytes)
{
    uint8 t[MBU_EXT];
    uint8 m[MBU_EXT];

    if (a==b)
        mbu_exp2_x(t,a,bytes);
    else mbu_mul_x(t,a,b,bytes);
    mbu_x(m,n,bytes,bytes+bytes);
    mbu_mod(t,t,m,bytes+bytes);
    mbu_r(r,t,bytes+bytes,bytes);
}

void mbu_mod_exp_window(uint8 *r,const uint8 *a,const uint8 *m,const uint8 *e,unsigned bytes,unsigned expbytes)
{
    unsigned i,j,start,wstart,wend,window,wvalue;
    uint8 d[MBU_MAX],w[16][MBU_MAX];

    mbu_mod(w[0],a,m,bytes);
    mbu_mod_mul(d,w[0],w[0],m,bytes);

    if (expbytes<=3)
        window=1;
    else if (expbytes>=32)
            window=5;
    else if (expbytes>=16)
            window=4;
    else window=3;

    for (j=1<<(window-1), i=1; i<j; i++)
        mbu_mod_mul(w[i],w[i-1],d,m,bytes);

    mbu_set_u(r,1,bytes);

    start=1;
    wvalue=0;
    wstart=expbytes*8-1;
    wend=0;
    for (;;)
    {
        if (mbu_bit(e,wstart,expbytes)==0)
        {
            if (!start)
                mbu_mod_mul(r,r,r,m,bytes);

            if (wstart==0)
                break;

            wstart--;
            continue;
        }

        j=wstart;
        wvalue=1;
        wend=0;
        for (i=1; i<window; i++)
        {
            if (wstart<i)
                break;
            if (mbu_bit(e,wstart-i,expbytes))
            {
                wvalue<<=(i-wend);
                wvalue|=1;
                wend=i;
            }
        }

        j=wend+1;
        if (!start)
            for (i=0; i<j; i++)
                mbu_mod_mul(r,r,r,m,bytes);

        mbu_mod_mul(r,r,w[wvalue>>1],m,bytes);

        if (wstart<wend+1)
            break;

        wstart-=wend+1;
        wvalue=0;
        start=0;
    }
}

void mbu_mod_exp_crt(uint8 *r,const uint8 *a,const uint8 *p,const uint8 *q,const uint8 *dmp1,const uint8 *dmq1,const uint8 *iqmp,unsigned bytes)
{
    uint8 p1[MBU_EXT];
    uint8 p2[MBU_EXT];
    uint8 q2[MBU_EXT];

    /* Compute q2 = (a mod q) ^ dmq1 mod q. */

    memset(q2,0,bytes);
    memcpy(q2+bytes,q,bytes);

    mbu_mod(q2,a,q2,bytes+bytes);
    mbu_mod_exp(q2+bytes,q2+bytes,q,dmq1,bytes,bytes);

    /* Compute p2 = (a mod p) ^ dmp1 mod p. */

    memset(p1,0,bytes);
    memcpy(p1+bytes,p,bytes);

    mbu_mod(p2,a,p1,bytes+bytes);
    mbu_mod_exp(p2,p2+bytes,p,dmp1,bytes,bytes);

    /* Compute p2 = ((p2 - q2) mod p) * iqmp mod p. */

    if (memcmp(p2,q2+bytes,bytes)<0)
    {
        mbu_sub(p2,q2+bytes,p2,bytes);
        mbu_mul_x(p2,p2,iqmp,bytes);
        mbu_mod(p2,p2,p1,bytes+bytes);
        mbu_sub(p2,p,p2+bytes,bytes);
    }
    else
    {
        mbu_sub(p2,p2,q2+bytes,bytes);
        mbu_mul_x(p2,p2,iqmp,bytes);
        mbu_mod(p2,p2,p1,bytes+bytes);
    }

    /* Compute r = q2 + q * p2. */

    mbu_mul_x(r,q,p2,bytes);
    mbu_add(r,r,q2,bytes+bytes);
}

void mbu_mod_inverse(uint8 *r,const uint8 *a,const uint8 *n,unsigned bytes)
{
    uint8 a1[MBU_EXT],b1[MBU_EXT],x1[MBU_EXT],y1[MBU_EXT],m1[MBU_EXT],d1[MBU_EXT];
    uint8 *A,*B,*X,*Y,*M,*D,*T;
    int negative;

    memcpy(A=a1,a,bytes);
    memcpy(B=b1,n,bytes);
    memset(X=x1,0,bytes);
    memset(Y=y1,0,bytes-1);
    Y[bytes-1]=1;
    M=m1;
    D=d1;
    negative=0;

    while (memcmp(B,mbu_zero,bytes))
    {
        mbu_div_rem(D,M,A,B,bytes);
        T=A;
        A=B;
        B=M;
        mbu_mul(T,D,X,bytes);
        mbu_add(T,T,Y,bytes);
        M=Y;
        Y=X;
        X=T;
        negative=!negative;
    }

    if ((A[bytes-1]!=1)||memcmp(A,mbu_zero,bytes-1))
    {
        /* no inverse modulus
         */
        memset(r,0,bytes);
    }
    else 
    {
        if (negative)
            mbu_sub(Y,n,Y,bytes);
        mbu_mod(r,Y,n,bytes);
    }
}

void mbu_init_montgomery(mbu_montgomery *mont,const uint8 *n,unsigned bytes)
{
    uint8 ri[MBU_EXT],n1[MBU_EXT];

    /* R  = 1<<(bytes*8)
     * Ri = R^-1 mod N
     * Ni = (R*Ri-1)/N
     * RR = R*R mod N
     */
    mont->nbytes=bytes;
    memcpy(mont->n,n,bytes);
    ri[0]=1;
    memset(ri+1,0,bytes+bytes);
    memset(n1,0,bytes+1);
    memcpy(n1+bytes+1,n,bytes);
    mbu_mod_inverse(ri,ri,n1+bytes,bytes+1);
    mbu_sub_u8(ri,ri,1,bytes+bytes+1);
    mbu_div(ri,ri,n1,bytes+bytes+1);
    memcpy(mont->ni,ri+bytes+1,bytes);
    ri[0]=1;
    memset(ri+1,0,bytes+bytes);
    mbu_mod(ri,ri,n1,bytes+bytes+1);
    memcpy(mont->rr,ri+bytes+1,bytes);
}

void mbu_from_montgomery(uint8 *r,const uint8 *a,mbu_montgomery *mont,unsigned bytes)
{
    uint8 t1[MBU_EXT],t2[MBU_EXT];
    unsigned xbytes,nbytes;

    xbytes=((nbytes=mont->nbytes)*2);
    memcpy(t1,a+bytes-nbytes,nbytes);
    mbu_mul(t2,t1,mont->ni,nbytes);  /* t2=((a&((1<<(nbytes*8))-1))*Ni)&((1<<(nbytes*8))-1) */
    if (bytes<=xbytes)
    {
        mbu_mul_x(t1,t2,mont->n,nbytes); /* t1=t2*N */
        memset(t2,0,xbytes-bytes);
        memcpy(t2+xbytes-bytes,a,bytes);
        mbu_add_x(t2,t2,t1,xbytes); /* t2=a+t1 */
        t1[0]=0;
        memcpy(t1+1,mont->n,nbytes);
        if (memcmp(t2,t1,nbytes+1)>=0)
            mbu_sub(t2,t2,t1,nbytes+1);
        memcpy(r,t2+1,nbytes);
    }
    else
    {
        memset(t1,0,bytes+1-xbytes);
        mbu_mul_x(t1+bytes+1-xbytes,t2,mont->n,nbytes); /* t1=t2*N */
        mbu_add_x(t2,t1+1,a,bytes); /* t2=a+t1 */
        memset(t1,0,bytes+1-xbytes);
        memcpy(t1+bytes+1-xbytes,mont->n,nbytes);
        if (memcmp(t2,t1,bytes+1-nbytes)>=0)
            mbu_sub(t2,t2,t1,bytes+1-nbytes);
        memcpy(r,t2+bytes+1-nbytes,nbytes);
    }
}

void mbu_mod_mul_montgomery(uint8 *r,const uint8 *a,const uint8 *b,mbu_montgomery *mont)
{
    uint8 t[MBU_EXT];

    if (a==b)
        mbu_exp2_x(t,a,mont->nbytes);
    else mbu_mul_x(t,a,b,mont->nbytes);
    mbu_from_montgomery(r,t,mont,mont->nbytes+mont->nbytes);
}

void mbu_mod_exp_montgomery(uint8 *r,const uint8 *a,mbu_montgomery *mont,const uint8 *e,unsigned expbytes)
{
    uint8 d[MBU_MAX];
    unsigned i,j,start,wstart,wend,window,wvalue;

    mbu_mod_mul_montgomery(mont->w[0],a,mont->rr,mont);
    mbu_mod_mul_montgomery(d,mont->w[0],mont->w[0],mont);

    if (expbytes<=3)
        window=1;
    else if (expbytes>=32)
            window=5;
    else if (expbytes>=16)
            window=4;
    else window=3;

    for (j=1<<(window-1), i=1; i<j; i++)
        mbu_mod_mul_montgomery
         (mont->w[i],mont->w[i-1],d,mont);

    mbu_from_montgomery(r,mont->rr,mont,mont->nbytes);

    start=1;
    wvalue=0;
    wstart=expbytes*8-1;
    wend=0;
    for (;;)
    {
        if (mbu_bit(e,wstart,expbytes)==0)
        {
            if (!start)
                mbu_mod_mul_montgomery(r,r,r,mont);

            if (wstart==0)
                break;

            wstart--;
            continue;
        }

        j=wstart;
        wvalue=1;
        wend=0;
        for (i=1; i<window; i++)
        {
            if (wstart<i)
                break;
            if (mbu_bit(e,wstart-i,expbytes))
            {
                wvalue<<=(i-wend);
                wvalue|=1;
                wend=i;
            }
        }

        j=wend+1;
        if (!start)
            for (i=0; i<j; i++)
                mbu_mod_mul_montgomery(r,r,r,mont);

        mbu_mod_mul_montgomery(r,r,mont->w[wvalue>>1],mont);

        if (wstart<wend+1)
            break;

        wstart-=wend+1;
        wvalue=0;
        start=0;
    }

    mbu_from_montgomery(r,r,mont,mont->nbytes);
}

void mbu_mod_exp_crt_montgomery(uint8 *r,const uint8 *a,const uint8 *p,const uint8 *q,const uint8 *dmp1,const uint8 *dmq1,const uint8 *iqmp,mbu_montgomery *montp,mbu_montgomery *montq)
{
    uint8 p1[MBU_EXT];
    uint8 p2[MBU_EXT];
    uint8 q2[MBU_EXT];
    unsigned bytes;

    /* Compute q2 = (a mod q) ^ dmq1 mod q. */

    memset(q2,0,bytes=montp->nbytes);
    memcpy(q2+bytes,q,bytes);

    mbu_mod(q2,a,q2,bytes+bytes);
    mbu_mod_exp_montgomery(q2+bytes,q2+bytes,montq,dmq1,bytes);

    /* Compute p2 = (a mod p) ^ dmp1 mod p. */

    memset(p1,0,bytes);
    memcpy(p1+bytes,p,bytes);

    mbu_mod(p2,a,p1,bytes+bytes);
    mbu_mod_exp_montgomery(p2,p2+bytes,montp,dmp1,bytes);

    /* Compute p2 = ((p2 - q2) mod p) * iqmp mod p. */

    if (memcmp(p2,q2+bytes,bytes)<0)
    {
        mbu_sub(p2,q2+bytes,p2,bytes);
        mbu_mul_x(p2,p2,iqmp,bytes);
        mbu_mod(p2,p2,p1,bytes+bytes);
        mbu_sub(p2,p,p2+bytes,bytes);
    }
    else
    {
        mbu_sub(p2,p2,q2+bytes,bytes);
        mbu_mul_x(p2,p2,iqmp,bytes);
        mbu_mod(p2,p2,p1,bytes+bytes);
    }

    /* Compute r = q2 + q * p2. */

    mbu_mul_x(r,q,p2,bytes);
    mbu_add(r,r,q2,bytes+bytes);
}
