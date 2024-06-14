#include <TreeStyleRender.hpp>

void TreeStyleRender::render_line(std::string key, std::string val,
                                  unsigned level, bool isLast) {
  if (level == 1) indent = isLast ? L"   " : L"│  ";
  std::wstring toindent = L"";
  for (unsigned i = 1; i < level; i++) {
    if (i == 1)
      toindent += indent;
    else
      toindent += L"│  ";
  }
  std::wstring prefix = isLast ? L"└─ " : L"├─ ";
  std::string content = val == "" ? key : key + ": " + val;
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wide_line = toindent + prefix + converter.from_bytes(content) + L"\n";

  append(wide_line);
}