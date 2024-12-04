#include <LittleFS.h>
#include <string>
#include <WString.h>

class NeMarker {
public:
    NeMarker(){
      if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed");
      }
    }

    template<typename... Args>
    String getHTML(const String url, Args... args) {
      std::string html = readFile("/" + url).c_str();
      std::string key = "%content";
      for (String item : {args...}) {
        int indexFirst = html.find(key);
        html.replace(indexFirst, key.length(), item.c_str());
      }

      return html.data();
    }

private:
  String readFile(const String &fileName) {
    File file = LittleFS.open(fileName, "r");
    if (!file) {
      Serial.println("File not found");
      return "<h1>404</h1><br/><h3>Page not found</h3>";
    }
    String content;
    while (file.available()) {
      content = file.readString();
    }

    file.close();
    return content;
  }
};