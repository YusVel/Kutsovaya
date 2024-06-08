void gen_arrays(double **time,double **Uvx, double **Uvix, double tn, double tk,double Un,double U, double a,double b, double dt, int n)
{
	*time = (double*)(malloc(n*sizeof(double)));
	*Uvx = (double*)(malloc(n*sizeof(double)));
	*Uvix = (double*)(malloc(n*sizeof(double)));
	
	if(*time==NULL&&*Uvx==NULL&&*Uvix==NULL)
	{
		printf("\n***Память не аллоцирована!!!***\n");
	}

	for(int i = 0; i<n; i++) //массив времени
	{
		(*time)[i] = i*dt + tn;
	}

	for(int i = 0; i<n; i++) // массив входного напряжения
	{
		(*Uvx)[i] = Un-U*sin((*time)[i]);
	}


	for(int i = 0; i<n; i++) // массив ВЫХОДНОГО напряжения
	{
		(*Uvix)[i] = a*pow(2.71828284, b*((*Uvx)[i]));
	}	
}



double return_extremum(double * arr, int size, int flag) //вернуть максимальное (flag >0) или минимальное (flag<1) значение из массива
{
	if(flag>0)
	{
		double max = -9999999;
		for(int i = 0; i<size; i++) //массив времени
		{
			if(max<arr[i])
			{
				max = arr[i];
			}
		}	
		return max;	
	}
	else
	{
		double min = 9999999;
		for(int i = 0; i<size; i++) //массив времени
		{
			if(min>arr[i])
			{
				min = arr[i];
			}
		}	
		return min;	
	}
}


double impulse_duration(double dt, double *U, int size) // получение длительности импульса
{
	double Uimp = return_extremum(U,size,0)+0.5*(return_extremum(U,size,1)-return_extremum(U,size,0));
	
	double result = 0;
	for(int i = 0; i<size; i++)
	{
		if(U[i]>=Uimp)
		{
			result +=dt;
		}
	}
	return result;
}


double duration_of_back_front_impulse(double dt, double *U, int size)
{
	double U1  = return_extremum(U,size,0)+0.9*(return_extremum(U,size,1)-return_extremum(U,size,0));
	double U2  = return_extremum(U,size,0)+0.1*(return_extremum(U,size,1)-return_extremum(U,size,0));
	double result = 0;
	for(int i = 0; i<size;i++)
	{
		if(U[i]<U1&&U[i]>U2&&U[i+1]<U[i])
		{
			result+=dt;
		}
	}
	return result;
}


double voltage_point(double *time, double *U,int size, double voltage)
{
	double result = -1;
	for(int i = 0; i<size;i++)
	{
		if(U[i]<=voltage)
		{
			result = time[i];
			break;
		}
	}
	if(result == -1)
	{
		printf("**** Напряжение не достигло %5.2lf В ****\n",voltage);
	}
	return result;
}

double maximum_point(double *time, double *U,int size)
{
	double max = return_extremum(U,size,1);
	double result = -999999;
	for(int i = 0; i<size;i++)
	{
		if(U[i]==max)
		{
			result = time[i];
			break;
		}
	}
	return result;
}

void show_arrays(double *time,double *Uvx, double *Uvix, int n)
{
	printf("time\t|Uvx\t |Uvix\t |\n");
	printf("--------|--------|-------|\n");

	for(int i = 0; i<n; i++) // массив ВЫХОДНОГО напряжения
	{
		printf("%1.2lf \t|%1.2lf \t |%1.2lf  |\n",time[i],Uvx[i],Uvix[i]);
	}

}

int get_valid_int()
{

int num = 0;
int good_read =scanf("%d",&num);
while(good_read!=1||getchar()!=10)
{
printf("INPUT ERROR!!! ENTER int n AGAIN: ");
	
	while (getchar()!=10)
	{	
		good_read = 0;
	}
	good_read = scanf("%d",&num);
}
return num;
}

int write_to_file(double *time,double *Uvx, double *Uvix, int size)
{
	FILE *f1,*f2, *f3;
	
	if((f1 = fopen("Massive_time.txt","w"))==NULL)
	{
		fprintf(stderr,"Error! Can not to write to Massive_time.txt");
		return 1;
	}
	if((f2 = fopen("Massive_Uvx.txt","w"))==NULL)
	{
		fprintf(stderr,"Error! Can not to write to Massive_time.txt");
		return 1;
	}
	if((f3 = fopen("Massive_Uvix.txt","w"))==NULL)
	{
		fprintf(stderr,"Error! Can not to write to Massive_time.txt");
		return 1;
	}
	for(int i = 0;i<size;i++)
	{
		fprintf(f1,"\n%5.3lf",time[i]);
		fprintf(f2,"\n%5.3lf",Uvx[i]);
		fprintf(f3,"\n%5.3lf",Uvix[i]);
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
	return 0;
}

int show_zast()
{
	FILE *f1;
	if((f1=fopen("zast.txt","r"))==NULL)
	{
		fprintf(stderr,"Error! Can not to read zast.txt");
		return 1;
	}
	char ch;
	while(!feof(f1))
	{
		fscanf(f1,"%c",&ch);
		printf("%c",ch);
	}
	fclose(f1);
	
}

int precision(double **time,double **Uvx, double **Uvix, double tn, double tk,double Un,double U, double a,double b, double prec, double parametr )
{
	int n = 10;

	do
	{
		double dt = (tk-tn)/n;
		gen_arrays(time,Uvx,Uvix, tn,tk,Un,U,a,b,dt,n);
		
		for(int i = 0;i<n;i++)
		{
			if((*Uvix)[i]<=parametr)
			{
				if((*Uvix)[i]/parametr<(double)(1.0+prec)&&(*Uvix)[i]/parametr>(double)(1.0-prec))
				{
					return n;
				}
				else
				{
					n*=2; 
					free(*time);
					free(*Uvx);
					free(*Uvix);
					break;
				}
			}
		}
		
	}while(1);
	
}

