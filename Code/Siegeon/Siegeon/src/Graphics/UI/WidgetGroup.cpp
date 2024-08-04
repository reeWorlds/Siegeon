#include "WidgetGroup.h"

#include <limits>


namespace UI
{
	WidgetGroup::WidgetGroup()
	{
		type = WidgetType::WIDGETGROUP;

		setHidden(false);
	}

	WidgetGroup::WidgetGroup(const WidgetGroup& other)
	{
		copyState(other);
	}

	WidgetGroup::~WidgetGroup() { }

	void WidgetGroup::update(Core::Entities::WindowEventData& windowEvent)
	{
		for (auto& widget : _widgets)
		{
			widget->update(windowEvent);
		}
	}

	void WidgetGroup::render(sf::RenderWindow& window)
	{
		for (auto& widget : _widgets)
		{
			widget->render(window);
		}
	}

	void WidgetGroup::construct(int32_t windowX, int32_t windowY, sf::Font* font)
	{
		for (auto& widget : _widgets)
		{
			widget->construct(windowX, windowY, font);
		}
	}

	sf::FloatRect WidgetGroup::boundingBox()
	{
		if (_widgets.size() == 0)
		{
			constexpr float minValue = std::numeric_limits<float>::min();

			return sf::FloatRect(minValue, minValue, 0.0, 0.0);
		}

		sf::FloatRect boundingBox = _widgets[0]->boundingBox();

		for (auto& widget : _widgets)
		{
			sf::FloatRect nextBB = widget->boundingBox();

			float maxX = std::max(boundingBox.left + boundingBox.width, nextBB.left + nextBB.width);
			float maxY = std::max(boundingBox.top + boundingBox.height, nextBB.top + nextBB.height);

			boundingBox.left = std::min(boundingBox.left, nextBB.left);
			boundingBox.top = std::min(boundingBox.top, nextBB.top);
			boundingBox.width = maxX - boundingBox.left;
			boundingBox.height = maxY - boundingBox.top;
		}

		return boundingBox;
	}

	void WidgetGroup::copyState(const WidgetGroup& other)
	{
		_hidden = other._hidden;
	}

	void WidgetGroup::addWidget(std::shared_ptr<Widget> widget)
	{
		_widgets.push_back(widget);
	}

	void WidgetGroup::setHidden(bool enabled)
	{
		_hidden = enabled;
	}

	bool WidgetGroup::getHidden() const
	{
		return _hidden;
	}
}
