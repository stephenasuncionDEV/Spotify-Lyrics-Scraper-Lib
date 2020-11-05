# Spotify-Lyrics-Scraper-API :musical_note:
Get spotify's current song and extract lyrics from a website.

-> This API extracts lyrics from https://www.azlyrics.com/. Usage of azlyrics.com content by any third-party lyrics provider is prohibited by their licensing agreement. This API is for educational purposes only.

<img src="https://i.ibb.co/X7XDzsH/Screenshot-1.png"/>

Coded in C++

Usage:
```
SpotifyLyricsScraperAPI SpotifyScraper;

void GetLyrics() 
{
	SpotifyScraper.waitForSpotify();
	SpotifyScraper.initialize(true, 1);
	cout << SpotifyScraper.getLyrics() << endl;
	for (;;)
		SpotifyScraper.reset();
}
```

## SpotifyScraper.initialize Parameters

| Parameter  | Meaning |
| ------------- | ------------- |
| BOOL isPremium  | true if you have spotify premium, false otherwise  |
| INT database  | 1 to use azlyrics.com (api currently has 1 database for now)  |


>Note: This API uses CURL Library      Get [CURL HERE!!!](https://curl.haxx.se/)
