
#pragma once

#include "Steel/Events/Event.hpp"
#include "Steel/Events/ApplicationEvent.h"
#include "Steel/Events/KeyEvent.hpp"
#include "Steel/Events/MouseEvent.hpp"


#include <string>

namespace Steel
{
	class STEEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return myDebugName; }

	protected:
		std::string myDebugName;
	};
}