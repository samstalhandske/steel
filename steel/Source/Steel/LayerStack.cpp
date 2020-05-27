
#include "pch.h"
#include "LayerStack.hpp"

namespace Steel
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : myLayers)
		{
			if(layer)
				delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* aLayer)
	{
		myLayers.emplace(myLayers.begin() + myLayerInsertIndex, aLayer);
		myLayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* aOverlay)
	{
		myLayers.emplace_back(aOverlay);
	}

	void LayerStack::PopLayer(Layer* aLayer)
	{
		auto it = std::find(myLayers.begin(), myLayers.end(), aLayer);
		if (it != myLayers.end())
		{
			myLayers.erase(it);
			myLayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* aOverlay)
	{
		auto it = std::find(myLayers.begin(), myLayers.end(), aOverlay);
		if (it != myLayers.end())
		{
			myLayers.erase(it);
		}
	}
}
