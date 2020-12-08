

es_anio_bisiesto
if(year%400 == 0)
printf("%d is a leap year.n", year);
else if(year%100 == 0)
printf("%d isn't a leap year.n", year);
else if (year%4 == 0)
printf("%d is a leap year.n", year);
else
printf("%d isn't a leap year.n", year);