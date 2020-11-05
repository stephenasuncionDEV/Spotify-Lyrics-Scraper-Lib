#include "SpotifyLyricsScraperAPI.h"

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp);

INT SpotifyLyricsScraperAPI::waitForSpotify() {
	while (!isProcessRunning(exeName)) {}
	return true;
}

INT SpotifyLyricsScraperAPI::initialize(BOOL isPremium, INT database) {
	procID = findProcessId(exeName);
	string premium = isPremium ? "Spotify Premium" : "Spotify";
	premiumBOOL = isPremium;

	while (!procHWND) { procHWND = FindWindowA(NULL, &premium[0]); }

	if (procHWND) {
		getWindowTitle();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Window Title: " << windowTitle << endl;

		while (windowTitle == premium) { getWindowTitle(); }

		getWindowTitle();

		artist = windowTitle.substr(0, windowTitle.find_first_of("-") - 1);
		song = windowTitle.substr(windowTitle.find_first_of("-") + 2, windowTitle.length());

		cout << "Artist: " << artist << endl;
		cout << "Title: " << song << endl;

		currentsong = windowTitle;
		
		/*
			For AZLyrics.com
		*/

		vector<char> restrictedChars = { ' ','.','\'','/','-' };
		vector<string> restrictedChars2 = { "<div>", "</div>", "<br>" };

		if (database == 1) {
			string artistTemp = artist;
			artistTemp.erase(std::remove(artistTemp.begin(), artistTemp.end(), ' '), artistTemp.end());
			std::transform(artistTemp.begin(), artistTemp.end(), artistTemp.begin(), ::tolower);

			string songTemp = song;
			for (int n = 0; n < song.length(); n++) {
				if (songTemp.at(n) == '(') {
					songTemp = song.substr(0, n - 1);
				}
			}
			for (int n2 = 0; n2 < restrictedChars.size(); n2++) {
				songTemp.erase(std::remove(songTemp.begin(), songTemp.end(), restrictedChars[n2]), songTemp.end());
			}
			std::transform(songTemp.begin(), songTemp.end(), songTemp.begin(), ::tolower);

			lyricslink = "https://www.azlyrics.com/lyrics/" + artistTemp + "/" + songTemp + ".html";

			cout << lyricslink << endl;

			CURL* curl;
			CURLcode res;
			std::string readBuffer;

			curl = curl_easy_init();
			if (curl) {
				curl_easy_setopt(curl, CURLOPT_URL, lyricslink);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
				res = curl_easy_perform(curl);
				curl_easy_cleanup(curl);

				size_t s = readBuffer.find("<!-- Usage of azlyrics.com content by any third-party lyrics provider is prohibited by our licensing agreement. Sorry about that. -->");
				size_t e = readBuffer.find("<!-- MxM banner -->", s);

				lyrics = readBuffer.substr(s + 133, e - s - 133);

				for (int n3 = 0; n3 < restrictedChars2.size(); n3++) {
					removeString(lyrics, restrictedChars2[n3]);
				}
			}
		}
	}
}

string SpotifyLyricsScraperAPI::getLyrics() {
	while (lyrics.empty()) { }
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	procedure = 1;
	return lyrics;
}

VOID SpotifyLyricsScraperAPI::reset() {
	while (getWindowTitle() == currentsong) {}
	system("cls");
	procedure = 0;
	lyrics = "";
	initialize(premiumBOOL, 1);
	cout << getLyrics() << endl;
}

VOID SpotifyLyricsScraperAPI::removeString(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p);
		i != string::npos;
		i = s.find(p))
		s.erase(i, n);
}

string SpotifyLyricsScraperAPI::getWindowTitle() {
	int bufsize = GetWindowTextLength(procHWND) + 1;
	LPWSTR title = new WCHAR[bufsize];
	GetWindowText(procHWND, title, bufsize);

	wstring tempWstring(title);
	string tempString(tempWstring.begin(), tempWstring.end());
	windowTitle = tempString;

	return windowTitle;
}

DWORD SpotifyLyricsScraperAPI::findProcessId(const wchar_t* exename)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE) {

	}

	PROCESSENTRY32 pe32{ 0 };
	pe32.dwSize = sizeof(pe32);

	_bstr_t exefile(pe32.szExeFile);

	BOOL status = Process32First(hSnap, &pe32);
	while (status) {
		if (!_wcsicmp(pe32.szExeFile, exename))
		{
			CloseHandle(hSnap);
			return pe32.th32ProcessID;
		}
		status = Process32Next(hSnap, &pe32);
	}
	CloseHandle(hSnap);
	return 0;
}

BOOL SpotifyLyricsScraperAPI::isProcessRunning(const wchar_t* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_wcsicmp(entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}