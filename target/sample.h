/**
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
#ifndef __cplusplus
#if __STDC_VERSION__ < 201112L
#error /** Only C11 */
#endif
#endif
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#ifdef WIN_TEST
	#ifdef __cplusplus
		#include <cstddef>
		#include <cstdio>
	#endif
#else
#define DefBSP_IMXRT1060_EVK
#endif

#ifdef DefBSP_IMXRT1060_EVK
/** OS */
#include "FreeRTOS.h"
#include "event_groups.h"
#include "timers.h"
#include "semphr.h"
#include "OSResource.h"

/** Board */
#include "MIMXRT1062.h"
#include "UART/DrvLPUART.h"
#define kStdioPort enLPUART1

/**
 * @brief getc (Blocking)
 * @param [out] ch Received character
 * @return void
 */
static inline void RTOS_GetChar(TCHAR *ch)
{
	if (ch != NULL)
	{
		DrvUARTRecv(kStdioPort, (uint8_t *)ch, sizeof(TCHAR), portMAX_DELAY);
	}
}
/**
 * @brief putc (NonBlocking)
 * @param [in] ch character
 * @return void
 */
static inline void RTOS_PutChar(TCHAR ch)
{
	DrvUARTSend(kStdioPort, (const uint8_t *)&ch, sizeof(TCHAR));
}
/**
 * @brief puts (with Semapore)
 * @param [in] pszStr NULL Terminate String
 * @return void
 */
static inline void RTOS_PutString(const TCHAR pszStr[])
{
	uint32_t ByteCnt = mimic_tcslen(pszStr)*sizeof(TCHAR);
	DrvUARTSend(kStdioPort, (const uint8_t *)pszStr, ByteCnt);
}

/**
 * @brief kbhits
 * @return true There are some characters in Buffer
 * @return false There are no characters in Buffer
 */
static inline _Bool RTOS_kbhit(void){
	return (_Bool)!DrvUARTIsRxBufferEmpty(kStdioPort);
}
#endif

#ifndef __cplusplus
#ifndef NULL
#define NULL (void*)0
#endif
#endif

#ifndef TCHAR_TYPE
typedef char TCHAR;
#endif

/**
 * @brief gets
 * @param [out] szStr NULL Terminate String buffer
 * @param [out] u32Size buffer elements size
 * @return elements count
 */
extern uint32_t mimic_gets(TCHAR pszStr[], uint32_t u32Size);

extern void mimic_printf(const char* fmt, ...);

extern _Bool mimic_kbhit(void);

extern void mimic_tcsvprintf(TCHAR szDst[], uint32_t u32MaxElementOfszDst, const TCHAR szFormat[], va_list arg);

/**
 * @brief toupper
 * @param [in] szStr NULL Terminate String
 * @return void
 */
static inline char *mimic_strupper(char szStr[]){
	if(szStr != NULL){
		uint32_t i=0;
		while(szStr[i] != '\0'){
			if((szStr[i] >= 'a') && (szStr[i] <= 'z')){
				szStr[i] += 'A';
				szStr[i] -= 'a';
			}
			i++;
		}
	}
	return szStr;
}
static inline char *mimic_tcsupper(TCHAR szStr[]){
	if(szStr != NULL){
		uint32_t i=0;
		while(szStr[i] != '\0'){
			if((szStr[i] >= 'a') && (szStr[i] <= 'z')){
				szStr[i] += 'A';
				szStr[i] -= 'a';
			}
			i++;
		}
	}
	return szStr;
}
/**
 * @brief strlen
 * @param [in] szStr NULL Terminate String
 * @return uint32_t Length
 */
static inline uint32_t mimic_strlen(const char pszStr[]){
	/*-- var --*/
	uint32_t u32Cnt = 0u;

	/*-- begin --*/
	if(pszStr != NULL){
		while(pszStr[u32Cnt] != '\0'){
			u32Cnt++;
		}

	}
	return u32Cnt;
}
static inline uint32_t mimic_tcslen(const TCHAR pszStr[]){
	/*-- var --*/
	uint32_t u32Cnt = 0u;

	/*-- begin --*/
	if(pszStr != NULL){
		while(pszStr[u32Cnt] != '\0'){
			u32Cnt++;
		}

	}
	return u32Cnt;
}


/**
 * @brief memcmp
 * @param [in] p1 Target Pointer1
 * @param [in] p2 Target Pointer2
 * @param [in] u32ByteCnt Compare Size
 * @return true Match
 * @return false Unmatch
 */
