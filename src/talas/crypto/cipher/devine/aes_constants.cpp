///////////////////////////////////////////////////////////////////////
/// FIPS-197 compliant AES implementation
///
/// Copyright (C) 2006-2007  Christophe Devine
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
///
/// The AES block cipher was designed by Vincent Rijmen and Joan Daemen.
///
/// http://csrc.nist.gov/encryption/aes/rijndael/Rijndael.pdf
/// http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
///
///   File: aes_constants.cpp
///
/// Author: $author$
///   Date: 4/30/2015
///
/// Christophe Devine's implementation of AES modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CIPHER_DEVINE_AES_CONSTANTS_CPP
#define _TALAS_CRYPTO_CIPHER_DEVINE_AES_CONSTANTS_CPP

#include "talas/crypto/cipher/devine/aes.hpp"

/*
 * Forward table
 */
#define FT \
\
    FV(A5,63,63,C6), FV(84,7C,7C,F8), FV(99,77,77,EE), FV(8D,7B,7B,F6), \
    FV(0D,F2,F2,FF), FV(BD,6B,6B,D6), FV(B1,6F,6F,DE), FV(54,C5,C5,91), \
    FV(50,30,30,60), FV(03,01,01,02), FV(A9,67,67,CE), FV(7D,2B,2B,56), \
    FV(19,FE,FE,E7), FV(62,D7,D7,B5), FV(E6,AB,AB,4D), FV(9A,76,76,EC), \
    FV(45,CA,CA,8F), FV(9D,82,82,1F), FV(40,C9,C9,89), FV(87,7D,7D,FA), \
    FV(15,FA,FA,EF), FV(EB,59,59,B2), FV(C9,47,47,8E), FV(0B,F0,F0,FB), \
    FV(EC,AD,AD,41), FV(67,D4,D4,B3), FV(FD,A2,A2,5F), FV(EA,AF,AF,45), \
    FV(BF,9C,9C,23), FV(F7,A4,A4,53), FV(96,72,72,E4), FV(5B,C0,C0,9B), \
    FV(C2,B7,B7,75), FV(1C,FD,FD,E1), FV(AE,93,93,3D), FV(6A,26,26,4C), \
    FV(5A,36,36,6C), FV(41,3F,3F,7E), FV(02,F7,F7,F5), FV(4F,CC,CC,83), \
    FV(5C,34,34,68), FV(F4,A5,A5,51), FV(34,E5,E5,D1), FV(08,F1,F1,F9), \
    FV(93,71,71,E2), FV(73,D8,D8,AB), FV(53,31,31,62), FV(3F,15,15,2A), \
    FV(0C,04,04,08), FV(52,C7,C7,95), FV(65,23,23,46), FV(5E,C3,C3,9D), \
    FV(28,18,18,30), FV(A1,96,96,37), FV(0F,05,05,0A), FV(B5,9A,9A,2F), \
    FV(09,07,07,0E), FV(36,12,12,24), FV(9B,80,80,1B), FV(3D,E2,E2,DF), \
    FV(26,EB,EB,CD), FV(69,27,27,4E), FV(CD,B2,B2,7F), FV(9F,75,75,EA), \
    FV(1B,09,09,12), FV(9E,83,83,1D), FV(74,2C,2C,58), FV(2E,1A,1A,34), \
    FV(2D,1B,1B,36), FV(B2,6E,6E,DC), FV(EE,5A,5A,B4), FV(FB,A0,A0,5B), \
    FV(F6,52,52,A4), FV(4D,3B,3B,76), FV(61,D6,D6,B7), FV(CE,B3,B3,7D), \
    FV(7B,29,29,52), FV(3E,E3,E3,DD), FV(71,2F,2F,5E), FV(97,84,84,13), \
    FV(F5,53,53,A6), FV(68,D1,D1,B9), FV(00,00,00,00), FV(2C,ED,ED,C1), \
    FV(60,20,20,40), FV(1F,FC,FC,E3), FV(C8,B1,B1,79), FV(ED,5B,5B,B6), \
    FV(BE,6A,6A,D4), FV(46,CB,CB,8D), FV(D9,BE,BE,67), FV(4B,39,39,72), \
    FV(DE,4A,4A,94), FV(D4,4C,4C,98), FV(E8,58,58,B0), FV(4A,CF,CF,85), \
    FV(6B,D0,D0,BB), FV(2A,EF,EF,C5), FV(E5,AA,AA,4F), FV(16,FB,FB,ED), \
    FV(C5,43,43,86), FV(D7,4D,4D,9A), FV(55,33,33,66), FV(94,85,85,11), \
    FV(CF,45,45,8A), FV(10,F9,F9,E9), FV(06,02,02,04), FV(81,7F,7F,FE), \
    FV(F0,50,50,A0), FV(44,3C,3C,78), FV(BA,9F,9F,25), FV(E3,A8,A8,4B), \
    FV(F3,51,51,A2), FV(FE,A3,A3,5D), FV(C0,40,40,80), FV(8A,8F,8F,05), \
    FV(AD,92,92,3F), FV(BC,9D,9D,21), FV(48,38,38,70), FV(04,F5,F5,F1), \
    FV(DF,BC,BC,63), FV(C1,B6,B6,77), FV(75,DA,DA,AF), FV(63,21,21,42), \
    FV(30,10,10,20), FV(1A,FF,FF,E5), FV(0E,F3,F3,FD), FV(6D,D2,D2,BF), \
    FV(4C,CD,CD,81), FV(14,0C,0C,18), FV(35,13,13,26), FV(2F,EC,EC,C3), \
    FV(E1,5F,5F,BE), FV(A2,97,97,35), FV(CC,44,44,88), FV(39,17,17,2E), \
    FV(57,C4,C4,93), FV(F2,A7,A7,55), FV(82,7E,7E,FC), FV(47,3D,3D,7A), \
    FV(AC,64,64,C8), FV(E7,5D,5D,BA), FV(2B,19,19,32), FV(95,73,73,E6), \
    FV(A0,60,60,C0), FV(98,81,81,19), FV(D1,4F,4F,9E), FV(7F,DC,DC,A3), \
    FV(66,22,22,44), FV(7E,2A,2A,54), FV(AB,90,90,3B), FV(83,88,88,0B), \
    FV(CA,46,46,8C), FV(29,EE,EE,C7), FV(D3,B8,B8,6B), FV(3C,14,14,28), \
    FV(79,DE,DE,A7), FV(E2,5E,5E,BC), FV(1D,0B,0B,16), FV(76,DB,DB,AD), \
    FV(3B,E0,E0,DB), FV(56,32,32,64), FV(4E,3A,3A,74), FV(1E,0A,0A,14), \
    FV(DB,49,49,92), FV(0A,06,06,0C), FV(6C,24,24,48), FV(E4,5C,5C,B8), \
    FV(5D,C2,C2,9F), FV(6E,D3,D3,BD), FV(EF,AC,AC,43), FV(A6,62,62,C4), \
    FV(A8,91,91,39), FV(A4,95,95,31), FV(37,E4,E4,D3), FV(8B,79,79,F2), \
    FV(32,E7,E7,D5), FV(43,C8,C8,8B), FV(59,37,37,6E), FV(B7,6D,6D,DA), \
    FV(8C,8D,8D,01), FV(64,D5,D5,B1), FV(D2,4E,4E,9C), FV(E0,A9,A9,49), \
    FV(B4,6C,6C,D8), FV(FA,56,56,AC), FV(07,F4,F4,F3), FV(25,EA,EA,CF), \
    FV(AF,65,65,CA), FV(8E,7A,7A,F4), FV(E9,AE,AE,47), FV(18,08,08,10), \
    FV(D5,BA,BA,6F), FV(88,78,78,F0), FV(6F,25,25,4A), FV(72,2E,2E,5C), \
    FV(24,1C,1C,38), FV(F1,A6,A6,57), FV(C7,B4,B4,73), FV(51,C6,C6,97), \
    FV(23,E8,E8,CB), FV(7C,DD,DD,A1), FV(9C,74,74,E8), FV(21,1F,1F,3E), \
    FV(DD,4B,4B,96), FV(DC,BD,BD,61), FV(86,8B,8B,0D), FV(85,8A,8A,0F), \
    FV(90,70,70,E0), FV(42,3E,3E,7C), FV(C4,B5,B5,71), FV(AA,66,66,CC), \
    FV(D8,48,48,90), FV(05,03,03,06), FV(01,F6,F6,F7), FV(12,0E,0E,1C), \
    FV(A3,61,61,C2), FV(5F,35,35,6A), FV(F9,57,57,AE), FV(D0,B9,B9,69), \
    FV(91,86,86,17), FV(58,C1,C1,99), FV(27,1D,1D,3A), FV(B9,9E,9E,27), \
    FV(38,E1,E1,D9), FV(13,F8,F8,EB), FV(B3,98,98,2B), FV(33,11,11,22), \
    FV(BB,69,69,D2), FV(70,D9,D9,A9), FV(89,8E,8E,07), FV(A7,94,94,33), \
    FV(B6,9B,9B,2D), FV(22,1E,1E,3C), FV(92,87,87,15), FV(20,E9,E9,C9), \
    FV(49,CE,CE,87), FV(FF,55,55,AA), FV(78,28,28,50), FV(7A,DF,DF,A5), \
    FV(8F,8C,8C,03), FV(F8,A1,A1,59), FV(80,89,89,09), FV(17,0D,0D,1A), \
    FV(DA,BF,BF,65), FV(31,E6,E6,D7), FV(C6,42,42,84), FV(B8,68,68,D0), \
    FV(C3,41,41,82), FV(B0,99,99,29), FV(77,2D,2D,5A), FV(11,0F,0F,1E), \
    FV(CB,B0,B0,7B), FV(FC,54,54,A8), FV(D6,BB,BB,6D), FV(3A,16,16,2C)

