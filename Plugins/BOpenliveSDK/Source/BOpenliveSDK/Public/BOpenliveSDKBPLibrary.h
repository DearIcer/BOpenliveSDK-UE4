// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BApi.h"
#include "BApiInfo.h"
#include "BWebsocket.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BOpenliveSDKBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UBOpenliveSDKBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	static UBOpenliveSDKBPLibrary* GetInstancePtr();
	
	void init(const std::string &accessKeyId, const std::string &accessKeySecret, const std::string &appId, const std::string &code);
	void CreateWebsocket();
	static void WebSocketError(EErrorString error);
	static void WebSocketMessage(std::string message);
	void Start();
	static void OnStartInteractivePlay(bool isSuccess, const std::string& message);
	void timerEvent();
	static void OnTimerEvent(bool isSuccess, const std::string & response);

private:
	static UBOpenliveSDKBPLibrary* s_UBSdk;
	std::string m_accessKeyId;     // ������id
	std::string m_accessKeySecret; // ��������Կ
	std::string m_appId;           // ��Ŀid
	std::string m_code;            // ���������

	int timerId; // ��ʱ��id

	ApiInfo apiInfo;

	DanmaData danmaData;               // ��Ļ
	GiftData giftData;                 // ����
	GuardBuyData guardBuyData;         // �󺽺�
	SuperChatData superChatData;       // ��������
	SuperChatDelData superChatDelData; // ��ʱ�ĸ�������id

	UBWebsocket *danMuQWebsocket = nullptr;
	BApi *bapi = nullptr;
	FTimerHandle m_beatTimer;
};
