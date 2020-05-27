
#pragma once


namespace Steel
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
		//DX12 osv
	};

	class Renderer
	{
	public:
		inline static void SetAPI(RendererAPI anAPI) { myAPI = anAPI; }
		inline static RendererAPI GetAPI() { return myAPI; }

	private:
		static RendererAPI myAPI;
	};
}