/*
 * Reverse table
 */
#define RT \
\
    RV(50,A7,F4,51), RV(53,65,41,7E), RV(C3,A4,17,1A), RV(96,5E,27,3A), \
    RV(CB,6B,AB,3B), RV(F1,45,9D,1F), RV(AB,58,FA,AC), RV(93,03,E3,4B), \
    RV(55,FA,30,20), RV(F6,6D,76,AD), RV(91,76,CC,88), RV(25,4C,02,F5), \
    RV(FC,D7,E5,4F), RV(D7,CB,2A,C5), RV(80,44,35,26), RV(8F,A3,62,B5), \
    RV(49,5A,B1,DE), RV(67,1B,BA,25), RV(98,0E,EA,45), RV(E1,C0,FE,5D), \
    RV(02,75,2F,C3), RV(12,F0,4C,81), RV(A3,97,46,8D), RV(C6,F9,D3,6B), \
    RV(E7,5F,8F,03), RV(95,9C,92,15), RV(EB,7A,6D,BF), RV(DA,59,52,95), \
    RV(2D,83,BE,D4), RV(D3,21,74,58), RV(29,69,E0,49), RV(44,C8,C9,8E), \
    RV(6A,89,C2,75), RV(78,79,8E,F4), RV(6B,3E,58,99), RV(DD,71,B9,27), \
    RV(B6,4F,E1,BE), RV(17,AD,88,F0), RV(66,AC,20,C9), RV(B4,3A,CE,7D), \
    RV(18,4A,DF,63), RV(82,31,1A,E5), RV(60,33,51,97), RV(45,7F,53,62), \
    RV(E0,77,64,B1), RV(84,AE,6B,BB), RV(1C,A0,81,FE), RV(94,2B,08,F9), \
    RV(58,68,48,70), RV(19,FD,45,8F), RV(87,6C,DE,94), RV(B7,F8,7B,52), \
    RV(23,D3,73,AB), RV(E2,02,4B,72), RV(57,8F,1F,E3), RV(2A,AB,55,66), \
    RV(07,28,EB,B2), RV(03,C2,B5,2F), RV(9A,7B,C5,86), RV(A5,08,37,D3), \
    RV(F2,87,28,30), RV(B2,A5,BF,23), RV(BA,6A,03,02), RV(5C,82,16,ED), \
    RV(2B,1C,CF,8A), RV(92,B4,79,A7), RV(F0,F2,07,F3), RV(A1,E2,69,4E), \
    RV(CD,F4,DA,65), RV(D5,BE,05,06), RV(1F,62,34,D1), RV(8A,FE,A6,C4), \
    RV(9D,53,2E,34), RV(A0,55,F3,A2), RV(32,E1,8A,05), RV(75,EB,F6,A4), \
    RV(39,EC,83,0B), RV(AA,EF,60,40), RV(06,9F,71,5E), RV(51,10,6E,BD), \
    RV(F9,8A,21,3E), RV(3D,06,DD,96), RV(AE,05,3E,DD), RV(46,BD,E6,4D), \
    RV(B5,8D,54,91), RV(05,5D,C4,71), RV(6F,D4,06,04), RV(FF,15,50,60), \
    RV(24,FB,98,19), RV(97,E9,BD,D6), RV(CC,43,40,89), RV(77,9E,D9,67), \
    RV(BD,42,E8,B0), RV(88,8B,89,07), RV(38,5B,19,E7), RV(DB,EE,C8,79), \
    RV(47,0A,7C,A1), RV(E9,0F,42,7C), RV(C9,1E,84,F8), RV(00,00,00,00), \
    RV(83,86,80,09), RV(48,ED,2B,32), RV(AC,70,11,1E), RV(4E,72,5A,6C), \
    RV(FB,FF,0E,FD), RV(56,38,85,0F), RV(1E,D5,AE,3D), RV(27,39,2D,36), \
    RV(64,D9,0F,0A), RV(21,A6,5C,68), RV(D1,54,5B,9B), RV(3A,2E,36,24), \
    RV(B1,67,0A,0C), RV(0F,E7,57,93), RV(D2,96,EE,B4), RV(9E,91,9B,1B), \
    RV(4F,C5,C0,80), RV(A2,20,DC,61), RV(69,4B,77,5A), RV(16,1A,12,1C), \
    RV(0A,BA,93,E2), RV(E5,2A,A0,C0), RV(43,E0,22,3C), RV(1D,17,1B,12), \
    RV(0B,0D,09,0E), RV(AD,C7,8B,F2), RV(B9,A8,B6,2D), RV(C8,A9,1E,14), \
    RV(85,19,F1,57), RV(4C,07,75,AF), RV(BB,DD,99,EE), RV(FD,60,7F,A3), \
    RV(9F,26,01,F7), RV(BC,F5,72,5C), RV(C5,3B,66,44), RV(34,7E,FB,5B), \
    RV(76,29,43,8B), RV(DC,C6,23,CB), RV(68,FC,ED,B6), RV(63,F1,E4,B8), \
    RV(CA,DC,31,D7), RV(10,85,63,42), RV(40,22,97,13), RV(20,11,C6,84), \
    RV(7D,24,4A,85), RV(F8,3D,BB,D2), RV(11,32,F9,AE), RV(6D,A1,29,C7), \
    RV(4B,2F,9E,1D), RV(F3,30,B2,DC), RV(EC,52,86,0D), RV(D0,E3,C1,77), \
    RV(6C,16,B3,2B), RV(99,B9,70,A9), RV(FA,48,94,11), RV(22,64,E9,47), \
    RV(C4,8C,FC,A8), RV(1A,3F,F0,A0), RV(D8,2C,7D,56), RV(EF,90,33,22), \
    RV(C7,4E,49,87), RV(C1,D1,38,D9), RV(FE,A2,CA,8C), RV(36,0B,D4,98), \
    RV(CF,81,F5,A6), RV(28,DE,7A,A5), RV(26,8E,B7,DA), RV(A4,BF,AD,3F), \
    RV(E4,9D,3A,2C), RV(0D,92,78,50), RV(9B,CC,5F,6A), RV(62,46,7E,54), \
    RV(C2,13,8D,F6), RV(E8,B8,D8,90), RV(5E,F7,39,2E), RV(F5,AF,C3,82), \
    RV(BE,80,5D,9F), RV(7C,93,D0,69), RV(A9,2D,D5,6F), RV(B3,12,25,CF), \
    RV(3B,99,AC,C8), RV(A7,7D,18,10), RV(6E,63,9C,E8), RV(7B,BB,3B,DB), \
    RV(09,78,26,CD), RV(F4,18,59,6E), RV(01,B7,9A,EC), RV(A8,9A,4F,83), \
    RV(65,6E,95,E6), RV(7E,E6,FF,AA), RV(08,CF,BC,21), RV(E6,E8,15,EF), \
    RV(D9,9B,E7,BA), RV(CE,36,6F,4A), RV(D4,09,9F,EA), RV(D6,7C,B0,29), \
    RV(AF,B2,A4,31), RV(31,23,3F,2A), RV(30,94,A5,C6), RV(C0,66,A2,35), \
    RV(37,BC,4E,74), RV(A6,CA,82,FC), RV(B0,D0,90,E0), RV(15,D8,A7,33), \
    RV(4A,98,04,F1), RV(F7,DA,EC,41), RV(0E,50,CD,7F), RV(2F,F6,91,17), \
    RV(8D,D6,4D,76), RV(4D,B0,EF,43), RV(54,4D,AA,CC), RV(DF,04,96,E4), \
    RV(E3,B5,D1,9E), RV(1B,88,6A,4C), RV(B8,1F,2C,C1), RV(7F,51,65,46), \
    RV(04,EA,5E,9D), RV(5D,35,8C,01), RV(73,74,87,FA), RV(2E,41,0B,FB), \
    RV(5A,1D,67,B3), RV(52,D2,DB,92), RV(33,56,10,E9), RV(13,47,D6,6D), \
    RV(8C,61,D7,9A), RV(7A,0C,A1,37), RV(8E,14,F8,59), RV(89,3C,13,EB), \
    RV(EE,27,A9,CE), RV(35,C9,61,B7), RV(ED,E5,1C,E1), RV(3C,B1,47,7A), \
    RV(59,DF,D2,9C), RV(3F,73,F2,55), RV(79,CE,14,18), RV(BF,37,C7,73), \
    RV(EA,CD,F7,53), RV(5B,AA,FD,5F), RV(14,6F,3D,DF), RV(86,DB,44,78), \
    RV(81,F3,AF,CA), RV(3E,C4,68,B9), RV(2C,34,24,38), RV(5F,40,A3,C2), \
    RV(72,C3,1D,16), RV(0C,25,E2,BC), RV(8B,49,3C,28), RV(41,95,0D,FF), \
    RV(71,01,A8,39), RV(DE,B3,0C,08), RV(9C,E4,B4,D8), RV(90,C1,56,64), \
    RV(61,84,CB,7B), RV(70,B6,32,D5), RV(74,5C,6C,48), RV(42,57,B8,D0)

