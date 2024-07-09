#ifndef FLUTTER_PLUGIN_SPEECH_TO_TEXT_PLUGIN_H_
#define FLUTTER_PLUGIN_SPEECH_TO_TEXT_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <string>

#include <memory>
#include "sapi.h"


namespace speech_to_text {

class SpeechToTextPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  SpeechToTextPlugin();

  virtual ~SpeechToTextPlugin();

  // Disallow copy and assign.
  SpeechToTextPlugin(const SpeechToTextPlugin&) = delete;
  SpeechToTextPlugin& operator=(const SpeechToTextPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

    const std::string hasPermissionMethod = "has_permission";
    const std::string initializeMethod = "initialize";
    const std::string listenMethod = "listen";
    const std::string stopMethod = "stop";
    const std::string cancelMethod = "cancel";
    const std::string localesMethod = "locales";
    const std::string textRecognitionMethod = "textRecognition";
    const std::string notifyErrorMethod = "notifyError";
    const std::string notifyStatusMethod = "notifyStatus";
    const std::string soundLevelChangeMethod = "soundLevelChange";
    const std::string listeningStatus = "listening";
    const std::string notListeningStatus = "notListening";
    const std::string doneStatus = "done";

};

}  // namespace speech_to_text

#endif  // FLUTTER_PLUGIN_SPEECH_TO_TEXT_PLUGIN_H_