static inline _Bool mimic_memcmp(uintptr_t p1, uintptr_t p2, uint32_t u32ByteCnt){
	/*-- var --*/
	uint8_t *pu81 = (uint8_t*)p1;
	uint8_t *pu82 = (uint8_t*)p2;
	_Bool bret = true;

	/*-- begin --*/
	for(uint32_t i=0u;i<u32ByteCnt;i++){
		if(pu81[i] != pu82[i]){
			bret = false;
			break;
		}
	}
	return bret;
}
static inline _Bool mimic_memcpy(uintptr_t p1, uintptr_t p2, uint32_t u32ByteCnt){
	/*-- var --*/
	uint8_t *pu81 = (uint8_t*)p1;
	uint8_t *pu82 = (uint8_t*)p2;
	_Bool bret = true;

	/*-- begin --*/
	for(uint32_t i=0u;i<u32ByteCnt;i++){
		pu81[i] = pu82[i];
	}
#ifdef DefBSP_IMXRT1060_EVK
	__DMB();
#endif
	return bret;
}
static inline _Bool mimic_memset(uintptr_t p1, uint8_t val, uint32_t u32ByteCnt){
	/*-- var --*/
	uint8_t *pu81 = (uint8_t*)p1;
	_Bool bret = true;

	/*-- begin --*/
	for(uint32_t i=0u;i<u32ByteCnt;i++){
		pu81[i] = val;
	}
#ifdef DefBSP_IMXRT1060_EVK
	__DMB();
#endif
	return bret;
}
/**
 * @brief strtok_r
 * @param [in] szStr Target String
 * @param [in] szDelm Delemiter
 * @param [in] ctx 
 * @return char* 
 */
static inline char *mimic_strtok(char szStr[], const char szDelm[], char **ctx){
	/*-- var --*/
	char *pret = NULL;

	/*-- begin --*/
	if(szDelm != NULL){
		char *pszTmp;
		uint32_t u32=0u;
		uint32_t delmLen = mimic_strlen(szDelm);

		if(szStr == NULL){
			pszTmp = *ctx;
		}else{
			pszTmp = szStr;
		}
		if(pszTmp[0] != '\0'){
			pret = pszTmp;
			while(pszTmp[u32] != '\0'){
				*ctx = &pszTmp[u32 + delmLen];
				if(mimic_memcmp((uintptr_t)&pszTmp[u32], (uintptr_t)szDelm, delmLen) != false){
					pszTmp[u32] = '\0';
					pret = pszTmp;
					break;
				}
				u32++;
			}
		}
	}
	return pret;
}
static inline char *mimic_tcstok(TCHAR szStr[], const TCHAR szDelm[], TCHAR **ctx){
	/*-- var --*/
	TCHAR *pret = NULL;

	/*-- begin --*/
	if(szDelm != NULL){
		TCHAR *pszTmp;
		uint32_t u32=0u;
		uint32_t delmLen = mimic_tcslen(szDelm);

		if(szStr == NULL){
			pszTmp = *ctx;
		}else{
			pszTmp = szStr;
		}
		if(pszTmp[0] != (TCHAR)'\0'){
			pret = pszTmp;
			while(pszTmp[u32] != (TCHAR)'\0'){
				*ctx = &pszTmp[u32 + delmLen];
				if(mimic_memcmp((uintptr_t)&pszTmp[u32], (uintptr_t)szDelm, sizeof(TCHAR)*delmLen) != false){
					pszTmp[u32] = (TCHAR)'\0';
					pret = pszTmp;
					break;
				}
				u32++;
			}
		}
	}
	return pret;
}

static inline _Bool mimic_isprint(char c){
	if((c >= 0x20) && (c <= 0x7e)){
		return true;
	}else{
		return false;
	}
}


static inline TCHAR * mimic_tcscpy(TCHAR szDst[], const TCHAR pszSrc[], uint32_t DstSize){
	uint32_t i = 0u;

	for(i=0;i<DstSize;i++){
		szDst[i] = (TCHAR)'\0';
	}
	i = 0u;
	while(pszSrc[i] != (TCHAR)'\0'){
		szDst[i] = pszSrc[i];
		i++;
		if(i >= DstSize){
			break;
		}
	}

	return szDst;
}

static inline char *mimic_strcpy(char szDst[], const char szSrc[], uint32_t u32DstSize){
	/*-- var --*/
	uint32_t u32Cnt = 0u;

	/*-- begin --*/
	if((szDst != (char*)NULL) && (szSrc != (const char*)NULL)){
		while(szSrc[u32Cnt] != '\0'){
			szDst[u32Cnt] = szSrc[u32Cnt];
			u32Cnt++;
			if(u32Cnt >= u32DstSize){
				szDst[u32Cnt - 1u] = '\0';
				break;
			}
		}
	}

	return szDst;
}


