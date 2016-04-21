#ifndef STORYPOPUP_H
#define STORYPOPUP_H

class StoryPopup : public sf::Sprite
{
private:
	sf::Clock infoRevealClock;//clock that triggers whent o show the next piece of information

	bool allInfoRevealed;//Has all the information been shown yet?

	sf::Texture texture;//texture of story to display

	sf::IntRect textureRect;//Dictates how much of the texture we want to show

	int screenW;//screen width
	int screenH;//screen height

	enum Stories//the possible stories to show
	{
		INTRO,
		SEWER
	};
	int currentStory;//story we want to currently display

public:
	//constructor. Params: screen width and height
	StoryPopup(int sw, int sh);

	//destructor
	~StoryPopup();

	/*
	set the story to display.
	Load the correct texture and reset texture rectangle
	*/
	void SetStory(int story);

	//Check if it is time to show more information/end
	void Update();

	//increase how much of the texture we want to show
	void IncreaseTextureRect();

	bool IsAllInfoRevealed();
};

#endif
