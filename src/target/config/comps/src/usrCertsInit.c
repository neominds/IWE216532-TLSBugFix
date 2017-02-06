/* usrSecurityLib.c - Certificate Support Configuration */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,28feb05,cdw  added link syms
01a,07feb05,tat  written.
*/

/*
DESCRIPTION
This file is used to configure and initialize the Certificate Support component

NOMANUAL
*/
#include <openssl/rand.h>
#include <openssl/crypto.h>

                                 
STATUS sslMultiThreadInit(void); 
void* sslMemoryAllocate (size_t elemSize);
void* sslMemoryRealloc(void *pBlock, size_t newSize);
void sslMemoryFree (void* p_object);


extern FUNCPTR * asn1_link_syms();
extern FUNCPTR * pem_link_syms();
extern FUNCPTR * pkcs7_link_syms();
extern FUNCPTR * x509_link_syms();
extern FUNCPTR * x509v3_link_syms();



/*******************************************************************************
*
* usrCertSupportConfigure - configure and initialize the Certificate Support component
*
* Creates a configuration based on the user's Tornado settings and
* uses this configuration to create and initialize the Certificate Support component
*
* RETURNS: N/A
*
*
* NOMANUAL
*/
void usrCertSupportConfigure(void)
{
    static char initialized =FALSE;
    /* make sure the linker brings in the certificate support code */
    asn1_link_syms();
    pem_link_syms();
    pkcs7_link_syms();
    x509_link_syms();
    x509v3_link_syms();


    if(!initialized)
    {
       /* initialize memory partion for OpenSSL crypto library */ 
#ifdef SSL_MEMORY_USE_MEMORY_POOL
	/*sslMemoryPoolInit(); wrkk-iwe216532*/
       if (sslMemoryPoolInit() == OK)
	   sslMemoryPoolStatus = SSL_MEMPOOL_AVAILABLE;
#endif
       CRYPTO_set_mem_functions(sslMemoryAllocate,sslMemoryRealloc, sslMemoryFree);  

       sslMultiThreadInit();      /* setup multithreading callbacks for locking functions */
       RAND_set_rand_method(RAND_CCI()); /* setup security library to use CCI for random numbers */
       initialized = TRUE;
    }
}
