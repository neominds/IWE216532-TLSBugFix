/* 
   Copyright 2017
   Wind River KK
*/

#include <stdio.h>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

//wrapper to wrSSLTest.c
extern int wrkkssltest_client(void);

int wrkkssltest()
{
	wrkkssltest_client();

	return 0;
}
