#!bin/bash
#Mój skrypt wywołuje się poleceniem bash test.sh prog dir
#Podanie . jako drugi parametr powoduje działanie w bieżącym katalogu

#sprawdzam czy została podana poprawna ilość parametrów
if [ "$#" -ne 2 ] ; then
  echo -e "Nieprawidłowa liczba parametrów";
  exit 1;
fi;

program=$1;
test=$2;

#testowanie programu dla wszystkich plików testowych
for f in "$test"/*.in; 

#uruchamianie testów bez kontroli Valgrinda
do 
#./"$program" < "$f" >plik.out 2> plik.err;
 echo -n "Test dla pliku: $f ";
if ./"$program" < "$f" 2> plik.err | diff - "${f%in}out" &>/dev/null;
then
if cmp -s "${f%in}err" - <plik.err;
then echo "Poprawne działanie programu"; 
else echo "Poprawne wyjście standardowe, błędne wyjście diagnostyczne";
fi;
else echo "Niepoprawne oba wyjścia programu";
fi;
#testowanie programu pod kątem wycieków pamięci pod kontrolą Valgrinda
 echo -n "Test z Valgrindem dla pliku: $f ";
   if valgrind --leak-check=full --error-exitcode=-1 ./"$program" < "$f" 2>/dev/null | diff - "${f%in}out" &>/dev/null;
    then
   if cmp -s "${f%in}err" - <plik.err;
    then echo "Poprawne działanie programu";
   else echo "Poprawne wyjście standardowe, błędne wyjście diagnostyczne";
    fi;
   else echo "Niepoprawne oba wyjścia programu";
 
fi; done

