#pragma once

#include "Widget.h"


namespace UI
{
	class WidgetGroup : public Widget
	{
	public:

		WidgetGroup();
		WidgetGroup(const WidgetGroup& other);
		~WidgetGroup();

		void update(Core::Entities::WindowEventData& windowEvent) override;
		void render(sf::RenderWindow& window) override;
		void construct(int32_t windowX, int32_t windowY, sf::Font* font) override;
		sf::FloatRect boundingBox() override;

		void copyState(const WidgetGroup& other);

		void addWidget(std::shared_ptr<Widget> widget);

		void setHidden(bool enabled);
		bool getHidden() const;


	private:

		bool _hidden;
		std::vector<std::shared_ptr<Widget>> _widgets;

	};
}
