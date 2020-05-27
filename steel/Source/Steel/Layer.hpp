
#pragma once

#include "Steel/Core.hpp"
#include "Steel/Events/Event.hpp"

namespace Steel
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return myDebugName; }

	protected:
		std::string myDebugName;
	};
}