#ifndef COMBATMENU_H
#define COMBATMENU_H

class CombatMenu
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
public:
	/*constructor*/
	CombatMenu();
	/*destructor*/
	~CombatMenu();

	/*Draw all elements of the menu*/
	void Draw(sf::RenderTarget& window);
};

#endif
