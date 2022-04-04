int foo (int i);

int foo (int i)
{
	int arr2[10];
	int arr[5];
	int arr3[10];
	fill (arr2);
	fill (arr);
	fill (arr3);
	return arr[i] + arr2[i] + arr3[0];
}

int bar (int *p, int i)
{
	int arr[5];
	fill(arr);
	return arr[i] + p[i];
}


int garr[5];
int *gp;
int a;

int buz (int i)
{
	return a + garr[i] + gp[i];
}