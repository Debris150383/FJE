# FJE
a json file visualized command line interface tool

# Installation
```bash
git clone --recurse-submodules https://github.com/Debris150383/FJE.git
# external/json has a .git directory, remove it
cd FJE
rm -rf .git
```

# Usage
1. 修改src/main.cpp中的 icon_file_path 为 icon_config.json 的绝对路径！否则请确保运行FJE时icon_config.json在当前路径 
```bash
mkdir build
cd build
cmake ..
make
```
Usage: FJE [--help] [--version] [-f VAR] [--style VAR] [--icon VAR] [--output VAR]

Optional arguments:
  -h, --help     shows help message and exits  
  -v, --version  prints version information and exits 
  -f             json file to be parsed 
  -s, --style    Choose an icon style: rectangle or tree [nargs=0..1] [default: "tree"]
  -i, --icon     Choose an icon from the following pokerface star [nargs=0..1] [default: "star"]
  -o, --output   Output to a file [nargs=0..1] [default: ""]
