#include <filesystem>

#include "FontManager.h"
#include "Constants.h"


namespace FontManager
{
	FontManager& FontManager::getInstance()
	{
		static FontManager instance;

		return instance;
	}

	std::vector<std::string> FontManager::getListOfFonts()
	{
		std::vector<std::string> fontNames;

		for (auto& name_font : _fonts)
		{
			fontNames.push_back(name_font.first);
		}

		return fontNames;
	}

	sf::Font* FontManager::getFont(std::string fontName)
	{
		if (!_fonts.count(fontName))
		{
			throw std::invalid_argument("FontManager::getFont: Font " + fontName + " not found");
		}

		return _fonts[fontName].get();
	}

	FontManager::FontManager()
	{
		for (const auto& entry : std::filesystem::directory_iterator(FONTS_PATH))
		{
			if (entry.is_directory())
			{
				continue;
			}

			std::string filePath = entry.path().string();
			std::string fileName = entry.path().stem().string();
			std::string fileExtension = entry.path().extension().string();

			if (fileExtension != ".ttf")
			{
				continue;
			}

			sf::Font* font = new sf::Font();
			if (font->loadFromFile(filePath))
			{
				_fonts[fileName] = std::unique_ptr<sf::Font>(font);
			}
			else
			{
				delete font;
			}
		}

		if (_fonts.empty())
		{
			throw std::exception("FontManager::FontManager: No fonts found");
		}
	}

	FontManager::~FontManager()
	{

	}
}