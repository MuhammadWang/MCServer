
// Protocol132.h

// Interfaces to the cProtocol132 class representing the release 1.3.2 protocol (#39)





#pragma once

#include "Protocol125.h"
#include "CryptoPP/modes.h"
#include "CryptoPP/aes.h"





class cProtocol132 :
	public cProtocol125
{
	typedef cProtocol125 super;
public:

	cProtocol132(cClientHandle * a_Client);
	
	// DEBUG:
	virtual ~cProtocol132();

	/// Called when client sends some data:
	virtual void DataReceived(const char * a_Data, int a_Size) override;
	
	// Sending commands:
	virtual void SendBlockAction  (int a_BlockX, int a_BlockY, int a_BlockZ, char a_Byte1, char a_Byte2, BLOCKTYPE a_BlockType) override;
	virtual void SendBlockChange  (int a_BlockX, int a_BlockY, int a_BlockZ, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta) override;
	virtual void SendChunkData    (int a_ChunkX, int a_ChunkZ, cChunkDataSerializer & a_Serializer) override;
	virtual void SendDestroyEntity(const cEntity & a_Entity) override;
	virtual void SendLogin        (const cPlayer & a_Player) override;
	virtual void SendPlayerSpawn  (const cPlayer & a_Player) override;
	virtual void SendSpawnMob     (const cMonster & a_Mob) override;
	virtual void SendUnloadChunk  (int a_ChunkX, int a_ChunkZ) override;

	// DEBUG:
	virtual void SendKeepAlive  (int a_PingID) override;

	/// Handling of the additional packets:
	virtual int ParsePacket(unsigned char a_PacketType) override;
	
	// Modified packets:
	virtual int ParseBlockPlace     (void) override;
	virtual int ParseHandshake      (void) override;
	virtual int ParseLogin          (void) override;
	virtual int ParsePlayerAbilities(void) override;
	
	// New packets:
	virtual int ParseClientStatuses       (void);
	virtual int ParseEncryptionKeyResponse(void);
	virtual int ParseLocaleViewDistance   (void);
	
protected:
	bool m_IsEncrypted;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption m_Decryptor;
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption m_Encryptor;
	
	// DEBUG:
	AString m_DataToSend;
	int m_CurrentIn, m_CurrentOut;
	int m_EncIn, m_EncOut;
	
	virtual void SendData(const char * a_Data, int a_Size) override;
	
	// DEBUG:
	virtual void Flush(void) override;
	
	// Items in slots are sent differently
	virtual void WriteItem(const cItem & a_Item) override;
	
	/// Decrypts the key and nonce, checks nonce, starts the symmetric encryption
	void HandleEncryptionKeyResponse(const AString & a_EncKey, const AString & a_EncNonce);
	
	/// Starts the symmetric encryption with the specified key
	void StartEncryption(const byte * a_Key);
} ;




