// FingerDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <jni.h>
#include "com_yumt_zksoft_ZKTCP.h"
#include "com_yumt_zksoft_ZKTCP_cpp.h"
#include <stdio.h>
#include "Adapter.h"
extern CAdapter g_Adapter;

BOOL CheckConnectStatus()
{
	return g_Adapter.CheckConnectStatus();
}
jstring CStringTojstring(JNIEnv *m_penv,CString convert)  
{  	
	jstring retjstring;  
	jsize iLoop;  
	jsize jlength = convert.GetLength();  

	jchar *dummystring = new jchar[jlength];
	// First copy the character to a unicode form  
	for (iLoop = 0; iLoop < jlength; iLoop++)  
		dummystring[iLoop] = (jchar) convert.GetAt(iLoop);  
	// I commented the following part because NewString takes the length to be converted  
	// and it doesn't look to the excess string  
	/* 
	// Fill the rest of the string with nulls 
	for (jLoop = iLoop; jLoop < MAX_RESULT_INFO; jLoop++) 
	dummystring[iLoop] = (jchar) ""; 
	*/  
	retjstring = m_penv->NewString(dummystring, jlength);  
	delete []dummystring;
	return retjstring;  
}  
void OutPutFuncName(char *pFuncName){
	printf("javaCallFunc-->%s @AdapterMain.cpp\n",pFuncName);
}
JNIEXPORT jstring JNICALL Java_TestFingerDLL_testJni(JNIEnv *env, jobject obj, jstring pString){
	OutPutFuncName(__FUNCTION__);
	const char *nativeString = env->GetStringUTFChars(pString,0);
	printf("\n===xxxx%s\n",nativeString);

	env->ReleaseStringUTFChars(pString,nativeString);

	char str[] ="jnicall--<Hello>--jnicall\n";
	jstring jstr;
	jstr = env->NewStringUTF(str);
	return jstr;
}
namespace ZKTCP{
JNIEXPORT BOOL JNICALL Connect_Net(LPCTSTR lpnativeAddress,int port)
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.Connect_Net(lpnativeAddress,port);
}
JNIEXPORT BOOL JNICALL ReadAllGLogData(DWORD dwMachineNumber)
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.ReadAllGLogData(dwMachineNumber);
}
JNIEXPORT BOOL JNICALL GetGeneralLogDataStr ( long dwMachineNumber, long * dwEnrollNumber, long * dwVerifyMode, long * dwInOutMode, BSTR * TimeStr ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.GetGeneralLogDataStr(dwMachineNumber,dwEnrollNumber,dwVerifyMode,dwInOutMode,TimeStr);
}

