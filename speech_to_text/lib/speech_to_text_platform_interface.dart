import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'speech_to_text_method_channel.dart';

abstract class SpeechToTextPlatform extends PlatformInterface {
  /// Constructs a SpeechToTextPlatform.
  SpeechToTextPlatform() : super(token: _token);

  static final Object _token = Object();

  static SpeechToTextPlatform _instance = MethodChannelSpeechToText();

  /// The default instance of [SpeechToTextPlatform] to use.
  ///
  /// Defaults to [MethodChannelSpeechToText].
  static SpeechToTextPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [SpeechToTextPlatform] when
  /// they register themselves.
  static set instance(SpeechToTextPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
