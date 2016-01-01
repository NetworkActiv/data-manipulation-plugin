#include "stdafx.h"
#include "PluginBase.h"
#include "NA_Plugin_DataManipulation.h"

PluginBase::PluginBase()
{
}

PluginBase::~PluginBase()
{
}

const WCHAR * PluginBase::GetPluginType()
{
	return GetPluginTypeInternal();
}

void PluginBase::GetPluginTypeCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow)
{
	MessageBox(NULL, GetPluginTypeInternal(), L"My Type Is", MB_OK);
}

const WCHAR * PluginBase::GetPluginName()
{
	return GetPluginNameInternal();
}

void PluginBase::GetPluginNameCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow)
{
	MessageBox(NULL, GetPluginNameInternal(), L"My Name Is", MB_OK);
}

const WCHAR * PluginBase::GetPluginDescription()
{
	return GetPluginDescriptionInternal();
}

void PluginBase::GetPluginDescriptionCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow)
{
	MessageBox(NULL, GetPluginDescriptionInternal(), L"My Description Is", MB_OK);
}

const WCHAR * PluginBase::GetPluginVersion()
{
	return GetPluginVersionInternal();
}

void PluginBase::GetPluginVersionCmd(HINSTANCE hinst, LPSTR IPAddress, int nCmdShow)
{
	MessageBox(NULL, GetPluginVersionInternal(), L"My Version Is", MB_OK);
}

ManipulationBuffer * PluginBase::ProcessUpstreamData(ManipulationBuffer * InBuffer)
{
	return ProcessUpstreamDataInternal(InBuffer);
}

void PluginBase::ProcessUpstreamDataCmd(HINSTANCE hinst, LPSTR InBuffer, int nCmdShow)
{
	std::string InString = std::string(InBuffer);
	ManipulationBuffer *NewBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
	if (NewBuffer == NULL) {
		MessageBox(NULL, L"Error: Could not allocate manipulation buffer!", L"Allocation error", MB_OK | MB_ICONERROR);
		return;
	}
	memset(NewBuffer, 0, sizeof(NewBuffer));
	NewBuffer->BytesReceived = InString.length();
	NewBuffer->BufferSize = InString.length();
	memcpy(NewBuffer->Buffer, InString.c_str(), InString.length());
	ManipulationBuffer *ReturnValue = ProcessUpstreamDataInternal(NewBuffer);
	if (ReturnValue == NULL) {
		MessageBox(NULL, L"The client is to be disconnected.", L"Disconnect the client!", MB_OK);
	}
	else {
		std::string ReturnString = std::string(ReturnValue->Buffer, ReturnValue->BytesReceived);
		MessageBox(NULL, UTF8ToUTF16(ReturnString.c_str()).c_str(), (std::to_wstring(ReturnValue->BytesReceived) + L" bytes returned").c_str(), MB_OK);
	}
	delete NewBuffer;
}

ManipulationBuffer * PluginBase::ProcessDownstreamData(ManipulationBuffer * InBuffer)
{
	return ProcessDownstreamDataInternal(InBuffer);
}

void PluginBase::ProcessDownstreamDataCmd(HINSTANCE hinst, LPSTR InBuffer, int nCmdShow)
{
	std::string InString = std::string(InBuffer);
	ManipulationBuffer *NewBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
	if (NewBuffer == NULL) {
		MessageBox(NULL, L"Error: Could not allocate manipulation buffer!", L"Allocation error", MB_OK | MB_ICONERROR);
		return;
	}
	memset(NewBuffer, 0, sizeof(NewBuffer));
	NewBuffer->BytesReceived = InString.length();
	NewBuffer->BufferSize = InString.length();
	memcpy(NewBuffer->Buffer, InString.c_str(), InString.length());
	ManipulationBuffer *ReturnValue = ProcessDownstreamDataInternal(NewBuffer);
	if (ReturnValue == NULL) {
		MessageBox(NULL, L"The client is to be disconnected.", L"Disconnect the client!", MB_OK);
	}
	else {
		std::string ReturnString = std::string(ReturnValue->Buffer, ReturnValue->BytesReceived);
		MessageBox(NULL, UTF8ToUTF16(ReturnString.c_str()).c_str(), (std::to_wstring(ReturnValue->BytesReceived) + L" bytes returned").c_str(), MB_OK);
	}
	delete NewBuffer;
}

