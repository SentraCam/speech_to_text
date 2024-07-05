#include "include/speech_to_text/speech_to_text_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "speech_to_text_plugin.h"

void SpeechToTextPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  speech_to_text::SpeechToTextPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
