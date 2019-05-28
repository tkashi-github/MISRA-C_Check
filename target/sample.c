/**
 * 
 * @file mimiclib.h
 * @brief mimiclib is insteadof stdio.h, stdlib.h and string.h
 * @author Takashi Kashiwagi
 * @date 2019/5/19
 * @version     0.3.1
 * @details 
 * --
 * License Type <MIT License>
 * --
 * Copyright 2018 - 2019 Takashi Kashiwagi
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 * @par Update:
 * - 2018/07/05: Takashi Kashiwagi: v0.1
 * - 2018/10/28: Takashi Kashiwagi: v0.2 for IMXRT1060-EVK
 * - 2019/05/19: Takashi Kashiwagi: v0.3.1
 */
#include "mimiclib.h"
#include <stdarg.h>


#ifndef WIN_TEST
#define DefBSP_IMXRT1060_EVK
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t mimic_gets(char pszStr[], uint32_t u32Size){
	uint32_t ret = 0;
	if (fgets(pszStr, u32Size, stdin) != NULL) {
		ret = strlen(pszStr);
	}
	return ret;
}
_Bool mimic_kbhit(void){
	return true; //kbhit();
}
#endif


void mimic_printf(const char* fmt, ...){
	va_list arg;
	char szBuffer[1024];

	va_start(arg, fmt);
	mimic_tcsvprintf(szBuffer, sizeof(szBuffer), fmt, arg);
	va_end(arg);

#ifdef DefBSP_IMXRT1060_EVK
	RTOS_PutString(szBuffer);
#else
	fputs(szBuffer, stdout);
#endif
}

#ifdef DefBSP_IMXRT1060_EVK
/**
 * @brief gets
 * @param [out] pszStr input buffer
 * @param [in]  u32Size Array size of pszStr
 * @return u32Cnt recieved count
 */
uint32_t mimic_gets(char pszStr[], uint32_t u32Size){
	uint32_t u32Cnt = 0u;

	if((pszStr != NULL) && (u32Size > 0u)){
		_Bool bReturnCode = false;

		mimic_memset((uintptr_t)pszStr, 0, u32Size);
		
		while(bReturnCode == false){
			char ch;
			RTOS_GetChar(&ch);
			
			
			switch(ch){
			case '\b':	// バックスペース
				if(u32Cnt > 0u){
					u32Cnt--;
					pszStr[u32Cnt] = '\0';
					RTOS_PutChar('\b');
					RTOS_PutChar(' ');
					RTOS_PutChar('\b');
				}
				break;
			case '\r':		// TeraTermの改行コードは "CR"設定ではCRのみ送られてくる（CRLFにならない）
				//u32Cnt--;			
				pszStr[u32Cnt] = '\0';
				bReturnCode = true;
				RTOS_PutChar((char)ch);
				RTOS_PutChar('\n');		// 相手はWindowsと仮定してLRも送信する
				break;
			default:
				pszStr[u32Cnt] = ch;
				u32Cnt++;
				if(u32Cnt >= u32Size){
					u32Cnt--;
					pszStr[u32Cnt] = '\0';
					break;
				}
				RTOS_PutChar((char)ch);
				break;
			}
		}
	}

	return u32Cnt;
}


/**
 * @brief printf
 * @return true There are some characters in Buffer
 * @return false There are no characters in Buffer
 */
_Bool mimic_kbhit(void){
	return RTOS_kbhit();
}
#endif

typedef enum
{
    enPrintfFlagsMinus = 0x01U,
    enPrintfFlagsPlus = 0x02U,
    enPrintfFlagsSpace = 0x04U,
    enPrintfFlagsZero = 0x08U,
    enPrintfFlagsPound = 0x10U,
    enPrintfFlagsLengthChar = 0x20U,
    enPrintfFlagsLengthShortInt = 0x40U,
    enPrintfFlagsLengthLongInt = 0x80U,
    enPrintfFlagsLengthLongLongInt = 0x100U,
}enPrintfFlags_t;


