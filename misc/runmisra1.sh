#!/bin/bash

# Określ docelowy katalog dla plików .dump
TARGET_DIR="dumps"
SOURCE_DIR=".."
MISRA_PY_PATH="/home/pico/Desktop/cppcheck-main/addons/misra.py"
REPORT_FILE="misra-report1.txt"

# Stwórz katalog docelowy, jeśli nie istnieje
mkdir -p "$TARGET_DIR"

# Pliki źródłowe do analizy (można użyć wzorca np. *.c dla wszystkich plików .c w katalogu)
if [ -z $1 ]
then
	SOURCE_FILES="$SOURCE_DIR/main.c"
else
	SOURCE_FILES="$SOURCE_DIR/$1"
fi

echo "Script running on: $SOURCE_FILES"

# Uruchom cppcheck z opcją --dump dla każdego pliku źródłowego
for FILE in $SOURCE_FILES; do
    cppcheck -f --dump "$FILE"
done

# Przenieś wszystkie pliki .dump do katalogu docelowego
mv "$SOURCE_DIR"/*.dump "$TARGET_DIR"
mv "$SOURCE_DIR"/*ctu-info "$TARGET_DIR"


python3 "$MISRA_PY_PATH" --rule-texts=rules.txt "$TARGET_DIR"/main.c.dump 2>&1 | tee "$REPORT_FILE"

rm -rf "$TARGET_DIR"/*