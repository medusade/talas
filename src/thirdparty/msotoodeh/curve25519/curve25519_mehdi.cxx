/**
 **********************************************************************
 * Copyright Mehdi Sotoodeh.  All rights reserved.
 * <mehdisotoodeh@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that source code retains the
 * above copyright notice and following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *   File: curve25519_mehdi.cxx
 *
 * Author: $author$
 *   Date: 4/29/2015
 *
 * This file is used to encapsulate mehdi's curve25519 implementation,
 * and isolate it's types and definitions from collisions when used
 * with other frameworks.
 **********************************************************************
 */
#include "curve25519_mehdi.hxx"
#include "curve25519_mehdi.h"
#include "curve25519_mehdi.c"
#include "curve25519_order.c"
#include "curve25519_utils.c"

int curve25519_mehdi
(unsigned char* Q, const unsigned char* P, const unsigned char* K) {
    if ((Q) && (P) && (K)) {
        ecp_PointMultiply(Q, P, K, 32);
        return 0;
    }
    return 1;
}