const WCHAR * PluginBase::GetPluginTypeInternal()
{
	return L"DataManipulation";
}

const WCHAR * PluginBase::GetPluginNameInternal()
{
	return L"Basic Data Manipulator";
}

const WCHAR * PluginBase::GetPluginDescriptionInternal()
{
	return L"This plugin manipulates data as it traverses from client to server and server to client.";
}

const WCHAR * PluginBase::GetPluginVersionInternal()
{
	return L"1.0.0";
}

SettingsBase Settings;

ManipulationBuffer *BiggerBuffer = NULL;

ManipulationBuffer * PluginBase::ProcessUpstreamDataInternal(ManipulationBuffer * InBuffer)
{
	if (!Settings.HasLoaded) {
		DoLogEntry(L"FAILED: No settings are loaded");
		return nullptr;
	}
	// Manipulate the data:
	std::string InString = std::string(InBuffer->Buffer, InBuffer->BytesReceived);
	InString = ReplaceAll(InString, "string", "(a replacement)");
	// Return the result:
	if (InString.length() > InBuffer->BufferSize) {
		// Buffer is too small for new string; use a bigger buffer:
		if (BiggerBuffer == NULL) {
			// Allocate a new buffer:
			BiggerBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
			if (BiggerBuffer == NULL)
				return nullptr;
		}
		else if (BiggerBuffer->BufferSize < InString.length()) {
			// We need more room; let us make a bigger buffer:
			delete BiggerBuffer;// Warning: Make sure this buffer is done being used by plugin consumer;
				                // Using a collection of buffers may be recommended;
								// Consider differentiating clients based on IP address (in InBuffer);
			BiggerBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
			if (BiggerBuffer == NULL)
				return nullptr;
		}
		BiggerBuffer->BytesReceived = InString.length();
		memcpy(BiggerBuffer->Buffer, InString.c_str(), InString.length());
		return BiggerBuffer;// Return a pointer to our own buffer;
	}
	else {
		// Buffer provided by plugin consumer is big enough; use it:
		InBuffer->BytesReceived = InString.length();
		memcpy(InBuffer->Buffer, InString.c_str(), InString.length());
		return InBuffer;// Return a pointer to the (now modified) receive buffer;
	}
	// ********************
	return nullptr;
}

ManipulationBuffer * PluginBase::ProcessDownstreamDataInternal(ManipulationBuffer * InBuffer)
{
	if (!Settings.HasLoaded) {
		DoLogEntry(L"FAILED: No settings are loaded");
		return nullptr;
	}
	// Manipulate the data:
	std::string InString = std::string(InBuffer->Buffer, InBuffer->BytesReceived);
	InString = ReplaceAll(InString, "string", "(a replacement)");
	// Return the result:
	if (InString.length() > InBuffer->BufferSize) {
		// Buffer is too small for new string; use a bigger buffer:
		if (BiggerBuffer == NULL) {
			// Allocate a new buffer:
			BiggerBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
			if (BiggerBuffer == NULL)
				return nullptr;
		}
		else if (BiggerBuffer->BufferSize < InString.length()) {
			// We need more room; let us make a bigger buffer:
			delete BiggerBuffer;// Warning: Make sure this buffer is done being used by plugin consumer;
								// Using a collection of buffers may be recommended;
								// Consider differentiating clients based on IP address (in InBuffer);
			BiggerBuffer = (ManipulationBuffer *)malloc(sizeof(ManipulationBuffer) + InString.length());
			if (BiggerBuffer == NULL)
				return nullptr;
		}
		BiggerBuffer->BytesReceived = InString.length();
		memcpy(BiggerBuffer->Buffer, InString.c_str(), InString.length());
		return BiggerBuffer;// Return a pointer to our own buffer;
	}
	else {
		// Buffer provided by plugin consumer is big enough; use it:
		InBuffer->BytesReceived = InString.length();
		memcpy(InBuffer->Buffer, InString.c_str(), InString.length());
		return InBuffer;// Return a pointer to the (now modified) receive buffer;
	}
	// ********************
	return nullptr;
}