void mimic_tcsvprintf(
    TCHAR szDst[],
    uint32_t u32MaxElementOfszDst,
    const TCHAR szFormat[],
    va_list arg
)
{
    TCHAR *pszStr = NULL;
    uint32_t u32Cnt = 0;
    uint32_t u32FlagsUsed = 0;
    uint32_t u32FlagsWidth = 0;
    _Bool bValidFlagsWidth = false;
	uint32_t u32PrecisionWidth = 0;
    _Bool bValidPrecisionWidth= false;
    TCHAR vstr[33] = {0};
    uint32_t vlen = 0;
	/** -- */

	/** begin */
	if((szDst == NULL) ||
	(szFormat == NULL)){
		return;
	}
	memset(szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);

	pszStr = (TCHAR *)szFormat;
	while(*pszStr != (TCHAR)'\0')
    {
		TCHAR ch = *pszStr;

        if (ch != (TCHAR)'%')
        {
			szDst[u32Cnt] = *pszStr;
			u32Cnt++;
			pszStr++;
        }else{
			for(;;){
				pszStr++;
				if(*pszStr == '-'){
					u32FlagsUsed |= enPrintfFlagsMinus;
				}else if(*pszStr == (TCHAR)'+'){
					u32FlagsUsed |= enPrintfFlagsPlus;
				}else if(*pszStr == (TCHAR)'0'){
					u32FlagsUsed |= enPrintfFlagsZero;
				}else{
					--pszStr;
					break;
				}
			}
			u32FlagsWidth = 0;
			bValidFlagsWidth = false;
			for(;;){
				pszStr++;
				TCHAR ch = *pszStr;
				if ((ch >= (TCHAR)'0') && (ch <= (TCHAR)'9')){
					bValidFlagsWidth = true;
					u32FlagsWidth = (u32FlagsWidth * 10) + (ch - (TCHAR)'0');
				}else if (ch == (TCHAR)'*'){
					bValidFlagsWidth = true;
					u32FlagsWidth = (uint32_t)va_arg(arg, uint32_t);
				}else{
					--pszStr;
					break;
				}
			}
			
			u32PrecisionWidth = 6;
			bValidPrecisionWidth = false;
			pszStr++;
			if (*pszStr == (TCHAR)'.'){
				u32PrecisionWidth = 0;
				for(;;)
				{
					pszStr++;
					TCHAR ch = *pszStr;
					if ((ch >= (TCHAR)'0') && (ch <= (TCHAR)'9')){
						u32PrecisionWidth = (u32PrecisionWidth * 10) + (ch - (TCHAR)'0');
						bValidPrecisionWidth = true;
					}else if (ch == (TCHAR)'*'){
						u32PrecisionWidth = (uint32_t)va_arg(arg, uint32_t);
						bValidPrecisionWidth = true;
					}else{
						--pszStr;
						break;
					}
				}
			}else{
				--pszStr;
			}

			pszStr++;
			switch (*pszStr){
			case (TCHAR)'l':
				pszStr++;
				if (*pszStr != (TCHAR)'l'){
					u32FlagsUsed |= enPrintfFlagsLengthLongInt;
					--pszStr;
				}else{
					u32FlagsUsed |= enPrintfFlagsLengthLongLongInt;
				}
				break;
			default:
				--pszStr;
				break;
			}

			pszStr++;
			ch = *pszStr;
			{
				if ((ch == (TCHAR)'d') ||
				(ch == (TCHAR)'i') ||
				(ch == (TCHAR)'f') ||
				(ch == (TCHAR)'F') ||
				(ch == (TCHAR)'x') ||
				(ch == (TCHAR)'X') ||
				(ch == (TCHAR)'u') ||
				(ch == (TCHAR)'U'))
				{
					if ((ch == (TCHAR)'d') || (ch == (TCHAR)'i')){
						if (u32FlagsUsed & enPrintfFlagsLengthLongLongInt){
							mimic_lltoa((int64_t)va_arg(arg, int64_t), vstr, sizeof(vstr));
						}else{
							mimic_ltoa((int32_t)va_arg(arg, int32_t), vstr, sizeof(vstr));
						}
						vlen = mimic_tcslen(vstr);
					}else if ((ch == (TCHAR)'f') || (ch == (TCHAR)'F')){
						if(bValidPrecisionWidth == false){
							mimic_ftoa((double)va_arg(arg, double), vstr, sizeof(vstr), 6);
						}else{
							mimic_ftoa((double)va_arg(arg, double), vstr, sizeof(vstr), u32PrecisionWidth);
						}
						vlen = mimic_tcslen(vstr);
					}else if ((ch == (TCHAR)'X') || (ch == (TCHAR)'x')){
						if (u32FlagsUsed & enPrintfFlagsLengthLongLongInt){
							mimic_ulltoa((uint64_t)va_arg(arg, uint64_t), vstr, sizeof(vstr), 16);
						}else{
							mimic_ultoa((uint32_t)va_arg(arg, uint32_t), vstr, sizeof(vstr), 16);
						}
						vlen = mimic_tcslen(vstr);
					}else if ((ch == (TCHAR)'U') || (ch == (TCHAR)'u')){
						if (u32FlagsUsed & enPrintfFlagsLengthLongLongInt){
							mimic_ulltoa((uint64_t)va_arg(arg, uint64_t), vstr, sizeof(vstr), 10);
						}else{
							mimic_ultoa((uint32_t)va_arg(arg, uint32_t), vstr, sizeof(vstr), 10);
						}
						vlen = mimic_tcslen(vstr);
					}else{
						/* NOP */
						vlen = 0;
					}


					if(u32FlagsWidth > 0){
						if(vlen >= u32FlagsWidth){
							for(uint32_t i=0;i<u32FlagsWidth;i++){
								vstr[i] = vstr[i + (vlen - u32FlagsWidth)];
							}
							vlen = u32FlagsWidth;
							vstr[vlen] = (TCHAR)'\0';
						}else{
							uint32_t u32 = u32FlagsWidth - vlen;
							TCHAR szTemp[64];
							
							TCHAR tcTemp = (TCHAR)' ';
							if((u32FlagsUsed & enPrintfFlagsZero) == enPrintfFlagsZero){
								tcTemp = (TCHAR)'0';
							}
							mimic_tcscpy(szTemp, vstr, sizeof(szTemp));

							uint32_t i;
							for(i=0;i<u32;i++){
								vstr[i] = tcTemp;
							}
							vstr[i] = (TCHAR)'\0';

							mimic_tcscat(vstr, sizeof(vstr), szTemp);
							vlen = u32FlagsWidth;
							vstr[vlen] = (TCHAR)'\0';
						}
					}

					mimic_tcscat(&szDst[u32Cnt], u32MaxElementOfszDst - u32Cnt, vstr);
					u32Cnt += vlen;
					pszStr++;

				}
				else if (ch == (TCHAR)'c')
				{
					szDst[u32Cnt] = (TCHAR)va_arg(arg, uint32_t);
					u32Cnt++;
					pszStr++;
				}
				else if (ch == (TCHAR)'s')
				{
					TCHAR *psz = (TCHAR *)va_arg(arg, TCHAR *);
					if (psz != NULL)
					{
						if(bValidFlagsWidth == false){
							mimic_tcscat(&szDst[u32Cnt], u32MaxElementOfszDst - u32Cnt, psz);
							u32Cnt += mimic_tcslen(psz);
						}else{
							vlen = mimic_tcslen(psz);
							if(vlen > u32FlagsWidth){
								for(uint32_t i=0;i<u32FlagsWidth;i++){
									szDst[u32Cnt] =  psz[i];
									u32Cnt++;
								}
							}else{
								uint32_t u32 = u32FlagsWidth - vlen;
								if((u32FlagsUsed & enPrintfFlagsMinus) != enPrintfFlagsMinus){
									/** zero */
									for(uint32_t i=0;i<vlen;i++){
										szDst[u32Cnt] = psz[i];
										u32Cnt++;
									}
									for(uint32_t i=0;i<u32;i++){
										szDst[u32Cnt] = (TCHAR)' ';
										u32Cnt++;
									}
								}else{
									for(uint32_t i=0;i<u32;i++){
										szDst[u32Cnt] = (TCHAR)' ';
										u32Cnt++;
									}
									for(uint32_t i=0;i<vlen;i++){
										szDst[u32Cnt] = psz[i];
										u32Cnt++;
									}
								}
							}
							szDst[u32Cnt] = (TCHAR)'\0';
						}
					}
					pszStr++;
				}
				else
				{
					szDst[u32Cnt] =  *pszStr;
					u32Cnt++;
					pszStr++;
				}
			}
		}
	}
	return;
}