#define AES_FROUND(X0,X1,X2,X3,Y0,Y1,Y2,Y3)     \
{                                               \
    X0 = *RK++ ^ FT0[ ( Y0       ) & 0xFF ] ^   \
                 FT1[ ( Y1 >>  8 ) & 0xFF ] ^   \
                 FT2[ ( Y2 >> 16 ) & 0xFF ] ^   \
                 FT3[ ( Y3 >> 24 ) & 0xFF ];    \
                                                \
    X1 = *RK++ ^ FT0[ ( Y1       ) & 0xFF ] ^   \
                 FT1[ ( Y2 >>  8 ) & 0xFF ] ^   \
                 FT2[ ( Y3 >> 16 ) & 0xFF ] ^   \
                 FT3[ ( Y0 >> 24 ) & 0xFF ];    \
                                                \
    X2 = *RK++ ^ FT0[ ( Y2       ) & 0xFF ] ^   \
                 FT1[ ( Y3 >>  8 ) & 0xFF ] ^   \
                 FT2[ ( Y0 >> 16 ) & 0xFF ] ^   \
                 FT3[ ( Y1 >> 24 ) & 0xFF ];    \
                                                \
    X3 = *RK++ ^ FT0[ ( Y3       ) & 0xFF ] ^   \
                 FT1[ ( Y0 >>  8 ) & 0xFF ] ^   \
                 FT2[ ( Y1 >> 16 ) & 0xFF ] ^   \
                 FT3[ ( Y2 >> 24 ) & 0xFF ];    \
}

