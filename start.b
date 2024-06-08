#!/bin/bash
echo "Вас приветствует программа №1"
echo "Что Вам надо?"
echo "	0 - запустить Си - алгоритм"
echo -n "	1 - открыть элекроннный отчет отчет.doc ? "
read val

if [[ $val -eq 0 ]]; then
	./main.e
elif [[ $val -eq 1 ]]; then
	libreoffice otchet.odt
else 
echo "ОШИБКА! Перезапустите скрипт! "
fi
