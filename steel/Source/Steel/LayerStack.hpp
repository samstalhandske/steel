#pragma once

#include "Steel/Core.hpp"
#include "Layer.hpp"

#include <vector>

namespace Steel
{
	class STEEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* aLayer);
		void PushOverlay(Layer* aOverlay);
		void PopLayer(Layer* aLayer);
		void PopOverlay(Layer* aOverlay);

		std::vector<Layer*>::iterator begin()	{ return myLayers.begin();	}
		std::vector<Layer*>::iterator end()		{ return myLayers.end();	}

	private:
		std::vector<Layer*> myLayers;
		std::vector<Layer*>::iterator myLayerInsert;

	};
}