#define AES_RROUND(X0,X1,X2,X3,Y0,Y1,Y2,Y3)     \
{                                               \
    X0 = *RK++ ^ RT0[ ( Y0       ) & 0xFF ] ^   \
                 RT1[ ( Y3 >>  8 ) & 0xFF ] ^   \
                 RT2[ ( Y2 >> 16 ) & 0xFF ] ^   \
                 RT3[ ( Y1 >> 24 ) & 0xFF ];    \
                                                \
    X1 = *RK++ ^ RT0[ ( Y1       ) & 0xFF ] ^   \
                 RT1[ ( Y0 >>  8 ) & 0xFF ] ^   \
                 RT2[ ( Y3 >> 16 ) & 0xFF ] ^   \
                 RT3[ ( Y2 >> 24 ) & 0xFF ];    \
                                                \
    X2 = *RK++ ^ RT0[ ( Y2       ) & 0xFF ] ^   \
                 RT1[ ( Y1 >>  8 ) & 0xFF ] ^   \
                 RT2[ ( Y0 >> 16 ) & 0xFF ] ^   \
                 RT3[ ( Y3 >> 24 ) & 0xFF ];    \
                                                \
    X3 = *RK++ ^ RT0[ ( Y3       ) & 0xFF ] ^   \
                 RT1[ ( Y2 >>  8 ) & 0xFF ] ^   \
                 RT2[ ( Y1 >> 16 ) & 0xFF ] ^   \
                 RT3[ ( Y0 >> 24 ) & 0xFF ];    \
}