JNIEXPORT LPCTSTR JNICALL GetALLGeneralLogData_withJson( long dwMachineNumber) 
{
	OutPutFuncName(__FUNCTION__);
	ZKTCP::EnableDevice(dwMachineNumber,FALSE);

	CString strRet(_T("{\"log\":["));
	CString strEnd(_T("]}"));
	if(!ZKTCP::ReadAllGLogData(dwMachineNumber)){
		printf(_T("m_zkem.ReadAllGLogData faild"));
		ZKTCP::EnableDevice(dwMachineNumber,TRUE);
		return strRet+strEnd;
	}
	int iRetCount = 0;

	long   dwTMachineNumber,  dwEnrollNumber,  dwEMachineNumber,  dwVerifyMode, dwInOutMode,
		dwYear,  dwMonth,  dwDay, dwHour,  dwMinute,dwSecond ;

	while(ZKTCP::GetGeneralLogData(dwMachineNumber,  
		&dwTMachineNumber,  &dwEnrollNumber,  &dwEMachineNumber,  &dwVerifyMode, &dwInOutMode,
		&dwYear,  &dwMonth,  &dwDay, &dwHour,  &dwMinute,&dwSecond)){
			iRetCount++;
			CString strLog;
			strLog.Format(_T("GetGeneralLogData %d-%d,%d,%d,%d-%d-%d %d:%d\n"),
				dwMachineNumber,dwEnrollNumber,dwVerifyMode,dwInOutMode,
				dwYear,dwMonth,dwDay,dwHour,dwMinute);
			CString strRet_OneLog;
			strRet_OneLog.Format(_T("{\"dwEnrollNumber\":%d,\"dwVerifyMode\":%d,\"dwInOutMode\":%d,\"time\":\"%d-%d-%d %d:%d:%d\"},"),
				dwEnrollNumber,dwVerifyMode,dwInOutMode,
				dwYear,  dwMonth,  dwDay, dwHour,  dwMinute,dwSecond);
			strRet+=strRet_OneLog;
			dwEnrollNumber=0;
			dwVerifyMode=0;
			dwInOutMode=0;
	}

	ZKTCP::EnableDevice(dwMachineNumber,TRUE);

	//删除掉最后一个“,” 
	if(iRetCount>0)
		strRet.Delete(strRet.GetLength()-1);
	strRet+=strEnd;
	return strRet;
}
JNIEXPORT BOOL JNICALL ClearGLog ( long dwMachineNumber )
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.ClearGLog(dwMachineNumber);
}
JNIEXPORT BOOL JNICALL ReadAllUserID ( long dwMachineNumber )
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.ReadAllUserID(dwMachineNumber);
}
JNIEXPORT BOOL JNICALL GetAllUserInfo ( long dwMachineNumber, long * dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.GetAllUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}
JNIEXPORT LPCTSTR JNICALL GetAllUserInfo_WithJson(long dwMachineNumber)
{
	OutPutFuncName(__FUNCTION__);
	CString strRet(_T("{\"log\":["));
	CString strEnd(_T("]}"));

	if(!CheckConnectStatus())return strRet+strEnd;
	BSTR userName=NULL,passWord=NULL;
	VARIANT_BOOL bEnabled = VARIANT_FALSE;
	long dwEnrollNumber;
	long Privilege;

	int nDataCount = 0;

	ZKTCP::EnableDevice(dwMachineNumber,FALSE);
	while(g_Adapter.GetAllUserInfo(dwMachineNumber,
		&dwEnrollNumber,
		&userName,
		&passWord,
		&Privilege,
		&bEnabled)){		
			CString strRet_OneLog;
			CString ssName(userName);
			CString ssPassword(passWord);
			strRet_OneLog.Format(_T("{\"dwEnrollNumber\":%d,\"name\":\"%s\",\"pass\":\"%s\",\"Privilege\":%d,\"enable\":%d},"),
				dwEnrollNumber,ssName,ssPassword,Privilege,bEnabled);
			strRet+=strRet_OneLog;
			printf("UserInfo[%d]===%s",nDataCount,strRet_OneLog);
			nDataCount ++;

			dwEnrollNumber = 0;
			Privilege = 0;
			bEnabled = VARIANT_FALSE;
			if(userName!=NULL){
				SysFreeString(userName);
				userName =NULL;
			}
			if(passWord!=NULL){
				SysFreeString(passWord);
				passWord = NULL;
			}
	}

	ZKTCP::EnableDevice(dwMachineNumber,TRUE);
	if(nDataCount>0){
		strRet.Delete(strRet.GetLength()-1);
	}
	strRet +=strEnd;
	return strRet;
}
JNIEXPORT BOOL JNICALL GetUserInfo ( long dwMachineNumber, long dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.GetUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}
JNIEXPORT LPCTSTR JNICALL GetUserInfo_WithJson ( long dwMachineNumber, long dwEnrollNumber)
{
	OutPutFuncName(__FUNCTION__);
	CString strRet(_T("{}"));
	if(!CheckConnectStatus())return strRet;
	BSTR bstrName,bstrPassword;
	long Privilege=0;
	VARIANT_BOOL enabled = VARIANT_FALSE;
	BOOL bRet = g_Adapter.GetUserInfo(dwMachineNumber,dwEnrollNumber,&bstrName,&bstrPassword,&Privilege,&enabled);
	
	if(bRet){
		CString ssName(bstrName);
		CString ssPassword(bstrPassword);
		strRet.Format(_T("{\"dwEnrollNumber\":%d,\"name\":\"%s\",\"pass\":\"%s\",\"Privilege\":%d,\"enable\":%d}"),
			dwEnrollNumber,ssName,ssPassword,Privilege,enabled);
	}
	if(bstrName!=NULL)
		SysFreeString(bstrName);
	if(bstrPassword!=NULL)
		SysFreeString(bstrPassword);
	return strRet;
}
JNIEXPORT BOOL JNICALL SetUserInfo ( long dwMachineNumber, long dwEnrollNumber, BSTR Name, BSTR Password, long Privilege, VARIANT_BOOL Enabled ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.SetUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}
JNIEXPORT BOOL JNICALL SetUserTmpStr ( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, BSTR TmpData ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.SetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,TmpData);
}
JNIEXPORT BOOL JNICALL GetUserTmpStr ( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, BSTR * TmpData, long * TmpLength ) 
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.GetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,TmpData,TmpLength);
}
JNIEXPORT void JNICALL Disconnect()
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.Disconnect();
}
JNIEXPORT void JNICALL EnableDevice(LONG dwMachineNumber,VARIANT_BOOL Enabled)
{
	OutPutFuncName(__FUNCTION__);
	g_Adapter.EnableDevice(dwMachineNumber,Enabled);
}
JNIEXPORT BOOL JNICALL GetGeneralLogData( long dwMachineNumber, long * dwTMachineNumber, long * dwEnrollNumber, long * dwEMachineNumber, long * dwVerifyMode, long * dwInOutMode, long * dwYear, long * dwMonth, long * dwDay, long * dwHour, long * dwMinute,long *dwSecond )
{
	OutPutFuncName(__FUNCTION__);
	return g_Adapter.GetGeneralLogData(dwMachineNumber,dwTMachineNumber,dwEnrollNumber,dwEMachineNumber,dwVerifyMode,
		dwInOutMode,dwYear,dwMonth,dwDay,dwHour,dwMinute,dwSecond);
}
}
JNIEXPORT void JNICALL Java_com_yumt_zksoft_ZKTCP_Release(JNIEnv *pjniEnv, jclass cObject)
{
	g_Adapter.Release();
}
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_connect(JNIEnv *pjniEnv, jclass cObject, jstring model, jstring address, jint port){
	OutPutFuncName(__FUNCTION__);
	
	const char *nativeModel = pjniEnv->GetStringUTFChars(model,0);
	const char *nativeAddress = pjniEnv->GetStringUTFChars(address,0);
	BOOL bRet  = FALSE;
//*
	bRet = g_Adapter.Connect_Net(nativeAddress,port);
/**/	
	pjniEnv->ReleaseStringUTFChars(model,nativeModel);
	pjniEnv->ReleaseStringUTFChars(address,nativeAddress);
	
	return bRet;
}

