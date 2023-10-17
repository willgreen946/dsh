# A script for autoformatting C and C++ code with clang-format
touch copy && clang-format15 $1 > copy && mkdir -p backup && cp copy backup/$1 && rm $1 && mv copy $1