/**
* @brief strcmp
* @param[in]const char szStr1[]
* @param[in]const char szStr2[]
* @return true str1 == str2
* @return false str1 != str2
*/
static inline int32_t mimic_strcmp(const char szStr1[], const char szStr2[]){
	/*-- var --*/
	uint32_t u32Cnt = 0u;

	/*-- begin --*/
	if((szStr1 != (const char*)NULL) && (szStr2 != (const char*)NULL)){
		for(;;){
			if(szStr1[u32Cnt] < szStr2[u32Cnt]){
				return -1;
			}
			if(szStr1[u32Cnt] > szStr2[u32Cnt]){
				return 1;
			}
			if((szStr1[u32Cnt] == '\0') && (szStr2[u32Cnt] == '\0')){
				return 0;
			}
			u32Cnt++;
		}
	}

	return 0;
}
static inline int32_t mimic_tcsncmp(const TCHAR szStr1[], const TCHAR szStr2[], uint32_t u32NumberOfElements)
{
	if((szStr1 != (const TCHAR*)NULL) && (szStr2 != (const TCHAR*)NULL))
	{
		uint32_t u32Cnt = 0u;
		for(;;){
			if(szStr1[u32Cnt] < szStr2[u32Cnt]){
				return -1;
			}
			if(szStr1[u32Cnt] > szStr2[u32Cnt]){
				return 1;
			}
			if((szStr1[u32Cnt] == '\0') && (szStr2[u32Cnt] == '\0')){
				return 0;
			}
			u32Cnt++;
			if(u32Cnt >= u32NumberOfElements){
				return -1;
			}
		}
	}

	return -1;
}


static inline TCHAR *mimic_ltoa(const int32_t i32Val, TCHAR szDst[], uint32_t u32MaxElementOfszDst){
	uint32_t u32Index = 0;
	int32_t i32Sign;
	uint32_t u32Val;

	if((szDst == NULL) || (u32MaxElementOfszDst == 0)){
		return NULL;
	}
	i32Sign = i32Val;
	if(i32Sign < 0){
		u32Val = (uint32_t)-i32Val;
	}else{
		u32Val = (uint32_t)i32Val;
	}
	mimic_memset((uintptr_t)szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);

	while(u32Index < (u32MaxElementOfszDst - 1)){
		uint32_t u32 = (u32Val % 10);
		u32Val /= 10;
		szDst[u32Index] = (TCHAR)u32 + (TCHAR)'0'; 
		u32Index++;
		if(u32Val == 0){
			break;
		}
	}

	/** Add sign */
	if(i32Sign < 0){
		szDst[u32Index] = (TCHAR)'-';
		u32Index++;
	}

	/** Reverse*/
	for(uint32_t j=0;j<(u32Index/2);j++)
	{
		TCHAR tcTemp = szDst[j];
		szDst[j] = szDst[u32Index - 1 - j];
		szDst[u32Index - 1 - j] = tcTemp;
	}
	return szDst;
}

static inline TCHAR *mimic_ultoa(const uint32_t u32Val, TCHAR szDst[], uint32_t u32MaxElementOfszDst, uint32_t u32Radix){
	uint32_t u32Index = 0;
	uint32_t u32Temp = u32Val;

	if((szDst == NULL) || (u32MaxElementOfszDst == 0)){
		return NULL;
	}

	mimic_memset((uintptr_t)szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);

	while(u32Index < (u32MaxElementOfszDst - 1)){
		uint32_t u32 = (u32Temp % u32Radix);
		u32Temp /= u32Radix;
		if(u32 <= 9){
			szDst[u32Index] = (TCHAR)u32 + (TCHAR)'0';
		}else{
			szDst[u32Index] = (TCHAR)(u32 - 10) + (TCHAR)'A';
		}
		u32Index++;
		if(u32Temp == 0){
			break;
		}
	}

	/** Reverse*/
	for(uint32_t j=0;j<(u32Index/2);j++)
	{
		TCHAR tcTemp = szDst[j];
		szDst[j] = szDst[u32Index - 1 - j];
		szDst[u32Index - 1 - j] = tcTemp;
	}
	return szDst;
}

