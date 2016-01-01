#pragma once

struct ManipulationBuffer {
	const _SOCKADDR_INET *ClientAddress;   // 4/8 bytes;
	const _SOCKADDR_INET *ListeningAddress;// 4/8 bytes;
	const _SOCKADDR_INET *OLAddress;       // 4/8 bytes;
	const _SOCKADDR_INET *ServerAddress;   // 4/8 bytes;
	unsigned long BufferSize;              // 4 bytes;
	unsigned long BytesReceived;           // 4 bytes;
	INT_PTR Reserved;                      // 4/8 bytes;
	char Buffer[];                         // Variable bytes; see BufferSize;
};

class PluginBase
{
public:
	PluginBase();
	~PluginBase();
	AFX_EXT_CLASS const WCHAR *GetPluginType();
	AFX_EXT_CLASS void GetPluginTypeCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow);
	AFX_EXT_CLASS const WCHAR *GetPluginName();
	AFX_EXT_CLASS void GetPluginNameCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow);
	AFX_EXT_CLASS const WCHAR *GetPluginDescription();
	AFX_EXT_CLASS void GetPluginDescriptionCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow);
	AFX_EXT_CLASS const WCHAR *GetPluginVersion();
	AFX_EXT_CLASS void GetPluginVersionCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow);
	AFX_EXT_CLASS ManipulationBuffer *ProcessUpstreamData(ManipulationBuffer *InBuffer);
	AFX_EXT_CLASS void CALLBACK ProcessUpstreamDataCmd(HINSTANCE hinst, LPSTR InBuffer, int nCmdShow);
	AFX_EXT_CLASS ManipulationBuffer *ProcessDownstreamData(ManipulationBuffer *InBuffer);
	AFX_EXT_CLASS void CALLBACK ProcessDownstreamDataCmd(HINSTANCE hinst, LPSTR InBuffer, int nCmdShow);
private:
	const WCHAR *GetPluginTypeInternal();
	const WCHAR *GetPluginNameInternal();
	const WCHAR *GetPluginVersionInternal();
	const WCHAR *GetPluginDescriptionInternal();
	// ProcessUpstreamDataInternal() and ProcessDownstreamDataInternal() are where the actual processing takes place;
	ManipulationBuffer *ProcessUpstreamDataInternal(ManipulationBuffer *InBuffer);
	ManipulationBuffer *ProcessDownstreamDataInternal(ManipulationBuffer *InBuffer);
};
