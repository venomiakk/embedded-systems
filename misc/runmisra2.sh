#!/bin/bash
OUTPUT_FILE=misra-report2.txt
if [ -z $1 ]
then
	SOURCE_FILE=../main.c
else
	SOURCE_FILE=../$1
fi
echo Source file: $SOURCE_FILE

# Uruchom cppcheck i zapisz wyniki do pliku
cppcheck --addon=misra --output-file=$OUTPUT_FILE --suppress=*:../lwipopts.h $SOURCE_FILE 

# Poczekaj chwilę, aby upewnić się, że cppcheck skończył pisać do pliku
sleep 1

# Wczytaj zawartość pliku do zmiennej, usuń znaki sterujące i zapisz z powrotem do pliku
file_content=$(cat misra-report2.txt)
clean_content=$(echo "$file_content" | sed 's/\x1b\[[0-9;]*m//g')

# Zamień tekst "use --rule-texts=<file> to get proper output" na odpowiadającą regułę z pliku rules.txt
# while read -r rule; do
#     rule_id=$(echo "$rule" | cut -d' ' -f1)
# 	echo "Rule $rule_id"
#     rule_text=$(echo "$rule" | cut -d' ' -f2-)
# 	echo "Text: $rule_text"
#     clean_content=$(echo "$clean_content" | sed "s|use --rule-texts=<file> to get proper output|$rule_text|g")
# done < rules.txt


echo "$clean_content" > misra-report2.txt

# Wyszukaj linie zawierające "misra violation", wytnij część z numerem reguły,
# posortuj i zlicz wystąpienia każdej reguły, a następnie zapisz wyniki do pliku
echo -e "\nSummary of MISRA violations:" >> misra-report2.txt
grep "misra violation" misra-report2.txt | cut -d'[' -f2 | cut -d']' -f1 | sort | uniq -c >> misra-report2.txt

cat misra-report2.txt