/*
 * Forward S-box
 */
static const uint8_t FSb[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

/*
 * Forward tables
 */
#define FV(a,b,c,d) 0x##a##b##c##d
static const uint32_t FT0[256] = { FT };
#undef FV

#define FV(a,b,c,d) 0x##b##c##d##a
static const uint32_t FT1[256] = { FT };
#undef FV

#define FV(a,b,c,d) 0x##c##d##a##b
static const uint32_t FT2[256] = { FT };
#undef FV

#define FV(a,b,c,d) 0x##d##a##b##c
static const uint32_t FT3[256] = { FT };

/*
 * Reverse S-box
 */
static const uint8_t RSb[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

/*
 * Reverse tables
 */
#define RV(a,b,c,d) 0x##a##b##c##d
static const uint32_t RT0[256] = { RT };
#undef RV

#define RV(a,b,c,d) 0x##b##c##d##a
static const uint32_t RT1[256] = { RT };
#undef RV

#define RV(a,b,c,d) 0x##c##d##a##b
static const uint32_t RT2[256] = { RT };
#undef RV

#define RV(a,b,c,d) 0x##d##a##b##c
static const uint32_t RT3[256] = { RT };

/*
 * Round constants
 */
static const uint32_t RCON[10] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x0000001B, 0x00000036
};

namespace talas {
namespace crypto {
namespace cipher {
namespace devine {

enum {
    ERROR_KEY_SIZE = error_invalid_parameter_size,
    ERROR_KEY_SIZE_UNDER = error_invalid_parameter_size,
    ERROR_KEY_SIZE_OVER = error_invalid_parameter_size,

    ERROR_IV_SIZE = error_invalid_parameter_size,
    ERROR_IV_SIZE_UNDER = error_invalid_parameter_size,
    ERROR_IV_SIZE_OVER = error_invalid_parameter_size,

    ERROR_OUT_SIZE = error_invalid_parameter_size,
    ERROR_OUT_SIZE_UNDER = error_invalid_parameter_size,
    ERROR_OUT_SIZE_OVER = error_invalid_parameter_size
};
class Bytes: public bytes_t {
public:
    static inline tLength Set(void* b, tWhat to, tLength length) {
        return set((tWhat*)b, to, length);
    }
    static inline tLength Copy(void* to, const void* from, tLength length) {
        return copy((tWhat*)to, (const tWhat*)from, length);
    }
    static inline tLength Count(const void* b) {
        return count((const tWhat*)b);
    }
};

} // namespace devine 
} // namespace cipher 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CIPHER_DEVINE_AES_CONSTANTS_CPP 
