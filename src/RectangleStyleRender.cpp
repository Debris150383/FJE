#include <RectangleStyleRender.hpp>

void RectangleStyleRender::render_line(std::string key, std::string val,
                                       unsigned level, bool isLast) {
  std::wstring line = L"";
  for (unsigned i = 1; i < level; i++) {
    line += L"│  ";
  }
  line += L"├─ ";
  std::string content = val == "" ? key : key + ": " + val;
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  line += converter.from_bytes(content);
  lines.push_back(line);
  if (line.length() > maxLineLength) {
    maxLineLength = line.length();
  }
}

void RectangleStyleRender::render_content() {
    for (size_t i = 0; i < lines.size(); ++i) {
        auto& line = lines[i];

        if (i == 0) {
            line[0] = L'┌';
        }

        if (i == lines.size() - 1) {
            line[0] = L'└';
            std::replace(line.begin(), line.end(), L'├', L'└');
        }

        line.append(maxLineLength + 10 - line.length(), L'-');

        if (i == 0) {
            line += L'┐';
        } else if (i == lines.size() - 1) {
            line += L'┘';
        } else {
            line += L'┤';
        }
    }
    for (auto& line : lines) {
        rendered_content += line + L"\n";
    }  
}