JNIEXPORT void JNICALL Java_com_yumt_zksoft_ZKTCP_disConnect(JNIEnv *pjniEnv, jclass cObject){
	OutPutFuncName(__FUNCTION__);
	g_Adapter.Disconnect();
}
JNIEXPORT jint JNICALL Java_com_yumt_zksoft_ZKTCP_ReadAllGLogData(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber){
	OutPutFuncName(__FUNCTION__);
	BOOL bRet = g_Adapter.ReadAllGLogData(dwMachineNumber);
	return bRet?1:0;
}

	/**
	 * 获取考勤记录，需要先使用ReadAllGLogData读取数据
	 * 
	 * @param dwMachineNumber 机器号
	 * @return json格式的日志 {"log":
									 [
									  {"dwVerifyMode":1,"dwInOutMode":0,"time":"时间"},
									  {"dwVerifyMode":1,"dwInOutMode":0,"time":"时间"}
									  ]
								}<br/>
	 * 其中 dwVerifyMode表示校验模式，1为指纹，0为密码。dwInOutMode为考勤状态，0上班，1下班，2外出，3外出返回，4加班签到，5加班签到。time为记录时间

	 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetGeneralLogDataStr
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber){
 	OutPutFuncName(__FUNCTION__);
	return CStringTojstring(pjniEnv,ZKTCP::GetALLGeneralLogData_withJson(dwMachineNumber));
// 	if(!CheckConnectStatus())return NULL;
// 	g_Adapter.EnableDevice(dwMachineNumber,FALSE);
// 	int nRet = g_Adapter.ReadAllGLogData(dwMachineNumber);
// 	if(nRet <1){
// 		g_Adapter.EnableDevice(dwMachineNumber,TRUE);
// 		printf(_T("ReadAllGLogData Failed. fun:GetGeneralLogDataStr()\n"));
// 		return NULL;
// 	}/**/
// 	CString strRet(_T("{\"log\":["));
// 	CString strEnd(_T("]}"));
// 
// 	long dwEnrollNumber=0;
// 	long dwVerifyMode=0;
// 	long dwInOutMode=0;
// 	BSTR pTimeStr=NULL;
// 	BOOL bRet =FALSE;
// 	int iRetCount = 0;
// 	do{
// 		dwEnrollNumber=0;
// 		dwVerifyMode=0;
// 		dwInOutMode=0;
// 		pTimeStr=NULL;
// 		bRet = g_Adapter.GetGeneralLogDataStr(dwMachineNumber,&(dwEnrollNumber),&dwVerifyMode,&dwInOutMode,&pTimeStr);
// 		if(bRet){
// 			CString strRet_OneLog;
// 			CString sTimeStr(pTimeStr);
// 			strRet_OneLog.Format(_T("{\"dwEnrollNumber\":%d,\"dwVerifyMode\":%d,\"dwInOutMode\":%d,\"time\":\"%s\"},"),
// 				dwEnrollNumber,dwVerifyMode,dwInOutMode,sTimeStr);
// 			strRet+=strRet_OneLog;
// 			printf("GetGeneralLogDataStr[%d]===%s\n",iRetCount,strRet_OneLog);
// 			iRetCount++;
// 		}
// 	}while(bRet);
// 	g_Adapter.EnableDevice(dwMachineNumber,TRUE);
// 
// 	//删除掉最后一个“,” 
// 	if(iRetCount>0)
// 		strRet.Delete(strRet.GetLength()-1);
// 	strRet+=strEnd;
// 	SysFreeString(pTimeStr);
// 	//printf("%s\n",strRet);
// 
// 	return CStringTojstring(pjniEnv,strRet);
}
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_ClearGLog
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber){
	OutPutFuncName(__FUNCTION__);
	if(!CheckConnectStatus())return false;

	BOOL bRet = g_Adapter.ClearGLog(dwMachineNumber);
	return bRet;
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    ReadAllUserID
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_ReadAllUserID
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber){
	OutPutFuncName(__FUNCTION__);
	if(!CheckConnectStatus())return false;
	BOOL bRet = g_Adapter.ReadAllUserID(dwMachineNumber);
	return bRet;
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetAllUserInfo
 * Signature: (J)Ljava/util/List;
 * @return 返回json格式数据，内容如{"userInfo":[
												{"dwEnrollNumber":1,"name":"姓名","pass":"密码","Privilege":1,"enable":1},
												{"dwEnrollNumber":2,"name":"姓名","pass":"密码","Privilege":1,"enable":1}]}
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetAllUserInfo
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber){
	OutPutFuncName(__FUNCTION__);
	
	return CStringTojstring(pjniEnv,ZKTCP::GetAllUserInfo_WithJson(dwMachineNumber));
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    SetUserInfo
 * Signature: (JJLjava/lang/String;Ljava/lang/String;JZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_SetUserInfo
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber, jlong dwEnrollNumber, jstring name, jstring pass, jlong privilege, jboolean enable){
	OutPutFuncName(__FUNCTION__);
	if(!CheckConnectStatus())return false;

	const char *nativeName= pjniEnv->GetStringUTFChars(name,0);

	const char *nativePass= pjniEnv->GetStringUTFChars(pass,0);

	BOOL bRet = g_Adapter.SetUserInfo(dwMachineNumber,dwEnrollNumber,nativeName,nativePass,privilege,enable);

	pjniEnv->ReleaseStringUTFChars(name,nativeName);
	pjniEnv->ReleaseStringUTFChars(pass,nativePass);

	return bRet;
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetUserInfo
 * Signature: (JJ)Ljava/util/List;
 * @return 返回json格式数据，内容如
 {"dwEnrollNumber":1,"name":"姓名","pass":"密码","Privilege":1,"enable":1}
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetUserInfo
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber, jlong deEnrollNumber){
	OutPutFuncName(__FUNCTION__);
	
	return CStringTojstring(pjniEnv,ZKTCP::GetUserInfo_WithJson(dwMachineNumber,deEnrollNumber));
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    SetUserTmpStr
 * Signature: (JJJLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_yumt_zksoft_ZKTCP_SetUserTmpStr
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber, jlong dwEnrollNumber, jlong dwFingerIndex, jstring FingerInfo_by_Base64){
	OutPutFuncName(__FUNCTION__);
	if(!CheckConnectStatus())return false;
	const char *nativeString= pjniEnv->GetStringUTFChars(FingerInfo_by_Base64,0);

	BOOL bRet = g_Adapter.SetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,nativeString);

	pjniEnv->ReleaseStringUTFChars(FingerInfo_by_Base64,nativeString);
	return bRet;
}
/*
 * Class:     com_yumt_zksoft_ZKTCP
 * Method:    GetUserTmpStr
 * Signature: (JJJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_yumt_zksoft_ZKTCP_GetUserTmpStr
(JNIEnv *pjniEnv, jclass cObject, jlong dwMachineNumber, jlong dwEnrollNumber, jlong dwFingerIndex){
	OutPutFuncName(__FUNCTION__);
	CString strRet(_T("{log:[len:0,tempdata:\"\"]}"));
	strRet=_T("");
	if(!CheckConnectStatus())return CStringTojstring(pjniEnv,strRet);	
	BSTR tempData=NULL;
	long tempLength=0;	
	if(g_Adapter.GetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,&tempData,&tempLength)){

		CString strTempData(tempData);	
		strRet=strTempData;
		//strRet.Format(_T("{log:[len:%d,tempdata:\"%s\"]}"),tempLength,strTempData/*_T("fingerdata")*/);					
	}
	if(tempData!=NULL) 
		SysFreeString(tempData);		
	return CStringTojstring(pjniEnv,strRet);
}