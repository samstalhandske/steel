
#include "pch.h"
#include "LayerStack.hpp"

namespace Steel
{
	LayerStack::LayerStack()
	{
		myLayerInsert = myLayers.begin();
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
		myLayerInsert = myLayers.emplace(myLayerInsert, aLayer);
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
			myLayerInsert--;
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
