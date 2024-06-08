#include "foo.h"

int main()
{
	show_zast();
	double tn = 0; 
	double tk = 2; 
	double Un = 5; 
	double U = 2; 
	double a = 5;
	double b = 0.5;
	double *time, *Uvx, *Uvix;
	int n = 0;
	int ch = 1;
	while(ch>0)
	{
		printf("Выберите пукт меню:\n1 - Контрольный расчет для n точек\n2 - Расчет параметра с заданной точностью ---> ");
		ch = get_valid_int();
		switch(ch)
		{
		case 1:
			printf("Введите количество точек для контрольного расчета: ");
			n = get_valid_int();
			double dt = (tk-tn)/n;
			gen_arrays(&time,&Uvx,&Uvix, tn,tk,Un,U,a,b,dt,n);
			show_arrays(time,Uvx,Uvix,n);
			write_to_file(time,Uvx,Uvix,n);
			printf("Продолжительность импульса = %2.2lf seconds\n", impulse_duration(dt,Uvix,n));
			printf("Длительность заднего фронта импульса = %2.2lf seconds\n", duration_of_back_front_impulse(dt,Uvix,n));
			printf("Момент времени, при корором Uvix понизился до 25 вольт = %2.2lf seconds\n", voltage_point(time,Uvix,n,25));
			printf("Момент времени, при корором Uvix имее максимальное(%5.2lfВ) значение = %2.2lf seconds\n",return_extremum(Uvix,n,1),maximum_point(time,Uvix,n));
			printf("ПОКАЗАТЬ ГРАФИКИ(1/0)? ");
			ch = get_valid_int();
			if(ch!=0)
			{
				system("wxmaxima grathics.wxmx");	
			}
			break;
		case 2: 
			printf("Расчет необходимого количества точек для заданной точночти 0,01....\n");
			n = precision(&time,&Uvx,&Uvix, tn,tk,Un,U,a,b,0.01,40.1);
			printf("Необходимое количество точек для расчета = %d\n", n);
			show_arrays(time,Uvx,Uvix,n);
			write_to_file(time,Uvx,Uvix,n);
			printf("Продолжительность импульса = %2.2lf seconds\n", impulse_duration(dt,Uvix,n));
			printf("Длительность заднего фронта импульса = %2.2lf seconds\n", duration_of_back_front_impulse(dt,Uvix,n));
			printf("Момент времени, при корором Uvix понизился до 25 вольт = %2.2lf seconds\n", voltage_point(time,Uvix,n,25));
			printf("Момент времени, при корором Uvix имее максимальное(%5.2lfВ) значение = %2.2lf seconds\n",return_extremum(Uvix,n,1),maximum_point(time,Uvix,n));
			printf("ПОКАЗАТЬ ГРАФИКИ(1/0)? ");
			ch = get_valid_int();
			if(ch!=0)
			{
				system("wxmaxima grathics.wxmx");	
			}
			break;	
		default: printf("Ошибочный ввод! ");break;	
		}
		printf("ПРОДОЛЖИТЬ?(0- нет)? ");
		ch = get_valid_int();
		if(ch>0)
		{
			free(time);
			free(Uvx);
			free(Uvix);
		}
	}

free(time);
free(Uvx);
free(Uvix);
return 0;
}
