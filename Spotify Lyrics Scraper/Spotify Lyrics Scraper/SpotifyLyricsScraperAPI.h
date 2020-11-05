/*
	Spotify Lyrics Scraper API

	MADE BY STEPHEN ASUNCION
	Github: https://github.com/stephenasuncionDEV
*/

#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <comdef.h>
#include <algorithm>
#include <vector>

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "Wtsapi32.lib")
#pragma comment (lib, "Iphlpapi.lib")

using namespace std;

#pragma once
class SpotifyLyricsScraperAPI
{
public:
	INT waitForSpotify();
	INT initialize(BOOL isPremium, INT database);
	string getLyrics();
	VOID reset();

private:
	INT procID;
	HWND procHWND;
	const wchar_t* exeName = L"Spotify.exe";
	DWORD findProcessId(const wchar_t* exename);
	BOOL isProcessRunning(const wchar_t* processName);
	string getWindowTitle();
	string windowTitle;
	string artist;
	string song;
	string featuring;
	string currentsong;
	string lyricslink;
	string lyrics;
	bool premiumBOOL;
	INT procedure;
	VOID removeString(string& s, string& p);
};
