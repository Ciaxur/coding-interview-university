/*
  Facade Design Pattern basically simplifies a requirement (Converting a Video)
    by integrating other complex/simple but specific Classes in order
    to construct a straight-forward output
*/
#include <string>
#include <algorithm>
#include <fmt/format-inl.h>

// 3RD PARTY CLASSES/FRAMEWORK
class VideoFile {
private:
  char *data;     // "Compiled Data"
  
public:
  VideoFile(std::string filePath) {
    fmt::print("Parsing Video Data...\n");
    data = new char[255];
  }
  ~VideoFile() {
    delete[] data;
  }

  void convertToMp4() {
    fmt::print("Successfuly Converted to Mp4!\n");
  }
};

class OggCompressionCodec {
public:
  static void compress(const char *audioData) {
    fmt::print("Compressed Audio to OGG.\n");
  }
};

class AudioFile {
private:
  char *data;     // "Compiled Data"
  
public:
  AudioFile(std::string filePath) {
    fmt::print("Parsing Audio Data...\n");
    data = new char[255];
  }
  ~AudioFile() {
    delete[] data;
  }

  void convertToOgg() {
    OggCompressionCodec::compress(data);
    fmt::print("Converted Audio to Ogg.\n");
  }
};



// FACADE Object
class VideoConvertion {
public:
  static void convert(std::string filePath, std::string format) {
    // Lowercase the format parameter
    std::string _format{format};
    std::transform(format.begin(), format.end(), _format.begin(), [](unsigned const char c) { return std::tolower(c); });
    
    if (_format == "mp4") {
      fmt::print("Converting to mp4...\n");
      
      // Convert Video
      VideoFile video{filePath};
      video.convertToMp4();

      // Convert Audio
      AudioFile audio{filePath};
      audio.convertToOgg();
    } else {
      fmt::print("Unknown Format '{}'!\n", _format);
    }
    
  }
};