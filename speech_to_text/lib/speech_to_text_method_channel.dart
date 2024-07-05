import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'speech_to_text_platform_interface.dart';

/// An implementation of [SpeechToTextPlatform] that uses method channels.
class MethodChannelSpeechToText extends SpeechToTextPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('speech_to_text');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
