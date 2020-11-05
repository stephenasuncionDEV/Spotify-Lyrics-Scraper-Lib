#include <Windows.h>
#include <iostream>
#include "Tools.h"
#include "SpotifyLyricsScraperAPI.h"

using namespace std;

SpotifyLyricsScraperAPI SpotifyScraper;

void GetLyrics() 
{
	SpotifyScraper.waitForSpotify();
	SpotifyScraper.initialize(true, 1);
	cout << SpotifyScraper.getLyrics() << endl;
	for (;;)
		SpotifyScraper.reset();
}

int main() 
{
	cout << Tools().Color(12, "Stephen Asuncion - DEV") << endl;
	cout << endl;

	GetLyrics();

	for (;;) {}
}