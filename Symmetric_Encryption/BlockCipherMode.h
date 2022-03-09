#pragma once

#include "DES.h"

void DES_CBC_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len);
void DES_CFB_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len);
void DES_OFB_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len);
void DES_CTR_Enc(BYTE* p_text, BYTE* c_text, BYTE* key, UINT64 ctr, int msg_len);

void DES_CBC_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len);
void DES_CFB_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len);
void DES_OFB_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len);
void DES_CTR_Dec(BYTE* c_text, BYTE* d_text, BYTE* key, UINT64 ctr, int msg_len);

void DES_CBC_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE cipher[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++) {
			if (i == 0)
				cipher[j] = p_text[j] ^ IV[j];
			else
				cipher[j] = p_text[j] ^ c_text[j - 8];
		}
		DES_Encryption(&cipher[i * BLOCK_SIZE], &c_text[i * BLOCK_SIZE], key);
	}
}

void DES_CFB_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE cipher[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		if (i == 0)
			DES_Encryption(&IV[i * BLOCK_SIZE], &cipher[i * BLOCK_SIZE], key);
		else
			DES_Encryption(&c_text[i * BLOCK_SIZE - 8], &cipher[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			c_text[j] = p_text[j] ^ cipher[j];
	}
}

void DES_OFB_Enc(BYTE* p_text, BYTE* c_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE cipher[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		if (i == 0)
			DES_Encryption(&IV[i * BLOCK_SIZE], &cipher[i * BLOCK_SIZE], key);
		else
			DES_Encryption(&cipher[i * BLOCK_SIZE - 8], &cipher[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			c_text[j] = p_text[j] ^ cipher[j];
	}
}

void DES_CTR_Enc(BYTE* p_text, BYTE* c_text, BYTE* key, UINT64 ctr, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	int div = 1000000;
	int cnt = 0;
	BYTE cipher[128] = { 0, };
	BYTE ctrStream[128] = { 0, };

	for (int i = 0; i < 7; i++) {
		ctrStream[i] = (unsigned char)(ctr / div);
		ctr -= ctr / div * div;
		div /= 10;
	}

	for (int i = 0; i < block_count; i++) {
		cnt++;
		ctrStream[8] = (unsigned char)cnt;
		DES_Encryption(&ctrStream[i * BLOCK_SIZE], &cipher[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			c_text[j] = p_text[j] ^ cipher[j];
	}
}




void DES_CBC_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE plain[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		DES_Decryption(&c_text[i * BLOCK_SIZE], &plain[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++) {
			if (i == 0)
				d_text[j] = plain[j] ^ IV[j];
			else
				d_text[j] = plain[j] ^ c_text[j - 8];
		}
	}
}

void DES_CFB_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE plain[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		if (i == 0)
			DES_Encryption(&IV[i * BLOCK_SIZE], &plain[i * BLOCK_SIZE], key);
		else
			DES_Encryption(&c_text[i * BLOCK_SIZE - 8], &plain[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			d_text[j] = c_text[j] ^ plain[j];
	}
}

void DES_OFB_Dec(BYTE* c_text, BYTE* d_text, BYTE* IV, BYTE* key, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	BYTE plain[128] = { 0, };

	for (int i = 0; i < block_count; i++) {
		if (i == 0)
			DES_Encryption(&IV[i * BLOCK_SIZE], &plain[i * BLOCK_SIZE], key);
		else
			DES_Encryption(&plain[i * BLOCK_SIZE - 8], &plain[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			d_text[j] = c_text[j] ^ plain[j];
	}
}

void DES_CTR_Dec(BYTE* c_text, BYTE* d_text, BYTE* key, UINT64 ctr, int msg_len) {
	int block_count = (msg_len % BLOCK_SIZE) ? (msg_len / BLOCK_SIZE + 1) : (msg_len / BLOCK_SIZE);
	int div = 1000000;
	int cnt = 0;
	BYTE plain[128] = { 0, };
	BYTE ctrStream[128] = { 0, };

	for (int i = 0; i < 7; i++) {
		ctrStream[i] = (unsigned char)(ctr / div);
		ctr -= ctr / div * div;
		div /= 10;
	}

	for (int i = 0; i < block_count; i++) {
		cnt++;
		ctrStream[8] = (unsigned char)cnt;
		DES_Encryption(&ctrStream[i * BLOCK_SIZE], &plain[i * BLOCK_SIZE], key);

		for (int j = i * BLOCK_SIZE; j < i * BLOCK_SIZE + 8; j++)
			d_text[j] = c_text[j] ^ plain[j];
	}
}