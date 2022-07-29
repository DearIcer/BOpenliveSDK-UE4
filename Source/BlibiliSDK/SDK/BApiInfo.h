#pragma once

#include <string>
#include <vector>
#include "Tool/json.hpp"
#include <stdint.h>

//��֤�������Ϣ
struct AuthInfo
{
	std::string accessKeyId;
	std::string accessKeySecret;
	std::string appId;
	std::string code;
};

struct ApiInfo
{
	int64_t roomId;                   // ����id
	int64_t uid;                      // ����uid
	std::string uface;                // ����ͷ��
	std::string uname;                // ��������
	std::string gameId;               // ��Ϸid
	std::string authBody;             // ��֤�õ�
	std::vector<std::string> wssLink; // wss���õĵ�ַ

	explicit ApiInfo(const nlohmann::json& jsonData);
	ApiInfo() = default;
	void setValue(const nlohmann::json& jsonData);
};

// ��Ļ��Ϣ
struct DanmaData
{
	int64_t uid;                    // �û�UID
	int64_t timestamp;              // ��Ļ����ʱ���뼶ʱ���
	int64_t room_id;                // ��Ļ���յ�ֱ����
	int64_t guard_level;            // ��Ӧ����󺽺��ȼ�
	int64_t fans_medal_level;       // ��Ӧ����ѫ����Ϣ
	FString msg_id;             // ��ϢΨһid
	bool fans_medal_wearing_status; // ��ǰ����ķ�˿ѫ�����״̬
	FString uname;              // �û��ǳ�
	FString uface;              // �û�ͷ��
	FString msg;                // ��Ļ����
	FString fans_medal_name;    // ��˿ѫ����

	explicit DanmaData(const nlohmann::json& jsonData);
	DanmaData() = default;
	void setValue(const nlohmann::json& jsonData);
};

struct UserInfo
{
	int64_t uid;       // ��������uid
	FString uname; // ���������ǳ�
	FString uface; // ��������ͷ��
};

// ����
struct GiftData
{
	int64_t room_id;                // �����
	int64_t uid;                    // �����û�UID
	int64_t gift_id;                // ����id(ä��:��������id)
	int64_t gift_num;               // ���͵�������
	int64_t price;                  // ֧�����(1000 = 1Ԫ = 10���),ä��:�������ߵļ�ֵ
	int64_t fans_medal_level;       // ʵ�������˵�ѫ����Ϣ
	int64_t guard_level;            // �󺽺��ȼ�
	int64_t timestamp;              // ����ʱ���뼶ʱ���
	bool paid;                      // �Ƿ��Ǹ��ѵ���
	bool fans_medal_wearing_status; // ��ǰ����ķ�˿ѫ�����״̬
	FString uname;              //�����û��ǳ�
	FString uface;              // �����û�ͷ��
	FString gift_name;          // ������(ä��:����������)
	FString fans_medal_name;    //��˿ѫ����
	FString msg_id;             // ��ϢΨһid
	UserInfo anchor_info;           // ������Ϣ

	explicit GiftData(const nlohmann::json& jsonData);
	GiftData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// �󺽺�
struct GuardBuyData
{
	int64_t guard_level;            // �󺽺��ȼ�
	int64_t guard_num;              // �󺽺�����
	int64_t fans_medal_level;       // ��˿ѫ�µȼ�
	int64_t room_id;                // �����
	int64_t timestamp;              // �Ͻ�ʱ���뼶ʱ���
	bool fans_medal_wearing_status; // ����ķ�˿ѫ�����״̬
	FString guard_unit;         // �󺽺���λ
	FString fans_medal_name;    // ��˿ѫ����
	FString msg_id;             // ��ϢΨһid
	UserInfo user_info;             // �û���Ϣ
	explicit GuardBuyData(const nlohmann::json& jsonData);
	GuardBuyData() = default;
	void setValue(const nlohmann::json& jsonData);
};

// ��������
struct SuperChatData
{
	int64_t room_id;                // ֱ����id
	int64_t uid;                    // �����û�UID
	int64_t message_id;             // ����id(��س����³���������Ҫ)
	int64_t rmb;                    // ֧�����(Ԫ)
	int64_t timestamp;              // ����ʱ���뼶
	int64_t start_time;             // ��Ч��ʼʱ��
	int64_t end_time;               // ��Ч����ʱ��
	int64_t guard_level;            // ��Ӧ����󺽺��ȼ�
	int64_t fans_medal_level;       // ��Ӧ����ѫ����Ϣ
	bool fans_medal_wearing_status; // ��ǰ����ķ�˿ѫ�����״̬
	FString uname;              // ������û��ǳ�
	FString uface;              // �����û�ͷ��
	FString message;            // ��������
	FString fans_medal_name;    // ��Ӧ����ѫ������
	FString msg_id;             // ��ϢΨһid

	explicit SuperChatData(const nlohmann::json& jsonData);
	SuperChatData() = default;
	void setValue(const nlohmann::json& jsonData);
};

struct SuperChatDelData
{
	int64_t room_id;                  // ֱ����id
	FString msg_id;               // ����id
	std::vector<int64_t> message_ids; // ��ϢΨһid

	explicit SuperChatDelData(const nlohmann::json& jsonData);
	SuperChatDelData() = default;
	void setValue(const nlohmann::json& jsonData);
};

enum EErrorString {
	ERROR_DATA_INVAILD,				//��Ч����
	ERROR_WEBSOCKET_CONNECT,		//websocket����ʱ�����쳣
	ERROR_WEBSOCKET_DISCONNECT,		//websocket����
};