static inline TCHAR *mimic_lltoa(const int64_t i64Val, TCHAR szDst[], uint32_t u32MaxElementOfszDst){
	uint32_t u32Index = 0;
	int64_t i64Sign;
	uint64_t u64Val;

	if((szDst == NULL) || (u32MaxElementOfszDst == 0)){
		return NULL;
	}
	i64Sign = i64Val;
	if(i64Sign < 0){
		u64Val = (uint64_t)-i64Val;
	}else{
		u64Val = (uint64_t)i64Val;
	}
	mimic_memset((uintptr_t)szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);

	while(u32Index < (u32MaxElementOfszDst - 1)){
		uint32_t u32 = (uint32_t)(u64Val % 10ull);
		u64Val /= 10ull;
		szDst[u32Index] = (TCHAR)u32 + (TCHAR)'0'; 
		u32Index++;
		if(u64Val == 0){
			break;
		}
	}

	/** Add sign */
	if(i64Sign < 0){
		szDst[u32Index] = (TCHAR)'-';
		u32Index++;
	}

	/** Reverse*/
	for(uint32_t j=0;j<(u32Index/2);j++)
	{
		TCHAR tcTemp = szDst[j];
		szDst[j] = szDst[u32Index - 1 - j];
		szDst[u32Index - 1 - j] = tcTemp;
	}
	return szDst;
}


static inline TCHAR *mimic_ulltoa(const uint64_t u64Val, TCHAR szDst[], uint32_t u32MaxElementOfszDst, uint32_t u32Radix){
	uint32_t u32Index = 0;
	uint64_t u64Temp = u64Val;

	if((szDst == NULL) || (u32MaxElementOfszDst == 0)){
		return NULL;
	}

	mimic_memset((uintptr_t)szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);

	while(u32Index < (u32MaxElementOfszDst - 1)){
		uint32_t u32 = (uint32_t)(u64Temp % u32Radix);
		u64Temp /= u32Radix;
		if(u32 < 10){
			szDst[u32Index] = (TCHAR)u32 + (TCHAR)'0';
		}else{
			szDst[u32Index] = (TCHAR)(u32 - 10u) + (TCHAR)'A';
		}
		u32Index++;
		if(u64Temp == 0){
			break;
		}
	}

	/** Reverse*/
	for(uint32_t j=0;j<(u32Index/2);j++)
	{
		TCHAR tcTemp = szDst[j];
		szDst[j] = szDst[u32Index - 1 - j];
		szDst[u32Index - 1 - j] = tcTemp;
	}
	return szDst;
}


static inline TCHAR *mimic_tcscat(TCHAR pszStr1[], uint32_t u32MaxElementOfszStr1, const TCHAR pszStr2[]){
	uint32_t u32Pos = 0;
	uint32_t u32Index = 0;

	while(pszStr1[u32Pos] != (TCHAR)'\0')
	{
		u32Pos++;
		if(u32Pos >= (u32MaxElementOfszStr1 -1))
		{
			return pszStr1;
		}
	}

	while(pszStr2[u32Index] != (TCHAR)'\0')
	{
		pszStr1[u32Pos] = pszStr2[u32Index];
		u32Pos++;
		u32Index++;
		if(u32Pos >= (u32MaxElementOfszStr1 -1))
		{
			return pszStr1;
		}
	}

	return pszStr1;
}

/** TODO : これは良くない実装 */
static inline TCHAR *mimic_ftoa(const double dfpVal, TCHAR szDst[], uint32_t u32MaxElementOfszDst, uint32_t precision_width)
{
	double dfpTemp = dfpVal;
	uint64_t u64Z;
	uint32_t u32Pos = 0;
	uint32_t u32PrecCnt = 0;

	mimic_memset((uintptr_t)szDst, 0, sizeof(TCHAR)*u32MaxElementOfszDst);
	if(dfpVal < 0.0){
		dfpTemp = -dfpVal;
	}

	u64Z = dfpTemp;
	dfpTemp -= (double)u64Z;

	if(u64Z != 0){
		if(dfpVal < 0.0){
			szDst[0] = (TCHAR)'-';
			mimic_ulltoa(u64Z, &szDst[1], u32MaxElementOfszDst-1, 10);
		}else{
			mimic_ulltoa(u64Z, szDst, u32MaxElementOfszDst, 10);
		}
		
		u32Pos = mimic_tcslen(szDst);
	}else{
		if(dfpVal < 0.0){
			szDst[u32Pos] = (TCHAR)'-';
			u32Pos++;
		}
		szDst[u32Pos] = (TCHAR)'0';
		u32Pos++;
	}
	szDst[u32Pos] = (TCHAR)'.';
	u32Pos++;
	u32PrecCnt = 0;

	for(;;)
	{
		dfpTemp *= 10.0;
		if(u32PrecCnt >= (precision_width - 1)){
			dfpTemp += 0.5;
		}
		uint32_t u32Z = (uint32_t)dfpTemp;
		dfpTemp -= (double)u32Z;
		
		szDst[u32Pos] = (TCHAR)u32Z + (TCHAR)'0';
		u32Pos++;
		u32PrecCnt++;
		if((dfpTemp == 0.0) || (u32PrecCnt >= precision_width))
		{
			break;
		}

	}

	return szDst;
}

#ifdef __cplusplus
}
#endif

