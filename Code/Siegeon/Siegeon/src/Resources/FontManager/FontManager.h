#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>


namespace FontManager
{
	class FontManager
	{
	public:

		static FontManager& getInstance();

		std::vector<std::string> getListOfFonts();

		sf::Font* getFont(std::string fontName);


	private:

		std::map<std::string, std::unique_ptr<sf::Font> > _fonts;


		FontManager();
		~FontManager();

		FontManager(const FontManager&) = delete;
		FontManager& operator=(const FontManager&) = delete;
		FontManager(FontManager&&) = delete;
		FontManager& operator=(FontManager&&) = delete;

	};
}
