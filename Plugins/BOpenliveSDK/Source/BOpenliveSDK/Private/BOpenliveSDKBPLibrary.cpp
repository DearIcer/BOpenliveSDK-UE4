// Copyright Epic Games, Inc. All Rights Reserved.

#include "BOpenliveSDKBPLibrary.h"
#include "BOpenliveSDK.h"

UBOpenliveSDKBPLibrary*	UBOpenliveSDKBPLibrary::s_UBSdk = nullptr;
UBOpenliveSDKBPLibrary::UBOpenliveSDKBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}


UBOpenliveSDKBPLibrary* UBOpenliveSDKBPLibrary::GetInstancePtr()
{
	if (s_UBSdk == nullptr)
	{
		s_UBSdk = NewObject<UBOpenliveSDKBPLibrary>();
		s_UBSdk->AddToRoot();
	}
	return s_UBSdk;
}

void UBOpenliveSDKBPLibrary::init(const std::string& accessKeyId, const std::string& accessKeySecret, const std::string& appId,
                 const std::string& code)
{
	m_accessKeyId = accessKeyId;
	m_accessKeySecret = accessKeySecret;
	m_appId = appId;
	m_code = code;
	bapi = new BApi(accessKeyId, accessKeySecret);
}

void UBOpenliveSDKBPLibrary::CreateWebsocket()
{
	if (danMuQWebsocket == nullptr) {
		danMuQWebsocket = NewObject<UBWebsocket>(this);
		danMuQWebsocket->AddToRoot();
	}
	danMuQWebsocket->init(apiInfo, WebSocketError, WebSocketMessage);
}

void UBOpenliveSDKBPLibrary::WebSocketError(EErrorString error)
{

}

void UBOpenliveSDKBPLibrary::WebSocketMessage(std::string message)
{
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(message);
		std::string cmd = jsonData["cmd"].get<std::string>();
		if (cmd.find("LIVE_OPEN_PLATFORM_DM") != std::string::npos) {
			GetInstancePtr()->danmaData.setValue(jsonData["data"]);
			FString uname = GetInstancePtr()->danmaData.uname;
			FString msg = GetInstancePtr()->danmaData.msg;
			UE_LOG(LogTemp, Log, TEXT("��Ļ�����ߣ�%s, ��Ļ���ݣ�%s"), *uname, *msg);
			//emit ReceivedDanmaKu(this->danmaData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SEND_GIFT") != std::string::npos) {
			GetInstancePtr()->giftData.setValue(jsonData["data"]);
			//emit ReceivedGift(this->giftData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT") != std::string::npos) {
			GetInstancePtr()->superChatData.setValue(jsonData["data"]);
			//emit ReceivedSuperChat(this->superChatData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_SUPER_CHAT_DEL") != std::string::npos) {
			GetInstancePtr()->superChatDelData.setValue(jsonData["data"]);
			//emit ReceivedSuperChatDel(this->superChatDelData);
		} else if (cmd.find("LIVE_OPEN_PLATFORM_GUARD") != std::string::npos) {
			GetInstancePtr()->guardBuyData.setValue(jsonData["data"]);
			//emit ReceivedGuardBuy(this->guardBuyData);
		}
	}
	catch (nlohmann::detail::exception& e)
	{
		UE_LOG(LogTemp, Log, TEXT("json�����쳣�������룺%d"), e.id);
	}
}

void UBOpenliveSDKBPLibrary::Start()
{
	bapi->StartInteractivePlay(m_code, m_appId, OnStartInteractivePlay);
}

void UBOpenliveSDKBPLibrary::OnStartInteractivePlay(bool isSuccess, const std::string &message)
{
	if(isSuccess == false)
	{
		//TODO:notify error
		return;
	}
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(message);
		assert(jsonData["code"].get<int64_t>() == 0);
		FString messageStr(UTF8_TO_TCHAR(message.c_str()));
		UE_LOG(LogTemp, Log, TEXT("message is %s"), *messageStr);
		int64_t code = jsonData["code"].get<int64_t>();
		if (code != 0) {
			//TODO:notify error
			return;
		}
		UWorld* world = GEngine->GameViewport->GetWorld();
		if (world == nullptr) {
			UE_LOG(LogTemp, Log, TEXT("UWorld is null"));
		}
		world->GetTimerManager().SetTimer(GetInstancePtr()->m_beatTimer, GetInstancePtr(), &UBOpenliveSDKBPLibrary::timerEvent, 1, true); // ���߼��ͷ���������
		GetInstancePtr()->apiInfo.setValue(jsonData["data"]);
		GetInstancePtr()->CreateWebsocket();
	}
	catch (nlohmann::detail::exception& e)
	{
		UE_LOG(LogTemp, Log, TEXT("json�����쳣�������룺%d"), e.id);
	}
}

void UBOpenliveSDKBPLibrary::timerEvent()
{
	static int count = 0;
	// ����ʹ�õ���19�뷢һ��������
	if (count >= 19) {
		bapi->HeartBeatInteractivePlay(apiInfo.gameId, &UBOpenliveSDKBPLibrary::OnTimerEvent);
		count = 0;
	} else {
		++count;
	}
	// ÿ�붼���ж�websocket�Ƿ�Ͽ��ˣ��Ͽ��Ļ�������
	if (!danMuQWebsocket->getIsConnected()) {
		UE_LOG(LogTemp, Log, TEXT("websocket re connect"));
		CreateWebsocket();
	}
}

void UBOpenliveSDKBPLibrary::OnTimerEvent(bool isSuccess, const std::string & response)
{
	if(isSuccess)
	{
		try
		{
			nlohmann::json jsonData = nlohmann::json::parse(response);
			if (jsonData.find("code") != jsonData.end()) {
				if (jsonData["code"].get<int64_t>() == 0) {
					UE_LOG(LogTemp, Log, TEXT("������������Ӧ�ɹ�"));
				} else {
					UE_LOG(LogTemp, Log, TEXT("������������Ӧʧ�ܣ��п����ǳ�ʱ��"));
					// ����ֱ�����һ�û���Թ������ܻ���bug
					GetInstancePtr()->Start();
				}
			} else {
				UE_LOG(LogTemp, Log, TEXT(""));
			}
		}
		catch (nlohmann::detail::exception& e)
		{
			UE_LOG(LogTemp, Log, TEXT("json�����쳣�������룺%d"), e.id);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("����������ʧ��"));
		GetInstancePtr()->Start();
	}
}



