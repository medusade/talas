///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: rsa_test_keys_pem.cpp
///
/// Author: $author$
///   Date: 5/13/2015
///////////////////////////////////////////////////////////////////////
#include "talas/app/console/talas/rsa_test_keys_pem.hpp"

namespace talas {
namespace app {
namespace console {
namespace talas {

/// -----BEGIN RSA PUBLIC KEY-----
/// BASE64 ENCODED DATA (RSAPublicKey)
/// -----END RSA PUBLIC KEY-----
///
/// RSAPublicKey ::= SEQUENCE {
///     modulus           INTEGER,  -- n
///     publicExponent    INTEGER   -- e
/// }
const char rsa_public_pem[] = \
"-----BEGIN RSA PUBLIC KEY-----\n"
"-----END RSA PUBLIC KEY-----\n";

/// -----BEGIN RSA PRIVATE KEY-----
/// BASE64 ENCODED DATA (RSAPrivateKey)
/// -----END RSA PRIVATE KEY-----
///
/// RSAPrivateKey ::= SEQUENCE {
///   version           Version,
///   modulus           INTEGER,  -- n
///   publicExponent    INTEGER,  -- e
///   privateExponent   INTEGER,  -- d
///   prime1            INTEGER,  -- p
///   prime2            INTEGER,  -- q
///   exponent1         INTEGER,  -- d mod (p-1)
///   exponent2         INTEGER,  -- d mod (q-1)
///   coefficient       INTEGER,  -- (inverse of q) mod p
///   otherPrimeInfos   OtherPrimeInfos OPTIONAL
/// }
const char rsa_private_pem[] = \
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEowIBAAKCAQEAty8yn1CO7nDkrrS/QHZYA8Ucfv4P5LXQZkpH/1cHWX9X3Lio\n"
"ePZRC5zeorbAMAgM4wZk9/iI4BKmSpkzVTR2A2zDbefphwTc3b9JftwXV0ENAhKc\n"
"rZ57MqZO8jc2dhi/87I+kp2yeaT0JRGXnKw2julL84uoJmdOtaRfvYALgp0yckk9\n"
"eXtZkXMh5raGNfalBQ4MUdVTdsJaZG7XCajvBwLbWuaK+hCttcUORlPON59gKyH/\n"
"FZTGlHbamp87lSEll/u3jmHEj3tY6DwGB01OlDv35b5HuO700fSILq9HHv3vcimg\n"
"AK2QS+tfMMjEWCjleJBxaqLj+lDSTnWQrOS+VwIDAQABAoIBAH8J4meOLLG75Twr\n"
"6X7BE+T5a/u+IjOQy4hE941jQ5uTrtFJ1rycxjPxhIz/hGVLD/TZ2GgIGpSbGmwd\n"
"tvXePgG+CgJMlS2n96xpHoU2CZHfcTAAzFuzzuifYZylIcXhAC33bWGsr7ug5BhZ\n"
"DPYAkI2nyZ6LOf/4ISPjbOo0xMa9JIXKkJvv/5NGXgodGWwdCMXeUx1osEKqtZmB\n"
"60m2lrBIqaJeI4YW1Umf1YRcsE5L0POxSr2sQUamPK68/XJIY+zvJZK8wue0PkLF\n"
"ypM1UeO04ANFtELMjWB9EFr8HVn7GEl8QqN6SR44oqFN60BpPp8kzxcaXcPr78Oo\n"
"bdNQJCECgYEA6uLhogvfQ99Ugcok4N9cmsWvvLNpyCKQPKb841hgz7o1wQAz13wb\n"
"di3i9bz7pnIIAA/7od6HXc8Yer7G4xBkKPXX55XgZZg5i2lkVlB8a7zEGKu4hxHG\n"
"fUDu1qbVLjRtFmjvfTItWZeE/TiQ3gUJJkhVPtbFYiiyStdpoDlujNkCgYEAx6aS\n"
"Kh7ll6pnQWztjKNnn6P7ef0MWxV/98xADd/uanHbGD3tnk0QsjG1vRXJGINocvpY\n"
"LRLf2+gf0q3AAxZ/paXZ8bAaPaE1ITCMsrdeWO2fWLhfrGU6349ubo8pDX4ud8rN\n"
"z0+d04vTB7DzuzYRhkCUhHbcUcKawdIXHf9UZq8CgYAk9kj9YBLlMlqxBedhv6Rp\n"
"8pvh/PWzecTq1nhLKlgpuCrHUUnXKf+ETFo/w1pyadVadSlq4oK4v2Mhxa20g5rP\n"
"W0h7d/lU42yCxLX2YzoBFjZhj3w9PQ3YHgS3oI9BcxyLfz3YnLHIPHDADEu3tGEp\n"
"Ng68Eb4D4VWVM2q6vO7pmQKBgEy55P4u9Yj9wcTQ+dHMkmw1dtWAvBjdAFrYsd0j\n"
"K9rYepysX/8wGrSAihlqn+e9yIw3TV+1GzbF1EUA5QPKx69/N2y8grkglOx2Xfvo\n"
"oGeImm5cHNiB5sg3tPbkKaC311/OHp4HON4tpCIWjPRraPyxIOJvU2hQY20NMjkj\n"
"AOqdAoGBAMYba9egsixPGLZ8Y+GUtyTaM50b8ey2t1jZjjDGby6echXeY3tqE97t\n"
"Zbdgsua8istUlmhqdIYatkrjWVv5Z2kLCOTml+jAIP6ScsDxpDCifD5yJ7bg61BQ\n"
"1BgQ9C0zbZ6DEpnkLkGIBDZko4yQ6hLUExaDUxIaFuC33OAXfMeA\n"
"-----END RSA PRIVATE KEY-----\n";

} // namespace talas
} // namespace console 
} // namespace app 
} // namespace talas 
