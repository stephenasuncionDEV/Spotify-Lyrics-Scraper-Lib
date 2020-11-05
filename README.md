# Spotify-Lyrics-Scraper-API
Get spotify's current song and extract lyrics from a website.

<img src="https://i.imgur.com/UN6jR4R.png" width="600" height="400" />

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

>Note: This API uses CURL Library      Get [CURL HERE!!!](https://curl.haxx.se/)
