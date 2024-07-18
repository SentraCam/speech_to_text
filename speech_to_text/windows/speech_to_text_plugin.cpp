#include "speech_to_text_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <string>

#include <memory>
#include <sstream>
#include "sapi_helper.h"

namespace speech_to_text {

// static
void SpeechToTextPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "plugin.csdcorp.com/speech_to_text",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<SpeechToTextPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

SpeechToTextPlugin::SpeechToTextPlugin() {}

SpeechToTextPlugin::~SpeechToTextPlugin() {}

void SpeechToTextPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  SAPIHelper sapiHandler = SAPIHelper::SAPIHelper();
  const std::string methodName = method_call.method_name();
  std::cout << "Follow this command: " << methodName;
  if (methodName.compare(SpeechToTextPlugin::hasPermissionMethod) == 0) {
   result->NotImplemented();
  } 
  else if (methodName.compare(SpeechToTextPlugin::initializeMethod) == 0) {
  HRESULT response = sapiHandler.InitializeSAPIObjs();
    if (response == S_OK){
      result->Success();
    }
    else {
      result->Error("Failed to initialize", "Could not initialize speech recognition");
    }
     

  } 
  else if (methodName.compare(SpeechToTextPlugin::listenMethod) == 0) {
   result->NotImplemented();
  } 
  else if (methodName.compare(SpeechToTextPlugin::stopMethod) == 0){
    result->NotImplemented();
  }
   else if (methodName.compare(SpeechToTextPlugin::cancelMethod) == 0){
    result->NotImplemented();
  }
   else if (methodName.compare(SpeechToTextPlugin::localesMethod) == 0){
    result->NotImplemented();
  }
  else {
    result->NotImplemented();
  }
}

}  // namespace speech_to_text
